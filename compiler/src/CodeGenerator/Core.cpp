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
}

std::unique_ptr<Module>
CodeGenerator::generateCode(const shared_ptr<Program> &program) {
  // Process global declarations.
  for (const auto &decl : program->declarations) {
    if (auto varDecl = std::dynamic_pointer_cast<VariableDeclaration>(decl)) {
      llvm::Type *varType = getLLVMType(varDecl->type);
      // NEW: If there are array dimensions, wrap the base type.
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
      GlobalVariable *gVar = new GlobalVariable(*module, varType, false,
                                                GlobalValue::ExternalLinkage,
                                                nullptr, varDecl->name);
      if (varDecl->initializer) {
        if (auto lit = std::dynamic_pointer_cast<Literal>(
                varDecl->initializer.value())) {
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
                                "in global initializer.");

          if (initVal->getType() != varType) {
            if (initVal->getType()->isFloatingPointTy() &&
                varType->isFloatingPointTy()) {
              if (initVal->getType()->getFPMantissaWidth() >
                  varType->getFPMantissaWidth())
                initVal = ConstantFP::get(varType, (float)lit->doubleValue);
              else
                initVal = ConstantFP::get(varType, (double)lit->floatValue);
            } else {
              throw runtime_error(
                  "CodeGenerator Error: Incompatible initializer type in "
                  "global variable declaration.");
            }
          }
          gVar->setInitializer(initVal);
        } else {
          throw runtime_error("CodeGenerator Error: Global variable "
                              "initializer must be a literal.");
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
          throw runtime_error("CodeGenerator Error: Unsupported type in global "
                              "variable declaration.");
        gVar->setInitializer(defaultVal);
      }
    } else if (auto multiDecl =
                   std::dynamic_pointer_cast<MultiVariableDeclaration>(decl)) {
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
          if (auto lit = std::dynamic_pointer_cast<Literal>(
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
              throw runtime_error("CodeGenerator Error: Unsupported literal "
                                  "type in global initializer.");
            if (initVal->getType() != varType) {
              if (initVal->getType()->isFloatingPointTy() &&
                  varType->isFloatingPointTy()) {
                if (initVal->getType()->getFPMantissaWidth() >
                    varType->getFPMantissaWidth())
                  initVal = ConstantFP::get(varType, (float)lit->doubleValue);
                else
                  initVal = ConstantFP::get(varType, (double)lit->floatValue);
              } else {
                throw runtime_error(
                    "CodeGenerator Error: Incompatible initializer type in "
                    "global variable declaration.");
              }
            }
            gVar->setInitializer(initVal);
          } else {
            throw runtime_error("CodeGenerator Error: Global variable "
                                "initializer must be a literal.");
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
            throw runtime_error("CodeGenerator Error: Unsupported type in "
                                "global variable declaration.");
          gVar->setInitializer(defaultVal);
        }
      }
    } else if (auto enumDecl =
                   std::dynamic_pointer_cast<EnumDeclaration>(decl)) {
      for (size_t i = 0; i < enumDecl->enumerators.size(); ++i) {
        string enumName = enumDecl->enumerators[i].first;
        int value = enumDecl->enumeratorValues[i];
        Constant *initVal = ConstantInt::get(Type::getInt32Ty(context), value);
        GlobalVariable *gEnum =
            new GlobalVariable(*module, Type::getInt32Ty(context), true,
                               GlobalValue::ExternalLinkage, initVal, enumName);
      }
    }
  }

  // Function declarations are handled in generateFunction.
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
    // Extract the tag (name) of the union.
    std::string tag = type.substr(6);
    auto it = unionRegistry.find(tag);
    if (it == unionRegistry.end()) {
      throw runtime_error("CodeGenerator Error: Unknown union type '" + type +
                          "'.");
    }
    int maxSize = 0;
    // Initialize DataLayout using a pointer to the module.
    DataLayout dl(module.get());
    // Compute the maximum size among the union members.
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
        throw runtime_error(
            "CodeGenerator Error: Nested unions not supported.");
      else if (member->type.rfind("struct ", 0) == 0) {
        llvm::Type *structTy = getLLVMType(member->type);
        uint64_t size = dl.getTypeAllocSize(structTy);
        memberSize = static_cast<int>(size);
      } else
        throw runtime_error(
            "CodeGenerator Error: Unsupported union member type '" +
            member->type + "'.");
      if (memberSize > maxSize)
        maxSize = memberSize;
    }
    // Ensure we never pass zero or negative size.
    if (maxSize <= 0)
      maxSize = 1;
    return ArrayType::get(Type::getInt8Ty(context), maxSize);
  } else if (type.rfind("struct ", 0) == 0) {
    std::string tag = type.substr(7);
    auto it = structRegistry.find(tag);
    if (it == structRegistry.end()) {
      throw runtime_error("CodeGenerator Error: Unknown struct type '" + type +
                          "'.");
    }
    vector<Type *> memberTypes;
    for (auto &member : it->second->members) {
      memberTypes.push_back(getLLVMType(member->type));
    }
    StructType *structType =
        StructType::create(context, memberTypes, tag, false);
    return structType;
  } else
    throw runtime_error("CodeGenerator Error: Unsupported type '" + type +
                        "'.");
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

