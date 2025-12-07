#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <stdexcept>
#include <vector>

using namespace llvm;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;

Function *CodeGenerator::generateFunction(
    const shared_ptr<FunctionDeclaration> &funcDecl) {
  // Get the return type
  Type *returnType = getLLVMType(funcDecl->returnType);

  // Get parameter types
  vector<Type *> paramTypes;
  for (const auto &param : funcDecl->parameters) {
    Type *paramType = getLLVMType(param.first); // param.first is the type
    paramTypes.push_back(paramType);
  }

  // Create function type
  FunctionType *funcType = FunctionType::get(returnType, paramTypes, false);

  // Create the function
  Function *function = Function::Create(funcType, Function::ExternalLinkage,
                                        funcDecl->name, module.get());

  // Set parameter names
  unsigned idx = 0;
  for (auto &arg : function->args()) {
    if (idx < funcDecl->parameters.size()) {
      arg.setName(funcDecl->parameters[idx].second); // param.second is the name
    }
    idx++;
  }

  // If the function has a body, generate it
  if (funcDecl->body) {
    // Create the entry block
    BasicBlock *entryBlock = BasicBlock::Create(context, "entry", function);
    builder.SetInsertPoint(entryBlock);

    // Set up local scope
    pushLocalScope();

    // Allocate parameters to local variables
    idx = 0;
    for (auto &arg : function->args()) {
      if (idx < funcDecl->parameters.size()) {
        string paramName =
            funcDecl->parameters[idx].second; // param.second is the name

        // Create alloca for the parameter
        AllocaInst *alloca =
            builder.CreateAlloca(arg.getType(), nullptr, paramName);

        // Store the argument value
        builder.CreateStore(&arg, alloca);

        // Add to local variables
        localVariables[paramName] = alloca;
        localVarStack.back()[paramName] = alloca;
        declaredVarStack.back().insert(paramName);
      }
      idx++;
    }

    // Generate the function body
    generateStatement(funcDecl->body);

    // If the function doesn't end with a return statement, add one
    if (!builder.GetInsertBlock()->getTerminator()) {
      if (returnType->isVoidTy()) {
        builder.CreateRetVoid();
      } else {
        // For non-void functions, return a default value
        Value *defaultValue = nullptr;
        if (returnType->isIntegerTy(32)) {
          defaultValue = ConstantInt::get(returnType, 0);
        } else if (returnType->isFloatTy()) {
          defaultValue = ConstantFP::get(returnType, 0.0f);
        } else if (returnType->isDoubleTy()) {
          defaultValue = ConstantFP::get(returnType, 0.0);
        } else if (returnType->isIntegerTy(8)) {
          defaultValue = ConstantInt::get(returnType, 0);
        } else if (returnType->isIntegerTy(1)) {
          defaultValue = ConstantInt::get(returnType, 0);
        } else {
          defaultValue = Constant::getNullValue(returnType);
        }
        builder.CreateRet(defaultValue);
      }
    }

    // Pop local scope
    popLocalScope();
  }

  return function;
}

Function *
CodeGenerator::getOrCreateFunctionInModule(const string &name, Type *returnType,
                                           const vector<Type *> &paramTypes,
                                           bool isDefinition) {
  // Check if function already exists
  Function *existingFunction = module->getFunction(name);
  if (existingFunction) {
    // Verify that the existing function has the same signature
    FunctionType *existingType = existingFunction->getFunctionType();
    if (existingType->getReturnType() != returnType ||
        existingType->getNumParams() != paramTypes.size()) {
      throw runtime_error(
          "CodeGenerator Error: Function signature mismatch for " + name);
    }
    for (unsigned i = 0; i < paramTypes.size(); ++i) {
      if (existingType->getParamType(i) != paramTypes[i]) {
        throw runtime_error(
            "CodeGenerator Error: Function parameter type mismatch for " +
            name);
      }
    }
    return existingFunction;
  }

  // Create new function
  FunctionType *funcType = FunctionType::get(returnType, paramTypes, false);
  Function *function =
      Function::Create(funcType, Function::ExternalLinkage, name, module.get());

  if (!isDefinition) {
    function->setLinkage(Function::ExternalLinkage);
  }

  return function;
}
