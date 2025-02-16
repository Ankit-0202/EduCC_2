#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <sstream>
#include <stdexcept>

using namespace llvm;
using std::runtime_error;
using std::shared_ptr;
using std::string;

llvm::Value *CodeGenerator::generateLValue(const ExpressionPtr &expr) {
  if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    auto it = localVariables.find(id->name);
    if (it != localVariables.end()) {
      return it->second;
    }
    GlobalVariable *gVar = module->getGlobalVariable(id->name);
    if (gVar)
      return gVar;
    throw runtime_error("CodeGenerator Error: Undefined variable '" + id->name +
                        "' in lvalue generation.");
  } else if (auto memberAccess =
                 std::dynamic_pointer_cast<MemberAccess>(expr)) {
    llvm::Value *basePtr = generateLValue(memberAccess->base);
    return builder.CreateBitCast(
        basePtr, llvm::PointerType::getUnqual(Type::getInt32Ty(context)));
  } else {
    throw runtime_error(
        "CodeGenerator Error: Expression is not a valid lvalue.");
  }
}

llvm::Value *CodeGenerator::generateExpression(const ExpressionPtr &expr) {
  if (auto binExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
    llvm::Value *lhs = generateExpression(binExpr->left);
    llvm::Value *rhs = generateExpression(binExpr->right);

    if (lhs->getType() != rhs->getType()) {
      if (lhs->getType()->isIntegerTy() &&
          rhs->getType()->isFloatingPointTy()) {
        lhs = builder.CreateSIToFP(lhs, rhs->getType(), "sitofp");
      } else if (lhs->getType()->isFloatingPointTy() &&
                 rhs->getType()->isIntegerTy()) {
        rhs = builder.CreateSIToFP(rhs, lhs->getType(), "sitofp");
      } else {
        throw runtime_error(
            "CodeGenerator Error: Incompatible types in binary expression.");
      }
    }

    if (binExpr->op == "+") {
      if (lhs->getType()->isFloatingPointTy())
        return builder.CreateFAdd(lhs, rhs, "faddtmp");
      else
        return builder.CreateAdd(lhs, rhs, "addtmp");
    } else if (binExpr->op == "-") {
      if (lhs->getType()->isFloatingPointTy())
        return builder.CreateFSub(lhs, rhs, "fsubtmp");
      else
        return builder.CreateSub(lhs, rhs, "subtmp");
    } else if (binExpr->op == "*") {
      if (lhs->getType()->isFloatingPointTy())
        return builder.CreateFMul(lhs, rhs, "fmultmp");
      else
        return builder.CreateMul(lhs, rhs, "multmp");
    } else if (binExpr->op == "/") {
      if (lhs->getType()->isFloatingPointTy())
        return builder.CreateFDiv(lhs, rhs, "fdivtmp");
      else
        return builder.CreateSDiv(lhs, rhs, "divtmp");
    } else if (binExpr->op == "<=") {
      if (lhs->getType()->isFloatingPointTy())
        return builder.CreateFCmpOLE(lhs, rhs, "cmptmp");
      else
        return builder.CreateICmpSLE(lhs, rhs, "cmptmp");
    } else if (binExpr->op == "<") {
      if (lhs->getType()->isFloatingPointTy())
        return builder.CreateFCmpOLT(lhs, rhs, "cmptmp");
      else
        return builder.CreateICmpSLT(lhs, rhs, "cmptmp");
    } else if (binExpr->op == ">=") {
      if (lhs->getType()->isFloatingPointTy())
        return builder.CreateFCmpOGE(lhs, rhs, "cmptmp");
      else
        return builder.CreateICmpSGE(lhs, rhs, "cmptmp");
    } else if (binExpr->op == ">") {
      if (lhs->getType()->isFloatingPointTy())
        return builder.CreateFCmpOGT(lhs, rhs, "cmptmp");
      else
        return builder.CreateICmpSGT(lhs, rhs, "cmptmp");
    } else if (binExpr->op == "==") {
      if (lhs->getType()->isFloatingPointTy())
        return builder.CreateFCmpOEQ(lhs, rhs, "cmptmp");
      else
        return builder.CreateICmpEQ(lhs, rhs, "cmptmp");
    } else if (binExpr->op == "!=") {
      if (lhs->getType()->isFloatingPointTy())
        return builder.CreateFCmpONE(lhs, rhs, "cmptmp");
      else
        return builder.CreateICmpNE(lhs, rhs, "cmptmp");
    } else if (binExpr->op == "&&") {
      if (!lhs->getType()->isIntegerTy(1))
        lhs = builder.CreateICmpNE(lhs, ConstantInt::get(lhs->getType(), 0),
                                   "booltmp");
      if (!rhs->getType()->isIntegerTy(1))
        rhs = builder.CreateICmpNE(rhs, ConstantInt::get(rhs->getType(), 0),
                                   "booltmp");
      return builder.CreateAnd(lhs, rhs, "andtmp");
    } else if (binExpr->op == "||") {
      if (!lhs->getType()->isIntegerTy(1))
        lhs = builder.CreateICmpNE(lhs, ConstantInt::get(lhs->getType(), 0),
                                   "booltmp");
      if (!rhs->getType()->isIntegerTy(1))
        rhs = builder.CreateICmpNE(rhs, ConstantInt::get(rhs->getType(), 0),
                                   "booltmp");
      return builder.CreateOr(lhs, rhs, "ortmp");
    } else if (binExpr->op == "&") {
      return builder.CreateAnd(lhs, rhs, "bitandtmp");
    } else if (binExpr->op == "^") {
      return builder.CreateXor(lhs, rhs, "bitxortmp");
    } else if (binExpr->op == "|") {
      return builder.CreateOr(lhs, rhs, "bitor_tmp");
    } else if (binExpr->op == "<<") {
      return builder.CreateShl(lhs, rhs, "shltmp");
    } else if (binExpr->op == ">>") {
      return builder.CreateAShr(lhs, rhs, "shrtmp");
    } else {
      throw runtime_error("CodeGenerator Error: Unsupported binary operator '" +
                          binExpr->op + "'.");
    }
  } else if (auto castExpr = std::dynamic_pointer_cast<CastExpression>(expr)) {
    llvm::Value *operandVal = generateExpression(castExpr->operand);
    llvm::Type *targetType = getLLVMType(castExpr->castType);
    llvm::Type *operandType = operandVal->getType();
    if (operandType == targetType)
      return operandVal;
    if (operandType->isFloatingPointTy() && targetType->isIntegerTy()) {
      return builder.CreateFPToSI(operandVal, targetType, "casttmp");
    } else if (operandType->isIntegerTy() && targetType->isFloatingPointTy()) {
      return builder.CreateSIToFP(operandVal, targetType, "casttmp");
    } else if (operandType->isIntegerTy() && targetType->isIntegerTy()) {
      return builder.CreateIntCast(operandVal, targetType, false, "casttmp");
    } else if (operandType->isFloatingPointTy() &&
               targetType->isFloatingPointTy()) {
      return builder.CreateFPCast(operandVal, targetType, "casttmp");
    } else {
      throw runtime_error("CodeGenerator Error: Unsupported cast conversion.");
    }
  } else if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
    if (std::holds_alternative<char>(lit->value))
      return ConstantInt::get(Type::getInt8Ty(context),
                              std::get<char>(lit->value));
    else if (std::holds_alternative<bool>(lit->value))
      return ConstantInt::get(Type::getInt1Ty(context),
                              std::get<bool>(lit->value));
    else if (std::holds_alternative<int>(lit->value))
      return ConstantInt::get(Type::getInt32Ty(context),
                              std::get<int>(lit->value));
    else if (std::holds_alternative<float>(lit->value))
      return ConstantFP::get(Type::getFloatTy(context),
                             std::get<float>(lit->value));
    else if (std::holds_alternative<double>(lit->value))
      return ConstantFP::get(Type::getDoubleTy(context),
                             std::get<double>(lit->value));
  } else if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    auto it = localVariables.find(id->name);
    if (it != localVariables.end()) {
      llvm::Value *varPtr = it->second;
      if (auto allocaInst = dyn_cast<AllocaInst>(varPtr)) {
        llvm::Type *allocatedType = allocaInst->getAllocatedType();
        return builder.CreateLoad(allocatedType, varPtr, id->name.c_str());
      } else {
        throw runtime_error("CodeGenerator Error: '" + id->name +
                            "' is not an alloca instruction.");
      }
    }
    GlobalVariable *gVar = module->getGlobalVariable(id->name);
    if (gVar) {
      return builder.CreateLoad(gVar->getValueType(), gVar, id->name.c_str());
    }
    throw runtime_error("CodeGenerator Error: Undefined variable '" + id->name +
                        "'.");
  } else if (auto memberAccess =
                 std::dynamic_pointer_cast<MemberAccess>(expr)) {
    llvm::Value *ptr = generateLValue(expr);
    return builder.CreateLoad(Type::getInt32Ty(context), ptr, "memberload");
  } else if (auto post = std::dynamic_pointer_cast<PostfixExpression>(expr)) {
    auto id = std::dynamic_pointer_cast<Identifier>(post->operand);
    if (!id) {
      throw runtime_error(
          "CodeGenerator Error: Postfix operator applied to non-identifier.");
    }
    auto it = localVariables.find(id->name);
    if (it == localVariables.end()) {
      throw runtime_error("CodeGenerator Error: Undefined variable '" +
                          id->name + "' in postfix expression.");
    }
    llvm::Value *varPtr = it->second;
    AllocaInst *allocaInst = dyn_cast<AllocaInst>(varPtr);
    if (!allocaInst) {
      throw runtime_error("CodeGenerator Error: Postfix operator applied to "
                          "non-alloca variable.");
    }
    llvm::Value *oldVal = builder.CreateLoad(allocaInst->getAllocatedType(),
                                             varPtr, id->name.c_str());
    llvm::Value *one = nullptr;
    if (oldVal->getType()->isIntegerTy()) {
      one = ConstantInt::get(oldVal->getType(), 1);
    } else if (oldVal->getType()->isFloatingPointTy()) {
      one = ConstantFP::get(oldVal->getType(), 1.0);
    } else {
      throw runtime_error(
          "CodeGenerator Error: Unsupported type for postfix operator.");
    }
    llvm::Value *newVal = nullptr;
    if (post->op == "++") {
      if (oldVal->getType()->isFloatingPointTy())
        newVal = builder.CreateFAdd(oldVal, one, "postinc");
      else
        newVal = builder.CreateAdd(oldVal, one, "postinc");
    } else if (post->op == "--") {
      if (oldVal->getType()->isFloatingPointTy())
        newVal = builder.CreateFSub(oldVal, one, "postdec");
      else
        newVal = builder.CreateSub(oldVal, one, "postdec");
    } else {
      throw runtime_error("CodeGenerator Error: Unknown postfix operator '" +
                          post->op + "'.");
    }
    builder.CreateStore(newVal, varPtr);
    return oldVal;
  } else if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
    llvm::Value *ptr = generateLValue(assign->lhs);
    llvm::Value *rhsVal = generateExpression(assign->rhs);
    builder.CreateStore(rhsVal, ptr);
    return rhsVal;
  } else if (auto funcCall = std::dynamic_pointer_cast<FunctionCall>(expr)) {
    llvm::Function *callee = module->getFunction(funcCall->functionName);
    if (!callee) {
      throw runtime_error("CodeGenerator Error: Undefined function '" +
                          funcCall->functionName + "' in IR.");
    }
    std::vector<llvm::Value *> args;
    for (auto &argExpr : funcCall->arguments) {
      args.push_back(generateExpression(argExpr));
    }
    return builder.CreateCall(callee, args, "calltmp");
  }
  throw runtime_error("CodeGenerator Error: Unsupported expression type in "
                      "generateExpression().");
}
