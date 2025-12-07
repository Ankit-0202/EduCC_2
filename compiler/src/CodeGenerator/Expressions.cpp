#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "CodeGenerator/Helpers.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"

#include <iostream>
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

namespace {
MemberInfo *resolveMemberInfo(CodeGenerator &CG, const MemberAccess &mem) {
  string baseType = getEffectiveType(CG, mem.base);
  if (baseType.rfind("struct ", 0) == 0) {
    string tag = normalizeTag(baseType.substr(7));
    return getMemberInfo(tag, mem.member);
  }
  if (baseType.rfind("union ", 0) == 0) {
    string tag = normalizeTag(baseType.substr(6));
    return getMemberInfo(tag, mem.member);
  }
  return nullptr;
}

llvm::Value *maskBitfieldValue(llvm::IRBuilder<> &builder, llvm::Value *value,
                               unsigned width, bool isUnsigned) {
  if (!value->getType()->isIntegerTy() || width == 0)
    return value;
  unsigned rawBits = value->getType()->getIntegerBitWidth();
  if (width >= rawBits)
    return value;
  auto *mask = llvm::ConstantInt::get(value->getType(), (1ULL << width) - 1);
  llvm::Value *masked = builder.CreateAnd(value, mask, "bf.mask");
  if (isUnsigned)
    return masked;

  unsigned shift = rawBits - width;
  auto *shiftVal = llvm::ConstantInt::get(value->getType(), shift);
  llvm::Value *shifted = builder.CreateShl(masked, shiftVal, "bf.shl");
  return builder.CreateAShr(shifted, shiftVal, "bf.sext");
}
} // namespace

//===----------------------------------------------------------------------===//
// Array Access Helper
//===----------------------------------------------------------------------===//

llvm::Value *
CodeGenerator::generateArrayElementPointer(const shared_ptr<ArrayAccess> &arr) {
  // Handle array access on identifiers (e.g., arr[i])
  if (auto baseId = std::dynamic_pointer_cast<Identifier>(arr->base)) {
    llvm::Type *baseType = nullptr;
    llvm::Value *basePtr = nullptr;
    auto it = declaredTypes.find(baseId->name);
    if (it != declaredTypes.end()) {
      baseType = it->second;
      basePtr = generateLValue(arr->base);
    } else if (auto gVar = module->getGlobalVariable(baseId->name)) {
      baseType = gVar->getValueType();
      basePtr = gVar;
    } else {
      throw runtime_error("Declared type for array variable not found: " +
                          baseId->name);
    }

    // Evaluate the index expression.
    llvm::Value *indexVal = generateExpression(arr->index);
    if (!indexVal->getType()->isIntegerTy(32))
      indexVal = builder.CreateIntCast(indexVal, Type::getInt32Ty(context),
                                       true, "arrayidxcast");

    if (baseType->isArrayTy()) {
      vector<llvm::Value *> indices;
      indices.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
      indices.push_back(indexVal);
      return builder.CreateGEP(baseType, basePtr, indices, "arraygep");
    }

    if (baseType->isPointerTy()) {
      std::string effTypeStr = getEffectiveType(*this, arr->base);
      while (!effTypeStr.empty() && effTypeStr.back() == '*')
        effTypeStr.pop_back();
      llvm::Type *elemType = getLLVMType(effTypeStr);
      llvm::Value *ptrValue = basePtr;
      if (auto *allocaInst = dyn_cast<AllocaInst>(basePtr)) {
        ptrValue =
            builder.CreateLoad(baseType, allocaInst, baseId->name + "_ptr");
      } else if (auto *global = dyn_cast<GlobalVariable>(basePtr)) {
        ptrValue = builder.CreateLoad(baseType, global, baseId->name + "_ptr");
      }
      return builder.CreateGEP(elemType, ptrValue, indexVal, "ptridx");
    }

    throw runtime_error("Expected array or pointer type for variable: " +
                        baseId->name);
  }
  // Handle array access on member access (e.g., struct.member[i] or
  // union.member[i])
  else if (auto baseMember =
               std::dynamic_pointer_cast<MemberAccess>(arr->base)) {
    // Get the base pointer (e.g., pointer to struct/union)
    llvm::Value *basePtr = generateLValue(baseMember);

    // Get the effective type of the member to determine array element type
    string memberType = getEffectiveType(*this, baseMember);
    llvm::Type *elementType = getLLVMType(memberType);

    // Evaluate the index expression.
    llvm::Value *indexVal = generateExpression(arr->index);
    if (!indexVal->getType()->isIntegerTy(32))
      indexVal = builder.CreateIntCast(indexVal, Type::getInt32Ty(context),
                                       true, "arrayidxcast");

    // For array members, we need to get a pointer to the array element
    vector<llvm::Value *> indices;
    indices.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
    indices.push_back(indexVal);

    llvm::Value *gep =
        builder.CreateGEP(elementType, basePtr, indices, "memberarraygep");
    return gep;
  } else {
    throw runtime_error("Array access on unsupported base type.");
  }
}

