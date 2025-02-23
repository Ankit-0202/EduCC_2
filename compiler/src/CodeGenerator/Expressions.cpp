#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "CodeGenerator/Helpers.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"

#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
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

// Helper: find an identified struct type by name in the module.
static StructType *getStructTypeByName(Module *M, const string &tag) {
  for (StructType *ST : M->getIdentifiedStructTypes()) {
    if (ST->getName() == tag)
      return ST;
  }
  return nullptr;
}

//===----------------------------------------------------------------------===//
// Array Access Helper
//===----------------------------------------------------------------------===//

llvm::Value *
CodeGenerator::generateArrayElementPointer(const shared_ptr<ArrayAccess> &arr) {
  // We require that the base of the array access is an identifier.
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
    // First index: 0 (to dereference the pointer to the array)
    indices.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
    // Second index: the array index.
    indices.push_back(indexVal);

    // Get the base pointer (the address of the array).
    llvm::Value *baseLVal = generateLValue(arr->base);
    // GEP into the array
    llvm::Value *gep =
        builder.CreateGEP(arrayTy, baseLVal, indices, "arraygep");
    return gep;
  } else {
    throw runtime_error("Array access on non-identifier base not supported.");
  }
}

//===----------------------------------------------------------------------===//
// generateLValue: returns an lvalue pointer for an expression
//===----------------------------------------------------------------------===//

llvm::Value *CodeGenerator::generateLValue(const ExpressionPtr &expr) {
  // 1) Identifier
  if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    llvm::Value *v = lookupLocalVar(id->name);
    if (v)
      return v;
    GlobalVariable *gVar = module->getGlobalVariable(id->name);
    if (gVar)
      return gVar;
    throw runtime_error("Undefined variable in generateLValue: " + id->name);
  }

  // 2) MemberAccess
  else if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    // For a member access on a struct, look up the base lvalue and then
    // generate a GEP into the struct.
    string baseEffectiveType = getEffectiveType(*this, mem->base);
    llvm::Value *basePtr = generateLValue(mem->base);

    if (baseEffectiveType.rfind("struct ", 0) == 0) {
      // Extract tag (skip "struct ")
      string tag = baseEffectiveType.substr(7);
      tag = normalizeTag(tag);
      auto sit = structRegistry.find(tag);
      if (sit == structRegistry.end())
        throw runtime_error("Unknown struct type '" + tag + "'.");

      // Find the member index
      size_t index = 0;
      bool found = false;
      for (size_t i = 0; i < sit->second->members.size(); i++) {
        if (sit->second->members[i]->name == mem->member) {
          index = i;
          found = true;
          break;
        }
      }
      if (!found)
        throw runtime_error("Struct type '" + tag +
                            "' does not contain member '" + mem->member + "'.");

      // Retrieve or create the LLVM struct type
      StructType *structTy = getStructTypeByName(module.get(), tag);
      if (!structTy) {
        // Build from registry
        vector<Type *> memberTypes;
        for (auto &m : sit->second->members) {
          memberTypes.push_back(getLLVMType(m->type));
        }
        structTy = StructType::create(context, memberTypes, tag, false);
      }
      return builder.CreateStructGEP(structTy, basePtr, index, mem->member);
    } else {
      // For non-struct aggregates, simply generate the lvalue of the base.
      return generateLValue(mem->base);
    }
  }

  // 3) PostfixExpression (like i++ or i--)
  else if (auto post = std::dynamic_pointer_cast<PostfixExpression>(expr)) {
    auto id = std::dynamic_pointer_cast<Identifier>(post->operand);
    if (!id)
      throw runtime_error("Postfix operator applied to non-identifier.");
    llvm::Value *v = lookupLocalVar(id->name);
    if (!v)
      throw runtime_error("Undefined variable in postfix expression: " +
                          id->name);
    AllocaInst *allocaInst = dyn_cast<AllocaInst>(v);
    if (!allocaInst)
      throw runtime_error("Postfix operator applied to non-alloca variable: " +
                          id->name);

    // We load the old value
    llvm::Value *oldVal =
        builder.CreateLoad(allocaInst->getAllocatedType(), v, id->name.c_str());
    // Then we increment or decrement
    llvm::Value *one = nullptr;
    if (oldVal->getType()->isIntegerTy())
      one = ConstantInt::get(oldVal->getType(), 1);
    else if (oldVal->getType()->isFloatingPointTy())
      one = ConstantFP::get(oldVal->getType(), 1.0);
    else
      throw runtime_error("Unsupported type for postfix operator.");

    llvm::Value *newVal = nullptr;
    if (post->op == "++") {
      newVal = oldVal->getType()->isFloatingPointTy()
                   ? builder.CreateFAdd(oldVal, one, "postinc")
                   : builder.CreateAdd(oldVal, one, "postinc");
    } else {
      // op == "--"
      newVal = oldVal->getType()->isFloatingPointTy()
                   ? builder.CreateFSub(oldVal, one, "postdec")
                   : builder.CreateSub(oldVal, one, "postdec");
    }
    // Store the new value
    builder.CreateStore(newVal, v);
    // The lvalue is the oldVal? Actually for a postfix operation, the result
    // (the expression's value) is the oldVal, but the *address* is v.
    return oldVal;
  }

  // 4) Assignment
  else if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
    llvm::Value *ptr = generateLValue(assign->lhs);
    llvm::Value *rhsVal = generateExpression(assign->rhs);
    builder.CreateStore(rhsVal, ptr);
    return rhsVal;
  }

  // 5) ArrayAccess
  else if (auto arr = std::dynamic_pointer_cast<ArrayAccess>(expr)) {
    return generateArrayElementPointer(arr);
  }

  // 6) FunctionCall
  else if (auto funcCall = std::dynamic_pointer_cast<FunctionCall>(expr)) {
    // Typically not valid as an lvalue. We return a call, but that’s not
    // generally storable unless the function returns a reference type.
    throw runtime_error("Expression is not a valid lvalue: function call");
  }

  // 7) NEW: If it's a unary * expression => an lvalue is the pointer itself
  else if (auto un = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
    if (un->op == "*") {
      // e.g. *(somePointer) => the lvalue is (somePointer)
      llvm::Value *ptrVal = generateExpression(un->operand);
      if (!ptrVal->getType()->isPointerTy()) {
        throw runtime_error(
            "generateLValue: unary '*' applied to non-pointer expression");
      }
      // This pointer is the “lvalue” (the address) for storing.
      return ptrVal;
    }
  }

  throw runtime_error("Expression is not a valid lvalue.");
}

