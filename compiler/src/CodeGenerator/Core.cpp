#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "Debug.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"

#include <functional>
#include <iostream>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Verifier.h>
#include <llvm/MC/TargetRegistry.h>
#include <optional>
#if __has_include(<llvm/Support/Host.h>)
#include <llvm/Support/Host.h>
#elif __has_include(<llvm/TargetParser/Host.h>)
#include <llvm/TargetParser/Host.h>
#else
#error "Neither llvm/Support/Host.h nor llvm/TargetParser/Host.h is available."
#endif
#include <algorithm>
#include <llvm/Config/llvm-config.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Triple.h>
#include <stdexcept>
#include <unordered_map>
#include <vector>

using namespace llvm;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;

CodeGenerator::CodeGenerator()
    : builder(context),
      module(std::make_unique<Module>("main_module", context)) {
  std::string targetTriple = llvm::sys::getDefaultTargetTriple();
  llvm::Triple triple(targetTriple);
#if LLVM_VERSION_MAJOR >= 20
  module->setTargetTriple(triple);
#else
  module->setTargetTriple(triple.getTriple());
#endif

  std::string error;
  const llvm::Target *target =
      llvm::TargetRegistry::lookupTarget(triple.getTriple(), error);
  if (!target) {
    throw runtime_error("CodeGenerator Error: Unable to lookup target for "
                        "triple '" +
                        targetTriple + "': " + error);
  }

  std::string cpu = "generic";
  std::string features = "";
  llvm::TargetOptions opt;
  std::optional<llvm::Reloc::Model> relocModel;

#if LLVM_VERSION_MAJOR >= 20
  std::unique_ptr<llvm::TargetMachine> targetMachine(
      target->createTargetMachine(triple, cpu, features, opt, relocModel));
#else
  std::unique_ptr<llvm::TargetMachine> targetMachine(
      target->createTargetMachine(triple.getTriple(), cpu, features, opt,
                                  relocModel));
#endif
  if (!targetMachine) {
    throw runtime_error("CodeGenerator Error: Failed to create target machine "
                        "for triple '" +
                        targetTriple + "'.");
  }

  module->setDataLayout(targetMachine->createDataLayout());
  // NOTE: Opaque pointers are enabled by default in LLVM 15+.
  // To call getElementType(), your LLVM must disable opaque pointers.
}

void CodeGenerator::registerUnionType(
    const std::shared_ptr<UnionDeclaration> &unionDecl) {
  if (!unionDecl || !unionDecl->tag.has_value())
    return;

  const DataLayout &DL = module->getDataLayout();
  uint64_t maxSize = 0;

  for (const auto &member : unionDecl->members) {
    Type *memberType = getLLVMType(member->type);
    for (auto it = member->dimensions.rbegin(); it != member->dimensions.rend();
         ++it) {
      auto lit = std::dynamic_pointer_cast<Literal>(*it);
      if (!lit)
        throw runtime_error("CodeGenerator Error: Array dimension must be a "
                            "constant integer.");
      uint64_t arraySize = static_cast<uint64_t>(lit->intValue);
      memberType = ArrayType::get(memberType, arraySize);
    }
    maxSize = std::max<uint64_t>(maxSize, DL.getTypeAllocSize(memberType));
  }

  if (maxSize == 0)
    maxSize = 1;

  ArrayType *storageType = ArrayType::get(Type::getInt8Ty(context), maxSize);
  StructType *unionType = StructType::create(context, unionDecl->tag.value());
  unionType->setBody({storageType}, /*isPacked=*/false);
  declaredTypes[unionDecl->tag.value()] = unionType;
}

