#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "CodeGenerator/Helpers.hpp"
#include "Debug.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/Alignment.h>
#include <llvm/Support/raw_ostream.h>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace llvm;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

namespace {
llvm::Value *getUnionMemberPointer(CodeGenerator &CG, llvm::StructType *unionTy,
                                   llvm::Value *unionPtr,
                                   const std::string &unionTag,
                                   const std::string &memberName) {
  MemberInfo *memberInfo = getMemberInfo(unionTag, memberName);
  if (!memberInfo) {
    throw runtime_error("Union type '" + unionTag +
                        "' does not contain member '" + memberName + "'.");
  }
  llvm::Type *memberType = CG.getLLVMType(memberInfo->type);
  llvm::Value *storagePtr =
      CG.builder.CreateStructGEP(unionTy, unionPtr, 0, memberName + ".storage");
  return CG.builder.CreateBitCast(
      storagePtr, llvm::PointerType::get(memberType, 0), memberName + ".ptr");
}
} // namespace

//
// Local Scope Management
//
void CodeGenerator::pushLocalScope() {
  localVarStack.push_back(unordered_map<string, Value *>());
  declaredVarStack.push_back(unordered_set<string>());
}

void CodeGenerator::popLocalScope() {
  if (localVarStack.empty() || declaredVarStack.empty())
    throw runtime_error("CodeGenerator Error: No local scope to pop.");
  for (const auto &name : declaredVarStack.back()) {
    auto typeIt = typeShadowStack.find(name);
    if (typeIt != typeShadowStack.end() && !typeIt->second.empty()) {
      declaredTypes[name] = typeIt->second.back();
      typeIt->second.pop_back();
      if (typeIt->second.empty())
        typeShadowStack.erase(typeIt);
    } else {
      declaredTypes.erase(name);
    }
    auto strIt = typeStringShadowStack.find(name);
    if (strIt != typeStringShadowStack.end() && !strIt->second.empty()) {
      declaredTypeStrings[name] = strIt->second.back();
      strIt->second.pop_back();
      if (strIt->second.empty())
        typeStringShadowStack.erase(strIt);
    } else {
      declaredTypeStrings.erase(name);
    }
    dynamicArrayDimensions.erase(name);
    dynamicArrayVars.erase(name);
  }
  declaredVarStack.pop_back();
  localVarStack.pop_back();
}

llvm::Value *CodeGenerator::lookupLocalVar(const string &name) {
  for (auto it = localVarStack.rbegin(); it != localVarStack.rend(); ++it) {
    auto found = it->find(name);
    if (found != it->end())
      return found->second;
  }
  return nullptr;
}

void CodeGenerator::storeInitializerValue(const ExpressionPtr &init,
                                          llvm::Type *type, llvm::Value *ptr) {
  if (auto initList = std::dynamic_pointer_cast<InitializerList>(init)) {
    if (auto *arrTy = llvm::dyn_cast<llvm::ArrayType>(type)) {
      llvm::Type *elemTy = arrTy->getElementType();
      uint64_t count = arrTy->getNumElements();
      for (uint64_t i = 0; i < count; ++i) {
        ExpressionPtr elemInit =
            (i < initList->elements.size()) ? initList->elements[i] : nullptr;
        llvm::Value *elemPtr =
            builder.CreateGEP(type, ptr,
                              {ConstantInt::get(Type::getInt32Ty(context), 0),
                               ConstantInt::get(Type::getInt32Ty(context), i)},
                              "init.gep");
        if (elemInit) {
          storeInitializerValue(elemInit, elemTy, elemPtr);
        } else {
          builder.CreateStore(Constant::getNullValue(elemTy), elemPtr);
        }
      }
      return;
    }
    if (auto *structTy = llvm::dyn_cast<llvm::StructType>(type)) {
      for (size_t i = 0; i < structTy->getNumElements(); ++i) {
        ExpressionPtr fieldInit =
            (i < initList->elements.size()) ? initList->elements[i] : nullptr;
        llvm::Value *fieldPtr =
            builder.CreateStructGEP(structTy, ptr, i, "field.gep");
        llvm::Type *fieldTy = structTy->getElementType(i);
        if (fieldInit) {
          storeInitializerValue(fieldInit, fieldTy, fieldPtr);
        } else {
          builder.CreateStore(Constant::getNullValue(fieldTy), fieldPtr);
        }
      }
      return;
    }
  }

  if (auto lit = std::dynamic_pointer_cast<Literal>(init)) {
    if (lit->type == Literal::LiteralType::String) {
      if (auto *arrTy = llvm::dyn_cast<llvm::ArrayType>(type)) {
        if (arrTy->getElementType()->isIntegerTy(8)) {
          std::string str = lit->stringValue;
          uint64_t arraySize = arrTy->getNumElements();
          for (uint64_t i = 0; i < arraySize; ++i) {
            char c = (i < str.size()) ? str[i] : '\0';
            if (i + 1 == arraySize)
              c = '\0';
            llvm::Value *elemVal =
                llvm::ConstantInt::get(Type::getInt8Ty(context), c);
            std::vector<llvm::Value *> indices = {
                llvm::ConstantInt::get(Type::getInt32Ty(context), 0),
                llvm::ConstantInt::get(Type::getInt32Ty(context), i)};
            llvm::Value *elemPtr =
                builder.CreateGEP(type, ptr, indices, "str.init");
            builder.CreateStore(elemVal, elemPtr);
          }
          return;
        }
      }
    }
  }

  llvm::Value *val = generateExpression(init);
  if (val->getType() != type) {
    if (val->getType()->isFloatingPointTy() && type->isFloatingPointTy()) {
      if (val->getType()->getFPMantissaWidth() > type->getFPMantissaWidth())
        val = builder.CreateFPTrunc(val, type, "fptrunc");
      else
        val = builder.CreateFPExt(val, type, "fpext");
    } else if (val->getType()->isFloatingPointTy() && type->isIntegerTy()) {
      val = builder.CreateFPToSI(val, type, "fptosi");
    } else if (val->getType()->isIntegerTy() && type->isFloatingPointTy()) {
      val = builder.CreateSIToFP(val, type, "sitofp");
    } else if (val->getType()->isIntegerTy() && type->isIntegerTy()) {
      val = builder.CreateIntCast(val, type, false, "intcast");
    } else if (val->getType()->isPointerTy() && type->isPointerTy()) {
      val = builder.CreateBitCast(val, type, "ptrcast");
    }
  }
  builder.CreateStore(val, ptr);
}