//===----------------------------------------------------------------------===//
// generateExpression: computes the value of an expression
//===----------------------------------------------------------------------===//

llvm::Value *CodeGenerator::generateExpression(const ExpressionPtr &expr) {
  if (auto binExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
    llvm::Value *lhs = generateExpression(binExpr->left);
    llvm::Value *rhs = generateExpression(binExpr->right);

    // Convert int <-> float if needed
    if (lhs->getType() != rhs->getType()) {
      if (lhs->getType()->isIntegerTy() && rhs->getType()->isFloatingPointTy())
        lhs = builder.CreateSIToFP(lhs, rhs->getType(), "sitofp");
      else if (lhs->getType()->isFloatingPointTy() &&
               rhs->getType()->isIntegerTy())
        rhs = builder.CreateSIToFP(rhs, lhs->getType(), "sitofp");
      else
        throw runtime_error("Incompatible types in binary expression.");
    }

    if (binExpr->op == "+") {
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFAdd(lhs, rhs, "faddtmp")
                 : builder.CreateAdd(lhs, rhs, "addtmp");
    } else if (binExpr->op == "-") {
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFSub(lhs, rhs, "fsubtmp")
                 : builder.CreateSub(lhs, rhs, "subtmp");
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
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOLE(lhs, rhs, "cmptmp")
                 : builder.CreateICmpSLE(lhs, rhs, "cmptmp");
    } else if (binExpr->op == "<") {
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOLT(lhs, rhs, "cmptmp")
                 : builder.CreateICmpSLT(lhs, rhs, "cmptmp");
    } else if (binExpr->op == ">=") {
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOGE(lhs, rhs, "cmptmp")
                 : builder.CreateICmpSGE(lhs, rhs, "cmptmp");
    } else if (binExpr->op == ">") {
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOGT(lhs, rhs, "cmptmp")
                 : builder.CreateICmpSGT(lhs, rhs, "cmptmp");
    } else if (binExpr->op == "==") {
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOEQ(lhs, rhs, "cmptmp")
                 : builder.CreateICmpEQ(lhs, rhs, "cmptmp");
    } else if (binExpr->op == "!=") {
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
    } else {
      throw runtime_error("Unsupported binary operator: " + binExpr->op);
    }
  }

  else if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
    // left-hand side => lvalue
    llvm::Value *ptr = generateLValue(assign->lhs);
    llvm::Value *rhsVal = generateExpression(assign->rhs);
    builder.CreateStore(rhsVal, ptr);
    return rhsVal;
  }

  else if (auto castExpr = std::dynamic_pointer_cast<CastExpression>(expr)) {
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
  }

  else if (auto unExpr = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
    // e.g. *x, &x, -x, +x, !x
    if (unExpr->op == "-") {
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
        operand = builder.CreateICmpNE(
            operand, ConstantInt::get(operand->getType(), 0), "booltmp");
      }
      return builder.CreateNot(operand, "nottmp");
    } else if (unExpr->op == "&") {
      // Address-of => the pointer to an lvalue
      return generateLValue(unExpr->operand);
    } else if (unExpr->op == "*") {
      // Dereference => load from that pointer
      llvm::Value *ptrVal = generateExpression(unExpr->operand);
      if (!ptrVal->getType()->isPointerTy())
        throw runtime_error(
            "Dereference operator applied to non-pointer type.");
      // figure out the underlying type from AST
      string baseType = getEffectiveType(*this, unExpr->operand);
      if (!baseType.empty() && baseType.back() == '*') {
        baseType.pop_back();
      }
      llvm::Type *pointeeTy = getLLVMType(baseType);
      return builder.CreateLoad(pointeeTy, ptrVal, "deref");
    } else {
      throw runtime_error("Unsupported unary operator: " + unExpr->op);
    }
  }

  else if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
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
  }

  else if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    // check enum constants
    auto enumIt = enumRegistry.find(id->name);
    if (enumIt != enumRegistry.end()) {
      return ConstantInt::get(Type::getInt32Ty(context), enumIt->second);
    }
    // otherwise local or global
    llvm::Value *v = lookupLocalVar(id->name);
    if (v) {
      if (auto allocaInst = dyn_cast<AllocaInst>(v)) {
        return builder.CreateLoad(allocaInst->getAllocatedType(), v,
                                  id->name.c_str());
      }
      return v;
    }
    GlobalVariable *gVar = module->getGlobalVariable(id->name);
    if (gVar) {
      return builder.CreateLoad(gVar->getValueType(), gVar, id->name.c_str());
    }
    throw runtime_error("Undefined identifier: " + id->name);
  }

  else if (auto arrAccess = std::dynamic_pointer_cast<ArrayAccess>(expr)) {
    llvm::Value *elemPtr = generateArrayElementPointer(arrAccess);
    PointerType *ptrType = dyn_cast<PointerType>(elemPtr->getType());
    if (!ptrType) {
      throw runtime_error("Array access did not return a pointer.");
    }
    // For an array access on an identifier base, use the declared type.
    if (auto baseId = std::dynamic_pointer_cast<Identifier>(arrAccess->base)) {
      auto it = declaredTypes.find(baseId->name);
      if (it == declaredTypes.end()) {
        throw runtime_error("Declared type for array variable not found: " +
                            baseId->name);
      }
      llvm::Type *arrayTy = it->second;
      if (!arrayTy->isArrayTy()) {
        throw runtime_error("Expected array type for variable: " +
                            baseId->name);
      }
      llvm::Type *elemType = cast<ArrayType>(arrayTy)->getElementType();
      return builder.CreateLoad(elemType, elemPtr, "arrayload");
    } else {
      throw runtime_error("Array access on non-identifier base not supported.");
    }
  }

  else if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    // e.g. structVar.member as an rvalue => load from the member pointer
    llvm::Value *ptr = generateLValue(expr); // produce pointer
    string effType = getEffectiveType(*this, expr);
    llvm::Type *loadType = getLLVMType(effType);
    return builder.CreateLoad(loadType, ptr, "memberload");
  }

  else if (auto call = std::dynamic_pointer_cast<FunctionCall>(expr)) {
    llvm::Function *callee = module->getFunction(call->functionName);
    if (!callee) {
      throw runtime_error("Undefined function in IR: " + call->functionName);
    }
    vector<llvm::Value *> args;
    for (auto &argExpr : call->arguments) {
      args.push_back(generateExpression(argExpr));
    }
    return builder.CreateCall(callee, args, "calltmp");
  }

  else if (auto post = std::dynamic_pointer_cast<PostfixExpression>(expr)) {
    // Postfix expressions (x++) as rvalues => we get the old value
    return generateLValue(expr);
  }

  throw runtime_error("Unsupported expression type in generateExpression().");
}
