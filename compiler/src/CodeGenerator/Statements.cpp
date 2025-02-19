#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "CodeGenerator/Helpers.hpp" // Use our helper functions
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
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

// Local Scope Management
void CodeGenerator::pushLocalScope() {
  localVarStack.push_back(unordered_map<string, Value *>());
  declaredVarStack.push_back(unordered_set<string>());
}

void CodeGenerator::popLocalScope() {
  if (localVarStack.empty() || declaredVarStack.empty())
    throw runtime_error("CodeGenerator Error: No local scope to pop.");
  for (const auto &name : declaredVarStack.back()) {
    declaredTypes.erase(name);
    declaredTypeStrings.erase(name);
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

// Note: Do NOT define generateLValue here. Its unique definition is in
// Expressions.cpp.

// generateVariableDeclaration and generateStatement implementations remain as
// before.
void CodeGenerator::generateVariableDeclaration(
    const shared_ptr<VariableDeclaration> &varDecl) {
  llvm::Type *baseType = getLLVMType(varDecl->type);
  if (!varDecl->dimensions.empty()) {
    for (auto it = varDecl->dimensions.rbegin();
         it != varDecl->dimensions.rend(); ++it) {
      llvm::Value *dimVal = generateExpression(*it);
      ConstantInt *constDim = dyn_cast<ConstantInt>(dimVal);
      if (!constDim)
        throw runtime_error(
            "CodeGenerator Error: Array dimension must be a constant integer.");
      uint64_t arraySize = constDim->getZExtValue();
      baseType = ArrayType::get(baseType, arraySize);
    }
  }
  llvm::Type *varTy = baseType;
  AllocaInst *alloc =
      builder.CreateAlloca(varTy, nullptr, varDecl->name.c_str());
  localVarStack.back()[varDecl->name] = alloc;
  declaredVarStack.back().insert(varDecl->name);
  declaredTypes[varDecl->name] = varTy;
  declaredTypeStrings[varDecl->name] = varDecl->type;
  if (varDecl->initializer) {
    llvm::Value *initVal = generateExpression(varDecl->initializer.value());
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

//
// generateStatement
//
bool CodeGenerator::generateStatement(const StatementPtr &stmt) {
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
    generateExpression(exprStmt->expression);
    return false;
  } else if (auto varDeclStmt =
                 std::dynamic_pointer_cast<VariableDeclarationStatement>(
                     stmt)) {
    generateVariableDeclaration(varDeclStmt->varDecl);
    return false;
  } else if (auto multiVarDeclStmt =
                 std::dynamic_pointer_cast<MultiVariableDeclarationStatement>(
                     stmt)) {
    for (auto &singleDecl : multiVarDeclStmt->declarations) {
      generateVariableDeclaration(singleDecl);
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
  } else if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(stmt)) {
    llvm::Value *condVal = generateExpression(ifStmt->condition);
    if (condVal->getType() != Type::getInt1Ty(context))
      condVal = builder.CreateICmpNE(
          condVal, ConstantInt::get(condVal->getType(), 0), "ifcond");
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
    builder.CreateBr(condBB);
    builder.SetInsertPoint(condBB);
    llvm::Value *condVal = generateExpression(whileStmt->condition);
    if (condVal->getType() != Type::getInt1Ty(context))
      condVal = builder.CreateICmpNE(
          condVal, ConstantInt::get(condVal->getType(), 0), "whilecond");
    builder.CreateCondBr(condVal, bodyBB, afterBB);
    builder.SetInsertPoint(bodyBB);
    bool bodyTerminated = generateStatement(whileStmt->body);
    if (!bodyTerminated)
      builder.CreateBr(condBB);
    builder.SetInsertPoint(afterBB);
    return false;
  } else if (auto forStmt = std::dynamic_pointer_cast<ForStatement>(stmt)) {
    if (forStmt->initializer)
      generateStatement(forStmt->initializer);
    Function *theFunction = builder.GetInsertBlock()->getParent();
    BasicBlock *condBB = BasicBlock::Create(context, "for.cond", theFunction);
    BasicBlock *bodyBB = BasicBlock::Create(context, "for.body", theFunction);
    BasicBlock *incrBB = BasicBlock::Create(context, "for.incr", theFunction);
    BasicBlock *afterBB = BasicBlock::Create(context, "for.after", theFunction);
    builder.CreateBr(condBB);
    builder.SetInsertPoint(condBB);
    llvm::Value *condVal = nullptr;
    if (forStmt->condition) {
      condVal = generateExpression(forStmt->condition);
      if (condVal->getType() != Type::getInt1Ty(context))
        condVal = builder.CreateICmpNE(
            condVal, ConstantInt::get(condVal->getType(), 0), "forcond");
    } else {
      condVal = ConstantInt::get(Type::getInt1Ty(context), 1);
    }
    builder.CreateCondBr(condVal, bodyBB, afterBB);
    builder.SetInsertPoint(bodyBB);
    bool bodyTerminated = generateStatement(forStmt->body);
    if (!bodyTerminated)
      builder.CreateBr(incrBB);
    builder.SetInsertPoint(incrBB);
    if (forStmt->increment)
      generateExpression(forStmt->increment);
    builder.CreateBr(condBB);
    builder.SetInsertPoint(afterBB);
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
    builder.SetInsertPoint(mergeBB);
    return false;
  } else if (std::dynamic_pointer_cast<DeclarationStatement>(stmt)) {
    return false;
  } else {
    throw runtime_error("CodeGenerator Error: Unsupported statement type.");
  }
}
