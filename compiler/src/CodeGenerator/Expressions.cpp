#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h> // Provides composite type definitions.
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
    if (it != localVariables.end())
      return it->second;
    GlobalVariable *gVar = module->getGlobalVariable(id->name);
    if (gVar)
      return gVar;
    throw runtime_error("CodeGenerator Error: Undefined variable '" + id->name +
                        "' in lvalue generation.");
  } else if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    llvm::Value *basePtr = generateLValue(mem->base);
    // Look up the declared type for the base variable from our declaredTypes
    // map.
    llvm::Type *baseElemType = nullptr;
    if (auto baseId = std::dynamic_pointer_cast<Identifier>(mem->base)) {
      auto it = declaredTypes.find(baseId->name);
      if (it != declaredTypes.end())
        baseElemType = it->second;
    }
    if (!baseElemType)
      throw runtime_error("CodeGenerator Error: Declared type for base not "
                          "found in member access.");
    if (isa<StructType>(baseElemType)) {
      auto *structType = cast<StructType>(baseElemType);
      std::string tag = structType->getName().str();
      auto it = structRegistry.find(tag);
      if (it == structRegistry.end())
        throw runtime_error("CodeGenerator Error: Unknown struct type: " + tag);
      auto structDecl = it->second;
      size_t index = 0;
      bool found = false;
      for (size_t i = 0; i < structDecl->members.size(); i++) {
        if (structDecl->members[i]->name == mem->member) {
          index = i;
          found = true;
          break;
        }
      }
      if (!found)
        throw runtime_error("CodeGenerator Error: Struct type " + tag +
                            " does not contain member " + mem->member);
      return builder.CreateStructGEP(structType, basePtr, index, mem->member);
    } else if (baseElemType->isArrayTy()) {
      // For unions represented as an array, return a bitcast pointer.
      return builder.CreateBitCast(
          basePtr, PointerType::getUnqual(Type::getInt32Ty(context)));
    } else {
      throw runtime_error("CodeGenerator Error: Member access applied to "
                          "non-struct/union type.");
    }
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
      if (lhs->getType()->isIntegerTy() && rhs->getType()->isFloatingPointTy())
        lhs = builder.CreateSIToFP(lhs, rhs->getType(), "sitofp");
      else if (lhs->getType()->isFloatingPointTy() &&
               rhs->getType()->isIntegerTy())
        rhs = builder.CreateSIToFP(rhs, lhs->getType(), "sitofp");
      else
        throw runtime_error(
            "CodeGenerator Error: Incompatible types in binary expression.");
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
      throw runtime_error("CodeGenerator Error: Unsupported binary operator '" +
                          binExpr->op + "'.");
    }
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
    else
      throw runtime_error("CodeGenerator Error: Unsupported cast conversion.");
  } else if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
    if (lit->type == Literal::LiteralType::Char)
      return ConstantInt::get(Type::getInt8Ty(context), lit->charValue);
    else if (lit->type == Literal::LiteralType::Bool)
      return ConstantInt::get(Type::getInt1Ty(context), lit->boolValue);
    else if (lit->type == Literal::LiteralType::Int)
      return ConstantInt::get(Type::getInt32Ty(context), lit->intValue);
    else if (lit->type == Literal::LiteralType::Float)
      return ConstantFP::get(Type::getFloatTy(context), lit->floatValue);
    else if (lit->type == Literal::LiteralType::Double)
      return ConstantFP::get(Type::getDoubleTy(context), lit->doubleValue);
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
  }
  // Handle member access as an rvalue.
  else if (auto memberAccess = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    llvm::Value *ptr = generateLValue(expr);
    llvm::Type *loadType = nullptr;
    // Look up the declared type of the base variable from our declaredTypes
    // map.
    if (auto baseId =
            std::dynamic_pointer_cast<Identifier>(memberAccess->base)) {
      auto it = declaredTypes.find(baseId->name);
      if (it != declaredTypes.end()) {
        // For unions, the declared type is an array, so load as int32.
        if (it->second->isArrayTy())
          loadType = Type::getInt32Ty(context);
        // For structs, look up the member's type.
        else if (it->second->isStructTy()) {
          StructType *structType = cast<StructType>(it->second);
          std::string tag = structType->getName().str();
          auto sit = structRegistry.find(tag);
          if (sit == structRegistry.end())
            throw runtime_error("CodeGenerator Error: Unknown struct type '" +
                                tag + "'.");
          bool found = false;
          for (auto &member : sit->second->members) {
            if (member->name == memberAccess->member) {
              loadType = getLLVMType(member->type);
              found = true;
              break;
            }
          }
          if (!found)
            throw runtime_error("CodeGenerator Error: Struct type '" + tag +
                                "' does not contain member '" +
                                memberAccess->member + "'.");
        }
      }
    }
    if (!loadType)
      throw runtime_error(
          "CodeGenerator Error: Could not determine type for member load.");
    return builder.CreateLoad(loadType, ptr, "memberload");
  } else if (auto post = std::dynamic_pointer_cast<PostfixExpression>(expr)) {
    auto id = std::dynamic_pointer_cast<Identifier>(post->operand);
    if (!id)
      throw runtime_error(
          "CodeGenerator Error: Postfix operator applied to non-identifier.");
    auto it = localVariables.find(id->name);
    if (it == localVariables.end())
      throw runtime_error("CodeGenerator Error: Undefined variable '" +
                          id->name + "' in postfix expression.");
    llvm::Value *varPtr = it->second;
    AllocaInst *allocaInst = dyn_cast<AllocaInst>(varPtr);
    if (!allocaInst)
      throw runtime_error("CodeGenerator Error: Postfix operator applied to "
                          "non-alloca variable.");
    llvm::Value *oldVal = builder.CreateLoad(allocaInst->getAllocatedType(),
                                             varPtr, id->name.c_str());
    llvm::Value *one = nullptr;
    if (oldVal->getType()->isIntegerTy())
      one = ConstantInt::get(oldVal->getType(), 1);
    else if (oldVal->getType()->isFloatingPointTy())
      one = ConstantFP::get(oldVal->getType(), 1.0);
    else
      throw runtime_error(
          "CodeGenerator Error: Unsupported type for postfix operator.");
    llvm::Value *newVal = nullptr;
    if (post->op == "++") {
      newVal = oldVal->getType()->isFloatingPointTy()
                   ? builder.CreateFAdd(oldVal, one, "postinc")
                   : builder.CreateAdd(oldVal, one, "postinc");
    } else if (post->op == "--") {
      newVal = oldVal->getType()->isFloatingPointTy()
                   ? builder.CreateFSub(oldVal, one, "postdec")
                   : builder.CreateSub(oldVal, one, "postdec");
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
    if (!callee)
      throw runtime_error("CodeGenerator Error: Undefined function '" +
                          funcCall->functionName + "' in IR.");
    std::vector<llvm::Value *> args;
    for (auto &argExpr : funcCall->arguments)
      args.push_back(generateExpression(argExpr));
    return builder.CreateCall(callee, args, "calltmp");
  }
  throw runtime_error("CodeGenerator Error: Unsupported expression type in "
                      "generateExpression().");
}
