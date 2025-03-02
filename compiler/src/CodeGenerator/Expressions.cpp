// compiler/src/CodeGenerator/Expressions.cpp

#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "CodeGenerator/Helpers.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"

#include <algorithm>
#include <cctype>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/Casting.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

using namespace llvm;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;

//
// generateArrayElementPointer: returns a pointer to an element of an array.
// This function is used by both generateExpression() and generateLValue().
// It assumes that the base of the array access is an identifier.
//
llvm::Value *
CodeGenerator::generateArrayElementPointer(const shared_ptr<ArrayAccess> &arr) {
  if (auto baseId = std::dynamic_pointer_cast<Identifier>(arr->base)) {
    auto it = declaredTypes.find(baseId->name);
    if (it == declaredTypes.end())
      throw runtime_error("Declared type for array variable not found: " +
                          baseId->name);
    llvm::Type *arrayTy = it->second;
    if (!arrayTy->isArrayTy())
      throw runtime_error("Expected array type for variable: " + baseId->name);

    // Evaluate the index expression.
    llvm::Value *indexVal = generateExpression(arr->index);
    if (!indexVal->getType()->isIntegerTy(32))
      indexVal = builder.CreateIntCast(indexVal, Type::getInt32Ty(context),
                                       true, "arrayidxcast");

    vector<llvm::Value *> indices;
    // First index: 0 (to get the pointer to the array variable)
    indices.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
    // Second index: the array index.
    indices.push_back(indexVal);

    llvm::Value *baseLVal = generateLValue(arr->base);
    llvm::Value *gep =
        builder.CreateGEP(arrayTy, baseLVal, indices, "arraygep");
    return gep;
  } else {
    throw runtime_error("Array access on non-identifier base not supported.");
  }
}