void CodeGenerator::registerStructType(
    const std::shared_ptr<StructDeclaration> &structDecl) {
  if (!structDecl || !structDecl->tag.has_value())
    return;

  for (const auto &nestedUnion : structDecl->nestedUnions) {
    registerUnionType(nestedUnion);
  }
  for (const auto &nestedStruct : structDecl->nestedStructs) {
    registerStructType(nestedStruct);
  }

  unsigned maxAlign = 0;
  std::vector<Type *> memberTypes;
  for (const auto &member : structDecl->members) {
    Type *memberType = getLLVMType(member->type);
    if (!member->dimensions.empty()) {
      for (auto it = member->dimensions.rbegin();
           it != member->dimensions.rend(); ++it) {
        auto lit = std::dynamic_pointer_cast<Literal>(*it);
        if (!lit)
          throw runtime_error("CodeGenerator Error: Array dimension must be a "
                              "constant integer.");
        uint64_t arraySize = static_cast<uint64_t>(lit->intValue);
        memberType = ArrayType::get(memberType, arraySize);
      }
    } else if (member->hasEmptyArrayDimension) {
      // Flexible array member: represent as a zero-length array so the field
      // points at the start of the trailing storage.
      memberType = ArrayType::get(memberType, 0);
    }
    if (member->alignment.has_value())
      maxAlign = std::max<unsigned>(maxAlign, member->alignment.value());
    memberTypes.push_back(memberType);
  }

  bool isPacked = structDecl->isPacked;
  StructType *structType = StructType::create(context, structDecl->tag.value());
  structType->setBody(memberTypes, /*isPacked=*/isPacked);

  declaredTypes[structDecl->tag.value()] = structType;
  if (isPacked)
    maxAlign = 1;
  if (!isPacked && maxAlign == 0) {
    for (auto *ty : memberTypes) {
      maxAlign = std::max<unsigned>(
          maxAlign, module->getDataLayout().getABITypeAlign(ty).value());
    }
  }
  if (maxAlign > 0)
    declaredAlignments["struct " + structDecl->tag.value()] = maxAlign;
}

