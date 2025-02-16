#include "AST.hpp"
#include "CodeGenerator.hpp"
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

//===----------------------------------------------------------------------===//
//  Local Scope Management
//
// We maintain two parallel stacks:
//   - localVarStack: a stack (vector) of unordered_maps mapping variable names
//   to their AllocaInst pointers.
//   - declaredVarStack: a stack (vector) of unordered_sets of strings, which
//   record the variable names declared in each scope.
// When a scope is popped, we remove the variable names declared in that scope
// from declaredTypes and declaredTypeStrings.
//===----------------------------------------------------------------------===//

void CodeGenerator::pushLocalScope() {
  localVarStack.push_back(unordered_map<string, Value *>());
  declaredVarStack.push_back(unordered_set<string>());
}

void CodeGenerator::popLocalScope() {
  if (localVarStack.empty() || declaredVarStack.empty())
    throw runtime_error("CodeGenerator Error: No local scope to pop.");
  // Remove all variable declarations from the global maps that were declared in
  // this scope.
  for (const auto &name : declaredVarStack.back()) {
    declaredTypes.erase(name);
    declaredTypeStrings.erase(name);
  }
  declaredVarStack.pop_back();
  localVarStack.pop_back();
}

llvm::Value *CodeGenerator::lookupLocalVar(const string &name) {
  for (auto scopeIt = localVarStack.rbegin(); scopeIt != localVarStack.rend();
       ++scopeIt) {
    auto found = scopeIt->find(name);
    if (found != scopeIt->end())
      return found->second;
  }
  return nullptr;
}

//===----------------------------------------------------------------------===//
//  generateStatement
//
// For compound statements we push a new scope, process each substatement,
// and then (if this isn’t the outermost function body) pop the scope.
//===----------------------------------------------------------------------===//

bool CodeGenerator::generateStatement(const StatementPtr &stmt) {
  if (auto compound = std::dynamic_pointer_cast<CompoundStatement>(stmt)) {
    pushLocalScope();
    bool terminated = false;
    for (auto &substmt : compound->statements) {
      terminated = generateStatement(substmt);
      if (terminated)
        break;
    }
    // If more than one scope exists, we are in a nested compound and pop the
    // local scope.
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
    Value *retVal = generateExpression(retStmt->expression);
    Function *currentFunction = builder.GetInsertBlock()->getParent();
    Type *expectedType = currentFunction->getReturnType();
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
    Value *condVal = generateExpression(ifStmt->condition);
    if (condVal->getType() != Type::getInt1Ty(context)) {
      condVal = builder.CreateICmpNE(
          condVal, ConstantInt::get(condVal->getType(), 0), "ifcond");
    }
    Function *theFunction = builder.GetInsertBlock()->getParent();
    BasicBlock *thenBB = BasicBlock::Create(context, "then", theFunction);
    BasicBlock *elseBB = BasicBlock::Create(context, "else", theFunction);
    BasicBlock *mergeBB = BasicBlock::Create(context, "ifcont", theFunction);
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
    Function *theFunction = builder.GetInsertBlock()->getParent();
    BasicBlock *condBB = BasicBlock::Create(context, "while.cond", theFunction);
    BasicBlock *bodyBB = BasicBlock::Create(context, "while.body", theFunction);
    BasicBlock *afterBB =
        BasicBlock::Create(context, "while.after", theFunction);
    builder.CreateBr(condBB);
    builder.SetInsertPoint(condBB);
    Value *condVal = generateExpression(whileStmt->condition);
    if (condVal->getType() != Type::getInt1Ty(context)) {
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
    Function *theFunction = builder.GetInsertBlock()->getParent();
    BasicBlock *condBB = BasicBlock::Create(context, "for.cond", theFunction);
    BasicBlock *bodyBB = BasicBlock::Create(context, "for.body", theFunction);
    BasicBlock *incrBB = BasicBlock::Create(context, "for.incr", theFunction);
    BasicBlock *afterBB = BasicBlock::Create(context, "for.after", theFunction);
    builder.CreateBr(condBB);
    builder.SetInsertPoint(condBB);
    Value *condVal = nullptr;
    if (forStmt->condition) {
      condVal = generateExpression(forStmt->condition);
      if (condVal->getType() != Type::getInt1Ty(context)) {
        condVal = builder.CreateICmpNE(
            condVal, ConstantInt::get(condVal->getType(), 0), "forcond");
      }
    } else {
      condVal = ConstantInt::get(Type::getInt1Ty(context), 1);
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
    Value *condVal = generateExpression(switchStmt->expression);
    if (!condVal->getType()->isIntegerTy()) {
      throw runtime_error(
          "CodeGenerator Error: Switch expression must be of integer type.");
    }
    Function *theFunction = builder.GetInsertBlock()->getParent();
    BasicBlock *defaultBB =
        BasicBlock::Create(context, "switch.default", theFunction);
    SwitchInst *switchInst =
        builder.CreateSwitch(condVal, defaultBB, switchStmt->cases.size());
    for (auto &casePair : switchStmt->cases) {
      if (!casePair.first.has_value())
        throw runtime_error(
            "CodeGenerator Error: Case label missing in case clause.");
      Value *caseVal = generateExpression(casePair.first.value());
      if (!isa<ConstantInt>(caseVal))
        throw runtime_error(
            "CodeGenerator Error: Case label must be a constant integer.");
      BasicBlock *caseBB =
          BasicBlock::Create(context, "switch.case", theFunction);
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
  }
  // Handle DeclarationStatements that wrap an enum declaration.
  else if (auto declStmt =
               std::dynamic_pointer_cast<DeclarationStatement>(stmt)) {
    if (auto enumDecl =
            std::dynamic_pointer_cast<EnumDeclaration>(declStmt->declaration)) {
      // Generate global constants for each enumerator (if not already
      // generated).
      for (size_t i = 0; i < enumDecl->enumerators.size(); ++i) {
        string enumName = enumDecl->enumerators[i].first;
        int value = enumDecl->enumeratorValues[i];
        if (!module->getGlobalVariable(enumName)) {
          Constant *initVal =
              ConstantInt::get(Type::getInt32Ty(context), value);
          GlobalVariable *gEnum = new GlobalVariable(
              *module, Type::getInt32Ty(context), true,
              GlobalValue::ExternalLinkage, initVal, enumName);
        }
      }
      return false;
    } else {
      throw runtime_error(
          "CodeGenerator Error: Unsupported declaration statement type.");
    }
  } else {
    throw runtime_error("CodeGenerator Error: Unsupported statement type.");
  }
}

//===----------------------------------------------------------------------===//
//  generateVariableDeclarationStatement
//
// Allocates a local variable and records it in the current local scope.
//===----------------------------------------------------------------------===//

void CodeGenerator::generateVariableDeclarationStatement(
    const shared_ptr<VariableDeclarationStatement> &varDeclStmt) {
  llvm::Type *varTy = getLLVMType(varDeclStmt->type);
  AllocaInst *alloc =
      builder.CreateAlloca(varTy, nullptr, varDeclStmt->name.c_str());
  // Record the allocation in the current local scope.
  localVarStack.back()[varDeclStmt->name] = alloc;
  // Also record the variable name in the declaredVarStack for later removal.
  declaredVarStack.back().insert(varDeclStmt->name);
  // Record the LLVM type and the original type string.
  declaredTypes[varDeclStmt->name] = varTy;
  declaredTypeStrings[varDeclStmt->name] = varDeclStmt->type;
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