//
// generateVariableDeclaration
//
// If the declaration has no explicit dimensions but its initializer is an
// InitializerList (as in unsized array declarations like "int arr[] = { ...
// };"), we infer the array size from the initializer list.
void CodeGenerator::generateVariableDeclaration(
    const shared_ptr<VariableDeclaration> &varDecl) {
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] generateVariableDeclaration: Processing variable '"
              << varDecl->name << "' of type '" << varDecl->type << "'"
              << std::endl;
  if (varDecl->inlineStructDecl) {
    registerStructType(varDecl->inlineStructDecl);
  }
  if (varDecl->inlineUnionDecl) {
    registerUnionType(varDecl->inlineUnionDecl);
  }
  auto itExistingType = declaredTypes.find(varDecl->name);
  if (itExistingType != declaredTypes.end())
    typeShadowStack[varDecl->name].push_back(itExistingType->second);
  auto itExistingStr = declaredTypeStrings.find(varDecl->name);
  if (itExistingStr != declaredTypeStrings.end())
    typeStringShadowStack[varDecl->name].push_back(itExistingStr->second);
  llvm::Type *baseType = getLLVMType(varDecl->type);
  llvm::Type *varType = baseType;
  auto normalizeAlignVal = [](unsigned v) {
    const unsigned MAX_ALIGN = 1u << 20; // keep alignments reasonable
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
  unsigned desiredAlign = 0;
  if (varDecl->alignment.has_value())
    desiredAlign = varDecl->alignment.value();
  auto itAlign = declaredAlignments.find(varDecl->type);
  if (itAlign != declaredAlignments.end())
    desiredAlign = std::max<unsigned>(desiredAlign, itAlign->second);
  desiredAlign = normalizeAlignVal(desiredAlign);

  bool hasDynamicDim = false;
  std::vector<llvm::Value *> dimensionValues;
  if (!varDecl->dimensions.empty()) {
    dimensionValues.reserve(varDecl->dimensions.size());
    for (const auto &dimExpr : varDecl->dimensions) {
      llvm::Value *dimVal = generateExpression(dimExpr);
      dimensionValues.push_back(dimVal);
      if (!llvm::isa<ConstantInt>(dimVal))
        hasDynamicDim = true;
    }
  }

  // If dimensions were provided, treat as an array variable.
  if (!varDecl->dimensions.empty()) {
    if (hasDynamicDim) {
      if (educcDebugEnabled())
        std::cerr << "[DEBUG] VLA declare '" << varDecl->name
                  << "' dims=" << dimensionValues.size() << std::endl;
      llvm::Value *elementCount =
          ConstantInt::get(Type::getInt64Ty(context), 1);
      std::vector<llvm::Value *> dim64Values;
      for (auto *dimVal : dimensionValues) {
        llvm::Value *as64 = dimVal;
        if (!as64->getType()->isIntegerTy(64))
          as64 = builder.CreateIntCast(dimVal, Type::getInt64Ty(context), true,
                                       "vla.cast");
        dim64Values.push_back(as64);
        elementCount = builder.CreateMul(elementCount, as64, "vla.mul");
      }
      AllocaInst *alloc =
          builder.CreateAlloca(baseType, elementCount, varDecl->name.c_str());
      if (educcDebugEnabled())
        std::cerr << "[DEBUG] VLA alloca done for '" << varDecl->name << "'"
                  << std::endl;
      const DataLayout &DL = module->getDataLayout();
      llvm::Align align = desiredAlign > 0 ? llvm::Align(desiredAlign)
                                           : DL.getABITypeAlign(baseType);
      alloc->setAlignment(align);
      localVarStack.back()[varDecl->name] = alloc;
      declaredVarStack.back().insert(varDecl->name);
      declaredTypes[varDecl->name] = baseType->getPointerTo();
      // Preserve array shape information for type queries.
      auto dimToString = [](const ExpressionPtr &expr) -> std::string {
        if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
          if (lit->type == Literal::LiteralType::Int)
            return std::to_string(lit->intValue);
        }
        if (auto id = std::dynamic_pointer_cast<Identifier>(expr))
          return id->name;
        return "";
      };
      std::string typeWithDimensions = varDecl->type;
      for (const auto &dimExpr : varDecl->dimensions) {
        typeWithDimensions += "[" + dimToString(dimExpr) + "]";
      }
      // Local VLAs decay to a pointer value in expressions.
      declaredTypeStrings[varDecl->name] = typeWithDimensions + "*";
      dynamicArrayVars.insert(varDecl->name);
      if (!dim64Values.empty())
        dynamicArrayDimensions[varDecl->name] = dim64Values;
      if (educcDebugEnabled())
        std::cerr << "[DEBUG] generateVariableDeclaration: dynamic array '"
                  << varDecl->name << "' element type '" << varDecl->type << "'"
                  << std::endl;
      return;
    }
    for (auto it = dimensionValues.rbegin(); it != dimensionValues.rend();
         ++it) {
      auto *constDim = cast<ConstantInt>(*it);
      uint64_t arraySize = constDim->getZExtValue();
      varType = ArrayType::get(varType, arraySize);
    }
  }
  // Otherwise, if there is an initializer list, infer the array size from it.
  else if (varDecl->initializer.has_value() &&
           varDecl->hasEmptyArrayDimension) {
    if (auto initList = std::dynamic_pointer_cast<InitializerList>(
            varDecl->initializer.value())) {
      uint64_t arraySize = initList->elements.size();
      if (arraySize == 0)
        arraySize = 1;
      varType = ArrayType::get(baseType, arraySize);
      AllocaInst *alloc =
          builder.CreateAlloca(varType, nullptr, varDecl->name.c_str());
      const DataLayout &DL = module->getDataLayout();
      llvm::Align align = desiredAlign > 0 ? llvm::Align(desiredAlign)
                                           : DL.getABITypeAlign(varType);
      alloc->setAlignment(align);
      localVarStack.back()[varDecl->name] = alloc;
      declaredVarStack.back().insert(varDecl->name);
      declaredTypes[varDecl->name] = varType;
      declaredTypeStrings[varDecl->name] =
          varDecl->type + "[" + std::to_string(arraySize) + "]";
      storeInitializerValue(varDecl->initializer.value(), varType, alloc);
      return;
    } else if (auto lit = std::dynamic_pointer_cast<Literal>(
                   varDecl->initializer.value())) {
      if (lit->type == Literal::LiteralType::String) {
        // Infer array size from string length + 1 (for null terminator)
        uint64_t arraySize = lit->stringValue.size() + 1;
        varType = ArrayType::get(baseType, arraySize);
        // Re-create the alloca with the correct type
        AllocaInst *alloc =
            builder.CreateAlloca(varType, nullptr, varDecl->name.c_str());
        const DataLayout &DL = module->getDataLayout();
        llvm::Align align = desiredAlign > 0 ? llvm::Align(desiredAlign)
                                             : DL.getABITypeAlign(varType);
        alloc->setAlignment(align);
        localVarStack.back()[varDecl->name] = alloc;
        declaredVarStack.back().insert(varDecl->name);
        declaredTypes[varDecl->name] = varType;
        // Build the type string including array dimensions
        // For declarations with an empty dimension (e.g., char s[] = "hi"),
        // record the inferred size so later type queries see an array type.
        string typeWithDimensions =
            varDecl->type + "[" + std::to_string(arraySize) + "]";
        for (auto &dimExpr : varDecl->dimensions) {
          if (auto lit = std::dynamic_pointer_cast<Literal>(dimExpr)) {
            typeWithDimensions += "[" + std::to_string(lit->intValue) + "]";
          }
        }
        declaredTypeStrings[varDecl->name] = typeWithDimensions;
        storeInitializerValue(varDecl->initializer.value(), varType, alloc);
        return;
      }
    }
  }

  AllocaInst *alloc =
      builder.CreateAlloca(varType, nullptr, varDecl->name.c_str());
  const DataLayout &DL = module->getDataLayout();
  llvm::Align align = desiredAlign > 0 ? llvm::Align(desiredAlign)
                                       : DL.getABITypeAlign(varType);
  alloc->setAlignment(align);
  localVarStack.back()[varDecl->name] = alloc;
  declaredVarStack.back().insert(varDecl->name);
  declaredTypes[varDecl->name] = varType;

  // Build the type string including array dimensions
  string typeWithDimensions = varDecl->type;
  for (auto &dimExpr : varDecl->dimensions) {
    if (auto lit = std::dynamic_pointer_cast<Literal>(dimExpr)) {
      typeWithDimensions += "[" + std::to_string(lit->intValue) + "]";
    }
  }
  declaredTypeStrings[varDecl->name] = typeWithDimensions;

  if (educcDebugEnabled())
    std::cerr << "[DEBUG] generateVariableDeclaration: Variable '"
              << varDecl->name << "' registered with type '"
              << declaredTypeStrings[varDecl->name] << "'" << std::endl;

  bool isUnionValue = varDecl->type.rfind("union ", 0) == 0;
  if (varDecl->initializer.has_value() && isUnionValue &&
      varType->isStructTy()) {
    string unionTag = normalizeTag(varDecl->type.substr(6));
    auto unionTy = dyn_cast<StructType>(varType);
    if (!unionTy)
      throw runtime_error("CodeGenerator Error: Union type '" + unionTag +
                          "' is not a struct representation.");
    AggregateTypeInfo *unionInfo = getAggregateTypeInfo(unionTag);
    string targetMemberName;
    string targetMemberType;
    if (unionInfo && !unionInfo->members.empty()) {
      targetMemberName = unionInfo->members.front().name;
      targetMemberType = unionInfo->members.front().type;
    } else {
      targetMemberName = "anon_member_0";
      targetMemberType = "int";
    }

    auto pickMemberForLiteral = [&](const Literal &lit) -> void {
      if (!unionInfo)
        return;
      for (const auto &memberInfo : unionInfo->members) {
        string base = memberInfo.type;
        if (base.rfind("const ", 0) == 0)
          base = base.substr(6);
        if (base.rfind("unsigned ", 0) == 0)
          base = base.substr(9);
        if (base.rfind("signed ", 0) == 0)
          base = base.substr(7);
        if (lit.type == Literal::LiteralType::Float &&
            base.rfind("float", 0) == 0) {
          targetMemberName = memberInfo.name;
          targetMemberType = memberInfo.type;
          return;
        }
        if (lit.type == Literal::LiteralType::Double &&
            base.rfind("double", 0) == 0) {
          targetMemberName = memberInfo.name;
          targetMemberType = memberInfo.type;
          return;
        }
        if (lit.type == Literal::LiteralType::Int &&
            (base.rfind("int", 0) == 0 || base.rfind("long", 0) == 0 ||
             base.rfind("short", 0) == 0 || base.rfind("char", 0) == 0 ||
             base.rfind("bool", 0) == 0)) {
          targetMemberName = memberInfo.name;
          targetMemberType = memberInfo.type;
          return;
        }
      }
    };

    auto castToMemberType = [&](llvm::Value *value,
                                llvm::Type *memberTy) -> llvm::Value * {
      if (value->getType() == memberTy)
        return value;
      if (value->getType()->isFloatingPointTy() &&
          memberTy->isFloatingPointTy()) {
        if (value->getType()->getFPMantissaWidth() >
            memberTy->getFPMantissaWidth())
          return builder.CreateFPTrunc(value, memberTy, "fptrunc");
        return builder.CreateFPExt(value, memberTy, "fpext");
      }
      if (value->getType()->isFloatingPointTy() && memberTy->isIntegerTy()) {
        return builder.CreateFPToSI(value, memberTy, "fptosi");
      }
      if (value->getType()->isIntegerTy() && memberTy->isFloatingPointTy()) {
        return builder.CreateSIToFP(value, memberTy, "sitofp");
      }
      if (value->getType()->isIntegerTy() && memberTy->isIntegerTy()) {
        return builder.CreateIntCast(value, memberTy, true, "intcast");
      }
      return builder.CreateBitCast(value, memberTy, "unionbitcast");
    };

    auto getUnionMemberPtr = [&](llvm::Type *memberTy) -> llvm::Value * {
      if (unionInfo) {
        return getUnionMemberPointer(*this, unionTy, alloc, unionTag,
                                     targetMemberName);
      }
      llvm::Value *storagePtr = builder.CreateStructGEP(
          unionTy, alloc, 0, varDecl->name + ".storage");
      return builder.CreateBitCast(storagePtr,
                                   llvm::PointerType::get(memberTy, 0),
                                   varDecl->name + ".union");
    };

    if (auto initList = std::dynamic_pointer_cast<InitializerList>(
            varDecl->initializer.value())) {
      if (!initList->elements.empty()) {
        if (auto lit = std::dynamic_pointer_cast<Literal>(
                initList->elements.front())) {
          pickMemberForLiteral(*lit);
        }
        llvm::Type *memberTy = getLLVMType(targetMemberType);
        llvm::Value *memberPtr = getUnionMemberPtr(memberTy);
        llvm::Value *initVal = generateExpression(initList->elements.front());
        initVal = castToMemberType(initVal, memberTy);
        builder.CreateStore(initVal, memberPtr);
      }
      return;
    }

    llvm::Value *rhs = generateExpression(varDecl->initializer.value());
    if (rhs->getType() == unionTy) {
      builder.CreateStore(rhs, alloc);
      return;
    }
    llvm::Type *memberTy = getLLVMType(targetMemberType);
    llvm::Value *memberPtr = getUnionMemberPtr(memberTy);
    rhs = castToMemberType(rhs, memberTy);
    builder.CreateStore(rhs, memberPtr);
    return;
  }

  // Handle string literal initializer for char arrays. If the declared type is
  // a pointer (e.g., char*), fall back to the generic initializer so the
  // pointer simply receives the string literal address.
  if (varDecl->initializer.has_value()) {
    if (auto lit =
            std::dynamic_pointer_cast<Literal>(varDecl->initializer.value())) {
      if (lit->type == Literal::LiteralType::String &&
          !varType->isPointerTy()) {
        auto arrayTy = llvm::dyn_cast<llvm::ArrayType>(varType);
        std::string str = lit->stringValue;
        uint64_t arraySize =
            arrayTy ? arrayTy->getNumElements() : (str.size() + 1);
        if (!arrayTy) {
          varType = ArrayType::get(baseType, arraySize);
          alloc = builder.CreateAlloca(varType, nullptr, varDecl->name.c_str());
          alloc->setAlignment(DL.getABITypeAlign(varType));
          localVarStack.back()[varDecl->name] = alloc;
          declaredVarStack.back().insert(varDecl->name);
          declaredTypes[varDecl->name] = varType;
          // Build the type string including array dimensions
          string typeWithDimensions = varDecl->type;
          for (auto &dimExpr : varDecl->dimensions) {
            if (auto lit = std::dynamic_pointer_cast<Literal>(dimExpr)) {
              typeWithDimensions += "[" + std::to_string(lit->intValue) + "]";
            }
          }
          declaredTypeStrings[varDecl->name] = typeWithDimensions;
          arrayTy = llvm::dyn_cast<llvm::ArrayType>(varType);
        }
        if (!arrayTy || !arrayTy->getElementType()->isIntegerTy(8))
          throw std::runtime_error("CodeGenerator Error: String literal "
                                   "initializer for non-char array.");
        uint64_t numElems = arrayTy->getNumElements();
        for (uint64_t i = 0; i < numElems; ++i) {
          char c = (i < str.size()) ? str[i] : '\0';
          if (i + 1 == numElems)
            c = '\0';
          llvm::Value *elemVal =
              llvm::ConstantInt::get(Type::getInt8Ty(context), c);
          std::vector<llvm::Value *> indices = {
              llvm::ConstantInt::get(Type::getInt32Ty(context), 0),
              llvm::ConstantInt::get(Type::getInt32Ty(context), i)};
          llvm::Value *elemPtr =
              builder.CreateGEP(alloc->getAllocatedType(), alloc, indices,
                                varDecl->name + "_idx");
          builder.CreateStore(elemVal, elemPtr);
        }
        return;
      }
    }
  }

  if (varDecl->initializer.has_value()) {
    // If this is an array initializer (either with explicit dimensions or
    // inferred unsized)
    if (!varDecl->dimensions.empty() ||
        std::dynamic_pointer_cast<InitializerList>(
            varDecl->initializer.value())) {
      if (auto initList = std::dynamic_pointer_cast<InitializerList>(
              varDecl->initializer.value())) {
        auto arrayTy = dyn_cast<ArrayType>(varType);
        auto structTy = dyn_cast<StructType>(varType);

        if (arrayTy) {
          // Handle array initializer
          uint64_t arraySize = arrayTy->getNumElements();
          for (uint64_t i = 0; i < arraySize; i++) {
            vector<llvm::Value *> indices;
            indices.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
            indices.push_back(ConstantInt::get(Type::getInt32Ty(context), i));
            llvm::Value *elemPtr =
                builder.CreateGEP(alloc->getAllocatedType(), alloc, indices,
                                  varDecl->name + "_idx");
            if (i < initList->elements.size()) {
              storeInitializerValue(initList->elements[i],
                                    arrayTy->getElementType(), elemPtr);
            } else {
              builder.CreateStore(
                  Constant::getNullValue(arrayTy->getElementType()), elemPtr);
            }
          }
        } else if (structTy) {
          // Handle struct initializer
          for (size_t i = 0;
               i < initList->elements.size() && i < structTy->getNumElements();
               i++) {
            vector<llvm::Value *> indices;
            indices.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
            indices.push_back(ConstantInt::get(Type::getInt32Ty(context), i));
            llvm::Value *elemPtr =
                builder.CreateGEP(alloc->getAllocatedType(), alloc, indices,
                                  varDecl->name + "_member");
            storeInitializerValue(initList->elements[i],
                                  structTy->getElementType(i), elemPtr);
          }
        } else {
          throw runtime_error("CodeGenerator Error: Initializer list used for "
                              "non-array/non-struct "
                              "variable in local variable declaration.");
        }
      } else {
        throw runtime_error("CodeGenerator Error: Array initializer must be an "
                            "initializer list.");
      }
    } else {
      // Scalar variable: simply generate the initializer expression.
      llvm::Value *initVal = generateExpression(varDecl->initializer.value());
      if (initVal->getType() != varType) {
        if (initVal->getType()->isFloatingPointTy() &&
            varType->isFloatingPointTy()) {
          if (initVal->getType()->getFPMantissaWidth() >
              varType->getFPMantissaWidth())
            initVal = builder.CreateFPTrunc(initVal, varType, "fptrunc");
          else
            initVal = builder.CreateFPExt(initVal, varType, "fpext");
        } else if (initVal->getType()->isFloatingPointTy() &&
                   varType->isIntegerTy()) {
          // Handle float-to-int conversion (truncation)
          initVal = builder.CreateFPToSI(initVal, varType, "fptosi");
        } else if (initVal->getType()->isIntegerTy() &&
                   varType->isFloatingPointTy()) {
          // Handle int-to-float conversion
          initVal = builder.CreateSIToFP(initVal, varType, "sitofp");
        } else if (initVal->getType()->isIntegerTy() &&
                   varType->isIntegerTy()) {
          // Cast between integer widths (extend or truncate).
          bool sourceIsSigned = !initVal->getType()->isIntegerTy(1);
          initVal = builder.CreateIntCast(initVal, varType, sourceIsSigned,
                                          "intcast");
        } else if (varType->isPointerTy()) {
          if (initVal->getType()->isPointerTy()) {
            initVal = builder.CreateBitCast(initVal, varType, "ptrcast");
          } else if (initVal->getType()->isIntegerTy()) {
            initVal = builder.CreateIntToPtr(initVal, varType, "inttoptr");
          } else {
            throw runtime_error("CodeGenerator Error: Incompatible initializer "
                                "type in local variable declaration.");
          }
        } else {
          throw runtime_error("CodeGenerator Error: Incompatible initializer "
                              "type in local variable declaration.");
        }
      }
      builder.CreateStore(initVal, alloc);
    }
  } else if (varDecl->initializer.has_value()) {
    if (auto lit =
            std::dynamic_pointer_cast<Literal>(varDecl->initializer.value())) {
      if (educcDebugEnabled())
        std::cerr << "[DEBUG] (generateVariableDeclaration) found Literal "
                     "initializer, type="
                  << (int)lit->type << std::endl;
      if (lit->type == Literal::LiteralType::String) {
        auto arrayTy = llvm::dyn_cast<llvm::ArrayType>(varType);
        if (!arrayTy || !arrayTy->getElementType()->isIntegerTy(8))
          throw std::runtime_error("CodeGenerator Error: String literal "
                                   "initializer for non-char array.");
        std::string str = lit->stringValue;
        uint64_t numElems = arrayTy->getNumElements();
        for (uint64_t i = 0; i < numElems; ++i) {
          char c = (i < str.size()) ? str[i] : '\0';
          if (i + 1 == numElems)
            c = '\0';
          llvm::Value *elemVal =
              llvm::ConstantInt::get(Type::getInt8Ty(context), c);
          std::vector<llvm::Value *> indices = {
              llvm::ConstantInt::get(Type::getInt32Ty(context), 0),
              llvm::ConstantInt::get(Type::getInt32Ty(context), i)};
          llvm::Value *elemPtr =
              builder.CreateGEP(alloc->getAllocatedType(), alloc, indices,
                                varDecl->name + "_idx");
          builder.CreateStore(elemVal, elemPtr);
        }
        return;
      }
    }
  }
}