std::unique_ptr<Module>
CodeGenerator::generateCode(const shared_ptr<Program> &program) {
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] generateCode: Processing "
              << program->declarations.size() << " declarations\n";

  std::function<Constant *(const ExpressionPtr &, llvm::Type *)>
      buildConstantFromExpr;

  struct ConstAddress {
    Constant *ptr;
    llvm::Type *pointee;
  };
  std::function<std::optional<ConstAddress>(const ExpressionPtr &)>
      buildConstantAddress;

  buildConstantAddress =
      [&](const ExpressionPtr &addrExpr) -> std::optional<ConstAddress> {
    if (auto ident = std::dynamic_pointer_cast<Identifier>(addrExpr)) {
      if (auto *gv = module->getNamedGlobal(ident->name))
        return ConstAddress{gv, gv->getValueType()};
      if (auto *fn = module->getFunction(ident->name))
        return ConstAddress{fn, fn->getFunctionType()};
      return std::nullopt;
    }
    if (auto arrayAcc = std::dynamic_pointer_cast<ArrayAccess>(addrExpr)) {
      auto baseAddr = buildConstantAddress(arrayAcc->base);
      if (!baseAddr.has_value())
        return std::nullopt;
      auto idxLit = std::dynamic_pointer_cast<Literal>(arrayAcc->index);
      if (!idxLit)
        return std::nullopt;
      llvm::Type *pointeeTy = baseAddr->pointee;
      if (!pointeeTy)
        return std::nullopt;
      Constant *zero = ConstantInt::get(Type::getInt32Ty(context), 0);
      Constant *idxConst =
          ConstantInt::get(Type::getInt32Ty(context), idxLit->intValue);
      if (pointeeTy->isArrayTy()) {
        std::vector<Constant *> indices = {zero, idxConst};
        auto *arrTy = cast<ArrayType>(pointeeTy);
        Constant *gep = ConstantExpr::getInBoundsGetElementPtr(
            pointeeTy, baseAddr->ptr, indices);
        return ConstAddress{gep, arrTy->getElementType()};
      }
      std::vector<Constant *> indices = {idxConst};
      Constant *gep = ConstantExpr::getInBoundsGetElementPtr(
          pointeeTy, baseAddr->ptr, indices);
      return ConstAddress{gep, pointeeTy};
    }
    if (auto memberAcc = std::dynamic_pointer_cast<MemberAccess>(addrExpr)) {
      auto baseAddr = buildConstantAddress(memberAcc->base);
      if (!baseAddr.has_value())
        return std::nullopt;
      llvm::Type *pointeeTy = baseAddr->pointee;
      auto *structTy = llvm::dyn_cast_or_null<StructType>(pointeeTy);
      if (!structTy)
        return std::nullopt;
      std::string baseTypeName = "";
      for (auto &entry : declaredTypes) {
        if (entry.second == structTy) {
          baseTypeName = normalizeTag(entry.first);
          break;
        }
      }
      if (baseTypeName.empty())
        return std::nullopt;
      MemberInfo *info = getMemberInfo(baseTypeName, memberAcc->member);
      if (!info)
        return std::nullopt;
      Constant *zero = ConstantInt::get(Type::getInt32Ty(context), 0);
      Constant *fieldIdx =
          ConstantInt::get(Type::getInt32Ty(context), info->index);
      std::vector<Constant *> indices = {zero, fieldIdx};
      Constant *gep = ConstantExpr::getInBoundsGetElementPtr(
          pointeeTy, baseAddr->ptr, indices);
      return ConstAddress{gep, structTy->getElementType(info->index)};
    }
    return std::nullopt;
  };

  buildConstantFromExpr = [&](const ExpressionPtr &expr,
                              llvm::Type *expected) -> Constant * {
    static int strLiteralCounter = 0;
    if (!expected)
      return nullptr;
    if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
      if (lit->type == Literal::LiteralType::String) {
        auto strConst =
            ConstantDataArray::getString(context, lit->stringValue, true);
        if (auto *arrTy = dyn_cast<ArrayType>(expected)) {
          if (!arrTy->getElementType()->isIntegerTy(8))
            return nullptr;
          std::vector<Constant *> chars;
          chars.reserve(arrTy->getNumElements());
          for (uint64_t i = 0; i < arrTy->getNumElements(); ++i) {
            char c = (i < lit->stringValue.size()) ? lit->stringValue[i] : '\0';
            if (i + 1 == arrTy->getNumElements())
              c = '\0';
            chars.push_back(ConstantInt::get(Type::getInt8Ty(context), c));
          }
          return ConstantArray::get(arrTy, chars);
        }
        if (expected->isPointerTy()) {
          auto name = "strlit." + std::to_string(strLiteralCounter++);
          auto *gStr =
              new GlobalVariable(*module, strConst->getType(), true,
                                 GlobalValue::PrivateLinkage, strConst, name);
          return ConstantExpr::getBitCast(gStr, expected);
        }
        return nullptr;
      }
      if (expected->isIntegerTy()) {
        int64_t v = 0;
        if (lit->type == Literal::LiteralType::Int)
          v = lit->intValue;
        else if (lit->type == Literal::LiteralType::Bool)
          v = lit->boolValue ? 1 : 0;
        else if (lit->type == Literal::LiteralType::Char)
          v = lit->charValue;
        return ConstantInt::get(expected, v);
      } else if (expected->isFloatingPointTy()) {
        if (lit->type == Literal::LiteralType::Float)
          return ConstantFP::get(expected, lit->floatValue);
        if (lit->type == Literal::LiteralType::Double)
          return ConstantFP::get(expected, lit->doubleValue);
      }
    }
    if (expected->isPointerTy()) {
      if (auto unary = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
        if (unary->op == "&") {
          if (auto addr = buildConstantAddress(unary->operand)) {
            Constant *ptr = addr->ptr;
            if (ptr->getType() != expected)
              ptr = ConstantExpr::getBitCast(ptr, expected);
            return ptr;
          }
        }
      }
      if (auto ident = std::dynamic_pointer_cast<Identifier>(expr)) {
        if (auto addr = buildConstantAddress(ident)) {
          Constant *ptr = addr->ptr;
          if (ptr->getType() != expected)
            ptr = ConstantExpr::getBitCast(ptr, expected);
          return ptr;
        }
      }
    }
    if (auto list = std::dynamic_pointer_cast<InitializerList>(expr)) {
      if (auto *arrTy = dyn_cast<ArrayType>(expected)) {
        std::vector<Constant *> values;
        llvm::Type *elemTy = arrTy->getElementType();
        uint64_t count = arrTy->getNumElements();
        for (uint64_t i = 0; i < count; ++i) {
          Constant *c = nullptr;
          if (i < list->elements.size())
            c = buildConstantFromExpr(list->elements[i], elemTy);
          if (!c)
            c = Constant::getNullValue(elemTy);
          values.push_back(c);
        }
        return ConstantArray::get(arrTy, values);
      } else if (auto *structTy = dyn_cast<StructType>(expected)) {
        std::vector<Constant *> fields(structTy->getNumElements(), nullptr);
        std::string tag;
        for (auto &entry : declaredTypes) {
          if (entry.second == structTy && getAggregateTypeInfo(entry.first)) {
            tag = normalizeTag(entry.first);
            break;
          }
        }
        if (tag.empty()) {
          for (auto &entry : declaredTypes) {
            if (entry.second == structTy) {
              tag = normalizeTag(entry.first);
              break;
            }
          }
        }
        auto resolveIndex = [&](size_t listIndex) -> unsigned {
          if (list->designators.size() > listIndex &&
              list->designators[listIndex].has_value() && !tag.empty()) {
            if (auto *info =
                    getMemberInfo(tag, list->designators[listIndex].value())) {
              return static_cast<unsigned>(info->index);
            }
          }
          return static_cast<unsigned>(listIndex);
        };
        for (size_t i = 0; i < list->elements.size(); ++i) {
          unsigned targetIndex = resolveIndex(i);
          if (targetIndex >= structTy->getNumElements())
            continue;
          Constant *c = buildConstantFromExpr(
              list->elements[i], structTy->getElementType(targetIndex));
          if (!c)
            c = Constant::getNullValue(structTy->getElementType(targetIndex));
          fields[targetIndex] = c;
        }
        for (unsigned i = 0; i < structTy->getNumElements(); ++i) {
          if (!fields[i])
            fields[i] = Constant::getNullValue(structTy->getElementType(i));
        }
        return ConstantStruct::get(structTy, fields);
      }
    }
    if (expected->isPointerTy())
      return ConstantPointerNull::get(cast<PointerType>(expected));
    if (expected->isIntegerTy())
      return ConstantInt::get(expected, 0);
    if (expected->isFloatingPointTy())
      return ConstantFP::get(expected, 0.0);
    return nullptr;
  };

  // Process global declarations first.
  for (const auto &decl : program->declarations) {
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] generateCode: Processing declaration\n";

    if (auto varDecl = std::dynamic_pointer_cast<VariableDeclaration>(decl)) {
      if (educcDebugEnabled())
        std::cerr << "[DEBUG] generateCode: Variable declaration: "
                  << varDecl->name << "\n";
      if (varDecl->inlineStructDecl)
        registerStructType(varDecl->inlineStructDecl);
      if (varDecl->inlineUnionDecl)
        registerUnionType(varDecl->inlineUnionDecl);
      // e.g. int x;   or   int array[10];
      std::string typeWithDimensions = varDecl->type;
      llvm::Type *varType = getLLVMType(varDecl->type);
      // If there are array dimensions, wrap them in an ArrayType
      if (!varDecl->dimensions.empty()) {
        for (auto it = varDecl->dimensions.rbegin();
             it != varDecl->dimensions.rend(); ++it) {
          llvm::Value *dimVal = generateExpression(*it);
          ConstantInt *constDim = dyn_cast<ConstantInt>(dimVal);
          if (!constDim)
            throw runtime_error("CodeGenerator Error: Array dimension must be "
                                "a constant integer.");
          uint64_t arraySize = constDim->getZExtValue();
          varType = ArrayType::get(varType, arraySize);
          typeWithDimensions += "[" + std::to_string(arraySize) + "]";
        }
      }
      // Create the global
      GlobalVariable *gVar = new GlobalVariable(
          *module, varType, /*isConstant=*/false, GlobalValue::ExternalLinkage,
          nullptr, varDecl->name);
      declaredTypes[varDecl->name] = varType;
      declaredTypeStrings[varDecl->name] = typeWithDimensions;
      auto normalizeAlignVal = [](unsigned v) {
        const unsigned MAX_ALIGN = 1u << 20;
        if (v == 0 || v > MAX_ALIGN)
          return 0u;
        if ((v & (v - 1)) == 0)
          return v;
        unsigned a = 1;
        while (a < v && a < MAX_ALIGN)
          a <<= 1;
        if (a > MAX_ALIGN)
          return 0u;
        return a;
      };
      unsigned align = 0;
      if (varDecl->alignment.has_value())
        align = varDecl->alignment.value();
      auto itAlign = declaredAlignments.find(varDecl->type);
      if (itAlign != declaredAlignments.end())
        align = std::max<unsigned>(align, itAlign->second);
      align = normalizeAlignVal(align);
      if (align > 0)
        gVar->setAlignment(llvm::Align(align));

      // If it has an initializer
      if (varDecl->initializer) {
        Constant *initVal =
            buildConstantFromExpr(varDecl->initializer.value(), varType);
        if (!initVal)
          throw runtime_error("CodeGenerator Error: Unsupported global "
                              "initializer.");
        gVar->setInitializer(initVal);
      } else {
        // no initializer => zero init
        Constant *defaultVal = Constant::getNullValue(varType);
        gVar->setInitializer(defaultVal);
      }
    }

    else if (auto multiDecl =
                 std::dynamic_pointer_cast<MultiVariableDeclaration>(decl)) {
      // e.g. int x=1, y=2, z[10];
      for (const auto &singleDecl : multiDecl->declarations) {
        if (singleDecl->inlineStructDecl)
          registerStructType(singleDecl->inlineStructDecl);
        if (singleDecl->inlineUnionDecl)
          registerUnionType(singleDecl->inlineUnionDecl);
        std::string typeWithDimensions = singleDecl->type;
        llvm::Type *varType = getLLVMType(singleDecl->type);
        if (!singleDecl->dimensions.empty()) {
          for (auto it = singleDecl->dimensions.rbegin();
               it != singleDecl->dimensions.rend(); ++it) {
            llvm::Value *dimVal = generateExpression(*it);
            ConstantInt *constDim = dyn_cast<ConstantInt>(dimVal);
            if (!constDim)
              throw runtime_error("CodeGenerator Error: Array dimension must "
                                  "be a constant integer.");
            uint64_t arraySize = constDim->getZExtValue();
            varType = ArrayType::get(varType, arraySize);
            typeWithDimensions += "[" + std::to_string(arraySize) + "]";
          }
        }
        GlobalVariable *gVar = new GlobalVariable(*module, varType, false,
                                                  GlobalValue::ExternalLinkage,
                                                  nullptr, singleDecl->name);
        declaredTypes[singleDecl->name] = varType;
        declaredTypeStrings[singleDecl->name] = typeWithDimensions;

        if (singleDecl->initializer) {
          Constant *initVal =
              buildConstantFromExpr(singleDecl->initializer.value(), varType);
          if (!initVal)
            throw runtime_error("CodeGenerator Error: Unsupported global "
                                "initializer.");
          gVar->setInitializer(initVal);
        } else {
          // no initializer => zero
          Constant *defaultVal = Constant::getNullValue(varType);
          gVar->setInitializer(defaultVal);
        }
      }
    }

    else if (auto enumDecl = std::dynamic_pointer_cast<EnumDeclaration>(decl)) {
      for (size_t i = 0; i < enumDecl->enumerators.size(); ++i) {
        string enumName = enumDecl->enumerators[i].first;
        int value = enumDecl->enumeratorValues[i];
        Constant *initVal = ConstantInt::get(Type::getInt32Ty(context), value);
        new GlobalVariable(*module, Type::getInt32Ty(context), true,
                           GlobalValue::ExternalLinkage, initVal, enumName);
      }
    } else if (auto unionDecl =
                   std::dynamic_pointer_cast<UnionDeclaration>(decl)) {
      registerUnionType(unionDecl);
    } else if (auto structDecl =
                   std::dynamic_pointer_cast<StructDeclaration>(decl)) {
      registerStructType(structDecl);
    } else if (auto typedefDecl =
                   std::dynamic_pointer_cast<TypedefDeclaration>(decl)) {
      if (typedefDecl->structDecl) {
        registerStructType(typedefDecl->structDecl);
      } else if (typedefDecl->unionDecl) {
        registerUnionType(typedefDecl->unionDecl);
      }
    } else {
      if (educcDebugEnabled())
        std::cerr << "[DEBUG] generateCode: Unknown declaration type\n";
    }
  }

  // 2) Then handle function declarations
  for (const auto &decl : program->declarations) {
    if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclaration>(decl)) {
      if (educcDebugEnabled())
        std::cerr << "[DEBUG] generateCode: Function declaration: "
                  << funcDecl->name << "\n";
      generateFunction(funcDecl);
    }
  }

  // verify
  if (verifyModule(*module, &errs()))
    throw runtime_error("CodeGenerator Error: Module verification failed.");
  return std::move(module);
}
