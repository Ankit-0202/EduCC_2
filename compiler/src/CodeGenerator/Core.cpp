// compiler/src/CodeGenerator/Core.cpp

#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <iostream>
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
  // Set a default data layout for the module.
  module->setDataLayout("e-m:o-i64:64-f80:128-n8:16:32:64-S128");
  // NOTE: Opaque pointers are enabled by default in LLVM 15+.
  // To call getElementType(), your LLVM must disable opaque pointers.
}

std::unique_ptr<Module>
CodeGenerator::generateCode(const shared_ptr<Program> &program) {
  // Process global declarations first.
  for (const auto &decl : program->declarations) {
    if (auto varDecl = std::dynamic_pointer_cast<VariableDeclaration>(decl)) {
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
          // single literal init
          Constant *initVal = nullptr;
          if (lit->type == Literal::LiteralType::Int)
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
        Constant *defaultVal = nullptr;
        if (varDecl->type == "int")
          defaultVal = ConstantInt::get(Type::getInt32Ty(context), 0);
        else if (varDecl->type == "float")
          defaultVal = ConstantFP::get(Type::getFloatTy(context), 0.0f);
        else if (varDecl->type == "char")
          defaultVal = ConstantInt::get(Type::getInt8Ty(context), 0);
        else if (varDecl->type == "double")
          defaultVal = ConstantFP::get(Type::getDoubleTy(context), 0.0);
        else if (varDecl->type == "bool")
          defaultVal = ConstantInt::get(Type::getInt1Ty(context), 0);
        else
          throw runtime_error("CodeGenerator Error: Unsupported type in global "
                              "var declaration.");
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
            if (lit->type == Literal::LiteralType::Int)
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
          Constant *defaultVal = nullptr;
          if (singleDecl->type == "int")
            defaultVal = ConstantInt::get(Type::getInt32Ty(context), 0);
          else if (singleDecl->type == "float")
            defaultVal = ConstantFP::get(Type::getFloatTy(context), 0.0f);
          else if (singleDecl->type == "char")
            defaultVal = ConstantInt::get(Type::getInt8Ty(context), 0);
          else if (singleDecl->type == "double")
            defaultVal = ConstantFP::get(Type::getDoubleTy(context), 0.0);
          else if (singleDecl->type == "bool")
            defaultVal = ConstantInt::get(Type::getInt1Ty(context), 0);
          else
            throw runtime_error(
                "CodeGenerator Error: Unsupported type in global var decl.");
          gVar->setInitializer(defaultVal);
        }
      }
    }

    else if (auto enumDecl = std::dynamic_pointer_cast<EnumDeclaration>(decl)) {
      for (size_t i = 0; i < enumDecl->enumerators.size(); ++i) {
        string enumName = enumDecl->enumerators[i].first;
        int value = enumDecl->enumeratorValues[i];
        Constant *initVal = ConstantInt::get(Type::getInt32Ty(context), value);
        GlobalVariable *gEnum =
            new GlobalVariable(*module, Type::getInt32Ty(context), true,
                               GlobalValue::ExternalLinkage, initVal, enumName);
      }
    }
    else if (auto unionDecl = std::dynamic_pointer_cast<UnionDeclaration>(decl)) {
      // Handle union declarations - register the type for later use
      if (!unionDecl->tag.has_value()) {
        // Anonymous union: skip type registration
        continue;
      }
      
      // Create LLVM struct type for the union
      // For unions, we need to find the largest member size
      int maxSize = 0;
      std::vector<Type*> memberTypes;
      
      for (const auto& member : unionDecl->members) {
        Type* memberType = getLLVMType(member->type);
        memberTypes.push_back(memberType);
        
        // Calculate member size
        int memberSize = 0;
        if (member->type == "int" || member->type == "float")
          memberSize = 4;
        else if (member->type == "char" || member->type == "bool")
          memberSize = 1;
        else if (member->type == "double")
          memberSize = 8;
        else if (member->type.rfind("enum ", 0) == 0)
          memberSize = 4;
        else {
          // For other types, we'll use a conservative size
          memberSize = 8;
        }
        if (memberSize > maxSize)
          maxSize = memberSize;
      }
      
      if (maxSize <= 0)
        maxSize = 1;
      
      // Create a struct type for the union (LLVM doesn't have native union types)
      // We'll use a struct with the largest member size
      StructType* unionType = StructType::create(context, unionDecl->tag.value());
      unionType->setBody(memberTypes, /*isPacked=*/true); // Packed for union-like behavior
      
      // Register the type in our type registry
      declaredTypes[unionDecl->tag.value()] = unionType;
    }
    else if (auto structDecl = std::dynamic_pointer_cast<StructDeclaration>(decl)) {
      // Handle struct declarations - register the type for later use
      if (!structDecl->tag.has_value()) {
        // Anonymous struct: skip type registration
        continue;
      }
      
      // Create LLVM struct type for the struct
      std::vector<Type*> memberTypes;
      for (const auto& member : structDecl->members) {
        Type* memberType = getLLVMType(member->type);
        memberTypes.push_back(memberType);
      }
      
      StructType* structType = StructType::create(context, structDecl->tag.value());
      structType->setBody(memberTypes, /*isPacked=*/false);
      
      // Register the type in our type registry
      declaredTypes[structDecl->tag.value()] = structType;
    }
  }

  // 2) Then handle function declarations
  for (const auto &decl : program->declarations) {
    if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclaration>(decl)) {
      generateFunction(funcDecl);
    }
  }

  // verify
  if (verifyModule(*module, &errs()))
    throw runtime_error("CodeGenerator Error: Module verification failed.");
  return std::move(module);
}

static bool functionSignaturesMatch(FunctionType *existing,
                                    FunctionType *candidate) {
  if (existing->getReturnType() != candidate->getReturnType())
    return false;
  if (existing->getNumParams() != candidate->getNumParams())
    return false;
  for (unsigned i = 0; i < existing->getNumParams(); ++i) {
    if (existing->getParamType(i) != candidate->getParamType(i))
      return false;
  }
  return true;
}
