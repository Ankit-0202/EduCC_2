// compiler/src/CodeGenerator/Expressions.cpp
#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h> // For composite types.
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

using namespace llvm;
using std::runtime_error;
using std::shared_ptr;
using std::string;

extern std::unordered_map<std::string, int>
    enumRegistry; // Global map for enum constants

//
// Helper: Recursively retrieve the top-level base variable name from a member
// access chain. For example, given "rect.topLeft.x", returns "rect".
//
namespace {
string getBaseVariableName(const ExpressionPtr &expr) {
  if (auto id = std::dynamic_pointer_cast<Identifier>(expr))
    return id->name;
  if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr))
    return getBaseVariableName(mem->base);
  throw runtime_error(
      "CodeGenerator Error: Base variable not found in member access chain.");
}
} // namespace

//
// Helper: Normalize a tag (struct or union name) by stripping any trailing
// ".<number>". For example, "Point.1" becomes "Point".
//
namespace {
string normalizeTag(const string &tag) {
  size_t pos = tag.find('.');
  if (pos != string::npos)
    return tag.substr(0, pos);
  return tag;
}
} // namespace

//
// Helper: Recursively resolve the declared LLVM type for a member access chain.
// Uses both the declaredTypes and declaredTypeStrings maps from the
// CodeGenerator, as well as the global registries (structRegistry and
// unionRegistry).
//
namespace {
llvm::Type *resolveFullMemberType(const ExpressionPtr &expr,
                                  CodeGenerator &CG) {
  // If expr is an identifier, look it up in declaredTypes.
  if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    auto it = CG.declaredTypes.find(id->name);
    if (it == CG.declaredTypes.end())
      throw runtime_error("CodeGenerator Error: Declared type for variable '" +
                          id->name + "' not found.");
    return it->second;
  }
  // If expr is a member access, resolve its base first.
  if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    llvm::Type *baseType = resolveFullMemberType(mem->base, CG);
    // Retrieve the original declared type string for the base variable.
    string baseName = getBaseVariableName(mem->base);
    auto tsIt = CG.declaredTypeStrings.find(baseName);
    if (tsIt == CG.declaredTypeStrings.end())
      throw runtime_error(
          "CodeGenerator Error: Declared type string for variable '" +
          baseName + "' not found.");
    string origType = tsIt->second;
    // If the base was declared as a union, look it up in unionRegistry.
    if (origType.rfind("union ", 0) == 0) {
      string tag = origType.substr(6);
      tag = normalizeTag(tag);
      auto uit = unionRegistry.find(tag);
      if (uit == unionRegistry.end())
        throw runtime_error("CodeGenerator Error: Unknown union type '" + tag +
                            "'.");
      for (auto &member : uit->second->members) {
        if (member->name == mem->member)
          return CG.getLLVMType(member->type);
      }
      throw runtime_error("CodeGenerator Error: Union type '" + tag +
                          "' does not contain member '" + mem->member + "'.");
    }
    // Otherwise, assume the base is a struct.
    if (!baseType->isStructTy())
      throw runtime_error("CodeGenerator Error: Base type is not a struct in "
                          "member access chain.");
    StructType *structType = cast<StructType>(baseType);
    string tag = normalizeTag(structType->getName().str());
    auto sit = structRegistry.find(tag);
    if (sit == structRegistry.end())
      throw runtime_error("CodeGenerator Error: Unknown struct type '" + tag +
                          "'.");
    for (auto &member : sit->second->members) {
      if (member->name == mem->member)
        return CG.getLLVMType(member->type);
    }
    throw runtime_error("CodeGenerator Error: Struct type '" + tag +
                        "' does not contain member '" + mem->member + "'.");
  }
  throw runtime_error("CodeGenerator Error: Cannot resolve full member type.");
}
} // namespace

