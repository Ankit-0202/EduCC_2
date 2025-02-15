#include "CodeGenerator.hpp"
#include "AST.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
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
      module(std::make_unique<Module>("main_module", context)) {}

std::unique_ptr<Module>
CodeGenerator::generateCode(const shared_ptr<Program> &program) {
  // Process global declarations.
  for (const auto &decl : program->declarations) {
    if (auto varDecl = std::dynamic_pointer_cast<VariableDeclaration>(decl)) {
      llvm::Type *varType = getLLVMType(varDecl->type);
      GlobalVariable *gVar = new GlobalVariable(*module, varType, false,
                                                GlobalValue::ExternalLinkage,
                                                nullptr, varDecl->name);
      if (varDecl->initializer) {
        if (auto lit = std::dynamic_pointer_cast<Literal>(
                varDecl->initializer.value())) {
          Constant *initVal = nullptr;
          if (std::holds_alternative<int>(lit->value))
            initVal = ConstantInt::get(Type::getInt32Ty(context),
                                       std::get<int>(lit->value));
          else if (std::holds_alternative<float>(lit->value))
            initVal = ConstantFP::get(Type::getFloatTy(context),
                                      std::get<float>(lit->value));
          else if (std::holds_alternative<double>(lit->value))
            initVal = ConstantFP::get(Type::getDoubleTy(context),
                                      std::get<double>(lit->value));
          else if (std::holds_alternative<char>(lit->value))
            initVal = ConstantInt::get(Type::getInt8Ty(context),
                                       std::get<char>(lit->value));
          else if (std::holds_alternative<bool>(lit->value))
            initVal = ConstantInt::get(Type::getInt1Ty(context),
                                       std::get<bool>(lit->value));
          else
            throw runtime_error("CodeGenerator Error: Unsupported literal type in global initializer.");

          if (initVal->getType() != varType) {
            if (initVal->getType()->isFloatingPointTy() &&
                varType->isFloatingPointTy()) {
              if (initVal->getType()->getFPMantissaWidth() >
                  varType->getFPMantissaWidth())
                initVal = ConstantFP::get(varType,
                                          (float)std::get<double>(lit->value));
              else
                initVal = ConstantFP::get(varType,
                                          (double)std::get<float>(lit->value));
            } else {
              throw runtime_error("CodeGenerator Error: Incompatible initializer type in global variable declaration.");
            }
          }
          gVar->setInitializer(initVal);
        } else {
          throw runtime_error("CodeGenerator Error: Global variable initializer must be a literal.");
        }
      } else {
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
          throw runtime_error("CodeGenerator Error: Unsupported type in global variable declaration.");
        gVar->setInitializer(defaultVal);
      }
    } else if (auto multiDecl = std::dynamic_pointer_cast<MultiVariableDeclaration>(decl)) {
      for (const auto &singleDecl : multiDecl->declarations) {
        llvm::Type *varType = getLLVMType(singleDecl->type);
        GlobalVariable *gVar = new GlobalVariable(*module, varType, false,
                                                  GlobalValue::ExternalLinkage,
                                                  nullptr, singleDecl->name);
        if (singleDecl->initializer) {
          if (auto lit = std::dynamic_pointer_cast<Literal>(singleDecl->initializer.value())) {
            Constant *initVal = nullptr;
            if (std::holds_alternative<int>(lit->value))
              initVal = ConstantInt::get(Type::getInt32Ty(context),
                                         std::get<int>(lit->value));
            else if (std::holds_alternative<float>(lit->value))
              initVal = ConstantFP::get(Type::getFloatTy(context),
                                        std::get<float>(lit->value));
            else if (std::holds_alternative<double>(lit->value))
              initVal = ConstantFP::get(Type::getDoubleTy(context),
                                        std::get<double>(lit->value));
            else if (std::holds_alternative<char>(lit->value))
              initVal = ConstantInt::get(Type::getInt8Ty(context),
                                         std::get<char>(lit->value));
            else if (std::holds_alternative<bool>(lit->value))
              initVal = ConstantInt::get(Type::getInt1Ty(context),
                                         std::get<bool>(lit->value));
            else
              throw runtime_error("CodeGenerator Error: Unsupported literal type in global initializer.");
            if (initVal->getType() != varType) {
              if (initVal->getType()->isFloatingPointTy() &&
                  varType->isFloatingPointTy()) {
                if (initVal->getType()->getFPMantissaWidth() > varType->getFPMantissaWidth())
                  initVal = ConstantFP::get(varType, (float)std::get<double>(lit->value));
                else
                  initVal = ConstantFP::get(varType, (double)std::get<float>(lit->value));
              } else {
                throw runtime_error("CodeGenerator Error: Incompatible initializer type in global variable declaration.");
              }
            }
            gVar->setInitializer(initVal);
          } else {
            throw runtime_error("CodeGenerator Error: Global variable initializer must be a literal.");
          }
        } else {
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
            throw runtime_error("CodeGenerator Error: Unsupported type in global variable declaration.");
          gVar->setInitializer(defaultVal);
        }
      }
    } else if (auto enumDecl = std::dynamic_pointer_cast<EnumDeclaration>(decl)) {
      for (size_t i = 0; i < enumDecl->enumerators.size(); ++i) {
        string enumName = enumDecl->enumerators[i].first;
        int value = enumDecl->enumeratorValues[i];
        Constant *initVal = ConstantInt::get(Type::getInt32Ty(context), value);
        GlobalVariable *gEnum = new GlobalVariable(*module, Type::getInt32Ty(context), true,
                                                     GlobalValue::ExternalLinkage, initVal, enumName);
      }
    }
  }

  // Function declarations are handled in CodeGenerator_Functions.cpp

  for (const auto &decl : program->declarations) {
    if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclaration>(decl)) {
      generateFunction(funcDecl);
    }
  }

  if (verifyModule(*module, &errs())) {
    throw runtime_error("CodeGenerator Error: Module verification failed.");
  }
  return std::move(module);
}