//
// generateStatement
//
bool CodeGenerator::generateStatement(const StatementPtr &stmt) {
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] generateStatement: handling "
              << (stmt ? typeid(*stmt).name() : "null") << std::endl;
  auto toBool = [&](llvm::Value *val, const std::string &tag) -> llvm::Value * {
    if (val->getType()->isIntegerTy(1))
      return val;
    if (val->getType()->isPointerTy()) {
      return builder.CreateICmpNE(
          val,
          ConstantPointerNull::get(
              llvm::cast<llvm::PointerType>(val->getType())),
          tag);
    }
    if (val->getType()->isIntegerTy()) {
      return builder.CreateICmpNE(val, ConstantInt::get(val->getType(), 0),
                                  tag);
    }
    if (val->getType()->isFloatingPointTy()) {
      return builder.CreateFCmpONE(val, ConstantFP::get(val->getType(), 0.0),
                                   tag);
    }
    return val;
  };
  if (auto compound = std::dynamic_pointer_cast<CompoundStatement>(stmt)) {
    pushLocalScope();
    bool terminated = false;
    for (auto &substmt : compound->statements) {
      terminated = generateStatement(substmt);
      if (terminated)
        break;
    }
    if (localVarStack.size() > 1)
      popLocalScope();
    return terminated;
  } else if (auto exprStmt =
                 std::dynamic_pointer_cast<ExpressionStatement>(stmt)) {
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] ExpressionStatement expr type: "
                << (exprStmt->expression ? typeid(*exprStmt->expression).name()
                                         : "null")
                << std::endl;
    generateExpression(exprStmt->expression);
    return false;
  } else if (auto varDeclStmt =
                 std::dynamic_pointer_cast<VariableDeclarationStatement>(
                     stmt)) {
    // For local variable declarations, wrap the declaration in a
    // VariableDeclaration node.
    auto varDecl = std::make_shared<VariableDeclaration>(
        varDeclStmt->type, varDeclStmt->name, varDeclStmt->bitWidth,
        varDeclStmt->initializer, varDeclStmt->dimensions,
        varDeclStmt->alignment, varDeclStmt->hasEmptyArrayDimension, false,
        false, varDeclStmt->inlineStructDecl, varDeclStmt->inlineUnionDecl);
    generateVariableDeclaration(varDecl);
    return false;
  } else if (auto multiVarDeclStmt =
                 std::dynamic_pointer_cast<MultiVariableDeclarationStatement>(
                     stmt)) {
    for (auto &singleDecl : multiVarDeclStmt->declarations) {
      auto varDecl = std::make_shared<VariableDeclaration>(
          singleDecl->type, singleDecl->name, singleDecl->bitWidth,
          singleDecl->initializer, singleDecl->dimensions,
          singleDecl->alignment, singleDecl->hasEmptyArrayDimension, false,
          false, singleDecl->inlineStructDecl, singleDecl->inlineUnionDecl);
      generateVariableDeclaration(varDecl);
    }
    return false;
  } else if (auto retStmt = std::dynamic_pointer_cast<ReturnStatement>(stmt)) {
    llvm::Value *retVal = generateExpression(retStmt->expression);
    Function *currentFunction = builder.GetInsertBlock()->getParent();
    llvm::Type *expectedType = currentFunction->getReturnType();
    if (retVal->getType() != expectedType) {
      if (retVal->getType()->isIntegerTy(1) && expectedType->isIntegerTy(32))
        retVal = builder.CreateZExt(retVal, expectedType, "zexttmp");
      else if (retVal->getType()->isIntegerTy() && expectedType->isIntegerTy())
        retVal =
            builder.CreateIntCast(retVal, expectedType, false, "intcasttmp");
      else
        throw runtime_error("CodeGenerator Error: Return value type does not "
                            "match function return type.");
    }
    builder.CreateRet(retVal);
    return true;
  } else if (auto breakStmt = std::dynamic_pointer_cast<BreakStatement>(stmt)) {
    if (loopStack.empty()) {
      throw runtime_error(
          "CodeGenerator Error: 'break' statement not in a loop or switch");
    }
    // Branch to the innermost loop/switch exit block
    builder.CreateBr(loopStack.back().afterBlock);
    return true;
  } else if (auto continueStmt =
                 std::dynamic_pointer_cast<ContinueStatement>(stmt)) {
    if (loopStack.empty()) {
      throw runtime_error(
          "CodeGenerator Error: 'continue' statement not in a loop");
    }
    // Branch to the appropriate block based on loop type
    if (loopStack.back().isForLoop) {
      // For for loops, continue should go to the increment block
      builder.CreateBr(loopStack.back().incrementBlock);
    } else {
      // For while loops, continue should go to the condition block
      builder.CreateBr(loopStack.back().conditionBlock);
    }
    return true;
  } else if (auto gotoStmt = std::dynamic_pointer_cast<GotoStatement>(stmt)) {
    // For now, we'll just skip goto statements
    // TODO: Implement proper goto label handling
    return false;
  } else if (auto doWhileStmt =
                 std::dynamic_pointer_cast<DoWhileStatement>(stmt)) {
    llvm::BasicBlock *currentBB = builder.GetInsertBlock();
    if (!currentBB)
      throw runtime_error("CodeGenerator Error: No active block for for-loop.");
    Function *theFunction = currentBB->getParent();
    if (!theFunction)
      throw runtime_error(
          "CodeGenerator Error: No function parent for for-loop.");
    BasicBlock *bodyBB =
        BasicBlock::Create(context, "dowhile_body", theFunction);
    BasicBlock *condBB =
        BasicBlock::Create(context, "dowhile_cond", theFunction);
    BasicBlock *afterBB =
        BasicBlock::Create(context, "dowhile_after", theFunction);

    // Branch to the body
    builder.CreateBr(bodyBB);
    builder.SetInsertPoint(bodyBB);

    // Generate the body
    bool bodyTerminated = generateStatement(doWhileStmt->body);
    if (!bodyTerminated) {
      builder.CreateBr(condBB);
    }

    builder.SetInsertPoint(condBB);
    llvm::Value *condVal =
        toBool(generateExpression(doWhileStmt->condition), "dowhilecond");

    builder.CreateCondBr(condVal, bodyBB, afterBB);
    builder.SetInsertPoint(afterBB);
    return false;
  } else if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(stmt)) {
    llvm::Value *condVal =
        toBool(generateExpression(ifStmt->condition), "ifcond");
    Function *theFunction = builder.GetInsertBlock()->getParent();
    BasicBlock *thenBB = BasicBlock::Create(context, "then", theFunction);
    BasicBlock *elseBB = BasicBlock::Create(context, "else", theFunction);
    BasicBlock *mergeBB = BasicBlock::Create(context, "ifcont", theFunction);
    builder.CreateCondBr(condVal, thenBB, elseBB);
    builder.SetInsertPoint(thenBB);
    bool thenTerminated = generateStatement(ifStmt->thenBranch);
    if (!thenTerminated)
      builder.CreateBr(mergeBB);
    builder.SetInsertPoint(elseBB);
    bool elseTerminated = false;
    if (ifStmt->elseBranch)
      elseTerminated = generateStatement(ifStmt->elseBranch.value());
    if (!elseTerminated)
      builder.CreateBr(mergeBB);
    builder.SetInsertPoint(mergeBB);
    return false;
  } else if (auto whileStmt = std::dynamic_pointer_cast<WhileStatement>(stmt)) {
    Function *theFunction = builder.GetInsertBlock()->getParent();
    BasicBlock *condBB = BasicBlock::Create(context, "while.cond", theFunction);
    BasicBlock *bodyBB = BasicBlock::Create(context, "while.body", theFunction);
    BasicBlock *afterBB =
        BasicBlock::Create(context, "while.after", theFunction);

    // Push loop context for break/continue
    loopStack.push_back({condBB, bodyBB, afterBB, nullptr, false});

    builder.CreateBr(condBB);
    builder.SetInsertPoint(condBB);
    llvm::Value *condVal =
        toBool(generateExpression(whileStmt->condition), "whilecond");
    builder.CreateCondBr(condVal, bodyBB, afterBB);
    builder.SetInsertPoint(bodyBB);
    bool bodyTerminated = generateStatement(whileStmt->body);
    if (!bodyTerminated)
      builder.CreateBr(condBB);
    builder.SetInsertPoint(afterBB);

    // Pop loop context
    loopStack.pop_back();
    return false;
  } else if (auto forStmt = std::dynamic_pointer_cast<ForStatement>(stmt)) {
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] generateStatement: For init\n";
    if (forStmt->initializer)
      generateStatement(forStmt->initializer);
    Function *theFunction = builder.GetInsertBlock()->getParent();
    BasicBlock *condBB = BasicBlock::Create(context, "for.cond", theFunction);
    BasicBlock *bodyBB = BasicBlock::Create(context, "for.body", theFunction);
    BasicBlock *incrBB = BasicBlock::Create(context, "for.incr", theFunction);
    BasicBlock *afterBB = BasicBlock::Create(context, "for.after", theFunction);
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] generateStatement: For blocks created\n";

    // Push loop context for break/continue
    loopStack.push_back({condBB, bodyBB, afterBB, incrBB, true});

    llvm::BasicBlock *insertBB = builder.GetInsertBlock();
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] generateStatement: For insert block "
                << (insertBB ? insertBB->getName().str() : "null") << std::endl;
    if (!insertBB || insertBB->getTerminator()) {
      if (educcDebugEnabled())
        std::cerr << "[DEBUG] generateStatement: insert block missing or "
                     "terminated, creating prologue\n";
      insertBB = BasicBlock::Create(context, "for.prologue", theFunction);
      builder.SetInsertPoint(insertBB);
    }

    builder.CreateBr(condBB);
    builder.SetInsertPoint(condBB);
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] generateStatement: For evaluating condition\n";
    llvm::Value *condVal = nullptr;
    if (forStmt->condition) {
      if (educcDebugEnabled())
        std::cerr << "[DEBUG] generateStatement: For condition\n";
      condVal = toBool(generateExpression(forStmt->condition), "forcond");
    } else {
      condVal = ConstantInt::get(Type::getInt1Ty(context), 1);
    }
    builder.CreateCondBr(condVal, bodyBB, afterBB);
    builder.SetInsertPoint(bodyBB);
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] generateStatement: For body\n";
    bool bodyTerminated = generateStatement(forStmt->body);
    if (!bodyTerminated)
      builder.CreateBr(incrBB);
    builder.SetInsertPoint(incrBB);
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] generateStatement: For increment\n";
    if (forStmt->increment)
      generateExpression(forStmt->increment);
    builder.CreateBr(condBB);
    builder.SetInsertPoint(afterBB);

    // Pop loop context
    loopStack.pop_back();
    return false;
  } else if (auto switchStmt =
                 std::dynamic_pointer_cast<SwitchStatement>(stmt)) {
    llvm::Value *condVal = generateExpression(switchStmt->expression);
    if (!condVal->getType()->isIntegerTy())
      throw runtime_error(
          "CodeGenerator Error: Switch expression must be of integer type.");
    Function *theFunction = builder.GetInsertBlock()->getParent();
    BasicBlock *mergeBB =
        BasicBlock::Create(context, "switch.merge", theFunction);
    vector<BasicBlock *> caseBBs;
    for (size_t i = 0; i < switchStmt->cases.size(); i++) {
      BasicBlock *bb = BasicBlock::Create(context, "switch.case", theFunction);
      caseBBs.push_back(bb);
    }
    BasicBlock *defaultBB = mergeBB;
    if (switchStmt->defaultCase.has_value())
      defaultBB = BasicBlock::Create(context, "switch.default", theFunction);
    SwitchInst *switchInst =
        builder.CreateSwitch(condVal, defaultBB, switchStmt->cases.size());
    for (size_t i = 0; i < switchStmt->cases.size(); i++) {
      if (!switchStmt->cases[i].first.has_value())
        throw runtime_error(
            "CodeGenerator Error: Case label missing in case clause.");
      llvm::Value *caseVal =
          generateExpression(switchStmt->cases[i].first.value());
      if (!isa<ConstantInt>(caseVal))
        throw runtime_error(
            "CodeGenerator Error: Case label must be a constant integer.");
      switchInst->addCase(cast<ConstantInt>(caseVal), caseBBs[i]);
    }
    loopStack.push_back({nullptr, nullptr, mergeBB, nullptr, false});
    for (size_t i = 0; i < caseBBs.size(); i++) {
      builder.SetInsertPoint(caseBBs[i]);
      bool terminated = generateStatement(switchStmt->cases[i].second);
      if (!terminated) {
        if (i + 1 < caseBBs.size())
          builder.CreateBr(caseBBs[i + 1]);
        else
          builder.CreateBr(defaultBB);
      }
    }
    if (switchStmt->defaultCase.has_value()) {
      builder.SetInsertPoint(defaultBB);
      bool terminated = generateStatement(switchStmt->defaultCase.value());
      if (!terminated)
        builder.CreateBr(mergeBB);
    }
    loopStack.pop_back();
    builder.SetInsertPoint(mergeBB);
    return false;
  } else if (auto declStmt =
                 std::dynamic_pointer_cast<DeclarationStatement>(stmt)) {
    // Handle local declarations (struct, union, enum)
    if (auto structDecl = std::dynamic_pointer_cast<StructDeclaration>(
            declStmt->declaration)) {
      registerStructType(structDecl);
    } else if (auto unionDecl = std::dynamic_pointer_cast<UnionDeclaration>(
                   declStmt->declaration)) {
      registerUnionType(unionDecl);
    } else if (auto enumDecl = std::dynamic_pointer_cast<EnumDeclaration>(
                   declStmt->declaration)) {
      // Handle local enum declaration
      for (size_t i = 0; i < enumDecl->enumerators.size(); ++i) {
        string enumName = enumDecl->enumerators[i].first;
        int value = enumDecl->enumeratorValues[i];
        Constant *initVal = ConstantInt::get(Type::getInt32Ty(context), value);
        new GlobalVariable(*module, Type::getInt32Ty(context), true,
                           GlobalValue::ExternalLinkage, initVal, enumName);
      }
    } else if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclaration>(
                   declStmt->declaration)) {
      IRBuilder<>::InsertPointGuard guard(builder);
      generateFunction(funcDecl);
    }
    return false;
  } else {
    throw runtime_error("CodeGenerator Error: Unsupported statement type.");
  }
}