llvm::Value *CodeGenerator::generateLValue(const ExpressionPtr &expr) {
  if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    // Look up the identifier in the local variable stack.
    llvm::Value *v = lookupLocalVar(id->name);
    if (v)
      return v;
    GlobalVariable *gVar = module->getGlobalVariable(id->name);
    if (gVar) {
      // If the global variable is constant and has an initializer (as with
      // enums), return the initializer directly.
      if (gVar->isConstant() && gVar->hasInitializer())
        return gVar->getInitializer();
      return builder.CreateLoad(gVar->getValueType(), gVar, id->name.c_str());
    }
    // Check for an enum constant in the global enumRegistry.
    auto ecIt = enumRegistry.find(id->name);
    if (ecIt != enumRegistry.end())
      return ConstantInt::get(Type::getInt32Ty(context), ecIt->second);
    throw runtime_error("CodeGenerator Error: Undefined variable '" + id->name +
                        "'.");
  } else if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    // Get the base variable name.
    string baseName = getBaseVariableName(mem->base);
    // Look up its declared original type string.
    auto tsIt = declaredTypeStrings.find(baseName);
    if (tsIt == declaredTypeStrings.end())
      throw runtime_error(
          "CodeGenerator Error: Declared type string for variable '" +
          baseName + "' not found.");
    string origType = tsIt->second;
    llvm::Value *basePtr = generateLValue(mem->base);
    // If the base was declared as a union, generate an lvalue via bitcast.
    if (origType.rfind("union ", 0) == 0) {
      string tag = origType.substr(6);
      tag = normalizeTag(tag);
      auto uit = unionRegistry.find(tag);
      if (uit == unionRegistry.end())
        throw runtime_error("CodeGenerator Error: Unknown union type '" + tag +
                            "'.");
      llvm::Type *memberType = nullptr;
      for (auto &member : uit->second->members) {
        if (member->name == mem->member) {
          memberType = getLLVMType(member->type);
          break;
        }
      }
      if (!memberType)
        throw runtime_error("CodeGenerator Error: Union type '" + tag +
                            "' does not contain member '" + mem->member + "'.");
      return builder.CreateBitCast(basePtr, PointerType::getUnqual(memberType));
    }
    // Otherwise, assume a struct.
    llvm::Type *baseElemType = resolveFullMemberType(mem->base, *this);
    if (baseElemType->isStructTy()) {
      StructType *structType = cast<StructType>(baseElemType);
      string tag = normalizeTag(structType->getName().str());
      auto sit = structRegistry.find(tag);
      if (sit == structRegistry.end())
        throw runtime_error("CodeGenerator Error: Unknown struct type '" + tag +
                            "'.");
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
        throw runtime_error("CodeGenerator Error: Struct type '" + tag +
                            "' does not contain member '" + mem->member + "'.");
      return builder.CreateStructGEP(structType, basePtr, index, mem->member);
    } else if (baseElemType->isArrayTy()) {
      return builder.CreateBitCast(
          basePtr, PointerType::getUnqual(Type::getInt32Ty(context)));
    }
    throw runtime_error(
        "CodeGenerator Error: Member access applied to non-aggregate type.");
  } else {
    throw runtime_error(
        "CodeGenerator Error: Expression is not a valid lvalue.");
  }
}

