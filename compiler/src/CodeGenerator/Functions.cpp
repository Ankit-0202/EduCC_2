#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "Debug.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <iostream>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/Alignment.h>
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
  FunctionType *funcType =
      FunctionType::get(returnType, paramTypes, funcDecl->isVarArgs);

  if (educcDebugEnabled())
    std::cerr << "[DEBUG] generateFunction: '" << funcDecl->name
              << "' varargs=" << (funcDecl->isVarArgs ? "true" : "false")
              << std::endl;

  // Reuse an existing prototype if it matches, otherwise recreate.
  Function *function = module->getFunction(funcDecl->name);
  if (function) {
    if (function->getFunctionType() != funcType) {
      function->eraseFromParent();
      function = nullptr;
    }
  }
  if (!function) {
    function = Function::Create(funcType, Function::ExternalLinkage,
                                funcDecl->name, module.get());
  }

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
    labelBlocks.clear();
    // Create the entry block
    BasicBlock *entryBlock = BasicBlock::Create(context, "entry", function);
    builder.SetInsertPoint(entryBlock);

    // Add a small padding buffer to reduce accidental stack corruption from
    // aggressive local packing.
    auto *padTy = ArrayType::get(Type::getInt8Ty(context), 64);
    AllocaInst *framePad = builder.CreateAlloca(padTy, nullptr, "frame.pad");
    framePad->setAlignment(llvm::Align(16));
    builder.CreateStore(Constant::getNullValue(padTy), framePad, true);

    // Set up local scope
    pushLocalScope();

    // Allocate parameters to local variables
    idx = 0;
    auto extractDimStrings = [](const std::string &typeStr) {
      std::vector<std::string> dims;
      size_t pos = 0;
      while ((pos = typeStr.find('[', pos)) != std::string::npos) {
        size_t end = typeStr.find(']', pos);
        if (end == std::string::npos)
          break;
        std::string dim = typeStr.substr(pos + 1, end - pos - 1);
        dims.push_back(dim);
        pos = end + 1;
      }
      return dims;
    };
    auto dimValueFromString = [&](const std::string &dim) -> llvm::Value * {
      if (dim.empty())
        return nullptr;
      try {
        long long v = std::stoll(dim);
        return llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), v);
      } catch (...) {
      }
      llvm::Value *ptr = lookupLocalVar(dim);
      if (!ptr)
        return nullptr;
      llvm::Type *pointeeTy = nullptr;
      auto it = declaredTypes.find(dim);
      if (it != declaredTypes.end())
        pointeeTy = it->second;
      if (!pointeeTy)
        pointeeTy = llvm::Type::getInt32Ty(context);
      llvm::Value *loaded =
          builder.CreateLoad(pointeeTy, ptr, dim + ".ld.param");
      if (loaded->getType()->isIntegerTy(64))
        return loaded;
      if (loaded->getType()->isIntegerTy())
        return builder.CreateIntCast(loaded, llvm::Type::getInt64Ty(context),
                                     true, dim + ".cast");
      return builder.CreatePtrToInt(loaded, llvm::Type::getInt64Ty(context),
                                    dim + ".ptrint");
    };
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
        auto existingTy = declaredTypes.find(paramName);
        if (existingTy != declaredTypes.end())
          typeShadowStack[paramName].push_back(existingTy->second);
        auto existingStr = declaredTypeStrings.find(paramName);
        if (existingStr != declaredTypeStrings.end())
          typeStringShadowStack[paramName].push_back(existingStr->second);
        declaredTypes[paramName] = arg.getType();
        declaredTypeStrings[paramName] = funcDecl->parameters[idx].first;
        auto dimStrs = extractDimStrings(funcDecl->parameters[idx].first);
        std::vector<llvm::Value *> dimVals;
        for (const auto &d : dimStrs) {
          if (auto *v = dimValueFromString(d))
            dimVals.push_back(v);
        }
        if (!dimVals.empty())
          dynamicArrayDimensions[paramName] = dimVals;
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
    labelBlocks.clear();
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