// Add or extend generateExpression to support bitwise NOT (~)
llvm::Value *CodeGenerator::generateExpression(const ExpressionPtr &expr) {
  if (auto binExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
    llvm::Value *lhs = generateExpression(binExpr->left);
    llvm::Value *rhs = generateExpression(binExpr->right);

    // Debug output to see what types we're dealing with
    std::cerr << "[DEBUG] Binary expression: " << binExpr->op << std::endl;
    std::cerr << "[DEBUG] LHS type: "
              << (lhs->getType()->isPointerTy() ? "pointer" : "value")
              << std::endl;
    std::cerr << "[DEBUG] RHS type: "
              << (rhs->getType()->isPointerTy() ? "pointer" : "value")
              << std::endl;
    std::cerr << "[DEBUG] LHS type name: "
              << (lhs->getType()->isFloatTy()       ? "float"
                  : lhs->getType()->isDoubleTy()    ? "double"
                  : lhs->getType()->isIntegerTy(32) ? "int32"
                  : lhs->getType()->isIntegerTy(64) ? "int64"
                  : lhs->getType()->isIntegerTy(8)  ? "int8"
                                                    : "other")
              << std::endl;
    std::cerr << "[DEBUG] RHS type name: "
              << (rhs->getType()->isFloatTy()       ? "float"
                  : rhs->getType()->isDoubleTy()    ? "double"
                  : rhs->getType()->isIntegerTy(32) ? "int32"
                  : rhs->getType()->isIntegerTy(64) ? "int64"
                  : rhs->getType()->isIntegerTy(8)  ? "int8"
                                                    : "other")
              << std::endl;

    // Only perform conversion if neither operand is a pointer arithmetic case.
    if (!((lhs->getType()->isPointerTy() && rhs->getType()->isIntegerTy()) ||
          (rhs->getType()->isPointerTy() && lhs->getType()->isIntegerTy()))) {
      if (lhs->getType() != rhs->getType()) {
        if (lhs->getType()->isIntegerTy() &&
            rhs->getType()->isFloatingPointTy()) {
          lhs = builder.CreateSIToFP(lhs, rhs->getType(), "sitofp");
        } else if (lhs->getType()->isFloatingPointTy() &&
                   rhs->getType()->isIntegerTy()) {
          rhs = builder.CreateSIToFP(rhs, lhs->getType(), "sitofp");
        } else if (lhs->getType()->isFloatingPointTy() &&
                   rhs->getType()->isFloatingPointTy()) {
          // Convert between float and double
          if (lhs->getType()->isFloatTy() && rhs->getType()->isDoubleTy()) {
            lhs = builder.CreateFPExt(lhs, rhs->getType(), "fpext");
          } else if (lhs->getType()->isDoubleTy() &&
                     rhs->getType()->isFloatTy()) {
            rhs = builder.CreateFPExt(rhs, lhs->getType(), "fpext");
          }
        } else if (lhs->getType()->isIntegerTy() &&
                   rhs->getType()->isIntegerTy()) {
          // Convert between different integer types
          if (lhs->getType()->getIntegerBitWidth() <
              rhs->getType()->getIntegerBitWidth()) {
            lhs = builder.CreateSExt(lhs, rhs->getType(), "sext");
          } else if (rhs->getType()->getIntegerBitWidth() <
                     lhs->getType()->getIntegerBitWidth()) {
            rhs = builder.CreateSExt(rhs, lhs->getType(), "sext");
          }
        } else {
          throw runtime_error("Incompatible types in binary expression.");
        }
      }
    }
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
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFDiv(lhs, rhs, "fdivtmp")
                 : builder.CreateSDiv(lhs, rhs, "divtmp");
    } else if (binExpr->op == "%") {
      if (lhs->getType()->isIntegerTy()) {
        return builder.CreateSRem(lhs, rhs, "modtmp");
      } else if (lhs->getType()->isFloatingPointTy()) {
        return builder.CreateFRem(lhs, rhs, "modtmp");
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
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOLE(lhs, rhs, "cmptmp")
                 : builder.CreateICmpSLE(lhs, rhs, "cmptmp");
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
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOLT(lhs, rhs, "cmptmp")
                 : builder.CreateICmpSLT(lhs, rhs, "cmptmp");
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
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOGE(lhs, rhs, "cmptmp")
                 : builder.CreateICmpSGE(lhs, rhs, "cmptmp");
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
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOGT(lhs, rhs, "cmptmp")
                 : builder.CreateICmpSGT(lhs, rhs, "cmptmp");
    } else if (binExpr->op == "==") {
      if (lhs->getType()->isPointerTy() && rhs->getType()->isPointerTy()) {
        return builder.CreateICmpEQ(lhs, rhs, "ptreqtmp");
      }
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOEQ(lhs, rhs, "cmptmp")
                 : builder.CreateICmpEQ(lhs, rhs, "cmptmp");
    } else if (binExpr->op == "!=") {
      if (lhs->getType()->isPointerTy() && rhs->getType()->isPointerTy()) {
        return builder.CreateICmpNE(lhs, rhs, "ptrnetmp");
      }
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpONE(lhs, rhs, "cmptmp")
                 : builder.CreateICmpNE(lhs, rhs, "cmptmp");
    } else if (binExpr->op == "&&") {
      if (!lhs->getType()->isIntegerTy(1)) {
        lhs = builder.CreateICmpNE(lhs, ConstantInt::get(lhs->getType(), 0),
                                   "booltmp");
      }
      if (!rhs->getType()->isIntegerTy(1)) {
        rhs = builder.CreateICmpNE(rhs, ConstantInt::get(rhs->getType(), 0),
                                   "booltmp");
      }
      return builder.CreateAnd(lhs, rhs, "andtmp");
    } else if (binExpr->op == "||") {
      if (!lhs->getType()->isIntegerTy(1)) {
        lhs = builder.CreateICmpNE(lhs, ConstantInt::get(lhs->getType(), 0),
                                   "booltmp");
      }
      if (!rhs->getType()->isIntegerTy(1)) {
        rhs = builder.CreateICmpNE(rhs, ConstantInt::get(rhs->getType(), 0),
                                   "booltmp");
      }
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
    if (auto mem = std::dynamic_pointer_cast<MemberAccess>(assign->lhs)) {
      if (auto *info = resolveMemberInfo(*this, *mem)) {
        if (info->bitWidth > 0) {
          llvm::Value *ptr = generateLValue(assign->lhs);
          llvm::Value *rhsVal = generateExpression(assign->rhs);
          llvm::Type *fieldType = getLLVMType(info->type);
          if (fieldType->isIntegerTy() && rhsVal->getType() != fieldType) {
            rhsVal = builder.CreateIntCast(rhsVal, fieldType, !info->isUnsigned,
                                           "bf.cast");
          }
          rhsVal = maskBitfieldValue(builder, rhsVal,
                                     static_cast<unsigned>(info->bitWidth),
                                     info->isUnsigned);
          builder.CreateStore(rhsVal, ptr);
          return rhsVal;
        }
      }
    }

    llvm::Value *ptr = generateLValue(assign->lhs);
    llvm::Value *rhsVal = generateExpression(assign->rhs);

    string targetTypeStr = getEffectiveType(*this, assign->lhs);
    llvm::Type *targetType = getLLVMType(targetTypeStr);
    llvm::Type *rhsType = rhsVal->getType();

    if (targetType != rhsType) {
      if (targetType->isFloatingPointTy() && rhsType->isFloatingPointTy()) {
        if (targetType->isFloatTy() && rhsType->isDoubleTy()) {
          rhsVal = builder.CreateFPTrunc(rhsVal, targetType, "fptrunc");
        } else if (targetType->isDoubleTy() && rhsType->isFloatTy()) {
          rhsVal = builder.CreateFPExt(rhsVal, targetType, "fpext");
        }
      } else if (targetType->isIntegerTy() && rhsType->isFloatingPointTy()) {
        rhsVal = builder.CreateFPToSI(rhsVal, targetType, "fptosi");
      } else if (targetType->isFloatingPointTy() && rhsType->isIntegerTy()) {
        rhsVal = builder.CreateSIToFP(rhsVal, targetType, "sitofp");
      } else if (targetType->isIntegerTy() && rhsType->isIntegerTy()) {
        rhsVal = builder.CreateIntCast(rhsVal, targetType, false, "intcast");
      }
    }

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
    else if (operandType->isPointerTy() && targetType->isIntegerTy())
      return builder.CreatePtrToInt(operandVal, targetType, "casttmp");
    else if (operandType->isIntegerTy() && targetType->isPointerTy())
      return builder.CreateIntToPtr(operandVal, targetType, "casttmp");
    else if (operandType->isPointerTy() && targetType->isPointerTy())
      return builder.CreateBitCast(operandVal, targetType, "casttmp");
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
    } else if (unExpr->op == "~") {
      llvm::Value *operand = generateExpression(unExpr->operand);
      if (!operand->getType()->isIntegerTy())
        throw runtime_error(
            "CodeGenerator Error: Bitwise NOT '~' applied to non-integer type");
      return builder.CreateNot(operand, "bnot");
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
    case Literal::LiteralType::String: {
      llvm::Constant *strConstant =
          llvm::ConstantDataArray::getString(context, lit->stringValue, true);
      llvm::GlobalVariable *gVar = new llvm::GlobalVariable(
          *module, strConstant->getType(), true,
          llvm::GlobalValue::PrivateLinkage, strConstant, "str");
      return builder.CreateBitCast(gVar, PointerType::get(context, 0),
                                   "strptr");
    }
    default:
      throw runtime_error("Cannot infer type for literal.");
    }
  } else if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    auto enumIt = enumRegistry.find(id->name);
    if (enumIt != enumRegistry.end()) {
      return ConstantInt::get(Type::getInt32Ty(context), enumIt->second);
    }
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
    if (auto *fn = module->getFunction(id->name)) {
      return fn;
    }
    throw runtime_error("Undefined identifier: " + id->name);
  } else if (auto arrAccess = std::dynamic_pointer_cast<ArrayAccess>(expr)) {
    llvm::Value *elemPtr = generateArrayElementPointer(arrAccess);
    PointerType *ptrType = dyn_cast<PointerType>(elemPtr->getType());
    if (!ptrType)
      throw runtime_error("Array access did not return a pointer.");

    // Handle array access on identifiers (e.g., arr[i])
    if (auto baseId = std::dynamic_pointer_cast<Identifier>(arrAccess->base)) {
      std::string elementTypeStr = getEffectiveType(*this, arrAccess->base);
      size_t bracketPos = elementTypeStr.find('[');
      if (bracketPos != string::npos) {
        elementTypeStr = elementTypeStr.substr(0, bracketPos);
      }
      while (!elementTypeStr.empty() && elementTypeStr.back() == '*')
        elementTypeStr.pop_back();
      llvm::Type *elemType = getLLVMType(elementTypeStr);
      return builder.CreateLoad(elemType, elemPtr, "arrayload");
    }
    // Handle array access on member access (e.g., struct.member[i] or
    // union.member[i])
    else if (auto baseMember =
                 std::dynamic_pointer_cast<MemberAccess>(arrAccess->base)) {
      string memberType = getEffectiveType(*this, baseMember);

      // Extract the element type from array type (e.g., "char[20]" -> "char")
      string elementTypeStr = memberType;
      size_t bracketPos = memberType.find('[');
      if (bracketPos != string::npos) {
        elementTypeStr = memberType.substr(0, bracketPos);
      }

      llvm::Type *elementType = getLLVMType(elementTypeStr);
      return builder.CreateLoad(elementType, elemPtr, "memberarrayload");
    } else {
      throw runtime_error("Array access on unsupported base type.");
    }
  } else if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    llvm::Value *ptr = generateLValue(expr);
    string effType = getEffectiveType(*this, expr);
    llvm::Type *loadType = getLLVMType(effType);
    llvm::Value *loaded = builder.CreateLoad(loadType, ptr, "memberload");
    if (auto *info = resolveMemberInfo(*this, *mem)) {
      if (info->bitWidth > 0 && loaded->getType()->isIntegerTy()) {
        loaded = maskBitfieldValue(builder, loaded,
                                   static_cast<unsigned>(info->bitWidth),
                                   info->isUnsigned);
      }
    }
    return loaded;
  } else if (auto call = std::dynamic_pointer_cast<FunctionCall>(expr)) {
    vector<llvm::Value *> args;
    for (auto &argExpr : call->arguments) {
      args.push_back(generateExpression(argExpr));
    }

    auto resolveCallable = [&](llvm::Value *ptr, const std::string *typeStr)
        -> std::pair<llvm::Value *, llvm::FunctionType *> {
      llvm::Value *calleeVal = ptr;
      llvm::FunctionType *fnTy = nullptr;

      auto applyTypeHint = [&](const std::string *hint) {
        if (!hint)
          return;
        std::string retTypeStr;
        std::vector<std::string> paramTypeStrs;
        std::string base = *hint;
        if (!parseFunctionPointerType(base, retTypeStr, paramTypeStrs)) {
          if (!base.empty() && base.back() == '*') {
            base.pop_back();
            parseFunctionPointerType(base, retTypeStr, paramTypeStrs);
          }
        }
        if (!retTypeStr.empty()) {
          std::vector<llvm::Type *> paramLLVMTypes;
          paramLLVMTypes.reserve(paramTypeStrs.size());
          for (const auto &p : paramTypeStrs) {
            paramLLVMTypes.push_back(getLLVMType(p));
          }
          fnTy = llvm::FunctionType::get(getLLVMType(retTypeStr),
                                         paramLLVMTypes, false);
        }
      };

      applyTypeHint(typeStr);

      if (auto *allocaInst = llvm::dyn_cast<llvm::AllocaInst>(calleeVal)) {
        calleeVal =
            builder.CreateLoad(allocaInst->getAllocatedType(), allocaInst,
                               call->functionName + ".fnptr");
      } else if (auto *global =
                     llvm::dyn_cast<llvm::GlobalVariable>(calleeVal)) {
        calleeVal = builder.CreateLoad(global->getValueType(), global,
                                       call->functionName + ".fnptr");
      }

      if (auto *func = llvm::dyn_cast<llvm::Function>(calleeVal)) {
        fnTy = func->getFunctionType();
        return {func, fnTy};
      }
      return std::make_pair(calleeVal, fnTy);
    };

    auto emitCall = [&](llvm::FunctionType *fnTy,
                        llvm::Value *calleeVal) -> llvm::Value * {
      if (!fnTy || !calleeVal)
        return nullptr;
      llvm::CallInst *callInst = builder.CreateCall(
          fnTy, calleeVal, args,
          fnTy->getReturnType()->isVoidTy() ? "" : "calltmp");
      if (fnTy->getReturnType()->isVoidTy()) {
        return ConstantInt::get(Type::getInt32Ty(context), 0);
      }
      return callInst;
    };

    if (call->hasCalleeExpr()) {
      std::string calleeType = getEffectiveType(*this, call->calleeExpr);
      llvm::Value *calleeVal = generateExpression(call->calleeExpr);
      auto [fnVal, fnTy] = resolveCallable(calleeVal, &calleeType);
      if (!fnTy) {
        if (auto *fn = llvm::dyn_cast<llvm::Function>(fnVal))
          fnTy = fn->getFunctionType();
      }
      if (auto *result = emitCall(fnTy, fnVal))
        return result;
      throw runtime_error("Attempting to call a non-callable expression.");
    }

    const std::string *typeStr = nullptr;
    auto typeIt = declaredTypeStrings.find(call->functionName);
    if (typeIt != declaredTypeStrings.end())
      typeStr = &typeIt->second;

    if (llvm::Value *localPtr = lookupLocalVar(call->functionName)) {
      auto [fnVal, fnTy] = resolveCallable(localPtr, typeStr);
      if (auto *result = emitCall(fnTy, fnVal))
        return result;
    }
    if (auto *gVar = module->getGlobalVariable(call->functionName)) {
      auto [fnVal, fnTy] = resolveCallable(gVar, typeStr);
      if (auto *result = emitCall(fnTy, fnVal))
        return result;
    }

    llvm::Function *callee = module->getFunction(call->functionName);
    if (!callee) {
      vector<llvm::Type *> paramTypes;
      if (call->functionName == "printf") {
        paramTypes.push_back(llvm::PointerType::get(context, 0));
      } else {
        paramTypes.reserve(args.size());
        for (auto *argVal : args) {
          paramTypes.push_back(argVal->getType());
        }
      }
      llvm::FunctionType *funcType =
          llvm::FunctionType::get(llvm::Type::getInt32Ty(context), paramTypes,
                                  call->functionName == "printf");
      callee = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage,
                                      call->functionName, module.get());
    }
    llvm::CallInst *directCall = builder.CreateCall(
        callee, args, callee->getReturnType()->isVoidTy() ? "" : "calltmp");
    if (callee->getReturnType()->isVoidTy()) {
      return ConstantInt::get(Type::getInt32Ty(context), 0);
    }
    return directCall;

  } else if (auto post = std::dynamic_pointer_cast<PostfixExpression>(expr)) {
    llvm::Value *ptr = generateLValue(post->operand);
    string effType = getEffectiveType(*this, post->operand);
    llvm::Type *valType = getLLVMType(effType);
    llvm::Value *oldVal = builder.CreateLoad(valType, ptr, "postfix.old");

    llvm::Value *newVal = nullptr;
    bool treatAsPointer =
        valType->isPointerTy() || (!effType.empty() && effType.back() == '*');
    if (treatAsPointer) {
      string elementTypeStr = effType;
      while (!elementTypeStr.empty() &&
             isspace(static_cast<unsigned char>(elementTypeStr.back()))) {
        elementTypeStr.pop_back();
      }
      while (!elementTypeStr.empty() && elementTypeStr.back() == '*') {
        elementTypeStr.pop_back();
        while (!elementTypeStr.empty() &&
               isspace(static_cast<unsigned char>(elementTypeStr.back()))) {
          elementTypeStr.pop_back();
        }
      }
      if (elementTypeStr.empty())
        throw runtime_error("Unsupported pointer type for postfix operator.");
      llvm::Type *elemTy = getLLVMType(elementTypeStr);
      llvm::Value *step = ConstantInt::get(Type::getInt32Ty(context),
                                           post->op == "++" ? 1 : -1);
      llvm::Value *ptrValue = oldVal;
      if (!oldVal->getType()->isPointerTy()) {
        ptrValue = builder.CreateIntToPtr(
            oldVal, llvm::PointerType::getUnqual(elemTy), "postfix.ptrcast");
      }
      newVal =
          builder.CreateGEP(elemTy, ptrValue, step,
                            post->op == "++" ? "postinc.ptr" : "postdec.ptr");
    } else {
      llvm::Value *one = nullptr;
      if (valType->isFloatingPointTy())
        one = ConstantFP::get(valType, 1.0);
      else if (valType->isIntegerTy())
        one = ConstantInt::get(valType, 1);
      else
        throw runtime_error("Unsupported type for postfix operator.");

      if (post->op == "++") {
        newVal = valType->isFloatingPointTy()
                     ? builder.CreateFAdd(oldVal, one, "postinc")
                     : builder.CreateAdd(oldVal, one, "postinc");
      } else {
        newVal = valType->isFloatingPointTy()
                     ? builder.CreateFSub(oldVal, one, "postdec")
                     : builder.CreateSub(oldVal, one, "postdec");
      }
    }

    builder.CreateStore(newVal, ptr);
    return oldVal;
  } else if (auto ternary =
                 std::dynamic_pointer_cast<TernaryExpression>(expr)) {
    llvm::Value *condVal = generateExpression(ternary->condition);
    if (condVal->getType() != Type::getInt1Ty(context)) {
      condVal = builder.CreateICmpNE(
          condVal, ConstantInt::get(condVal->getType(), 0), "ternarycond");
    }
    llvm::Value *trueVal = generateExpression(ternary->trueExpr);
    llvm::Value *falseVal = generateExpression(ternary->falseExpr);
    if (trueVal->getType() != falseVal->getType()) {
      if (trueVal->getType()->isIntegerTy() &&
          falseVal->getType()->isIntegerTy()) {
        if (trueVal->getType()->getIntegerBitWidth() <
            falseVal->getType()->getIntegerBitWidth()) {
          trueVal = builder.CreateSExt(trueVal, falseVal->getType(), "sexttmp");
        } else {
          falseVal =
              builder.CreateSExt(falseVal, trueVal->getType(), "sexttmp");
        }
      }
    }
    return builder.CreateSelect(condVal, trueVal, falseVal, "selecttmp");
  } else if (auto sizeofExpr =
                 std::dynamic_pointer_cast<SizeOfExpression>(expr)) {
    if (sizeofExpr->isType) {
      llvm::Type *type = getLLVMType(sizeofExpr->typeName);
      auto DL = module->getDataLayout();
      uint64_t size = DL.getTypeAllocSize(type);
      return ConstantInt::get(Type::getInt32Ty(context), size);
    } else {
      llvm::Value *operand = generateExpression(sizeofExpr->operand);
      llvm::Type *operandType = operand->getType();
      if (operandType->isPointerTy()) {
        string effectiveType = getEffectiveType(*this, sizeofExpr->operand);
        while (!effectiveType.empty() && effectiveType.back() == '*')
          effectiveType.pop_back();
        llvm::Type *pointeeType = getLLVMType(effectiveType);
        auto DL = module->getDataLayout();
        uint64_t size = DL.getTypeAllocSize(pointeeType);
        return ConstantInt::get(Type::getInt32Ty(context), size);
      } else {
        auto DL = module->getDataLayout();
        uint64_t size = DL.getTypeAllocSize(operandType);
        return ConstantInt::get(Type::getInt32Ty(context), size);
      }
    }
  }
  throw runtime_error("Unsupported expression type in generateExpression().");
}