llvm::Type *CodeGenerator::getLLVMType(const string &type) {
  if (type == "int")
    return Type::getInt32Ty(context);
  else if (type == "float")
    return Type::getFloatTy(context);
  else if (type == "char")
    return Type::getInt8Ty(context);
  else if (type == "double")
    return Type::getDoubleTy(context);
  else if (type == "bool")
    return Type::getInt1Ty(context);
  else if (type == "void")
    return Type::getVoidTy(context);
  else if (type.rfind("enum ", 0) == 0)
    return Type::getInt32Ty(context);
  else if (type.rfind("union ", 0) == 0) {
    std::string tag = type.substr(6);
    auto it = unionRegistry.find(tag);
    if (it == unionRegistry.end()) {
      throw runtime_error("CodeGenerator Error: Unknown union type '" + type + "'");
    }
    int maxSize = 0;
    for (auto &member : it->second->members) {
      int memberSize = 0;
      if (member->type == "int")
        memberSize = 4;
      else if (member->type == "float")
        memberSize = 4;
      else if (member->type == "char")
        memberSize = 1;
      else if (member->type == "double")
        memberSize = 8;
      else if (member->type == "bool")
        memberSize = 1;
      else if (member->type.rfind("enum ", 0) == 0)
        memberSize = 4;
      else if (member->type.rfind("union ", 0) == 0)
        throw runtime_error("CodeGenerator Error: Nested unions not supported.");
      else
        throw runtime_error("CodeGenerator Error: Unsupported union member type '" + member->type + "'.");
      if (memberSize > maxSize)
        maxSize = memberSize;
    }
    return ArrayType::get(Type::getInt8Ty(context), maxSize);
  } else
    throw runtime_error("CodeGenerator Error: Unsupported type '" + type + "'.");
}

static bool functionSignaturesMatch(FunctionType *existing, FunctionType *candidate) {
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

llvm::Function *CodeGenerator::getOrCreateFunctionInModule(const std::string &name, Type *returnType, const vector<Type *> &paramTypes, bool isDefinition) {
  FunctionType *fType = FunctionType::get(returnType, paramTypes, false);
  if (Function *existingFn = module->getFunction(name)) {
    FunctionType *existingType = existingFn->getFunctionType();
    if (!functionSignaturesMatch(existingType, fType)) {
      throw runtime_error("CodeGenerator Error: Conflicting function signature for '" + name + "'.");
    }
    if (isDefinition && !existingFn->empty()) {
      throw runtime_error("CodeGenerator Error: Function '" + name + "' is already defined.");
    }
    return existingFn;
  }
  Function *newFn = Function::Create(fType, Function::ExternalLinkage, name, module.get());
  return newFn;
}
