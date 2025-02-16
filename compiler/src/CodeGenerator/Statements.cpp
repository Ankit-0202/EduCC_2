#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/raw_ostream.h>
#include <stdexcept>
#include <vector>

using namespace llvm;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;

bool CodeGenerator::generateStatement(const StatementPtr &stmt) {
  if (auto compound = std::dynamic_pointer_cast<CompoundStatement>(stmt)) {
    bool terminated = false;
    for (auto &substmt : compound->statements) {
      terminated = generateStatement(substmt);
      if (terminated)
        break;
    }
    return terminated;
  } else if (auto exprStmt =
                 std::dynamic_pointer_cast<ExpressionStatement>(stmt)) {
    generateExpression(exprStmt->expression);
    return false;
  } else if (auto varDeclStmt =
                 std::dynamic_pointer_cast<VariableDeclarationStatement>(
                     stmt)) {
    generateVariableDeclarationStatement(varDeclStmt);
    return false;
  } else if (auto multiVarDeclStmt =
                 std::dynamic_pointer_cast<MultiVariableDeclarationStatement>(
                     stmt)) {
    for (auto &singleDeclStmt : multiVarDeclStmt->declarations) {
      generateVariableDeclarationStatement(singleDeclStmt);
    }
    return false;
  } else if (auto retStmt = std::dynamic_pointer_cast<ReturnStatement>(stmt)) {
    llvm::Value *retVal = generateExpression(retStmt->expression);
    llvm::Function *currentFunction = builder.GetInsertBlock()->getParent();
    llvm::Type *expectedType = currentFunction->getReturnType();
    if (retVal->getType() != expectedType) {
      if (retVal->getType()->isIntegerTy(1) && expectedType->isIntegerTy(32)) {
        retVal = builder.CreateZExt(retVal, expectedType, "zexttmp");
      } else if (retVal->getType()->isIntegerTy() &&
                 expectedType->isIntegerTy()) {
        retVal =
            builder.CreateIntCast(retVal, expectedType, false, "intcasttmp");
      } else {
        throw runtime_error("CodeGenerator Error: Return value type does not "
                            "match function return type.");
      }
    }
    builder.CreateRet(retVal);
    return true;
  } else if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(stmt)) {
    llvm::Value *condVal = generateExpression(ifStmt->condition);
    if (condVal->getType() != llvm::Type::getInt1Ty(context)) {
      condVal = builder.CreateICmpNE(
          condVal, ConstantInt::get(condVal->getType(), 0), "ifcond");
    }
    llvm::Function *theFunction = builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *thenBB =
        llvm::BasicBlock::Create(context, "then", theFunction);
    llvm::BasicBlock *elseBB =
        llvm::BasicBlock::Create(context, "else", theFunction);
    llvm::BasicBlock *mergeBB =
        llvm::BasicBlock::Create(context, "ifcont", theFunction);
    builder.CreateCondBr(condVal, thenBB, elseBB);

    builder.SetInsertPoint(thenBB);
    bool thenTerminated = generateStatement(ifStmt->thenBranch);
    if (!thenTerminated) {
      builder.CreateBr(mergeBB);
    }

    builder.SetInsertPoint(elseBB);
    bool elseTerminated = false;
    if (ifStmt->elseBranch)
      elseTerminated = generateStatement(ifStmt->elseBranch.value());
    if (!elseTerminated) {
      builder.CreateBr(mergeBB);
    }

    builder.SetInsertPoint(mergeBB);
    return false;
  } else if (auto whileStmt = std::dynamic_pointer_cast<WhileStatement>(stmt)) {
    llvm::Function *theFunction = builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *condBB =
        llvm::BasicBlock::Create(context, "while.cond", theFunction);
    llvm::BasicBlock *bodyBB =
        llvm::BasicBlock::Create(context, "while.body", theFunction);
    llvm::BasicBlock *afterBB =
        llvm::BasicBlock::Create(context, "while.after", theFunction);
    builder.CreateBr(condBB);
    builder.SetInsertPoint(condBB);
    llvm::Value *condVal = generateExpression(whileStmt->condition);
    if (condVal->getType() != llvm::Type::getInt1Ty(context)) {
      condVal = builder.CreateICmpNE(
          condVal, ConstantInt::get(condVal->getType(), 0), "whilecond");
    }
    builder.CreateCondBr(condVal, bodyBB, afterBB);
    builder.SetInsertPoint(bodyBB);
    bool bodyTerminated = generateStatement(whileStmt->body);
    if (!bodyTerminated) {
      builder.CreateBr(condBB);
    }
    builder.SetInsertPoint(afterBB);
    return false;
  } else if (auto forStmt = std::dynamic_pointer_cast<ForStatement>(stmt)) {
    if (forStmt->initializer)
      generateStatement(forStmt->initializer);
    llvm::Function *theFunction = builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *condBB =
        llvm::BasicBlock::Create(context, "for.cond", theFunction);
    llvm::BasicBlock *bodyBB =
        llvm::BasicBlock::Create(context, "for.body", theFunction);
    llvm::BasicBlock *incrBB =
        llvm::BasicBlock::Create(context, "for.incr", theFunction);
    llvm::BasicBlock *afterBB =
        llvm::BasicBlock::Create(context, "for.after", theFunction);
    builder.CreateBr(condBB);

    builder.SetInsertPoint(condBB);
    llvm::Value *condVal = nullptr;
    if (forStmt->condition) {
      condVal = generateExpression(forStmt->condition);
      if (condVal->getType() != llvm::Type::getInt1Ty(context)) {
        condVal = builder.CreateICmpNE(
            condVal, ConstantInt::get(condVal->getType(), 0), "forcond");
      }
    } else {
      condVal = ConstantInt::get(llvm::Type::getInt1Ty(context), 1);
    }
    builder.CreateCondBr(condVal, bodyBB, afterBB);

    builder.SetInsertPoint(bodyBB);
    bool bodyTerminated = generateStatement(forStmt->body);
    if (!bodyTerminated) {
      builder.CreateBr(incrBB);
    }

    builder.SetInsertPoint(incrBB);
    if (forStmt->increment) {
      generateExpression(forStmt->increment);
    }
    builder.CreateBr(condBB);

    builder.SetInsertPoint(afterBB);
    return false;
  } else if (auto switchStmt =
                 std::dynamic_pointer_cast<SwitchStatement>(stmt)) {
    llvm::Value *condVal = generateExpression(switchStmt->expression);
    if (!condVal->getType()->isIntegerTy()) {
      throw runtime_error(
          "CodeGenerator Error: Switch expression must be of integer type.");
    }
    llvm::Function *theFunction = builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *defaultBB =
        llvm::BasicBlock::Create(context, "switch.default", theFunction);

    SwitchInst *switchInst =
        builder.CreateSwitch(condVal, defaultBB, switchStmt->cases.size());
    for (auto &casePair : switchStmt->cases) {
      if (!casePair.first.has_value()) {
        throw runtime_error(
            "CodeGenerator Error: Case label missing in case clause.");
      }
      llvm::Value *caseVal = generateExpression(casePair.first.value());
      if (!isa<ConstantInt>(caseVal)) {
        throw runtime_error(
            "CodeGenerator Error: Case label must be a constant integer.");
      }
      llvm::BasicBlock *caseBB =
          llvm::BasicBlock::Create(context, "switch.case", theFunction);
      switchInst->addCase(cast<ConstantInt>(caseVal), caseBB);
      builder.SetInsertPoint(caseBB);
      bool terminated = generateStatement(casePair.second);
      if (!terminated) {
        builder.CreateBr(defaultBB);
      }
    }
    builder.SetInsertPoint(defaultBB);
    if (switchStmt->defaultCase.has_value()) {
      bool terminated = generateStatement(switchStmt->defaultCase.value());
      if (!terminated) {
        builder.CreateUnreachable();
      }
    } else {
      builder.CreateUnreachable();
    }
    return false;
  } else {
    throw runtime_error("CodeGenerator Error: Unsupported statement type.");
  }
}

void CodeGenerator::generateVariableDeclarationStatement(
    const shared_ptr<VariableDeclarationStatement> &varDeclStmt) {
  llvm::Type *varTy = getLLVMType(varDeclStmt->type);
  AllocaInst *alloc =
      builder.CreateAlloca(varTy, nullptr, varDeclStmt->name.c_str());
  localVariables[varDeclStmt->name] = alloc;
  // Record the declared type.
  declaredTypes[varDeclStmt->name] = varTy;

  if (varDeclStmt->initializer) {
    llvm::Value *initVal = generateExpression(varDeclStmt->initializer.value());
    if (initVal->getType() != varTy) {
      if (initVal->getType()->isFloatingPointTy() &&
          varTy->isFloatingPointTy()) {
        if (initVal->getType()->getFPMantissaWidth() >
            varTy->getFPMantissaWidth())
          initVal = builder.CreateFPTrunc(initVal, varTy, "fptrunc");
        else
          initVal = builder.CreateFPExt(initVal, varTy, "fpext");
      } else {
        throw runtime_error("CodeGenerator Error: Incompatible initializer "
                            "type in local variable declaration.");
      }
    }
    builder.CreateStore(initVal, alloc);
  }
}
