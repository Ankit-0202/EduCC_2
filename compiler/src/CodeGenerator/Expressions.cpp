#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "CodeGenerator/Helpers.hpp"
#include "Debug.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"

#include <iostream>
#include <limits>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Intrinsics.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/raw_ostream.h>
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
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] generateArrayElementPointer: begin\n";
  // Collect the full chain of indices (e.g., matrix[i][j][k])
  vector<ExpressionPtr> indices;
  ExpressionPtr baseExpr = arr->base;
  indices.push_back(arr->index);
  while (auto nested = std::dynamic_pointer_cast<ArrayAccess>(baseExpr)) {
    indices.push_back(nested->index);
    baseExpr = nested->base;
  }
  std::reverse(indices.begin(), indices.end());

  auto extractDimStrings = [](const std::string &typeStr) {
    std::vector<std::string> dims;
    size_t pos = 0;
    while ((pos = typeStr.find('[', pos)) != std::string::npos) {
      size_t end = typeStr.find(']', pos);
      if (end == std::string::npos)
        break;
      dims.push_back(typeStr.substr(pos + 1, end - pos - 1));
      pos = end + 1;
    }
    return dims;
  };

  auto castToI64 = [&](llvm::Value *v, const std::string &name) {
    if (v->getType()->isIntegerTy(64))
      return v;
    if (v->getType()->isIntegerTy())
      return builder.CreateIntCast(v, Type::getInt64Ty(context), true,
                                   name + ".idx.cast");
    return builder.CreatePtrToInt(v, Type::getInt64Ty(context),
                                  name + ".idx.ptrint");
  };

  auto dataPointerForBase = [&](const ExpressionPtr &expr,
                                const std::string &name) -> llvm::Value * {
    llvm::Value *basePtr = generateLValue(expr);
    if (dynamicArrayVars.find(name) != dynamicArrayVars.end())
      return basePtr;
    if (auto *allocaInst = dyn_cast<AllocaInst>(basePtr)) {
      llvm::Type *allocTy = allocaInst->getAllocatedType();
      if (allocTy->isArrayTy()) {
        return builder.CreateGEP(
            allocTy, basePtr,
            {ConstantInt::get(Type::getInt32Ty(context), 0),
             ConstantInt::get(Type::getInt32Ty(context), 0)},
            name + ".decay");
      }
      return builder.CreateLoad(allocTy, basePtr, name + ".ptr");
    }
    if (auto *global = dyn_cast<GlobalVariable>(basePtr)) {
      llvm::Type *valTy = global->getValueType();
      if (valTy->isArrayTy()) {
        return builder.CreateGEP(
            valTy, global,
            {ConstantInt::get(Type::getInt32Ty(context), 0),
             ConstantInt::get(Type::getInt32Ty(context), 0)},
            name + ".decay");
      }
      return builder.CreateLoad(valTy, global, name + ".ptr");
    }
    return basePtr;
  };

  // Fast path: identifier base (covers nested accesses too)
  if (auto baseId = std::dynamic_pointer_cast<Identifier>(baseExpr)) {
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] generateArrayElementPointer: base identifier "
                << baseId->name << " indices=" << indices.size() << std::endl;
    std::vector<llvm::Value *> idxVals;
    idxVals.reserve(indices.size());
    for (size_t i = 0; i < indices.size(); ++i) {
      idxVals.push_back(castToI64(generateExpression(indices[i]),
                                  baseId->name + ".idx" + std::to_string(i)));
    }

    std::vector<llvm::Value *> dimVals;
    auto dimIt = dynamicArrayDimensions.find(baseId->name);
    if (dimIt != dynamicArrayDimensions.end()) {
      dimVals = dimIt->second;
    } else {
      auto typeIt = declaredTypeStrings.find(baseId->name);
      if (typeIt != declaredTypeStrings.end()) {
        for (const auto &d : extractDimStrings(typeIt->second)) {
          if (d.empty())
            continue;
          try {
            long long v = std::stoll(d);
            dimVals.push_back(ConstantInt::get(Type::getInt64Ty(context), v));
          } catch (...) {
            if (auto *ptr = lookupLocalVar(d)) {
              llvm::Type *valTy = nullptr;
              auto tIt = declaredTypes.find(d);
              if (tIt != declaredTypes.end())
                valTy = tIt->second;
              if (!valTy)
                valTy = Type::getInt32Ty(context);
              llvm::Value *loaded =
                  builder.CreateLoad(valTy, ptr, d + ".ld.dim");
              dimVals.push_back(castToI64(loaded, d));
            }
          }
        }
      }
    }

    // Use the innermost dimensions we have available.
    size_t needed = idxVals.size() > 0 ? idxVals.size() - 1 : 0;
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] generateArrayElementPointer: dimVals="
                << dimVals.size() << " needed=" << needed << std::endl;
    if (!idxVals.empty() && dimVals.size() >= needed) {
      size_t start = dimVals.size() - needed;
      llvm::Value *offset = idxVals[0];
      for (size_t i = 0; i < needed; ++i) {
        llvm::Value *dim =
            castToI64(dimVals[start + i],
                      baseId->name + ".dim" + std::to_string(start + i));
        offset = builder.CreateMul(offset, dim, "array.mul");
        offset = builder.CreateAdd(offset, idxVals[i + 1], "array.add");
      }

      std::string elemTypeStr = declaredTypeStrings.count(baseId->name)
                                    ? declaredTypeStrings[baseId->name]
                                    : getEffectiveType(*this, baseExpr);
      if (educcDebugEnabled())
        std::cerr << "[DEBUG] generateArrayElementPointer: elem type string '"
                  << elemTypeStr << "'" << std::endl;
      size_t lb = elemTypeStr.find('[');
      bool hadBracket = lb != std::string::npos;
      if (hadBracket)
        elemTypeStr = elemTypeStr.substr(0, lb);
      if (!hadBracket && !elemTypeStr.empty() && elemTypeStr.back() == '*')
        elemTypeStr.pop_back();
      llvm::Type *elemTy = getLLVMType(elemTypeStr);
      llvm::Value *dataPtr = dataPointerForBase(baseExpr, baseId->name);
      return builder.CreateGEP(elemTy, dataPtr, offset, baseId->name + ".flat");
    }
  }

  // Handle array access on member access (e.g., struct.member[i] or
  // union.member[i])
  if (auto baseMember = std::dynamic_pointer_cast<MemberAccess>(arr->base)) {
    llvm::Value *basePtr = generateLValue(baseMember);
    string memberType = getEffectiveType(*this, baseMember);
    // Extract the element type for the member (strip one array dim or pointer
    // star).
    string elementTypeStr = memberType;
    size_t bracketPos = elementTypeStr.find('[');
    std::string bracketContent;
    if (bracketPos != string::npos) {
      size_t rb = elementTypeStr.find(']', bracketPos);
      if (rb != string::npos)
        bracketContent =
            elementTypeStr.substr(bracketPos + 1, rb - bracketPos - 1);
      elementTypeStr = elementTypeStr.substr(0, bracketPos);
    }
    if (bracketPos == string::npos && !elementTypeStr.empty() &&
        elementTypeStr.back() == '*')
      elementTypeStr.pop_back();
    llvm::Type *elementType = getLLVMType(elementTypeStr);
    llvm::Value *indexVal = generateExpression(arr->index);
    if (!indexVal->getType()->isIntegerTy(32))
      indexVal = builder.CreateIntCast(indexVal, Type::getInt32Ty(context),
                                       true, "arrayidxcast");
    if (bracketPos != string::npos) {
      uint64_t arraySize = 0;
      try {
        if (!bracketContent.empty())
          arraySize = static_cast<uint64_t>(std::stoll(bracketContent));
      } catch (...) {
      }
      llvm::ArrayType *arrTy = llvm::ArrayType::get(elementType, arraySize);
      std::vector<llvm::Value *> indicesVec;
      indicesVec.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
      indicesVec.push_back(indexVal);
      return builder.CreateGEP(arrTy, basePtr, indicesVec, "memberarraygep");
    }
    return builder.CreateGEP(elementType, basePtr, indexVal, "memberarraygep");
  }

  // Fallback to nested handling.
  if (auto nested = std::dynamic_pointer_cast<ArrayAccess>(arr->base)) {
    llvm::Value *baseElemPtr = generateArrayElementPointer(nested);
    auto *ptrTy = llvm::dyn_cast<llvm::PointerType>(baseElemPtr->getType());
    if (!ptrTy)
      throw runtime_error("Array access on unsupported base type (nested)");
    std::string elemTypeStr = getEffectiveType(*this, arr->base);
    if (!elemTypeStr.empty() && elemTypeStr.back() == '*')
      elemTypeStr.pop_back();
    llvm::Type *elemTy = getLLVMType(elemTypeStr);
    llvm::Value *indexVal = generateExpression(arr->index);
    if (!indexVal->getType()->isIntegerTy(32))
      indexVal = builder.CreateIntCast(indexVal, Type::getInt32Ty(context),
                                       true, "arrayidxcast");
    return builder.CreateGEP(elemTy, baseElemPtr, indexVal, "arrayidxnested");
  }

  llvm::Value *baseVal = nullptr;
  try {
    baseVal = generateLValue(arr->base);
  } catch (...) {
  }
  if (baseVal && baseVal->getType()->isPointerTy()) {
    std::string elemTypeStr = getEffectiveType(*this, arr->base);
    size_t lb = elemTypeStr.find('[');
    if (lb != std::string::npos)
      elemTypeStr = elemTypeStr.substr(0, lb);
    if (!elemTypeStr.empty() && elemTypeStr.back() == '*')
      elemTypeStr.pop_back();
    llvm::Type *elemTy = getLLVMType(elemTypeStr);
    llvm::Value *indexVal = generateExpression(arr->index);
    if (!indexVal->getType()->isIntegerTy(32))
      indexVal = builder.CreateIntCast(indexVal, Type::getInt32Ty(context),
                                       true, "arrayidxcast");
    return builder.CreateGEP(elemTy, baseVal, indexVal, "arrayidxgeneric");
  }

  // Generic fallback: treat a[b] as *(a + b) and allow the commutative form.
  llvm::Value *lhsVal = generateExpression(arr->base);
  llvm::Value *idxVal = generateExpression(arr->index);
  if (lhsVal->getType()->isPointerTy() && idxVal->getType()->isIntegerTy()) {
    std::string elemTypeStr = getEffectiveType(*this, arr->base);
    size_t lb = elemTypeStr.find('[');
    if (lb != std::string::npos)
      elemTypeStr = elemTypeStr.substr(0, lb);
    while (!elemTypeStr.empty() && elemTypeStr.back() == '*')
      elemTypeStr.pop_back();
    llvm::Type *elemTy = getLLVMType(elemTypeStr);
    return builder.CreateGEP(elemTy, lhsVal, idxVal, "arrayidxfallback");
  }
  if (idxVal->getType()->isPointerTy() && lhsVal->getType()->isIntegerTy()) {
    std::string elemTypeStr = getEffectiveType(*this, arr->index);
    size_t lb = elemTypeStr.find('[');
    if (lb != std::string::npos)
      elemTypeStr = elemTypeStr.substr(0, lb);
    while (!elemTypeStr.empty() && elemTypeStr.back() == '*')
      elemTypeStr.pop_back();
    llvm::Type *elemTy = getLLVMType(elemTypeStr);
    return builder.CreateGEP(elemTy, idxVal, lhsVal, "arrayidxfallback");
  }
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] generateArrayElementPointer: unsupported base type\n";
  throw runtime_error("Array access on unsupported base type (final)");
}