//
// generateExpression: compute the rvalue of an expression.
// This unified version includes support for pointer arithmetic and for
// signed/unsigned types as well as all previously implemented operators.
//
llvm::Value *CodeGenerator::generateExpression(const ExpressionPtr &expr) {
  if (auto binExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
    llvm::Value *lhs = generateExpression(binExpr->left);
    llvm::Value *rhs = generateExpression(binExpr->right);
    // For binary arithmetic operators, handle pointer arithmetic first.
    if (binExpr->op == "+") {
      if (lhs->getType()->isPointerTy() && rhs->getType()->isIntegerTy()) {
        string effectiveType = getEffectiveType(*this, binExpr->left);
        while (!effectiveType.empty() && effectiveType.back() == '*')
          effectiveType.pop_back();
        llvm::Type *elemTy = getLLVMType(effectiveType);
        return builder.CreateGEP(elemTy, lhs, rhs, "ptraddtmp");
      } else if (rhs->getType()->isPointerTy() &&
                 lhs->getType()->isIntegerTy()) {
        string effectiveType = getEffectiveType(*this, binExpr->right);
        while (!effectiveType.empty() && effectiveType.back() == '*')
          effectiveType.pop_back();
        llvm::Type *elemTy = getLLVMType(effectiveType);
        return builder.CreateGEP(elemTy, rhs, lhs, "ptraddtmp");
      } else {
        return lhs->getType()->isFloatingPointTy()
                   ? builder.CreateFAdd(lhs, rhs, "faddtmp")
                   : builder.CreateAdd(lhs, rhs, "addtmp");
      }
    } else if (binExpr->op == "-") {
      if (lhs->getType()->isPointerTy() && rhs->getType()->isIntegerTy()) {
        string effectiveType = getEffectiveType(*this, binExpr->left);
        while (!effectiveType.empty() && effectiveType.back() == '*')
          effectiveType.pop_back();
        llvm::Type *elemTy = getLLVMType(effectiveType);
        llvm::Value *neg = builder.CreateNeg(rhs, "negindex");
        return builder.CreateGEP(elemTy, lhs, neg, "ptrsubtmp");
      } else if (lhs->getType()->isPointerTy() &&
                 rhs->getType()->isPointerTy()) {
        auto DL = module->getDataLayout();
        llvm::Type *intptrTy = DL.getIntPtrType(context);
        llvm::Value *lhsInt =
            builder.CreatePtrToInt(lhs, intptrTy, "ptrtointlhs");
        llvm::Value *rhsInt =
            builder.CreatePtrToInt(rhs, intptrTy, "ptrtointrhs");
        llvm::Value *diffInt = builder.CreateSub(lhsInt, rhsInt, "ptrdiffint");
        string effectiveType = getEffectiveType(*this, binExpr->left);
        while (!effectiveType.empty() && effectiveType.back() == '*')
          effectiveType.pop_back();
        llvm::Type *elemTy = getLLVMType(effectiveType);
        uint64_t elemSize = DL.getTypeAllocSize(elemTy);
        llvm::Value *sizeVal = ConstantInt::get(intptrTy, elemSize);
        return builder.CreateSDiv(diffInt, sizeVal, "ptrdiff");
      } else {
        return lhs->getType()->isFloatingPointTy()
                   ? builder.CreateFSub(lhs, rhs, "fsubtmp")
                   : builder.CreateSub(lhs, rhs, "subtmp");
      }
    } else if (binExpr->op == "*") {
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFMul(lhs, rhs, "fmultmp")
                 : builder.CreateMul(lhs, rhs, "multmp");
    } else if (binExpr->op == "/") {
      if (lhs->getType()->isFloatingPointTy())
        return builder.CreateFDiv(lhs, rhs, "fdivtmp");
      else {
        string effectiveType = getEffectiveType(*this, binExpr->left);
        if (effectiveType.find("unsigned") != string::npos)
          return builder.CreateUDiv(lhs, rhs, "udivtmp");
        else
          return builder.CreateSDiv(lhs, rhs, "sdivtmp");
      }
    } else if (binExpr->op == "%") {
      if (lhs->getType()->isIntegerTy()) {
        string effectiveType = getEffectiveType(*this, binExpr->left);
        if (effectiveType.find("unsigned") != string::npos)
          return builder.CreateURem(lhs, rhs, "umodtmp");
        else
          return builder.CreateSRem(lhs, rhs, "smodtmp");
      } else if (lhs->getType()->isFloatingPointTy()) {
        return builder.CreateFRem(lhs, rhs, "fmodtmp");
      } else {
        throw runtime_error("Unsupported types for modulo operator.");
      }
    } else if (binExpr->op == "<=") {
      if (lhs->getType()->isPointerTy() && rhs->getType()->isPointerTy()) {
        auto DL = module->getDataLayout();
        llvm::Type *intptrTy = DL.getIntPtrType(context);
        llvm::Value *lhsInt =
            builder.CreatePtrToInt(lhs, intptrTy, "ptrtointlhs");
        llvm::Value *rhsInt =
            builder.CreatePtrToInt(rhs, intptrTy, "ptrtointrhs");
        return builder.CreateICmpULE(lhsInt, rhsInt, "ptrcmple");
      }
      if (lhs->getType()->isFloatingPointTy())
        return builder.CreateFCmpOLE(lhs, rhs, "cmptmp");
      else {
        string effectiveType = getEffectiveType(*this, binExpr->left);
        if (effectiveType.find("unsigned") != string::npos)
          return builder.CreateICmpULE(lhs, rhs, "cmptmp");
        else
          return builder.CreateICmpSLE(lhs, rhs, "cmptmp");
      }
    } else if (binExpr->op == "<") {
      if (lhs->getType()->isPointerTy() && rhs->getType()->isPointerTy()) {
        auto DL = module->getDataLayout();
        llvm::Type *intptrTy = DL.getIntPtrType(context);
        llvm::Value *lhsInt =
            builder.CreatePtrToInt(lhs, intptrTy, "ptrtointlhs");
        llvm::Value *rhsInt =
            builder.CreatePtrToInt(rhs, intptrTy, "ptrtointrhs");
        return builder.CreateICmpULT(lhsInt, rhsInt, "ptrcmplt");
      }
      if (lhs->getType()->isFloatingPointTy())
        return builder.CreateFCmpOLT(lhs, rhs, "cmptmp");
      else {
        string effectiveType = getEffectiveType(*this, binExpr->left);
        if (effectiveType.find("unsigned") != string::npos)
          return builder.CreateICmpULT(lhs, rhs, "cmptmp");
        else
          return builder.CreateICmpSLT(lhs, rhs, "cmptmp");
      }
    } else if (binExpr->op == ">=") {
      if (lhs->getType()->isPointerTy() && rhs->getType()->isPointerTy()) {
        auto DL = module->getDataLayout();
        llvm::Type *intptrTy = DL.getIntPtrType(context);
        llvm::Value *lhsInt =
            builder.CreatePtrToInt(lhs, intptrTy, "ptrtointlhs");
        llvm::Value *rhsInt =
            builder.CreatePtrToInt(rhs, intptrTy, "ptrtointrhs");
        return builder.CreateICmpUGE(lhsInt, rhsInt, "ptrcmpge");
      }
      if (lhs->getType()->isFloatingPointTy())
        return builder.CreateFCmpOGE(lhs, rhs, "cmptmp");
      else {
        string effectiveType = getEffectiveType(*this, binExpr->left);
        if (effectiveType.find("unsigned") != string::npos)
          return builder.CreateICmpUGE(lhs, rhs, "cmptmp");
        else
          return builder.CreateICmpSGE(lhs, rhs, "cmptmp");
      }
    } else if (binExpr->op == ">") {
      if (lhs->getType()->isPointerTy() && rhs->getType()->isPointerTy()) {
        auto DL = module->getDataLayout();
        llvm::Type *intptrTy = DL.getIntPtrType(context);
        llvm::Value *lhsInt =
            builder.CreatePtrToInt(lhs, intptrTy, "ptrtointlhs");
        llvm::Value *rhsInt =
            builder.CreatePtrToInt(rhs, intptrTy, "ptrtointrhs");
        return builder.CreateICmpUGT(lhsInt, rhsInt, "ptrcmpgt");
      }
      if (lhs->getType()->isFloatingPointTy())
        return builder.CreateFCmpOGT(lhs, rhs, "cmptmp");
      else {
        string effectiveType = getEffectiveType(*this, binExpr->left);
        if (effectiveType.find("unsigned") != string::npos)
          return builder.CreateICmpUGT(lhs, rhs, "cmptmp");
        else
          return builder.CreateICmpSGT(lhs, rhs, "cmptmp");
      }
    } else if (binExpr->op == "==") {
      if (lhs->getType()->isPointerTy() && rhs->getType()->isPointerTy())
        return builder.CreateICmpEQ(lhs, rhs, "ptreqtmp");
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOEQ(lhs, rhs, "cmptmp")
                 : builder.CreateICmpEQ(lhs, rhs, "cmptmp");
    } else if (binExpr->op == "!=") {
      if (lhs->getType()->isPointerTy() && rhs->getType()->isPointerTy())
        return builder.CreateICmpNE(lhs, rhs, "ptrnetmp");
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpONE(lhs, rhs, "cmptmp")
                 : builder.CreateICmpNE(lhs, rhs, "cmptmp");
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
    }
    throw runtime_error("Unsupported binary operator: " + binExpr->op);
  } else if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
    llvm::Value *ptr = generateLValue(assign->lhs);
    llvm::Value *rhsVal = generateExpression(assign->rhs);
    builder.CreateStore(rhsVal, ptr);
    return rhsVal;
  } else if (auto castExpr = std::dynamic_pointer_cast<CastExpression>(expr)) {
    llvm::Value *operandVal = generateExpression(castExpr->operand);
    llvm::Type *targetType = getLLVMType(castExpr->castType);
    llvm::Type *operandType = operandVal->getType();
    if (operandType == targetType)
      return operandVal;
    if (operandType->isFloatingPointTy() && targetType->isIntegerTy())
      return builder.CreateFPToSI(operandVal, targetType, "casttmp");
    else if (operandType->isIntegerTy() && targetType->isFloatingPointTy())
      return builder.CreateSIToFP(operandVal, targetType, "casttmp");
    else if (operandType->isIntegerTy() && targetType->isIntegerTy())
      return builder.CreateIntCast(operandVal, targetType, false, "casttmp");
    else if (operandType->isFloatingPointTy() &&
             targetType->isFloatingPointTy())
      return builder.CreateFPCast(operandVal, targetType, "casttmp");
    throw runtime_error("Unsupported cast conversion.");
  } else if (auto unExpr = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
    if (unExpr->op == "*") {
      llvm::Value *ptrVal = generateExpression(unExpr->operand);
      if (!ptrVal->getType()->isPointerTy())
        throw runtime_error("Dereference operator on non-pointer type.");
      string baseTypeStr = getEffectiveType(*this, unExpr->operand);
      if (!baseTypeStr.empty() && baseTypeStr.back() == '*')
        baseTypeStr.pop_back();
      llvm::Type *pointeeTy = getLLVMType(baseTypeStr);
      return builder.CreateLoad(pointeeTy, ptrVal, "deref");
    } else if (unExpr->op == "&") {
      return generateLValue(unExpr->operand);
    } else if (unExpr->op == "-") {
      llvm::Value *operand = generateExpression(unExpr->operand);
      if (operand->getType()->isFloatingPointTy())
        return builder.CreateFNeg(operand, "fnegtmp");
      else
        return builder.CreateNeg(operand, "negtmp");
    } else if (unExpr->op == "+") {
      return generateExpression(unExpr->operand);
    } else if (unExpr->op == "!") {
      llvm::Value *operand = generateExpression(unExpr->operand);
      if (!operand->getType()->isIntegerTy(1))
        operand = builder.CreateICmpNE(
            operand, ConstantInt::get(operand->getType(), 0), "booltmp");
      return builder.CreateNot(operand, "nottmp");
    }
    throw runtime_error("Unsupported unary operator: " + unExpr->op);
  } else if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
    switch (lit->type) {
    case Literal::LiteralType::Int:
      return ConstantInt::get(Type::getInt32Ty(context), lit->intValue);
    case Literal::LiteralType::Float:
      return ConstantFP::get(Type::getFloatTy(context), lit->floatValue);
    case Literal::LiteralType::Double:
      return ConstantFP::get(Type::getDoubleTy(context), lit->doubleValue);
    case Literal::LiteralType::Char:
      return ConstantInt::get(Type::getInt8Ty(context), lit->charValue);
    case Literal::LiteralType::Bool:
      return ConstantInt::get(Type::getInt1Ty(context), lit->boolValue);
    default:
      throw runtime_error("Cannot infer type for literal.");
    }
  } else if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    auto enumIt = enumRegistry.find(id->name);
    if (enumIt != enumRegistry.end())
      return ConstantInt::get(Type::getInt32Ty(context), enumIt->second);
    llvm::Value *v = lookupLocalVar(id->name);
    if (v) {
      if (auto allocaInst = dyn_cast<AllocaInst>(v)) {
        llvm::Type *allocType = allocaInst->getAllocatedType();
        if (allocType->isArrayTy()) {
          vector<llvm::Value *> indices;
          indices.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
          indices.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
          return builder.CreateGEP(allocType, v, indices, id->name + "_decay");
        } else {
          return builder.CreateLoad(allocType, v, id->name.c_str());
        }
      }
      return v;
    }
    GlobalVariable *gVar = module->getGlobalVariable(id->name);
    if (gVar) {
      llvm::Type *gType = gVar->getValueType();
      if (gType->isArrayTy()) {
        vector<llvm::Value *> indices;
        indices.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
        indices.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
        return builder.CreateGEP(gType, gVar, indices, id->name + "_decay");
      } else {
        return builder.CreateLoad(gType, gVar, id->name.c_str());
      }
    }
    throw runtime_error("Undefined identifier: " + id->name);
  } else if (auto arrAccess = std::dynamic_pointer_cast<ArrayAccess>(expr)) {
    llvm::Value *elemPtr = generateArrayElementPointer(arrAccess);
    PointerType *ptrType = dyn_cast<PointerType>(elemPtr->getType());
    if (!ptrType)
      throw runtime_error("Array access did not return a pointer.");
    if (auto baseId = std::dynamic_pointer_cast<Identifier>(arrAccess->base)) {
      auto it = declaredTypes.find(baseId->name);
      if (it == declaredTypes.end())
        throw runtime_error("Declared type for array var not found: " +
                            baseId->name);
      llvm::Type *arrayTy = it->second;
      if (!arrayTy->isArrayTy())
        throw runtime_error("Expected array type for variable: " +
                            baseId->name);
      llvm::Type *elemType = cast<ArrayType>(arrayTy)->getElementType();
      return builder.CreateLoad(elemType, elemPtr, "arrayload");
    } else {
      throw runtime_error("Array access on non-identifier base not supported.");
    }
  } else if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    llvm::Value *ptr = generateLValue(expr);
    string effType = getEffectiveType(*this, expr);
    llvm::Type *loadType = getLLVMType(effType);
    return builder.CreateLoad(loadType, ptr, "memberload");
  } else if (auto call = std::dynamic_pointer_cast<FunctionCall>(expr)) {
    llvm::Function *callee = module->getFunction(call->functionName);
    if (!callee)
      throw runtime_error("Undefined function in IR: " + call->functionName);
    vector<llvm::Value *> args;
    for (auto &argExpr : call->arguments)
      args.push_back(generateExpression(argExpr));
    if (callee->getReturnType()->isVoidTy()) {
      builder.CreateCall(callee, args);
      return ConstantInt::get(Type::getInt32Ty(context), 0);
    } else {
      return builder.CreateCall(callee, args, "calltmp");
    }
  } else if (auto post = std::dynamic_pointer_cast<PostfixExpression>(expr)) {
    return generateLValue(expr);
  }
  throw runtime_error("Unsupported expression type in generateExpression().");
}
