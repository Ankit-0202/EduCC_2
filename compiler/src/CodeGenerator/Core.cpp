#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"

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
  module->setTargetTriple(triple);

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

  std::unique_ptr<llvm::TargetMachine> targetMachine(
      target->createTargetMachine(triple, cpu, features, opt, relocModel));
  if (!targetMachine) {
    throw runtime_error("CodeGenerator Error: Failed to create target machine "
                        "for triple '" +
                        targetTriple + "'.");
  }

  module->setDataLayout(targetMachine->createDataLayout());
  // NOTE: Opaque pointers are enabled by default in LLVM 15+.
  // To call getElementType(), your LLVM must disable opaque pointers.
}

std::unique_ptr<Module>
CodeGenerator::generateCode(const shared_ptr<Program> &program) {
  std::cerr << "[DEBUG] generateCode: Processing "
            << program->declarations.size() << " declarations\n";

  auto registerUnionType =
      [&](const std::shared_ptr<UnionDeclaration> &unionDecl) {
        if (!unionDecl || !unionDecl->tag.has_value())
          return;

        const DataLayout &DL = module->getDataLayout();
        uint64_t maxSize = 0;

        for (const auto &member : unionDecl->members) {
          Type *memberType = getLLVMType(member->type);
          for (auto it = member->dimensions.rbegin();
               it != member->dimensions.rend(); ++it) {
            auto lit = std::dynamic_pointer_cast<Literal>(*it);
            if (!lit)
              throw runtime_error("CodeGenerator Error: Array dimension must "
                                  "be a constant integer.");
            uint64_t arraySize = static_cast<uint64_t>(lit->intValue);
            memberType = ArrayType::get(memberType, arraySize);
          }
          maxSize =
              std::max<uint64_t>(maxSize, DL.getTypeAllocSize(memberType));
        }

        if (maxSize == 0)
          maxSize = 1;

        ArrayType *storageType =
            ArrayType::get(Type::getInt8Ty(context), maxSize);
        StructType *unionType =
            StructType::create(context, unionDecl->tag.value());
        unionType->setBody({storageType}, /*isPacked=*/false);
        declaredTypes[unionDecl->tag.value()] = unionType;
      };

  auto registerStructType =
      [&](const std::shared_ptr<StructDeclaration> &structDecl) {
        if (!structDecl || !structDecl->tag.has_value())
          return;

        for (const auto &nestedUnion : structDecl->nestedUnions) {
          registerUnionType(nestedUnion);
        }

        std::vector<Type *> memberTypes;
        for (const auto &member : structDecl->members) {
          Type *memberType = getLLVMType(member->type);
          memberTypes.push_back(memberType);
        }

        StructType *structType =
            StructType::create(context, structDecl->tag.value());
        structType->setBody(memberTypes, /*isPacked=*/false);

        declaredTypes[structDecl->tag.value()] = structType;
      };

  // Process global declarations first.
  for (const auto &decl : program->declarations) {
    std::cerr << "[DEBUG] generateCode: Processing declaration\n";

    if (auto varDecl = std::dynamic_pointer_cast<VariableDeclaration>(decl)) {
      std::cerr << "[DEBUG] generateCode: Variable declaration: "
                << varDecl->name << "\n";
      // e.g. int x;   or   int array[10];
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
        }
      }
      // Create the global
      GlobalVariable *gVar = new GlobalVariable(
          *module, varType, /*isConstant=*/false, GlobalValue::ExternalLinkage,
          nullptr, varDecl->name);
      declaredTypes[varDecl->name] = varType;
      declaredTypeStrings[varDecl->name] = varDecl->type;

      // If it has an initializer
      if (varDecl->initializer) {
        if (auto initList = std::dynamic_pointer_cast<InitializerList>(
                varDecl->initializer.value())) {
          // array initializer
          auto arrayTy = dyn_cast<ArrayType>(varType);
          if (!arrayTy)
            throw runtime_error("CodeGenerator Error: Initializer list used "
                                "for non-array variable.");
          uint64_t arraySize = arrayTy->getNumElements();
          vector<Constant *> elems;
          for (uint64_t i = 0; i < arraySize; i++) {
            Constant *elemConst = nullptr;
            if (i < initList->elements.size()) {
              auto lit =
                  std::dynamic_pointer_cast<Literal>(initList->elements[i]);
              if (!lit)
                throw runtime_error("CodeGenerator Error: Global initializer "
                                    "list must contain literals.");
              if (lit->type == Literal::LiteralType::Int)
                elemConst =
                    ConstantInt::get(Type::getInt32Ty(context), lit->intValue);
              else if (lit->type == Literal::LiteralType::Float)
                elemConst =
                    ConstantFP::get(Type::getFloatTy(context), lit->floatValue);
              else if (lit->type == Literal::LiteralType::Double)
                elemConst = ConstantFP::get(Type::getDoubleTy(context),
                                            lit->doubleValue);
              else if (lit->type == Literal::LiteralType::Char)
                elemConst =
                    ConstantInt::get(Type::getInt8Ty(context), lit->charValue);
              else if (lit->type == Literal::LiteralType::Bool)
                elemConst =
                    ConstantInt::get(Type::getInt1Ty(context), lit->boolValue);
              else
                throw runtime_error("CodeGenerator Error: Unsupported literal "
                                    "in global initializer.");
            } else {
              elemConst = Constant::getNullValue(arrayTy->getElementType());
            }
            elems.push_back(elemConst);
          }
          Constant *arrayInit = ConstantArray::get(arrayTy, elems);
          gVar->setInitializer(arrayInit);
        } else if (auto lit = std::dynamic_pointer_cast<Literal>(
                       varDecl->initializer.value())) {
          Constant *initVal = nullptr;
          if (lit->type == Literal::LiteralType::String) {
            auto strConst =
                ConstantDataArray::getString(context, lit->stringValue, true);
            if (auto arrayTy = dyn_cast<ArrayType>(varType)) {
              if (!arrayTy->getElementType()->isIntegerTy(8)) {
                throw runtime_error("CodeGenerator Error: String literal "
                                    "initializer for non-char array.");
              }
              std::vector<Constant *> chars;
              chars.reserve(arrayTy->getNumElements());
              for (uint64_t i = 0; i < arrayTy->getNumElements(); ++i) {
                char c =
                    (i < lit->stringValue.size()) ? lit->stringValue[i] : '\0';
                chars.push_back(ConstantInt::get(Type::getInt8Ty(context), c));
              }
              initVal = ConstantArray::get(arrayTy, chars);
            } else if (varType->isPointerTy()) {
              auto *strGV =
                  new GlobalVariable(*module, strConst->getType(), true,
                                     GlobalValue::PrivateLinkage, strConst,
                                     varDecl->name + ".str");
              initVal = ConstantExpr::getBitCast(strGV, varType);
            } else {
              throw runtime_error("CodeGenerator Error: Unsupported string "
                                  "initializer in global var "
                                  "declaration.");
            }
          } else if (lit->type == Literal::LiteralType::Int)
            initVal =
                ConstantInt::get(Type::getInt32Ty(context), lit->intValue);
          else if (lit->type == Literal::LiteralType::Float)
            initVal =
                ConstantFP::get(Type::getFloatTy(context), lit->floatValue);
          else if (lit->type == Literal::LiteralType::Double)
            initVal =
                ConstantFP::get(Type::getDoubleTy(context), lit->doubleValue);
          else if (lit->type == Literal::LiteralType::Char)
            initVal =
                ConstantInt::get(Type::getInt8Ty(context), lit->charValue);
          else if (lit->type == Literal::LiteralType::Bool)
            initVal =
                ConstantInt::get(Type::getInt1Ty(context), lit->boolValue);
          else
            throw runtime_error("CodeGenerator Error: Unsupported literal type "
                                "in global init.");
          // possibly convert float -> double or double -> float
          if (initVal->getType() != varType) {
            if (initVal->getType()->isFloatingPointTy() &&
                varType->isFloatingPointTy()) {
              // cast from float->double or double->float
              auto litVal = (lit->type == Literal::LiteralType::Double)
                                ? (float)lit->doubleValue
                                : (double)lit->floatValue;
              initVal = ConstantFP::get(varType, litVal);
            } else if (initVal->getType()->isPointerTy() &&
                       varType->isPointerTy()) {
              initVal = ConstantExpr::getBitCast(initVal, varType);
            } else if (initVal->getType()->isArrayTy() &&
                       varType->isArrayTy()) {
              // Keep array literal as-is when sizes differ.
              if (auto arrayTy = dyn_cast<ArrayType>(varType)) {
                std::vector<Constant *> chars;
                std::string str = lit->stringValue;
                for (uint64_t i = 0; i < arrayTy->getNumElements(); ++i) {
                  char c = (i < str.size()) ? str[i] : '\0';
                  chars.push_back(
                      ConstantInt::get(Type::getInt8Ty(context), c));
                }
                initVal = ConstantArray::get(arrayTy, chars);
              }
            } else if (initVal->getType()->isIntegerTy() &&
                       varType->isIntegerTy()) {
              if (auto *intConst = dyn_cast<ConstantInt>(initVal)) {
                initVal = ConstantInt::get(varType, intConst->getValue());
              } else {
                auto *srcIntTy = cast<IntegerType>(initVal->getType());
                auto *dstIntTy = cast<IntegerType>(varType);
                Instruction::CastOps op;
                if (dstIntTy->getBitWidth() >= srcIntTy->getBitWidth()) {
                  op = srcIntTy->getBitWidth() == 1 ? Instruction::ZExt
                                                    : Instruction::SExt;
                } else {
                  op = Instruction::Trunc;
                }
                initVal = ConstantExpr::getCast(op, initVal, varType);
              }
            } else {
              throw runtime_error(
                  "CodeGenerator Error: Incompatible initializer type in "
                  "global var declaration.");
            }
          }
          gVar->setInitializer(initVal);
        } else {
          throw runtime_error("CodeGenerator Error: Global initializer must be "
                              "literal or list.");
        }
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
          }
        }
        GlobalVariable *gVar = new GlobalVariable(*module, varType, false,
                                                  GlobalValue::ExternalLinkage,
                                                  nullptr, singleDecl->name);
        declaredTypes[singleDecl->name] = varType;
        declaredTypeStrings[singleDecl->name] = singleDecl->type;

        if (singleDecl->initializer) {
          if (auto initList = std::dynamic_pointer_cast<InitializerList>(
                  singleDecl->initializer.value())) {
            auto arrayTy = dyn_cast<ArrayType>(varType);
            if (!arrayTy)
              throw runtime_error(
                  "CodeGenerator Error: Init list used for non-array.");
            uint64_t arraySize = arrayTy->getNumElements();
            vector<Constant *> elems;
            for (uint64_t i = 0; i < arraySize; i++) {
              Constant *elemConst = nullptr;
              if (i < initList->elements.size()) {
                auto lit =
                    std::dynamic_pointer_cast<Literal>(initList->elements[i]);
                if (!lit)
                  throw runtime_error(
                      "Global init list must contain literals only.");
                if (lit->type == Literal::LiteralType::Int)
                  elemConst = ConstantInt::get(Type::getInt32Ty(context),
                                               lit->intValue);
                else if (lit->type == Literal::LiteralType::Float)
                  elemConst = ConstantFP::get(Type::getFloatTy(context),
                                              lit->floatValue);
                else if (lit->type == Literal::LiteralType::Double)
                  elemConst = ConstantFP::get(Type::getDoubleTy(context),
                                              lit->doubleValue);
                else if (lit->type == Literal::LiteralType::Char)
                  elemConst = ConstantInt::get(Type::getInt8Ty(context),
                                               lit->charValue);
                else if (lit->type == Literal::LiteralType::Bool)
                  elemConst = ConstantInt::get(Type::getInt1Ty(context),
                                               lit->boolValue);
                else
                  throw runtime_error(
                      "Unsupported literal in global initializer.");
              } else {
                elemConst = Constant::getNullValue(arrayTy->getElementType());
              }
              elems.push_back(elemConst);
            }
            Constant *arrayInit = ConstantArray::get(arrayTy, elems);
            gVar->setInitializer(arrayInit);
          } else if (auto lit = std::dynamic_pointer_cast<Literal>(
                         singleDecl->initializer.value())) {
            Constant *initVal = nullptr;
            if (lit->type == Literal::LiteralType::String) {
              auto strConst =
                  ConstantDataArray::getString(context, lit->stringValue, true);
              if (auto arrayTy = dyn_cast<ArrayType>(varType)) {
                if (!arrayTy->getElementType()->isIntegerTy(8)) {
                  throw runtime_error("CodeGenerator Error: String literal "
                                      "initializer for non-char array.");
                }
                std::vector<Constant *> chars;
                chars.reserve(arrayTy->getNumElements());
                for (uint64_t i = 0; i < arrayTy->getNumElements(); ++i) {
                  char c = (i < lit->stringValue.size()) ? lit->stringValue[i]
                                                         : '\0';
                  chars.push_back(
                      ConstantInt::get(Type::getInt8Ty(context), c));
                }
                initVal = ConstantArray::get(arrayTy, chars);
              } else if (varType->isPointerTy()) {
                auto *strGV =
                    new GlobalVariable(*module, strConst->getType(), true,
                                       GlobalValue::PrivateLinkage, strConst,
                                       singleDecl->name + ".str");
                initVal = ConstantExpr::getBitCast(strGV, varType);
              } else {
                throw runtime_error(
                    "CodeGenerator Error: Unsupported string initializer in "
                    "global var declaration.");
              }
            } else if (lit->type == Literal::LiteralType::Int)
              initVal =
                  ConstantInt::get(Type::getInt32Ty(context), lit->intValue);
            else if (lit->type == Literal::LiteralType::Float)
              initVal =
                  ConstantFP::get(Type::getFloatTy(context), lit->floatValue);
            else if (lit->type == Literal::LiteralType::Double)
              initVal =
                  ConstantFP::get(Type::getDoubleTy(context), lit->doubleValue);
            else if (lit->type == Literal::LiteralType::Char)
              initVal =
                  ConstantInt::get(Type::getInt8Ty(context), lit->charValue);
            else if (lit->type == Literal::LiteralType::Bool)
              initVal =
                  ConstantInt::get(Type::getInt1Ty(context), lit->boolValue);
            else
              throw runtime_error(
                  "CodeGenerator Error: Unsupported literal in global init.");
            // possibly float <-> double
            if (initVal->getType() != varType) {
              if (initVal->getType()->isFloatingPointTy() &&
                  varType->isFloatingPointTy()) {
                auto litVal = (lit->type == Literal::LiteralType::Double)
                                  ? (float)lit->doubleValue
                                  : (double)lit->floatValue;
                initVal = ConstantFP::get(varType, litVal);
              } else if (initVal->getType()->isPointerTy() &&
                         varType->isPointerTy()) {
                initVal = ConstantExpr::getBitCast(initVal, varType);
              } else if (initVal->getType()->isArrayTy() &&
                         varType->isArrayTy()) {
                if (auto arrayTy = dyn_cast<ArrayType>(varType)) {
                  std::vector<Constant *> chars;
                  std::string str = lit->stringValue;
                  for (uint64_t i = 0; i < arrayTy->getNumElements(); ++i) {
                    char c = (i < str.size()) ? str[i] : '\0';
                    chars.push_back(
                        ConstantInt::get(Type::getInt8Ty(context), c));
                  }
                  initVal = ConstantArray::get(arrayTy, chars);
                }
              } else if (initVal->getType()->isIntegerTy() &&
                         varType->isIntegerTy()) {
                if (auto *intConst = dyn_cast<ConstantInt>(initVal)) {
                  initVal = ConstantInt::get(varType, intConst->getValue());
                } else {
                  auto *srcIntTy = cast<IntegerType>(initVal->getType());
                  auto *dstIntTy = cast<IntegerType>(varType);
                  Instruction::CastOps op;
                  if (dstIntTy->getBitWidth() >= srcIntTy->getBitWidth()) {
                    op = srcIntTy->getBitWidth() == 1 ? Instruction::ZExt
                                                      : Instruction::SExt;
                  } else {
                    op = Instruction::Trunc;
                  }
                  initVal = ConstantExpr::getCast(op, initVal, varType);
                }
              } else {
                throw runtime_error(
                    "CodeGenerator Error: Incompatible initializer type in "
                    "global var declaration.");
              }
            }
            gVar->setInitializer(initVal);
          } else {
            throw runtime_error("CodeGenerator Error: Global var init must be "
                                "literal or init list.");
          }
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
      std::cerr << "[DEBUG] generateCode: Unknown declaration type\n";
    }
  }

  // 2) Then handle function declarations
  for (const auto &decl : program->declarations) {
    if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclaration>(decl)) {
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