//
// generateExpression - Generates code for an expression.
// Parameter is now taken as a const reference to match the header.
//
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
    if (binExpr->op == "+")
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFAdd(lhs, rhs, "faddtmp")
                 : builder.CreateAdd(lhs, rhs, "addtmp");
    else if (binExpr->op == "-")
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFSub(lhs, rhs, "fsubtmp")
                 : builder.CreateSub(lhs, rhs, "subtmp");
    else if (binExpr->op == "*")
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFMul(lhs, rhs, "fmultmp")
                 : builder.CreateMul(lhs, rhs, "multmp");
    else if (binExpr->op == "/")
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFDiv(lhs, rhs, "fdivtmp")
                 : builder.CreateSDiv(lhs, rhs, "divtmp");
    else if (binExpr->op == "<=")
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOLE(lhs, rhs, "cmptmp")
                 : builder.CreateICmpSLE(lhs, rhs, "cmptmp");
    else if (binExpr->op == "<")
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOLT(lhs, rhs, "cmptmp")
                 : builder.CreateICmpSLT(lhs, rhs, "cmptmp");
    else if (binExpr->op == ">=")
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOGE(lhs, rhs, "cmptmp")
                 : builder.CreateICmpSGE(lhs, rhs, "cmptmp");
    else if (binExpr->op == ">")
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOGT(lhs, rhs, "cmptmp")
                 : builder.CreateICmpSGT(lhs, rhs, "cmptmp");
    else if (binExpr->op == "==")
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpOEQ(lhs, rhs, "cmptmp")
                 : builder.CreateICmpEQ(lhs, rhs, "cmptmp");
    else if (binExpr->op == "!=")
      return lhs->getType()->isFloatingPointTy()
                 ? builder.CreateFCmpONE(lhs, rhs, "cmptmp")
                 : builder.CreateICmpNE(lhs, rhs, "cmptmp");
    else if (binExpr->op == "&&") {
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
    } else if (binExpr->op == "&")
      return builder.CreateAnd(lhs, rhs, "bitandtmp");
    else if (binExpr->op == "^")
      return builder.CreateXor(lhs, rhs, "bitxortmp");
    else if (binExpr->op == "|")
      return builder.CreateOr(lhs, rhs, "bitor_tmp");
    else if (binExpr->op == "<<")
      return builder.CreateShl(lhs, rhs, "shltmp");
    else if (binExpr->op == ">>")
      return builder.CreateAShr(lhs, rhs, "shrtmp");
    else
      throw runtime_error("CodeGenerator Error: Unsupported binary operator '" +
                          binExpr->op + "'.");
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
    // Use lookupLocalVar to find the variable declared in the current scope(s).
    llvm::Value *v = lookupLocalVar(id->name);
    if (v) {
      if (auto allocaInst = dyn_cast<AllocaInst>(v)) {
        llvm::Type *allocatedType = allocaInst->getAllocatedType();
        return builder.CreateLoad(allocatedType, v, id->name.c_str());
      } else {
        throw runtime_error("CodeGenerator Error: '" + id->name +
                            "' is not an alloca instruction.");
      }
    }
    // Then check for global variable.
    GlobalVariable *gVar = module->getGlobalVariable(id->name);
    if (gVar) {
      // If this global is constant (e.g. an enum constant), return its
      // initializer.
      if (gVar->isConstant() && gVar->hasInitializer())
        return gVar->getInitializer();
      return builder.CreateLoad(gVar->getValueType(), gVar, id->name.c_str());
    }
    // Finally, check for an enum constant.
    auto ecIt = enumRegistry.find(id->name);
    if (ecIt != enumRegistry.end())
      return ConstantInt::get(Type::getInt32Ty(context), ecIt->second);
    throw runtime_error("CodeGenerator Error: Undefined variable '" + id->name +
                        "'.");
  } else if (auto memberAccess =
                 std::dynamic_pointer_cast<MemberAccess>(expr)) {
    llvm::Value *ptr = generateLValue(expr);
    llvm::Type *loadType = resolveFullMemberType(expr, *this);
    return builder.CreateLoad(loadType, ptr, "memberload");
  } else if (auto post = std::dynamic_pointer_cast<PostfixExpression>(expr)) {
    auto id = std::dynamic_pointer_cast<Identifier>(post->operand);
    if (!id)
      throw runtime_error(
          "CodeGenerator Error: Postfix operator applied to non-identifier.");
    llvm::Value *v = lookupLocalVar(id->name);
    if (!v)
      throw runtime_error("CodeGenerator Error: Undefined variable '" +
                          id->name + "' in postfix expression.");
    AllocaInst *allocaInst = dyn_cast<AllocaInst>(v);
    if (!allocaInst)
      throw runtime_error("CodeGenerator Error: Postfix operator applied to "
                          "non-alloca variable.");
    llvm::Value *oldVal =
        builder.CreateLoad(allocaInst->getAllocatedType(), v, id->name.c_str());
    llvm::Value *one = nullptr;
    if (oldVal->getType()->isIntegerTy())
      one = ConstantInt::get(oldVal->getType(), 1);
    else if (oldVal->getType()->isFloatingPointTy())
      one = ConstantFP::get(oldVal->getType(), 1.0);
    else
      throw runtime_error(
          "CodeGenerator Error: Unsupported type for postfix operator.");
    llvm::Value *newVal = nullptr;
    if (post->op == "++")
      newVal = oldVal->getType()->isFloatingPointTy()
                   ? builder.CreateFAdd(oldVal, one, "postinc")
                   : builder.CreateAdd(oldVal, one, "postinc");
    else if (post->op == "--")
      newVal = oldVal->getType()->isFloatingPointTy()
                   ? builder.CreateFSub(oldVal, one, "postdec")
                   : builder.CreateSub(oldVal, one, "postdec");
    else
      throw runtime_error("CodeGenerator Error: Unknown postfix operator '" +
                          post->op + "'.");
    builder.CreateStore(newVal, v);
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