//
// generateLValue: returns an lvalue pointer for an expression
//
llvm::Value *CodeGenerator::generateLValue(const ExpressionPtr &expr) {
  // 1) Identifier
  if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    llvm::Value *v = lookupLocalVar(id->name);
    if (v)
      return v;
    GlobalVariable *gVar = module->getGlobalVariable(id->name);
    if (gVar)
      return gVar;
    if (auto *fn = module->getFunction(id->name))
      return fn;
    throw runtime_error("Undefined variable in generateLValue: " + id->name);
  }
  // 2) MemberAccess: base.member
  else if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    if (educcDebugEnabled())
      std::cerr
          << "[DEBUG] generateLValue: Processing member access for member: "
          << mem->member << std::endl;
    string baseEffectiveType = getEffectiveType(*this, mem->base);
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] generateLValue: Base effective type: "
                << baseEffectiveType << std::endl;
    llvm::Value *basePtr = generateLValue(mem->base);
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] generateLValue: Got base pointer" << std::endl;

    if (baseEffectiveType.rfind("struct ", 0) == 0) {
      string tag = baseEffectiveType.substr(7);
      tag = normalizeTag(tag);

      // Get the struct type from our local registry
      auto it = declaredTypes.find(tag);
      if (it == declaredTypes.end())
        throw runtime_error("Unknown struct type '" + tag + "'.");

      StructType *structTy = dyn_cast<StructType>(it->second);
      if (!structTy)
        throw runtime_error("Type '" + tag + "' is not a struct type.");

      // Find the member index using the enhanced type registry
      AggregateTypeInfo *typeInfo = getAggregateTypeInfo(tag);
      if (!typeInfo) {
        throw runtime_error("Struct type info not found for '" + tag + "'.");
      }

      MemberInfo *memberInfo = getMemberInfo(tag, mem->member);
      if (!memberInfo) {
        throw runtime_error("Struct type '" + tag +
                            "' does not contain member '" + mem->member + "'.");
      }
      if (memberInfo->isUnionMemberAlias) {
        auto unionIt = declaredTypes.find(memberInfo->unionTag);
        if (unionIt == declaredTypes.end())
          throw runtime_error("Unknown union type '" + memberInfo->unionTag +
                              "' for member '" + mem->member + "'.");
        StructType *unionTy = dyn_cast<StructType>(unionIt->second);
        if (!unionTy)
          throw runtime_error("Type '" + memberInfo->unionTag +
                              "' is not a union type.");
        llvm::Value *unionPtr = builder.CreateStructGEP(
            structTy, basePtr, memberInfo->unionFieldIndex,
            mem->member + ".union");
        return getUnionMemberPointer(*this, unionTy, unionPtr,
                                     memberInfo->unionTag, memberInfo->name);
      }

      return builder.CreateStructGEP(structTy, basePtr, memberInfo->index,
                                     mem->member);
    } else if (baseEffectiveType.rfind("union ", 0) == 0) {
      string tag = baseEffectiveType.substr(6);
      tag = normalizeTag(tag);

      // Get the union type from our local registry
      auto it = declaredTypes.find(tag);
      if (it == declaredTypes.end())
        throw runtime_error("Unknown union type '" + tag + "'.");

      StructType *unionTy = dyn_cast<StructType>(it->second);
      if (!unionTy)
        throw runtime_error("Type '" + tag + "' is not a union type.");

      // Find the member index using the enhanced type registry
      AggregateTypeInfo *typeInfo = getAggregateTypeInfo(tag);
      if (!typeInfo) {
        throw runtime_error("Union type info not found for '" + tag + "'.");
      }

      MemberInfo *memberInfo = getMemberInfo(tag, mem->member);
      if (!memberInfo) {
        throw runtime_error("Union type '" + tag +
                            "' does not contain member '" + mem->member + "'.");
      }
      return getUnionMemberPointer(*this, unionTy, basePtr, tag, mem->member);
    }
    // non-struct/union => just get LValue of the base
    else {
      return generateLValue(mem->base);
    }
  }
  // 3) PostfixExpression: e.g. i++
  else if (auto post = std::dynamic_pointer_cast<PostfixExpression>(expr)) {
    return generateLValue(post->operand);
  }
  // 4) Assignment
  else if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
    llvm::Value *ptr = generateLValue(assign->lhs);
    llvm::Value *rhsVal = generateExpression(assign->rhs);
    builder.CreateStore(rhsVal, ptr);
    return rhsVal;
  }
  // 5) ArrayAccess
  else if (auto arr = std::dynamic_pointer_cast<ArrayAccess>(expr)) {
    return generateArrayElementPointer(arr);
  }
  // 6) FunctionCall => generally not an lvalue unless returning a reference
  // type
  else if (auto funcCall = std::dynamic_pointer_cast<FunctionCall>(expr)) {
    throw runtime_error("Expression is not a valid lvalue: function call");
  }
  // 7) Unary '*' operator (dereference)
  else if (auto un = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
    if (un->op == "*") {
      // For lvalue purposes, simply evaluate the operand to obtain the pointer.
      llvm::Value *ptr = generateExpression(un->operand);
      if (!ptr->getType()->isPointerTy())
        throw runtime_error(
            "generateLValue: '*' applied to non-pointer expression");
      return ptr;
    }
  }
  throw runtime_error("Expression is not a valid lvalue.");
}