llvm::Function *CodeGenerator::getOrCreateFunctionInModule(
    const std::string &name, llvm::Type *returnType,
    const vector<Type *> &paramTypes, bool isDefinition) {
  FunctionType *fType = FunctionType::get(returnType, paramTypes, false);
  if (Function *existingFn = module->getFunction(name)) {
    FunctionType *existingType = existingFn->getFunctionType();
    if (!functionSignaturesMatch(existingType, fType)) {
      throw runtime_error(
          "CodeGenerator Error: Conflicting function signature for '" + name +
          "'.");
    }
    if (isDefinition && !existingFn->empty()) {
      throw runtime_error("CodeGenerator Error: Function '" + name +
                          "' is already defined.");
    }
    return existingFn;
  }
  Function *newFn =
      Function::Create(fType, Function::ExternalLinkage, name, module.get());
  return newFn;
}

llvm::Function *CodeGenerator::generateFunction(
    const shared_ptr<FunctionDeclaration> &funcDecl) {
  llvm::Type *retTy = getLLVMType(funcDecl->returnType);
  vector<Type *> paramTys;
  for (auto &param : funcDecl->parameters) {
    paramTys.push_back(getLLVMType(param.first));
  }
  bool hasBody = (funcDecl->body != nullptr);
  llvm::Function *function =
      getOrCreateFunctionInModule(funcDecl->name, retTy, paramTys, hasBody);
  if (!hasBody)
    return function;
  if (function->empty()) {
    BasicBlock *entryBB = BasicBlock::Create(context, "entry", function);
    builder.SetInsertPoint(entryBB);

    // Clear any previous local state and push a new local scope.
    localVarStack.clear();
    pushLocalScope();

    // For each function parameter, allocate space in the current local scope.
    size_t i = 0;
    for (auto &arg : function->args()) {
      const auto &paramName = funcDecl->parameters[i].second;
      arg.setName(paramName);
      AllocaInst *alloc =
          builder.CreateAlloca(arg.getType(), nullptr, paramName);
      builder.CreateStore(&arg, alloc);
      // Store in the current local scope.
      localVarStack.back()[paramName] = alloc;
      // Record the declared type.
      declaredTypes[paramName] = arg.getType();
      i++;
    }

    // Generate code for the function body.
    auto compound =
        std::dynamic_pointer_cast<CompoundStatement>(funcDecl->body);
    if (!compound) {
      throw runtime_error(
          "CodeGenerator Error: Function body is not a CompoundStatement.");
    }
    generateStatement(compound);

    // If the current basic block is not terminated, add an appropriate return.
    if (!builder.GetInsertBlock()->getTerminator()) {
      if (funcDecl->returnType == "void") {
        builder.CreateRetVoid();
      } else if (funcDecl->returnType == "int") {
        builder.CreateRet(ConstantInt::get(Type::getInt32Ty(context), 0));
      } else if (funcDecl->returnType == "float") {
        builder.CreateRet(ConstantFP::get(Type::getFloatTy(context), 0.0f));
      } else if (funcDecl->returnType == "double") {
        builder.CreateRet(ConstantFP::get(Type::getDoubleTy(context), 0.0));
      } else if (funcDecl->returnType == "char") {
        builder.CreateRet(ConstantInt::get(Type::getInt8Ty(context), 0));
      } else if (funcDecl->returnType == "bool") {
        builder.CreateRet(ConstantInt::get(Type::getInt1Ty(context), 0));
      } else {
        throw runtime_error("CodeGenerator Error: Unsupported return type '" +
                            funcDecl->returnType + "'.");
      }
    }
    return function;
  } else {
    throw runtime_error(
        "CodeGenerator Error: Unexpected redefinition encountered for '" +
        funcDecl->name + "'.");
  }
}