// Add or extend generateExpression to support bitwise NOT (~)
llvm::Value *CodeGenerator::generateExpression(const ExpressionPtr &expr) {
  if (auto binExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] Binary expression: " << binExpr->op << std::endl;

    // The comma operator is strictly left-to-right and sequenced.
    if (binExpr->op == ",") {
      generateExpression(binExpr->left);
      return generateExpression(binExpr->right);
    }

    auto isUnsignedType = [](const std::string &t) {
      if (t.find("unsigned") != std::string::npos)
        return true;
      return t == "size_t" || t == "uintptr_t" || t == "uint8_t" ||
             t == "uint16_t" || t == "uint32_t" || t == "uint64_t";
    };
    std::string lhsTypeStr = getEffectiveType(*this, binExpr->left);
    std::string rhsTypeStr = getEffectiveType(*this, binExpr->right);
    bool lhsUnsigned = isUnsignedType(lhsTypeStr);
    bool rhsUnsigned = isUnsignedType(rhsTypeStr);
    bool useUnsignedOps = lhsUnsigned || rhsUnsigned;
    auto *complexTy =
        StructType::get(Type::getDoubleTy(context), Type::getDoubleTy(context));
    auto isComplexStruct = [&](llvm::Value *v) {
      if (auto *st = dyn_cast<StructType>(v->getType())) {
        return st->getNumElements() == 2 &&
               st->getElementType(0)->isDoubleTy() &&
               st->getElementType(1)->isDoubleTy();
      }
      return false;
    };
    auto toBool = [&](llvm::Value *v,
                      const std::string &tag = "booltmp") -> llvm::Value * {
      if (v->getType()->isIntegerTy(1))
        return v;
      if (v->getType()->isPointerTy()) {
        return builder.CreateICmpNE(
            v,
            ConstantPointerNull::get(
                llvm::cast<llvm::PointerType>(v->getType())),
            tag);
      }
      if (v->getType()->isIntegerTy()) {
        return builder.CreateICmpNE(v, ConstantInt::get(v->getType(), 0), tag);
      }
      if (v->getType()->isFloatingPointTy()) {
        return builder.CreateFCmpONE(v, ConstantFP::get(v->getType(), 0.0),
                                     tag);
      }
      return v;
    };

    if (binExpr->op == "&&" || binExpr->op == "||") {
      llvm::Value *lhsVal = toBool(generateExpression(binExpr->left),
                                   binExpr->op == "&&" ? "lhs.and" : "lhs.or");
      Function *fn = builder.GetInsertBlock()->getParent();
      BasicBlock *rhsBB = BasicBlock::Create(
          context, binExpr->op == "&&" ? "logic.and.rhs" : "logic.or.rhs", fn);
      BasicBlock *mergeBB = BasicBlock::Create(
          context, binExpr->op == "&&" ? "logic.and.merge" : "logic.or.merge",
          fn);
      BasicBlock *startBB = builder.GetInsertBlock();
      if (binExpr->op == "&&")
        builder.CreateCondBr(lhsVal, rhsBB, mergeBB);
      else
        builder.CreateCondBr(lhsVal, mergeBB, rhsBB);

      builder.SetInsertPoint(rhsBB);
      llvm::Value *rhsVal = toBool(generateExpression(binExpr->right),
                                   binExpr->op == "&&" ? "rhs.and" : "rhs.or");
      BasicBlock *rhsExitBB = builder.GetInsertBlock();
      if (!rhsExitBB->getTerminator())
        builder.CreateBr(mergeBB);
      rhsBB = rhsExitBB;

      builder.SetInsertPoint(mergeBB);
      PHINode *phi =
          builder.CreatePHI(Type::getInt1Ty(context), 2,
                            binExpr->op == "&&" ? "and.phi" : "or.phi");
      if (binExpr->op == "&&") {
        phi->addIncoming(rhsVal, rhsBB);
        phi->addIncoming(ConstantInt::getFalse(context), startBB);
      } else {
        phi->addIncoming(ConstantInt::getTrue(context), startBB);
        phi->addIncoming(rhsVal, rhsBB);
      }
      return phi;
    }

    // GCC typically evaluates binary operands right-to-left; mirror that order
    // so side effects match its behaviour in unspecified cases.
    llvm::Value *rhs = generateExpression(binExpr->right);
    llvm::Value *lhs = generateExpression(binExpr->left);
    auto makeComplex = [&](llvm::Value *re, llvm::Value *im,
                           StructType *ty = nullptr) {
      StructType *useTy = ty ? ty : complexTy;
      llvm::Value *undef = UndefValue::get(useTy);
      llvm::Value *withReal = builder.CreateInsertValue(undef, re, 0);
      return builder.CreateInsertValue(withReal, im, 1);
    };
    auto toComplexVal = [&](llvm::Value *v) -> llvm::Value * {
      if (isComplexStruct(v))
        return v;
      llvm::Value *realPart = nullptr;
      if (v->getType()->isDoubleTy())
        realPart = v;
      else if (v->getType()->isFloatTy())
        realPart =
            builder.CreateFPExt(v, Type::getDoubleTy(context), "cplx.cast");
      else if (v->getType()->isIntegerTy())
        realPart =
            builder.CreateSIToFP(v, Type::getDoubleTy(context), "cplx.cast");
      else
        return v;
      llvm::Value *imagPart = ConstantFP::get(Type::getDoubleTy(context), 0.0);
      return makeComplex(realPart, imagPart);
    };
    if (isComplexStruct(lhs) || isComplexStruct(rhs)) {
      lhs = toComplexVal(lhs);
      rhs = toComplexVal(rhs);
      auto *resTy = dyn_cast<StructType>(lhs->getType());
      auto extractParts = [&](llvm::Value *v) {
        return std::make_pair(builder.CreateExtractValue(v, 0, "c.re"),
                              builder.CreateExtractValue(v, 1, "c.im"));
      };
      auto [lr, li] = extractParts(lhs);
      auto [rr, ri] = extractParts(rhs);
      if (binExpr->op == "+") {
        return makeComplex(builder.CreateFAdd(lr, rr, "cadd.r"),
                           builder.CreateFAdd(li, ri, "cadd.i"), resTy);
      } else if (binExpr->op == "-") {
        return makeComplex(builder.CreateFSub(lr, rr, "csub.r"),
                           builder.CreateFSub(li, ri, "csub.i"), resTy);
      } else if (binExpr->op == "*") {
        llvm::Value *real =
            builder.CreateFSub(builder.CreateFMul(lr, rr, "cmul.rr"),
                               builder.CreateFMul(li, ri, "cmul.ii"), "cmul.r");
        llvm::Value *imag =
            builder.CreateFAdd(builder.CreateFMul(lr, ri, "cmul.ri"),
                               builder.CreateFMul(li, rr, "cmul.ir"), "cmul.i");
        return makeComplex(real, imag, resTy);
      }
    }

    // Only perform conversion if neither operand is a pointer arithmetic case.
    auto promoteInteger = [&](llvm::Value *v,
                              bool isUnsigned) -> llvm::Value * {
      if (v->getType()->isIntegerTy() &&
          v->getType()->getIntegerBitWidth() < 32) {
        if (v->getType()->isIntegerTy(1)) {
          return builder.CreateZExt(v, Type::getInt32Ty(context),
                                    "boolpromote");
        }
        return isUnsigned ? builder.CreateZExt(v, Type::getInt32Ty(context),
                                               "intpromote")
                          : builder.CreateSExt(v, Type::getInt32Ty(context),
                                               "intpromote");
      }
      return v;
    };
    lhs = promoteInteger(lhs, lhsUnsigned);
    rhs = promoteInteger(rhs, rhsUnsigned);

    auto normalizePointerInt = [&](llvm::Value *&a, llvm::Value *&b) {
      if (a->getType()->isPointerTy() && b->getType()->isIntegerTy()) {
        auto *intptrTy = module->getDataLayout().getIntPtrType(context);
        a = builder.CreatePtrToInt(a, intptrTy, "ptrtoint.lhs");
        if (b->getType() != intptrTy)
          b = builder.CreateIntCast(b, intptrTy, false, "ptrint.rhs.cast");
      } else if (b->getType()->isPointerTy() && a->getType()->isIntegerTy()) {
        auto *intptrTy = module->getDataLayout().getIntPtrType(context);
        b = builder.CreatePtrToInt(b, intptrTy, "ptrtoint.rhs");
        if (a->getType() != intptrTy)
          a = builder.CreateIntCast(a, intptrTy, false, "ptrint.lhs.cast");
      }
    };

    if (!((lhs->getType()->isPointerTy() && rhs->getType()->isIntegerTy()) ||
          (rhs->getType()->isPointerTy() && lhs->getType()->isIntegerTy()))) {
      if (lhs->getType() != rhs->getType()) {
        if (lhs->getType()->isIntegerTy() &&
            rhs->getType()->isFloatingPointTy()) {
          lhs = lhsUnsigned
                    ? builder.CreateUIToFP(lhs, rhs->getType(), "uitofp")
                    : builder.CreateSIToFP(lhs, rhs->getType(), "sitofp");
        } else if (lhs->getType()->isFloatingPointTy() &&
                   rhs->getType()->isIntegerTy()) {
          rhs = rhsUnsigned
                    ? builder.CreateUIToFP(rhs, lhs->getType(), "uitofp")
                    : builder.CreateSIToFP(rhs, lhs->getType(), "sitofp");
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
            lhs = lhsUnsigned ? builder.CreateZExt(lhs, rhs->getType(), "zext")
                              : builder.CreateSExt(lhs, rhs->getType(), "sext");
          } else if (rhs->getType()->getIntegerBitWidth() <
                     lhs->getType()->getIntegerBitWidth()) {
            rhs = rhsUnsigned ? builder.CreateZExt(rhs, lhs->getType(), "zext")
                              : builder.CreateSExt(rhs, lhs->getType(), "sext");
          }
        } else {
          throw runtime_error("Incompatible types in binary expression.");
        }
      }
    }
    auto decayPointerElementType = [](std::string t) {
      size_t lb = t.find('[');
      if (lb != std::string::npos) {
        size_t rb = t.find(']', lb);
        std::string suffix = (rb != std::string::npos) ? t.substr(rb + 1) : "";
        t = t.substr(0, lb) + suffix;
      }
      while (!t.empty() && t.back() == '*') {
        t.pop_back();
        while (!t.empty() && isspace(static_cast<unsigned char>(t.back()))) {
          t.pop_back();
        }
      }
      return t;
    };

    if (binExpr->op == "+") {
      if (lhs->getType()->isPointerTy() && rhs->getType()->isIntegerTy()) {
        string effectiveType =
            decayPointerElementType(getEffectiveType(*this, binExpr->left));
        llvm::Type *elemTy = getLLVMType(effectiveType);
        return builder.CreateGEP(elemTy, lhs, rhs, "ptraddtmp");
      } else if (rhs->getType()->isPointerTy() &&
                 lhs->getType()->isIntegerTy()) {
        string effectiveType =
            decayPointerElementType(getEffectiveType(*this, binExpr->right));
        llvm::Type *elemTy = getLLVMType(effectiveType);
        return builder.CreateGEP(elemTy, rhs, lhs, "ptraddtmp");
      } else {
        return lhs->getType()->isFloatingPointTy()
                   ? builder.CreateFAdd(lhs, rhs, "faddtmp")
                   : builder.CreateAdd(lhs, rhs, "addtmp");
      }
    } else if (binExpr->op == "-") {
      if (lhs->getType()->isPointerTy() && rhs->getType()->isIntegerTy()) {
        string effectiveType =
            decayPointerElementType(getEffectiveType(*this, binExpr->left));
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
        string effectiveType =
            decayPointerElementType(getEffectiveType(*this, binExpr->left));
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
                 : (useUnsignedOps ? builder.CreateUDiv(lhs, rhs, "divtmp")
                                   : builder.CreateSDiv(lhs, rhs, "divtmp"));
    } else if (binExpr->op == "%") {
      if (lhs->getType()->isIntegerTy()) {
        return useUnsignedOps ? builder.CreateURem(lhs, rhs, "modtmp")
                              : builder.CreateSRem(lhs, rhs, "modtmp");
      } else if (lhs->getType()->isFloatingPointTy()) {
        return builder.CreateFRem(lhs, rhs, "modtmp");
      } else {
        throw runtime_error("Unsupported types for modulo operator.");
      }
    } else if (binExpr->op == ",") {
      // Comma operator: evaluate LHS for side effects, result is RHS.
      return rhs;
    } else if (binExpr->op == "<=") {
      normalizePointerInt(lhs, rhs);
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
                 : (useUnsignedOps ? builder.CreateICmpULE(lhs, rhs, "cmptmp")
                                   : builder.CreateICmpSLE(lhs, rhs, "cmptmp"));
    } else if (binExpr->op == "<") {
      normalizePointerInt(lhs, rhs);
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
                 : (useUnsignedOps ? builder.CreateICmpULT(lhs, rhs, "cmptmp")
                                   : builder.CreateICmpSLT(lhs, rhs, "cmptmp"));
    } else if (binExpr->op == ">=") {
      normalizePointerInt(lhs, rhs);
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
                 : (useUnsignedOps ? builder.CreateICmpUGE(lhs, rhs, "cmptmp")
                                   : builder.CreateICmpSGE(lhs, rhs, "cmptmp"));
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
                 : (useUnsignedOps ? builder.CreateICmpUGT(lhs, rhs, "cmptmp")
                                   : builder.CreateICmpSGT(lhs, rhs, "cmptmp"));
    } else if (binExpr->op == "==") {
      normalizePointerInt(lhs, rhs);
      if (lhs->getType()->isPointerTy() && rhs->getType()->isPointerTy()) {
        return builder.CreateICmpEQ(lhs, rhs, "ptreqtmp");
      }
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOEQ(lhs, rhs, "cmptmp")
                 : builder.CreateICmpEQ(lhs, rhs, "cmptmp");
    } else if (binExpr->op == "!=") {
      normalizePointerInt(lhs, rhs);
      if (lhs->getType()->isPointerTy() && rhs->getType()->isPointerTy()) {
        return builder.CreateICmpNE(lhs, rhs, "ptrnetmp");
      }
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpONE(lhs, rhs, "cmptmp")
                 : builder.CreateICmpNE(lhs, rhs, "cmptmp");
    } else if (binExpr->op == "&") {
      return builder.CreateAnd(lhs, rhs, "bitandtmp");
    } else if (binExpr->op == "^") {
      return builder.CreateXor(lhs, rhs, "bitxortmp");
    } else if (binExpr->op == "|") {
      return builder.CreateOr(lhs, rhs, "bitor_tmp");
    } else if (binExpr->op == "<<") {
      return builder.CreateShl(lhs, rhs, "shltmp");
    } else if (binExpr->op == ">>") {
      return lhsUnsigned ? builder.CreateLShr(lhs, rhs, "shrtmp")
                         : builder.CreateAShr(lhs, rhs, "shrtmp");
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
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] Assignment: generated LHS pointer\n";
    llvm::Value *rhsVal = generateExpression(assign->rhs);
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] Assignment: generated RHS value\n";

    string targetTypeStr = getEffectiveType(*this, assign->lhs);
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] Assignment: target type " << targetTypeStr << "\n";
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
      } else if (targetType->isPointerTy()) {
        if (rhsType->isPointerTy()) {
          rhsVal = builder.CreateBitCast(rhsVal, targetType, "ptrcast");
        } else if (rhsType->isIntegerTy()) {
          rhsVal = builder.CreateIntToPtr(rhsVal, targetType, "inttoptr");
        }
      }
    }

    builder.CreateStore(rhsVal, ptr);
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] Assignment: stored value\n";
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
      string baseTypeStr = getEffectiveType(*this, unExpr->operand);
      llvm::Value *ptrVal = generateExpression(unExpr->operand);

      // Dereferencing a function pointer is a no-op in codegen; the value is
      // already the callable pointer.
      if (baseTypeStr.rfind("fnptr:", 0) == 0 &&
          (baseTypeStr.empty() || baseTypeStr.back() != '*')) {
        return ptrVal;
      }

      if (!ptrVal->getType()->isPointerTy())
        throw runtime_error("Dereference operator on non-pointer type.");

      // Handle pointer-to-function-pointer where one star should be removed.
      if (baseTypeStr.rfind("fnptr:", 0) == 0 && !baseTypeStr.empty() &&
          baseTypeStr.back() == '*') {
        baseTypeStr.pop_back();
        llvm::Type *pointeeTy = getLLVMType(baseTypeStr);
        return builder.CreateLoad(pointeeTy, ptrVal, "deref");
      }

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
      if (!operand->getType()->isIntegerTy(1)) {
        if (operand->getType()->isPointerTy()) {
          operand = builder.CreateICmpNE(
              operand,
              ConstantPointerNull::get(
                  llvm::cast<llvm::PointerType>(operand->getType())),
              "booltmp");
        } else {
          operand = builder.CreateICmpNE(
              operand, ConstantInt::get(operand->getType(), 0), "booltmp");
        }
      }
      return builder.CreateNot(operand, "nottmp");
    } else if (unExpr->op == "~") {
      llvm::Value *operand = generateExpression(unExpr->operand);
      if (!operand->getType()->isIntegerTy())
        throw runtime_error(
            "CodeGenerator Error: Bitwise NOT '~' applied to non-integer type");
      return builder.CreateNot(operand, "bnot");
    } else if (unExpr->op == "++" || unExpr->op == "--") {
      llvm::Value *ptr = generateLValue(unExpr->operand);
      std::string effType = getEffectiveType(*this, unExpr->operand);
      llvm::Type *valType = getLLVMType(effType);
      llvm::Value *oldVal = builder.CreateLoad(valType, ptr, "pre.old");
      llvm::Value *newVal = nullptr;
      bool treatAsPointer =
          valType->isPointerTy() || (!effType.empty() && effType.back() == '*');
      if (treatAsPointer) {
        std::string elementTypeStr = effType;
        while (!elementTypeStr.empty() && elementTypeStr.back() == '*') {
          elementTypeStr.pop_back();
          while (!elementTypeStr.empty() &&
                 isspace(static_cast<unsigned char>(elementTypeStr.back()))) {
            elementTypeStr.pop_back();
          }
        }
        if (elementTypeStr.empty())
          throw runtime_error("Unsupported pointer type for prefix operator.");
        llvm::Type *elemTy = getLLVMType(elementTypeStr);
        llvm::Value *step = ConstantInt::get(Type::getInt32Ty(context),
                                             unExpr->op == "++" ? 1 : -1);
        llvm::Value *ptrValue = oldVal;
        if (!oldVal->getType()->isPointerTy()) {
          ptrValue = builder.CreateIntToPtr(
              oldVal, llvm::PointerType::getUnqual(elemTy), "pre.ptrcast");
        }
        newVal =
            builder.CreateGEP(elemTy, ptrValue, step,
                              unExpr->op == "++" ? "preinc.ptr" : "predec.ptr");
      } else {
        llvm::Value *one = nullptr;
        if (valType->isFloatingPointTy())
          one = ConstantFP::get(valType, 1.0);
        else if (valType->isIntegerTy())
          one = ConstantInt::get(valType, 1);
        else
          throw runtime_error("Unsupported type for prefix operator.");
        newVal = (unExpr->op == "++")
                     ? builder.CreateAdd(oldVal, one, "preinc")
                     : builder.CreateSub(oldVal, one, "predec");
      }
      builder.CreateStore(newVal, ptr);
      return newVal;
    }
    throw runtime_error("Unsupported unary operator: " + unExpr->op);
  } else if (auto alignExpr =
                 std::dynamic_pointer_cast<AlignOfExpression>(expr)) {
    std::string typeName;
    if (alignExpr->isType) {
      typeName = alignExpr->typeName;
    } else {
      typeName = getEffectiveType(*this, alignExpr->operand);
    }
    llvm::Type *ty = getLLVMType(typeName);
    unsigned align = module->getDataLayout().getABITypeAlign(ty).value();
    return ConstantInt::get(Type::getInt32Ty(context), align);
  } else if (auto gen = std::dynamic_pointer_cast<GenericSelection>(expr)) {
    auto normalize = [](std::string t) {
      auto strip = [](std::string &s, const std::string &p) {
        if (s.rfind(p, 0) == 0) {
          s = s.substr(p.size());
          while (!s.empty() && s.front() == ' ')
            s.erase(s.begin());
        }
      };
      strip(t, "const ");
      strip(t, "volatile ");
      strip(t, "static ");
      strip(t, "_Atomic ");
      return t;
    };
    std::string selectorType =
        normalize(getEffectiveType(*this, gen->selector));
    if (auto litSel = std::dynamic_pointer_cast<Literal>(gen->selector)) {
      if (litSel->type == Literal::LiteralType::String)
        selectorType = "char[]";
    }
    for (auto &assoc : gen->associations) {
      if (normalize(assoc.first) == selectorType) {
        return generateExpression(assoc.second);
      }
    }
    if (gen->defaultExpr)
      return generateExpression(gen->defaultExpr.value());
    return ConstantInt::get(Type::getInt32Ty(context), 0);
  } else if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
    switch (lit->type) {
    case Literal::LiteralType::Int: {
      std::string litTy = !lit->literalType.empty() ? lit->literalType : "int";
      bool unsignedLit =
          lit->isUnsignedLiteral || litTy.find("unsigned") != std::string::npos;
      bool is64 = (litTy.find("long long") != std::string::npos) ||
                  (litTy == "long") || (litTy == "unsigned long");
      llvm::Type *ty =
          is64 ? Type::getInt64Ty(context) : Type::getInt32Ty(context);
      uint64_t val =
          unsignedLit ? lit->uintValue : static_cast<uint64_t>(lit->intValue);
      return ConstantInt::get(ty, val, !unsignedLit);
    }
    case Literal::LiteralType::Float:
      return ConstantFP::get(Type::getFloatTy(context), lit->floatValue);
    case Literal::LiteralType::Double:
      return ConstantFP::get(Type::getDoubleTy(context), lit->doubleValue);
    case Literal::LiteralType::Char:
      return ConstantInt::get(Type::getInt8Ty(context), lit->charValue);
    case Literal::LiteralType::Bool:
      return ConstantInt::get(Type::getInt1Ty(context), lit->boolValue);
    case Literal::LiteralType::String: {
      if (educcDebugEnabled())
        std::cerr << "[DEBUG] String literal length=" << lit->stringValue.size()
                  << std::endl;
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
  } else if (auto compLit = std::dynamic_pointer_cast<CompoundLiteral>(expr)) {
    std::string baseType = compLit->type;
    // Strip pointer stars for array compound literals.
    while (!baseType.empty() && baseType.back() == '*')
      baseType.pop_back();
    llvm::Type *elemTy = getLLVMType(baseType);
    uint64_t length = compLit->dimensions.empty()
                          ? compLit->initializer
                                ? std::dynamic_pointer_cast<InitializerList>(
                                      compLit->initializer)
                                      ->elements.size()
                                : 0
                          : 0;
    if (!compLit->dimensions.empty()) {
      auto dimExpr = compLit->dimensions.front();
      if (auto lit = std::dynamic_pointer_cast<Literal>(dimExpr)) {
        length = static_cast<uint64_t>(lit->intValue);
      } else if (auto dimInit =
                     std::dynamic_pointer_cast<InitializerList>(dimExpr)) {
        length = dimInit->elements.size();
      }
    }
    if (length == 0 && compLit->initializer) {
      if (auto initList =
              std::dynamic_pointer_cast<InitializerList>(compLit->initializer))
        length = initList->elements.size();
    }
    if (length == 0)
      length = 1;
    auto *arrTy = llvm::ArrayType::get(elemTy, length);
    AllocaInst *alloca =
        builder.CreateAlloca(arrTy, nullptr, "compound.literal");
    storeInitializerValue(compLit->initializer, arrTy, alloca);
    vector<llvm::Value *> indices;
    indices.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
    indices.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
    return builder.CreateGEP(arrTy, alloca, indices, "compound.decay");
  } else if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    if (id->name == "I") {
      auto *complexTy = StructType::get(Type::getDoubleTy(context),
                                        Type::getDoubleTy(context));
      llvm::Value *val = UndefValue::get(complexTy);
      val = builder.CreateInsertValue(
          val, ConstantFP::get(Type::getDoubleTy(context), 0.0), 0);
      val = builder.CreateInsertValue(
          val, ConstantFP::get(Type::getDoubleTy(context), 1.0), 1);
      return val;
    }
    auto enumIt = enumRegistry.find(id->name);
    if (enumIt != enumRegistry.end()) {
      return ConstantInt::get(Type::getInt32Ty(context), enumIt->second);
    }
    llvm::Value *v = lookupLocalVar(id->name);
    if (v) {
      if (dynamicArrayVars.find(id->name) != dynamicArrayVars.end()) {
        return v;
      }
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
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] generateExpression: ArrayAccess encountered\n";
    llvm::Value *elemPtr = generateArrayElementPointer(arrAccess);
    PointerType *ptrType = dyn_cast<PointerType>(elemPtr->getType());
    if (!ptrType)
      throw runtime_error("Array access did not return a pointer.");

    // Handle array access on identifiers (e.g., arr[i])
    if (auto baseId = std::dynamic_pointer_cast<Identifier>(arrAccess->base)) {
      std::string elementTypeStr = getEffectiveType(*this, arrAccess->base);
      size_t bracketPos = elementTypeStr.find('[');
      bool hadBracket = bracketPos != string::npos;
      if (hadBracket) {
        elementTypeStr = elementTypeStr.substr(0, bracketPos);
      }
      if (!hadBracket && !elementTypeStr.empty() &&
          elementTypeStr.back() == '*')
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
      if (bracketPos == string::npos && !elementTypeStr.empty() &&
          elementTypeStr.back() == '*')
        elementTypeStr.pop_back();

      llvm::Type *elementType = getLLVMType(elementTypeStr);
      return builder.CreateLoad(elementType, elemPtr, "memberarrayload");
    } else if (std::dynamic_pointer_cast<ArrayAccess>(arrAccess->base)) {
      std::string elementTypeStr = getEffectiveType(*this, arrAccess);
      size_t bracketPos = elementTypeStr.find('[');
      bool hadBracket = bracketPos != string::npos;
      if (hadBracket)
        elementTypeStr = elementTypeStr.substr(0, bracketPos);
      if (!hadBracket && !elementTypeStr.empty() &&
          elementTypeStr.back() == '*')
        elementTypeStr.pop_back();
      llvm::Type *elemType = getLLVMType(elementTypeStr);
      return builder.CreateLoad(elemType, elemPtr, "arrayload.nested");
    } else {
      std::string elementTypeStr = getEffectiveType(*this, arrAccess);
      size_t bracketPos = elementTypeStr.find('[');
      bool hadBracket = bracketPos != std::string::npos;
      if (hadBracket)
        elementTypeStr = elementTypeStr.substr(0, bracketPos);
      if (!hadBracket && !elementTypeStr.empty() &&
          elementTypeStr.back() == '*')
        elementTypeStr.pop_back();
      llvm::Type *elemType = getLLVMType(elementTypeStr);
      return builder.CreateLoad(elemType, elemPtr, "arrayload.generic");
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
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] FunctionCall: " << call->functionName
                << " args=" << call->arguments.size() << std::endl;
    std::string fname = call->functionName;
    if (fname == "va_start" || fname == "va_end" || fname == "va_arg")
      fname = "__builtin_" + fname;
    vector<llvm::Value *> args;
    for (size_t i = 0; i < call->arguments.size(); ++i) {
      if (fname == "__builtin_va_arg" && i == 1) {
        // The second argument is a type designator; no runtime code needed.
        args.push_back(llvm::UndefValue::get(Type::getInt32Ty(context)));
        continue;
      }
      if (educcDebugEnabled())
        std::cerr << "[DEBUG]   Arg " << i << " generate\n";
      args.push_back(generateExpression(call->arguments[i]));
      if (educcDebugEnabled())
        std::cerr << "[DEBUG]   Arg " << i << " done\n";
    }
    auto asDouble = [&](llvm::Value *v) -> llvm::Value * {
      if (v->getType()->isDoubleTy())
        return v;
      if (v->getType()->isFloatTy())
        return builder.CreateFPExt(v, Type::getDoubleTy(context), "fpext");
      if (v->getType()->isIntegerTy())
        return builder.CreateSIToFP(v, Type::getDoubleTy(context), "sitofp");
      return v;
    };
    auto classifyFP = [&](llvm::Value *v) -> llvm::Value * {
      llvm::Value *val = asDouble(v);
      llvm::Type *fty = val->getType();
      auto *fabsFn =
          Intrinsic::getDeclaration(module.get(), Intrinsic::fabs, {fty});
      llvm::Value *abs = builder.CreateCall(fabsFn, {val}, "fp.abs");
      llvm::Value *isNan = builder.CreateFCmpUNO(val, val, "fp.isnan");
      llvm::Value *infConst = ConstantFP::getInfinity(fty);
      llvm::Value *isInf = builder.CreateFCmpOEQ(abs, infConst, "fp.isinf");
      llvm::Value *zero = ConstantFP::get(fty, 0.0);
      llvm::Value *isZero = builder.CreateFCmpOEQ(val, zero, "fp.iszero");
      double minNormD = std::numeric_limits<double>::min();
      if (fty->isFloatTy())
        minNormD = std::numeric_limits<float>::min();
      llvm::Value *minNorm = ConstantFP::get(fty, minNormD);
      llvm::Value *geMinNorm =
          builder.CreateFCmpOGE(abs, minNorm, "fp.geMinNorm");

      llvm::Value *notNan = builder.CreateNot(isNan);
      llvm::Value *notInf = builder.CreateNot(isInf);
      llvm::Value *isFin = builder.CreateAnd(notNan, notInf, "fp.isfin");
      llvm::Value *isNorm = builder.CreateAnd(isFin, geMinNorm, "fp.isnorm");

      llvm::Value *fpNan = ConstantInt::get(Type::getInt32Ty(context), 1);
      llvm::Value *fpInf = ConstantInt::get(Type::getInt32Ty(context), 2);
      llvm::Value *fpZero = ConstantInt::get(Type::getInt32Ty(context), 3);
      llvm::Value *fpSub = ConstantInt::get(Type::getInt32Ty(context), 5);
      llvm::Value *fpNorm = ConstantInt::get(Type::getInt32Ty(context), 4);

      llvm::Value *result = builder.CreateSelect(isNan, fpNan, fpNan);
      result = builder.CreateSelect(isInf, fpInf, result);
      result = builder.CreateSelect(isZero, fpZero, result);
      llvm::Value *isSub = builder.CreateAnd(
          builder.CreateNot(isNorm),
          builder.CreateAnd(isFin, builder.CreateNot(isZero)));
      result = builder.CreateSelect(isSub, fpSub, result);
      result = builder.CreateSelect(isNorm, fpNorm, result);
      return result;
    };
    auto emitSignbit = [&](llvm::Value *v) -> llvm::Value * {
      llvm::Value *val = asDouble(v);
      llvm::Value *bits =
          builder.CreateBitCast(val, Type::getInt64Ty(context), "signbit.bits");
      llvm::Value *sign = builder.CreateLShr(
          bits, ConstantInt::get(Type::getInt64Ty(context), 63),
          "signbit.shift");
      llvm::Value *mask = ConstantInt::get(Type::getInt64Ty(context), 1);
      llvm::Value *res = builder.CreateAnd(sign, mask, "signbit.mask");
      return builder.CreateIntCast(res, Type::getInt32Ty(context), false,
                                   "signbit.i32");
    };
    auto isComplexStructVal = [&](llvm::Value *v) {
      if (auto *st = dyn_cast<StructType>(v->getType())) {
        return st->getNumElements() == 2 &&
               st->getElementType(0)->isDoubleTy() &&
               st->getElementType(1)->isDoubleTy();
      }
      return false;
    };
    auto makeComplex = [&](llvm::Value *re, llvm::Value *im) {
      auto *ty = StructType::get(Type::getDoubleTy(context),
                                 Type::getDoubleTy(context));
      llvm::Value *undef = UndefValue::get(ty);
      llvm::Value *withReal = builder.CreateInsertValue(undef, re, 0);
      return builder.CreateInsertValue(withReal, im, 1);
    };
    if (call->functionName == "creal" && args.size() == 1 &&
        isComplexStructVal(args[0])) {
      return builder.CreateExtractValue(args[0], 0, "creal");
    }
    if (call->functionName == "cimag" && args.size() == 1 &&
        isComplexStructVal(args[0])) {
      return builder.CreateExtractValue(args[0], 1, "cimag");
    }
    if (call->functionName == "cabs" && args.size() == 1 &&
        isComplexStructVal(args[0])) {
      auto re = builder.CreateExtractValue(args[0], 0, "cabs.re");
      auto im = builder.CreateExtractValue(args[0], 1, "cabs.im");
      auto re2 = builder.CreateFMul(re, re, "cabs.re2");
      auto im2 = builder.CreateFMul(im, im, "cabs.im2");
      auto sum = builder.CreateFAdd(re2, im2, "cabs.sum");
      auto sqrtFn = Intrinsic::getDeclaration(module.get(), Intrinsic::sqrt,
                                              {Type::getDoubleTy(context)});
      return builder.CreateCall(sqrtFn, {sum}, "cabs");
    }
    if (call->functionName == "cexp" && args.size() == 1 &&
        isComplexStructVal(args[0])) {
      auto re = builder.CreateExtractValue(args[0], 0, "cexp.re");
      auto im = builder.CreateExtractValue(args[0], 1, "cexp.im");
      auto expFn = Intrinsic::getDeclaration(module.get(), Intrinsic::exp,
                                             {Type::getDoubleTy(context)});
      auto cosFn = Intrinsic::getDeclaration(module.get(), Intrinsic::cos,
                                             {Type::getDoubleTy(context)});
      auto sinFn = Intrinsic::getDeclaration(module.get(), Intrinsic::sin,
                                             {Type::getDoubleTy(context)});
      llvm::Value *expRe = builder.CreateCall(expFn, {re}, "cexp.exp");
      llvm::Value *cosIm = builder.CreateCall(cosFn, {im}, "cexp.cos");
      llvm::Value *sinIm = builder.CreateCall(sinFn, {im}, "cexp.sin");
      llvm::Value *realPart = builder.CreateFMul(expRe, cosIm, "cexp.real");
      llvm::Value *imagPart = builder.CreateFMul(expRe, sinIm, "cexp.imag");
      return makeComplex(realPart, imagPart);
    }

    if (!call->hasCalleeExpr()) {
      if ((fname == "isnan" || fname == "isinf" || fname == "isfinite") &&
          args.size() == 1) {
        llvm::Value *val = asDouble(args[0]);
        llvm::Type *fty = val->getType();
        auto *fabsFn =
            Intrinsic::getDeclaration(module.get(), Intrinsic::fabs, {fty});
        llvm::Value *abs = builder.CreateCall(fabsFn, {val}, "abs.call");
        llvm::Value *res = nullptr;
        if (fname == "isnan") {
          res = builder.CreateFCmpUNO(val, val, "isnan");
        } else if (fname == "isinf") {
          llvm::Value *inf = ConstantFP::getInfinity(fty);
          res = builder.CreateFCmpOEQ(abs, inf, "isinf");
        } else {
          llvm::Value *inf = ConstantFP::getInfinity(fty);
          llvm::Value *nan = builder.CreateFCmpUNO(val, val, "isnan");
          llvm::Value *eqInf = builder.CreateFCmpOEQ(abs, inf, "isinf");
          res = builder.CreateAnd(builder.CreateNot(nan),
                                  builder.CreateNot(eqInf), "isfinite");
        }
        return builder.CreateIntCast(res, Type::getInt32Ty(context), false,
                                     fname + ".i32");
      }
      if (fname == "signbit" && args.size() == 1) {
        return emitSignbit(args[0]);
      }
      if (fname == "fpclassify" && args.size() == 1) {
        return classifyFP(args[0]);
      }
      if ((fname == "fabs" || fname == "fabsf") && args.size() == 1) {
        llvm::Value *val = args[0];
        Type *ty = val->getType()->isFloatTy() ? Type::getFloatTy(context)
                                               : Type::getDoubleTy(context);
        auto *fn =
            Intrinsic::getDeclaration(module.get(), Intrinsic::fabs, {ty});
        llvm::Value *asTy = val;
        if (val->getType() != ty)
          asTy = builder.CreateFPCast(val, ty, "fabs.cast");
        return builder.CreateCall(fn, {asTy}, "fabs");
      }
      if (fname == "sqrt" && args.size() == 1) {
        if (isComplexStructVal(args[0])) {
          llvm::Value *re = builder.CreateExtractValue(args[0], 0, "sqrt.re");
          llvm::Value *im = builder.CreateExtractValue(args[0], 1, "sqrt.im");
          llvm::Value *a2 = builder.CreateFMul(re, re, "sqrt.re2");
          llvm::Value *b2 = builder.CreateFMul(im, im, "sqrt.im2");
          llvm::Value *sum = builder.CreateFAdd(a2, b2, "sqrt.sum");
          auto *sqrtFn = Intrinsic::getDeclaration(
              module.get(), Intrinsic::sqrt, {Type::getDoubleTy(context)});
          llvm::Value *r = builder.CreateCall(sqrtFn, {sum}, "sqrt.r");
          llvm::Value *half = ConstantFP::get(Type::getDoubleTy(context), 0.5);
          llvm::Value *rPlusA = builder.CreateFAdd(r, re, "sqrt.rpa");
          llvm::Value *rMinusA = builder.CreateFSub(r, re, "sqrt.rma");
          llvm::Value *real = builder.CreateCall(
              sqrtFn, {builder.CreateFMul(rPlusA, half, "sqrt.hrpa")},
              "sqrt.real");
          llvm::Value *imag = builder.CreateCall(
              sqrtFn, {builder.CreateFMul(rMinusA, half, "sqrt.hrma")},
              "sqrt.imag.abs");
          llvm::Value *sign = builder.CreateSelect(
              builder.CreateFCmpOLT(
                  im, ConstantFP::get(Type::getDoubleTy(context), 0.0)),
              ConstantFP::get(Type::getDoubleTy(context), -1.0),
              ConstantFP::get(Type::getDoubleTy(context), 1.0));
          imag = builder.CreateFMul(imag, sign, "sqrt.imag");
          return makeComplex(real, imag);
        } else {
          Type *ty = args[0]->getType()->isFloatTy()
                         ? Type::getFloatTy(context)
                         : Type::getDoubleTy(context);
          auto *sqrtFn =
              Intrinsic::getDeclaration(module.get(), Intrinsic::sqrt, {ty});
          llvm::Value *asTy = args[0];
          if (args[0]->getType() != ty)
            asTy = builder.CreateFPCast(args[0], ty, "sqrt.cast");
          return builder.CreateCall(sqrtFn, {asTy}, "sqrt");
        }
      }
      if (educcDebugEnabled())
        std::cerr << "[DEBUG] FunctionCall: no builtin fast-path for " << fname
                  << std::endl;
      if (fname == "printf") {
        llvm::Type *charPtr =
            llvm::PointerType::get(Type::getInt8Ty(context), 0);
        auto printfTy =
            llvm::FunctionType::get(Type::getInt32Ty(context), {charPtr}, true);
        llvm::FunctionCallee printfFn =
            module->getOrInsertFunction("printf", printfTy);
        return builder.CreateCall(printfFn, args, "printf");
      }
      if (fname == "sprintf") {
        llvm::Type *charPtr =
            llvm::PointerType::get(Type::getInt8Ty(context), 0);
        auto sprintfTy = llvm::FunctionType::get(Type::getInt32Ty(context),
                                                 {charPtr, charPtr}, true);
        llvm::FunctionCallee sprintfFn =
            module->getOrInsertFunction("sprintf", sprintfTy);
        return builder.CreateCall(sprintfFn, args, "sprintf");
      }
      if (fname == "__builtin_va_start" && !args.empty()) {
        if (educcDebugEnabled())
          std::cerr << "[DEBUG] builtin va_start: preparing" << std::endl;
        Value *vaListPtr = nullptr;
        if (auto ident =
                std::dynamic_pointer_cast<Identifier>(call->arguments[0])) {
          vaListPtr = lookupLocalVar(ident->name);
        }
        if (!vaListPtr)
          vaListPtr = generateLValue(call->arguments[0]);
        if (!vaListPtr)
          throw runtime_error("__builtin_va_start requires lvalue va_list");
        if (educcDebugEnabled()) {
          std::cerr << "[DEBUG] builtin va_start: have ptr of type ";
          if (vaListPtr) {
            std::string tyStr;
            llvm::raw_string_ostream rso(tyStr);
            vaListPtr->getType()->print(rso);
            std::cerr << tyStr;
          }
          std::cerr << std::endl;
        }
        Value *asPtr = vaListPtr;
        if (vaListPtr->getType() != builder.getPtrTy())
          asPtr = builder.CreatePointerCast(vaListPtr, builder.getPtrTy(),
                                            "va.cast");
        if (educcDebugEnabled())
          std::cerr << "[DEBUG] builtin va_start: intrinsic acquired"
                    << std::endl;
        auto vaStartName = Intrinsic::getName(
            Intrinsic::vastart, {builder.getPtrTy()}, module.get());
        auto vaStartTy = FunctionType::get(Type::getVoidTy(context),
                                           {builder.getPtrTy()}, false);
        auto vaStart = module->getOrInsertFunction(vaStartName, vaStartTy);
        builder.CreateCall(vaStart, {asPtr});
        if (educcDebugEnabled())
          std::cerr << "[DEBUG] builtin va_start: emitted call" << std::endl;
        return ConstantInt::get(Type::getInt32Ty(context), 0);
      }
      if (fname == "__builtin_va_end" && !args.empty()) {
        if (educcDebugEnabled())
          std::cerr << "[DEBUG] builtin va_end: preparing" << std::endl;
        Value *vaListPtr = nullptr;
        if (auto ident =
                std::dynamic_pointer_cast<Identifier>(call->arguments[0])) {
          vaListPtr = lookupLocalVar(ident->name);
        }
        if (!vaListPtr)
          vaListPtr = generateLValue(call->arguments[0]);
        if (!vaListPtr)
          throw runtime_error("__builtin_va_end requires lvalue va_list");
        if (educcDebugEnabled())
          std::cerr << "[DEBUG] builtin va_end: have ptr" << std::endl;
        Value *asPtr = vaListPtr;
        if (vaListPtr->getType() != builder.getPtrTy())
          asPtr = builder.CreatePointerCast(vaListPtr, builder.getPtrTy(),
                                            "va.cast");
        if (educcDebugEnabled())
          std::cerr << "[DEBUG] builtin va_end: intrinsic acquired"
                    << std::endl;
        auto vaEndName = Intrinsic::getName(Intrinsic::vaend,
                                            {builder.getPtrTy()}, module.get());
        auto vaEndTy = FunctionType::get(Type::getVoidTy(context),
                                         {builder.getPtrTy()}, false);
        auto vaEnd = module->getOrInsertFunction(vaEndName, vaEndTy);
        builder.CreateCall(vaEnd, {asPtr});
        if (educcDebugEnabled())
          std::cerr << "[DEBUG] builtin va_end: emitted call" << std::endl;
        return ConstantInt::get(Type::getInt32Ty(context), 0);
      }
      if (fname == "__builtin_va_arg" && args.size() >= 1) {
        if (educcDebugEnabled())
          std::cerr << "[DEBUG] builtin va_arg: preparing" << std::endl;
        Value *vaListPtr = nullptr;
        if (auto ident =
                std::dynamic_pointer_cast<Identifier>(call->arguments[0])) {
          vaListPtr = lookupLocalVar(ident->name);
        }
        if (!vaListPtr)
          vaListPtr = generateLValue(call->arguments[0]);
        if (!vaListPtr)
          throw runtime_error("__builtin_va_arg requires lvalue va_list");
        std::string typeName = "int";
        if (call->arguments.size() >= 2) {
          if (auto ident =
                  std::dynamic_pointer_cast<Identifier>(call->arguments[1])) {
            typeName = ident->name;
          } else {
            std::string effType = getEffectiveType(*this, call->arguments[1]);
            if (!effType.empty())
              typeName = effType;
          }
        }
        Value *asPtr = vaListPtr;
        if (vaListPtr->getType() != builder.getPtrTy())
          asPtr = builder.CreatePointerCast(vaListPtr, builder.getPtrTy(),
                                            "va.cast");
        Type *retTy = getLLVMType(typeName);
        if (educcDebugEnabled())
          std::cerr << "[DEBUG] builtin va_arg: emitting for type " << typeName
                    << std::endl;
        return builder.CreateVAArg(asPtr, retTy, "va.arg");
      }
      if (fname == "atomic_fetch_add") {
        if (args.size() != 2)
          throw runtime_error("atomic_fetch_add expects 2 arguments");
        Value *ptr = args[0];
        Value *val = args[1];
        if (!ptr->getType()->isPointerTy())
          throw runtime_error("atomic_fetch_add expects pointer operand");
        Type *elemTy = val->getType();
        llvm::Align align = module->getDataLayout().getABITypeAlign(elemTy);
        auto *rmw =
            builder.CreateAtomicRMW(AtomicRMWInst::Add, ptr, val, align,
                                    AtomicOrdering::SequentiallyConsistent);
        return rmw;
      }
      if (fname == "atomic_load") {
        if (args.size() != 1)
          throw runtime_error("atomic_load expects 1 argument");
        Value *ptr = args[0];
        if (!ptr->getType()->isPointerTy())
          throw runtime_error("atomic_load expects pointer operand");
        Type *elemTy = Type::getInt32Ty(context);
        LoadInst *ld = builder.CreateLoad(elemTy, ptr, "atomic.load");
        ld->setAlignment(module->getDataLayout().getABITypeAlign(elemTy));
        ld->setAtomic(AtomicOrdering::SequentiallyConsistent);
        return ld;
      }
      if (fname == "atomic_compare_exchange_strong" ||
          fname == "atomic_compare_exchange_weak") {
        if (args.size() != 3)
          throw runtime_error("atomic_compare_exchange expects 3 arguments");
        Value *ptr = args[0];
        Value *expectedPtr = args[1];
        Value *desired = args[2];
        if (!ptr->getType()->isPointerTy())
          throw runtime_error(
              "atomic_compare_exchange expects pointer operand");
        Type *elemTy = desired->getType();
        Value *expectedVal =
            builder.CreateLoad(elemTy, expectedPtr, "atomic.exp");
        llvm::MaybeAlign align(module->getDataLayout().getABITypeAlign(elemTy));
        auto *cmpxchg =
            builder.CreateAtomicCmpXchg(ptr, expectedVal, desired, align,
                                        AtomicOrdering::SequentiallyConsistent,
                                        AtomicOrdering::SequentiallyConsistent);
        cmpxchg->setWeak(fname == "atomic_compare_exchange_weak");
        Value *oldVal = builder.CreateExtractValue(cmpxchg, 0, "atomic.old");
        builder.CreateStore(oldVal, expectedPtr);
        Value *success =
            builder.CreateExtractValue(cmpxchg, 1, "atomic.success");
        return builder.CreateZExt(success, Type::getInt32Ty(context),
                                  "atomic.success.int");
      }
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
      if (educcDebugEnabled())
        std::cerr << "[DEBUG] emitCall: fnTy params="
                  << (fnTy ? fnTy->getNumParams() : 0)
                  << " vararg=" << (fnTy ? fnTy->isVarArg() : false)
                  << std::endl;
      if (!fnTy || !calleeVal)
        return nullptr;
      std::vector<llvm::Value *> callArgs = args;
      if (fnTy->getNumParams() == callArgs.size()) {
        for (size_t i = 0; i < callArgs.size(); ++i) {
          llvm::Type *paramTy = fnTy->getParamType(i);
          if (callArgs[i]->getType() == paramTy)
            continue;
          llvm::Value *v = callArgs[i];
          if (v->getType()->isIntegerTy() && paramTy->isIntegerTy()) {
            v = builder.CreateIntCast(v, paramTy, false, "argcast");
          } else if (v->getType()->isPointerTy() && paramTy->isPointerTy()) {
            v = builder.CreateBitCast(v, paramTy, "argcast");
          } else if (v->getType()->isIntegerTy() && paramTy->isPointerTy()) {
            v = builder.CreateIntToPtr(v, paramTy, "argcast");
          } else if (v->getType()->isPointerTy() && paramTy->isIntegerTy()) {
            v = builder.CreatePtrToInt(v, paramTy, "argcast");
          } else if (v->getType()->isFloatingPointTy() &&
                     paramTy->isFloatingPointTy()) {
            v = builder.CreateFPCast(v, paramTy, "argcast");
          }
          callArgs[i] = v;
        }
      }
      if (educcDebugEnabled())
        std::cerr << "[DEBUG] emitCall: creating call with " << callArgs.size()
                  << " args" << std::endl;
      llvm::CallInst *callInst = builder.CreateCall(
          fnTy, calleeVal, callArgs,
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

    if (educcDebugEnabled())
      std::cerr << "[DEBUG] FunctionCall: resolving callee '"
                << call->functionName << "'" << std::endl;
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
      if (educcDebugEnabled())
        std::cerr << "[DEBUG] FunctionCall: creating external '"
                  << call->functionName << "'" << std::endl;
      vector<llvm::Type *> paramTypes;
      if (call->functionName == "printf") {
        paramTypes.push_back(llvm::PointerType::get(context, 0));
      } else if (call->functionName == "malloc") {
        llvm::Type *sizeTy = module->getDataLayout().getIntPtrType(context);
        paramTypes.push_back(sizeTy);
        llvm::FunctionType *funcType = llvm::FunctionType::get(
            llvm::PointerType::get(context, 0), paramTypes, false);
        callee =
            llvm::Function::Create(funcType, llvm::Function::ExternalLinkage,
                                   call->functionName, module.get());
      } else if (call->functionName == "calloc") {
        llvm::Type *sizeTy = module->getDataLayout().getIntPtrType(context);
        paramTypes.push_back(sizeTy);
        paramTypes.push_back(sizeTy);
        llvm::FunctionType *funcType = llvm::FunctionType::get(
            llvm::PointerType::get(context, 0), paramTypes, false);
        callee =
            llvm::Function::Create(funcType, llvm::Function::ExternalLinkage,
                                   call->functionName, module.get());
      } else if (call->functionName == "realloc") {
        llvm::Type *sizeTy = module->getDataLayout().getIntPtrType(context);
        paramTypes.push_back(llvm::PointerType::get(context, 0));
        paramTypes.push_back(sizeTy);
        llvm::FunctionType *funcType = llvm::FunctionType::get(
            llvm::PointerType::get(context, 0), paramTypes, false);
        callee =
            llvm::Function::Create(funcType, llvm::Function::ExternalLinkage,
                                   call->functionName, module.get());
      } else if (call->functionName == "free") {
        paramTypes.push_back(llvm::PointerType::get(context, 0));
        llvm::FunctionType *funcType = llvm::FunctionType::get(
            llvm::Type::getVoidTy(context), paramTypes, false);
        callee =
            llvm::Function::Create(funcType, llvm::Function::ExternalLinkage,
                                   call->functionName, module.get());
      } else {
        paramTypes.reserve(args.size());
        for (auto *argVal : args) {
          paramTypes.push_back(argVal->getType());
        }
        llvm::Type *retTy = llvm::Type::getInt32Ty(context);
        if (!args.empty()) {
          llvm::Type *firstTy = args[0]->getType();
          if (firstTy->isDoubleTy() || firstTy->isFloatTy())
            retTy = firstTy;
        }
        llvm::FunctionType *funcType = llvm::FunctionType::get(
            retTy, paramTypes, call->functionName == "printf");
        callee =
            llvm::Function::Create(funcType, llvm::Function::ExternalLinkage,
                                   call->functionName, module.get());
      }
    }
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] FunctionCall: emitting call" << std::endl;
    if (auto *result = emitCall(callee->getFunctionType(), callee))
      return result;
    throw runtime_error("Attempting to call a non-callable expression.");

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
    Function *fn = builder.GetInsertBlock()->getParent();
    BasicBlock *thenBB = BasicBlock::Create(context, "ternary.then", fn);
    BasicBlock *elseBB = BasicBlock::Create(context, "ternary.else", fn);
    BasicBlock *mergeBB = BasicBlock::Create(context, "ternary.merge", fn);
    builder.CreateCondBr(condVal, thenBB, elseBB);

    builder.SetInsertPoint(thenBB);
    llvm::Value *trueVal = generateExpression(ternary->trueExpr);
    BasicBlock *thenEnd = builder.GetInsertBlock();
    if (!thenEnd->getTerminator())
      builder.CreateBr(mergeBB);

    builder.SetInsertPoint(elseBB);
    llvm::Value *falseVal = generateExpression(ternary->falseExpr);
    BasicBlock *elseEnd = builder.GetInsertBlock();
    if (!elseEnd->getTerminator())
      builder.CreateBr(mergeBB);
    builder.SetInsertPoint(mergeBB);

    // Align types if needed (simple integer widening).
    if (trueVal->getType() != falseVal->getType()) {
      if (trueVal->getType()->isIntegerTy() &&
          falseVal->getType()->isIntegerTy()) {
        if (trueVal->getType()->getIntegerBitWidth() <
            falseVal->getType()->getIntegerBitWidth()) {
          IRBuilder<> castBuilder(thenEnd->getTerminator());
          trueVal =
              castBuilder.CreateSExt(trueVal, falseVal->getType(), "sexttmp");
        } else if (falseVal->getType()->getIntegerBitWidth() <
                   trueVal->getType()->getIntegerBitWidth()) {
          IRBuilder<> castBuilder(elseEnd->getTerminator());
          falseVal =
              castBuilder.CreateSExt(falseVal, trueVal->getType(), "sexttmp");
        }
      }
    }

    PHINode *phi = builder.CreatePHI(trueVal->getType(), 2, "ternaryphi");
    phi->addIncoming(trueVal, thenEnd);
    phi->addIncoming(falseVal, elseEnd);
    return phi;
  } else if (auto sizeofExpr =
                 std::dynamic_pointer_cast<SizeOfExpression>(expr)) {
    if (sizeofExpr->isType) {
      llvm::Type *type = getLLVMType(sizeofExpr->typeName);
      auto DL = module->getDataLayout();
      uint64_t size = DL.getTypeAllocSize(type);
      return ConstantInt::get(Type::getInt32Ty(context), size);
    } else {
      // For VLAs, compute size from dynamic dimensions.
      if (auto id =
              std::dynamic_pointer_cast<Identifier>(sizeofExpr->operand)) {
        auto dimIt = dynamicArrayDimensions.find(id->name);
        if (dimIt != dynamicArrayDimensions.end()) {
          auto baseTypeStr = declaredTypeStrings.count(id->name)
                                 ? declaredTypeStrings[id->name]
                                 : getEffectiveType(*this, sizeofExpr->operand);
          size_t lb = baseTypeStr.find('[');
          if (lb != std::string::npos)
            baseTypeStr = baseTypeStr.substr(0, lb);
          while (!baseTypeStr.empty() && baseTypeStr.back() == '*')
            baseTypeStr.pop_back();
          llvm::Type *elemTy = getLLVMType(baseTypeStr);
          auto DL = module->getDataLayout();
          llvm::Value *sizeVal = ConstantInt::get(Type::getInt64Ty(context),
                                                  DL.getTypeAllocSize(elemTy));
          for (llvm::Value *dim : dimIt->second) {
            llvm::Value *dim64 = dim;
            if (!dim64->getType()->isIntegerTy(64))
              dim64 = builder.CreateIntCast(dim, Type::getInt64Ty(context),
                                            true, "vla.dim.cast");
            sizeVal = builder.CreateMul(sizeVal, dim64, "vla.size.mul");
          }
          return builder.CreateIntCast(sizeVal, Type::getInt32Ty(context),
                                       false, "sizeof.vla");
        }
      }
      std::string effectiveType = getEffectiveType(*this, sizeofExpr->operand);
      llvm::Type *type = getLLVMType(effectiveType);
      auto DL = module->getDataLayout();
      uint64_t size = DL.getTypeAllocSize(type);
      return ConstantInt::get(Type::getInt32Ty(context), size);
    }
  }
  throw runtime_error("Unsupported expression type in generateExpression().");
}