//
// getLLVMType: convert a string type (which may contain pointer stars) into an
// LLVM type. Updated to support multiple pointer levels (e.g. "int **").
llvm::Type *CodeGenerator::getLLVMType(const string &type) {
  // Count trailing '*' characters (pointer levels).
  int pointerCount = 0;
  size_t end = type.size();
  while (end > 0 && isspace(static_cast<unsigned char>(type[end - 1])))
    --end;
  while (end > 0 && type[end - 1] == '*') {
    pointerCount++;
    --end;
    while (end > 0 && isspace(static_cast<unsigned char>(type[end - 1])))
      --end;
  }
  // Extract base type without trailing pointers and trim whitespace.
  string baseType = type.substr(0, end);
  while (!baseType.empty() &&
         isspace(static_cast<unsigned char>(baseType.front())))
    baseType.erase(baseType.begin());
  while (!baseType.empty() &&
         isspace(static_cast<unsigned char>(baseType.back())))
    baseType.pop_back();

  auto tdIt = typedefRegistry.find(baseType);
  if (tdIt != typedefRegistry.end()) {
    baseType = tdIt->second.underlyingType;
  }

  auto stripPrefix = [](string &s, const string &prefix) {
    while (s.rfind(prefix, 0) == 0) {
      s = s.substr(prefix.size());
      while (!s.empty() && isspace(s.front()))
        s.erase(s.begin());
    }
  };

  bool isUnsigned = false;
  bool isSigned = false;
  stripPrefix(baseType, "const ");
  stripPrefix(baseType, "volatile ");
  stripPrefix(baseType, "static ");
  stripPrefix(baseType, "const ");
  stripPrefix(baseType, "volatile ");
  stripPrefix(baseType, "_Atomic ");
  if (baseType.rfind("unsigned ", 0) == 0) {
    isUnsigned = true;
    stripPrefix(baseType, "unsigned ");
  } else if (baseType.rfind("signed ", 0) == 0) {
    isSigned = true;
    stripPrefix(baseType, "signed ");
  }

  std::string returnType;
  std::vector<std::string> paramTypes;
  llvm::Type *ty = nullptr;
  if (parseFunctionPointerType(baseType, returnType, paramTypes)) {
    vector<Type *> paramLLVM;
    for (const auto &p : paramTypes) {
      paramLLVM.push_back(getLLVMType(p));
    }
    ty = FunctionType::get(getLLVMType(returnType), paramLLVM, false)
             ->getPointerTo();
  } else if (baseType == "int" || baseType.empty())
    ty = Type::getInt32Ty(context);
  else if (baseType == "float complex" || baseType == "complex float")
    ty = StructType::get(Type::getFloatTy(context), Type::getFloatTy(context));
  else if (baseType == "float")
    ty = Type::getFloatTy(context);
  else if (baseType == "char")
    ty = Type::getInt8Ty(context);
  else if (baseType == "double complex" || baseType == "complex double")
    ty =
        StructType::get(Type::getDoubleTy(context), Type::getDoubleTy(context));
  else if (baseType == "double")
    ty = Type::getDoubleTy(context);
  else if (baseType == "long long")
    ty = Type::getInt64Ty(context);
  else if (baseType == "long")
    ty = Type::getInt64Ty(context);
  else if (baseType == "short")
    ty = Type::getInt16Ty(context);
  else if (baseType == "size_t" || baseType == "uintptr_t" ||
           baseType == "intptr_t" || baseType == "ptrdiff_t" ||
           baseType == "ssize_t" || baseType == "uint64_t" ||
           baseType == "int64_t")
    ty = Type::getInt64Ty(context);
  else if (baseType == "uint32_t" || baseType == "int32_t")
    ty = Type::getInt32Ty(context);
  else if (baseType == "uint16_t" || baseType == "int16_t")
    ty = Type::getInt16Ty(context);
  else if (baseType == "uint8_t" || baseType == "int8_t")
    ty = Type::getInt8Ty(context);
  else if (baseType == "bool")
    ty = Type::getInt1Ty(context);
  else if (baseType == "__builtin_va_list" || baseType == "va_list")
    ty = PointerType::get(Type::getInt8Ty(context), 0);
  else if (baseType == "max_align_t")
    ty = Type::getDoubleTy(context);
  else if (baseType == "void")
    ty = Type::getVoidTy(context);
  else if (baseType.rfind("enum ", 0) == 0)
    ty = Type::getInt32Ty(context);
  else if (baseType.rfind("union ", 0) == 0) {
    string tag = baseType.substr(6);
    auto it = declaredTypes.find(tag);
    if (it == declaredTypes.end()) {
      if (auto *info = getAggregateTypeInfo(tag)) {
        uint64_t size = info->totalSize ? info->totalSize : 1;
        ArrayType *storage = ArrayType::get(Type::getInt8Ty(context), size);
        StructType *unionTy = StructType::create(context, tag);
        unionTy->setBody({storage}, /*isPacked=*/false);
        declaredTypes[tag] = unionTy;
        it = declaredTypes.find(tag);
      } else {
        throw runtime_error("CodeGenerator Error: Unknown union type '" + type +
                            "'.");
      }
    }
    ty = it->second;
  } else if (baseType.rfind("struct ", 0) == 0) {
    string tag = baseType.substr(7);
    auto it = declaredTypes.find(tag);
    if (it == declaredTypes.end()) {
      throw runtime_error("CodeGenerator Error: Unknown struct type '" + type +
                          "'.");
    }
    ty = it->second;
  } else {
    (void)isUnsigned;
    (void)isSigned;
    // Check if this is an array type (e.g., "char[20]" or with dynamic []).
    size_t bracketPos = baseType.find('[');
    if (bracketPos != string::npos) {
      string elementType = baseType.substr(0, bracketPos);
      string rest = baseType.substr(bracketPos);
      stripPrefix(elementType, "const ");
      stripPrefix(elementType, "volatile ");
      stripPrefix(elementType, "static ");
      if (elementType.rfind("unsigned ", 0) == 0) {
        stripPrefix(elementType, "unsigned ");
      } else if (elementType.rfind("signed ", 0) == 0) {
        stripPrefix(elementType, "signed ");
      }

      // Get the element type
      llvm::Type *elementTy = nullptr;
      if (elementType == "int")
        elementTy = Type::getInt32Ty(context);
      else if (elementType == "float")
        elementTy = Type::getFloatTy(context);
      else if (elementType == "char")
        elementTy = Type::getInt8Ty(context);
      else if (elementType == "double")
        elementTy = Type::getDoubleTy(context);
      else if (elementType == "long long")
        elementTy = Type::getInt64Ty(context);
      else if (elementType == "long")
        elementTy = Type::getInt64Ty(context);
      else if (elementType == "short")
        elementTy = Type::getInt16Ty(context);
      else if (elementType == "bool")
        elementTy = Type::getInt1Ty(context);
      else {
        throw runtime_error(
            "CodeGenerator Error: Unsupported array element type '" +
            elementType + "'.");
      }

      // Parse each dimension; non-numeric (or empty) dims decay to pointers.
      vector<string> dimStrs;
      size_t pos = 0;
      while ((pos = rest.find('[')) != string::npos) {
        size_t close = rest.find(']', pos);
        if (close == string::npos)
          break;
        dimStrs.push_back(rest.substr(pos + 1, close - pos - 1));
        rest = rest.substr(close + 1);
      }
      llvm::Type *arrTy = elementTy;
      bool dynamicSeen = false;
      for (auto it = dimStrs.rbegin(); it != dimStrs.rend(); ++it) {
        if (dynamicSeen || it->empty()) {
          arrTy = PointerType::get(arrTy, 0);
          dynamicSeen = true;
          continue;
        }
        try {
          int arraySize = std::stoi(*it);
          arrTy = ArrayType::get(arrTy, arraySize);
        } catch (...) {
          arrTy = PointerType::get(arrTy, 0);
          dynamicSeen = true;
        }
      }
      ty = arrTy;
    } else {
      throw runtime_error("CodeGenerator Error: Unsupported type '" + type +
                          "'.");
    }
  }
  // Now wrap the base type in pointer types as needed.
  for (int i = 0; i < pointerCount; i++) {
    ty = PointerType::get(ty, 0);
  }
  return ty;
}
