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

void CodeGenerator::generateFunction(
    const shared_ptr<FunctionDeclaration> &funcDecl) {
  llvm::Type *retTy = getLLVMType(funcDecl->returnType);
  vector<Type *> paramTys;
  for (auto &param : funcDecl->parameters) {
    paramTys.push_back(getLLVMType(param.first));
  }
  bool hasBody = (funcDecl->body != nullptr);
  Function *function =
      getOrCreateFunctionInModule(funcDecl->name, retTy, paramTys, hasBody);
  if (!hasBody)
    return;
  if (function->empty()) {
    BasicBlock *entryBB = BasicBlock::Create(context, "entry", function);
    builder.SetInsertPoint(entryBB);

    localVariables.clear();

    size_t i = 0;
    for (auto &arg : function->args()) {
      const auto &paramName = funcDecl->parameters[i].second;
      arg.setName(paramName);
      AllocaInst *alloc =
          builder.CreateAlloca(arg.getType(), nullptr, paramName);
      builder.CreateStore(&arg, alloc);
      localVariables[paramName] = alloc;
      i++;
    }

    auto compound =
        std::dynamic_pointer_cast<CompoundStatement>(funcDecl->body);
    if (!compound) {
      throw runtime_error(
          "CodeGenerator Error: Function body is not a CompoundStatement.");
    }

    generateStatement(compound);

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
  } else {
    throw runtime_error(
        "CodeGenerator Error: Unexpected redefinition encountered for '" +
        funcDecl->name + "'.");
  }
}
