#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "CodeGenerator/Helpers.hpp"
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

// Helper: find an identified struct type by name in the module.
static StructType *getStructTypeByName(Module *M, const string &tag) {
  for (StructType *ST : M->getIdentifiedStructTypes()) {
    if (ST->getName() == tag)
      return ST;
  }
  return nullptr;
}

//
// Local Scope Management
//
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

//
// generateVariableDeclaration
//
// If the declaration has no explicit dimensions but its initializer is an
// InitializerList (as in unsized array declarations like "int arr[] = { ...
// };"), we infer the array size from the initializer list.
void CodeGenerator::generateVariableDeclaration(
    const shared_ptr<VariableDeclaration> &varDecl) {
  llvm::Type *baseType = getLLVMType(varDecl->type);
  llvm::Type *varType = baseType;

  // If dimensions were provided, treat as an array variable.
  if (!varDecl->dimensions.empty()) {
    for (auto it = varDecl->dimensions.rbegin();
         it != varDecl->dimensions.rend(); ++it) {
      llvm::Value *dimVal = generateExpression(*it);
      ConstantInt *constDim = dyn_cast<ConstantInt>(dimVal);
      if (!constDim)
        throw runtime_error(
            "CodeGenerator Error: Array dimension must be a constant integer.");
      uint64_t arraySize = constDim->getZExtValue();
      varType = ArrayType::get(varType, arraySize);
    }
  }
  // Otherwise, if there is an initializer list, infer the array size from it.
  else if (varDecl->initializer) {
    if (auto initList = std::dynamic_pointer_cast<InitializerList>(
            varDecl->initializer.value())) {
      uint64_t arraySize = initList->elements.size();
      varType = ArrayType::get(baseType, arraySize);
    }
  }

  AllocaInst *alloc =
      builder.CreateAlloca(varType, nullptr, varDecl->name.c_str());
  localVarStack.back()[varDecl->name] = alloc;
  declaredVarStack.back().insert(varDecl->name);
  declaredTypes[varDecl->name] = varType;
  declaredTypeStrings[varDecl->name] = varDecl->type;

  if (varDecl->initializer) {
    // If this is an array initializer (either with explicit dimensions or
    // inferred unsized)
    if (!varDecl->dimensions.empty() ||
        std::dynamic_pointer_cast<InitializerList>(
            varDecl->initializer.value())) {
      if (auto initList = std::dynamic_pointer_cast<InitializerList>(
              varDecl->initializer.value())) {
        auto arrayTy = dyn_cast<ArrayType>(varType);
        if (!arrayTy)
          throw runtime_error(
              "CodeGenerator Error: Initializer list used for non-array "
              "variable in local variable declaration.");
        uint64_t arraySize = arrayTy->getNumElements();
        for (uint64_t i = 0; i < arraySize; i++) {
          llvm::Value *elemVal = nullptr;
          if (i < initList->elements.size()) {
            elemVal = generateExpression(initList->elements[i]);
          } else {
            elemVal = Constant::getNullValue(arrayTy->getElementType());
          }
          vector<llvm::Value *> indices;
          indices.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
          indices.push_back(ConstantInt::get(Type::getInt32Ty(context), i));
          llvm::Value *elemPtr =
              builder.CreateGEP(alloc->getAllocatedType(), alloc, indices,
                                varDecl->name + "_idx");
          builder.CreateStore(elemVal, elemPtr);
        }
      } else {
        throw runtime_error("CodeGenerator Error: Array initializer must be an "
                            "initializer list.");
      }
    } else {
      // Scalar variable: simply generate the initializer expression.
      llvm::Value *initVal = generateExpression(varDecl->initializer.value());
      if (initVal->getType() != varType) {
        if (initVal->getType()->isFloatingPointTy() &&
            varType->isFloatingPointTy()) {
          if (initVal->getType()->getFPMantissaWidth() >
              varType->getFPMantissaWidth())
            initVal = builder.CreateFPTrunc(initVal, varType, "fptrunc");
          else
            initVal = builder.CreateFPExt(initVal, varType, "fpext");
        } else {
          throw runtime_error("CodeGenerator Error: Incompatible initializer "
                              "type in local variable declaration.");
        }
      }
      builder.CreateStore(initVal, alloc);
    }
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
    // For local variable declarations, wrap the declaration in a
    // VariableDeclaration node.
    auto varDecl = std::make_shared<VariableDeclaration>(
        varDeclStmt->type, varDeclStmt->name, varDeclStmt->initializer,
        varDeclStmt->dimensions);
    generateVariableDeclaration(varDecl);
    return false;
  } else if (auto multiVarDeclStmt =
                 std::dynamic_pointer_cast<MultiVariableDeclarationStatement>(
                     stmt)) {
    for (auto &singleDecl : multiVarDeclStmt->declarations) {
      auto varDecl = std::make_shared<VariableDeclaration>(
          singleDecl->type, singleDecl->name, singleDecl->initializer,
          singleDecl->dimensions);
      generateVariableDeclaration(varDecl);
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

//
// generateLValue: returns an lvalue pointer for an expression
//
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
  // 2) MemberAccess: base.member
  else if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    string baseEffectiveType = getEffectiveType(*this, mem->base);
    llvm::Value *basePtr = generateLValue(mem->base);
    if (baseEffectiveType.rfind("struct ", 0) == 0) {
      string tag = baseEffectiveType.substr(7);
      tag = normalizeTag(tag);
      auto sit = structRegistry.find(tag);
      if (sit == structRegistry.end())
        throw runtime_error("Unknown struct type '" + tag + "'.");
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
      StructType *structTy = getStructTypeByName(module.get(), tag);
      if (!structTy) {
        // Build from the registry
        vector<Type *> memberTypes;
        for (auto &m : sit->second->members) {
          memberTypes.push_back(getLLVMType(m->type));
        }
        structTy = StructType::create(context, memberTypes, tag, false);
      }
      return builder.CreateStructGEP(structTy, basePtr, index, mem->member);
    }
    // non-struct => just get LValue of the base
    else {
      return generateLValue(mem->base);
    }
  }
  // 3) PostfixExpression: e.g. i++
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
      throw runtime_error("Postfix operator on non-alloca variable: " +
                          id->name);
    llvm::Value *oldVal =
        builder.CreateLoad(allocaInst->getAllocatedType(), v, id->name.c_str());
    llvm::Value *one = nullptr;
    if (oldVal->getType()->isIntegerTy())
      one = ConstantInt::get(oldVal->getType(), 1);
    else if (oldVal->getType()->isFloatingPointTy())
      one = ConstantFP::get(oldVal->getType(), 1.0);
    else
      throw runtime_error("Unsupported type for postfix operator.");
    llvm::Value *newVal = nullptr;
    if (post->op == "++") {
      if (oldVal->getType()->isFloatingPointTy())
        newVal = builder.CreateFAdd(oldVal, one, "postinc");
      else
        newVal = builder.CreateAdd(oldVal, one, "postinc");
    } else {
      // op == "--"
      if (oldVal->getType()->isFloatingPointTy())
        newVal = builder.CreateFSub(oldVal, one, "postdec");
      else
        newVal = builder.CreateSub(oldVal, one, "postdec");
    }
    builder.CreateStore(newVal, v);
    return oldVal; // The "postfix" expression's value is the oldVal
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
  // 6) FunctionCall => generally not an lvalue unless returning a reference
  // type
  else if (auto funcCall = std::dynamic_pointer_cast<FunctionCall>(expr)) {
    throw runtime_error("Expression is not a valid lvalue: function call");
  }
  // 7) Unary '*' operator (dereference)
  else if (auto un = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
    if (un->op == "*") {
      // For lvalue purposes, simply evaluate the operand to obtain the pointer.
      llvm::Value *ptr = generateExpression(un->operand);
      if (!ptr->getType()->isPointerTy())
        throw runtime_error(
            "generateLValue: '*' applied to non-pointer expression");
      return ptr;
    }
  }
  throw runtime_error("Expression is not a valid lvalue.");
}

//
// generateExpression: compute the rvalue of an expression
//
llvm::Value *CodeGenerator::generateExpression(const ExpressionPtr &expr) {
  if (auto binExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
    llvm::Value *lhs = generateExpression(binExpr->left);
    llvm::Value *rhs = generateExpression(binExpr->right);
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
      // Retrieve the declared type (as a string) for the operand.
      // For example, if the operand is declared as "int**", then
      // getEffectiveType() will return "int**" and we remove one trailing '*'
      // to get "int", the element type.
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
    if (!callee) {
      throw runtime_error("Undefined function in IR: " + call->functionName);
    }
    vector<llvm::Value *> args;
    for (auto &argExpr : call->arguments) {
      args.push_back(generateExpression(argExpr));
    }
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

//
// getLLVMType: convert a string type (which may contain pointer stars) into an
// LLVM type. Updated to support multiple pointer levels (e.g. "int **") and
// typedef resolution.
llvm::Type *CodeGenerator::getLLVMType(const string &type) {
  // Count the number of '*' characters.
  int pointerCount = 0;
  size_t pos = type.find('*');
  if (pos != string::npos) {
    for (char c : type) {
      if (c == '*')
        pointerCount++;
    }
  }
  // Remove all '*' and trim whitespace.
  string baseType = type;
  baseType.erase(std::remove(baseType.begin(), baseType.end(), '*'),
                 baseType.end());
  // Trim leading/trailing spaces.
  while (!baseType.empty() && isspace(baseType.front()))
    baseType.erase(baseType.begin());
  while (!baseType.empty() && isspace(baseType.back()))
    baseType.pop_back();

  // NEW: Resolve typedef alias if it exists.
  if (typedefRegistry.find(baseType) != typedefRegistry.end()) {
    baseType = typedefRegistry[baseType];
  }

  llvm::Type *ty = nullptr;
  if (baseType == "int")
    ty = Type::getInt32Ty(context);
  else if (baseType == "float")
    ty = Type::getFloatTy(context);
  else if (baseType == "char")
    ty = Type::getInt8Ty(context);
  else if (baseType == "double")
    ty = Type::getDoubleTy(context);
  else if (baseType == "bool")
    ty = Type::getInt1Ty(context);
  else if (baseType == "void")
    ty = Type::getVoidTy(context);
  else if (baseType.rfind("enum ", 0) == 0)
    ty = Type::getInt32Ty(context);
  else if (baseType.rfind("union ", 0) == 0) {
    string tag = baseType.substr(6);
    auto it = unionRegistry.find(tag);
    if (it == unionRegistry.end())
      throw runtime_error("CodeGenerator Error: Unknown union type '" + type +
                          "'.");
    int maxSize = 0;
    DataLayout dl(module.get());
    for (auto &member : it->second->members) {
      int memberSize = 0;
      if (member->type == "int" || member->type == "float")
        memberSize = 4;
      else if (member->type == "char" || member->type == "bool")
        memberSize = 1;
      else if (member->type == "double")
        memberSize = 8;
      else if (member->type.rfind("enum ", 0) == 0)
        memberSize = 4;
      else if (member->type.rfind("union ", 0) == 0)
        throw runtime_error("Nested unions not supported.");
      else if (member->type.rfind("struct ", 0) == 0) {
        llvm::Type *structTy = getLLVMType(member->type);
        uint64_t size = dl.getTypeAllocSize(structTy);
        memberSize = (int)size;
      } else {
        throw runtime_error("Unsupported union member type '" + member->type +
                            "'.");
      }
      if (memberSize > maxSize)
        maxSize = memberSize;
    }
    if (maxSize <= 0)
      maxSize = 1;
    ty = ArrayType::get(Type::getInt8Ty(context), maxSize);
  } else if (baseType.rfind("struct ", 0) == 0) {
    string tag = baseType.substr(7);
    auto it = structRegistry.find(tag);
    if (it == structRegistry.end())
      throw runtime_error("CodeGenerator Error: Unknown struct type '" + type +
                          "'.");
    vector<Type *> memberTypes;
    for (auto &m : it->second->members) {
      memberTypes.push_back(getLLVMType(m->type));
    }
    ty = StructType::create(context, memberTypes, tag, /*packed=*/false);
  } else {
    throw runtime_error("CodeGenerator Error: Unsupported type '" + type +
                        "'.");
  }
  // Now wrap the base type in pointer types as needed.
  for (int i = 0; i < pointerCount; i++) {
    ty = PointerType::getUnqual(ty);
  }
  return ty;
}

static bool functionSignaturesMatch(FunctionType *existing,
                                    FunctionType *candidate) {
  if (existing->getReturnType() != candidate->getReturnType())
    return false;
  if (existing->getNumParams() != candidate->getNumParams())
    return false;
  for (unsigned i = 0; i < existing->getNumParams(); ++i) {
    if (existing->getParamType(i) != candidate->getParamType(i))
      return false;
  }
  return true;
}

llvm::Function *CodeGenerator::getOrCreateFunctionInModule(
    const std::string &name, llvm::Type *returnType,
    const vector<Type *> &paramTypes, bool isDefinition) {
  FunctionType *fType = FunctionType::get(returnType, paramTypes, false);
  if (Function *existingFn = module->getFunction(name)) {
    FunctionType *existingType = existingFn->getFunctionType();
    if (!functionSignaturesMatch(existingType, fType))
      throw runtime_error("CodeGenerator Error: Conflicting signature for '" +
                          name + "'.");
    if (isDefinition && !existingFn->empty())
      throw runtime_error("CodeGenerator Error: Function '" + name +
                          "' is already defined.");
    return existingFn;
  }
  Function *newFn =
      Function::Create(fType, Function::ExternalLinkage, name, module.get());
  return newFn;
}

llvm::Function *CodeGenerator::generateFunction(
    const shared_ptr<FunctionDeclaration> &funcDecl) {
  llvm::Type *retTy = getLLVMType(funcDecl->returnType);
  vector<Type *> paramTys;
  for (auto &param : funcDecl->parameters) {
    paramTys.push_back(getLLVMType(param.first));
  }
  bool hasBody = (funcDecl->body != nullptr);
  llvm::Function *function =
      getOrCreateFunctionInModule(funcDecl->name, retTy, paramTys, hasBody);
  if (!hasBody)
    return function;
  if (!function->empty()) {
    throw runtime_error(
        "CodeGenerator Error: Unexpected redefinition encountered for '" +
        funcDecl->name + "'.");
  }

  // Create entry block.
  llvm::BasicBlock *entryBB =
      llvm::BasicBlock::Create(context, "entry", function);
  builder.SetInsertPoint(entryBB);

  // Push a new local scope (used by lookupLocalVar in Statements.cpp).
  pushLocalScope();

  // For each function parameter, allocate local space and add to the local
  // scope.
  size_t i = 0;
  for (auto &arg : function->args()) {
    const string &paramName = funcDecl->parameters[i].second; // e.g., "a"
    arg.setName(paramName);
    llvm::AllocaInst *alloc =
        builder.CreateAlloca(arg.getType(), nullptr, paramName);
    builder.CreateStore(&arg, alloc);
    localVarStack.back()[paramName] = alloc;
    declaredTypes[paramName] = arg.getType();
    declaredTypeStrings[paramName] = funcDecl->parameters[i].first;
    i++;
  }

  // Generate the function body.
  auto compound = std::dynamic_pointer_cast<CompoundStatement>(funcDecl->body);
  if (!compound) {
    throw runtime_error(
        "CodeGenerator Error: Function body is not a CompoundStatement.");
  }
  generateStatement(compound);

  // If no terminator was generated, add a default return.
  if (!builder.GetInsertBlock()->getTerminator()) {
    if (funcDecl->returnType == "void")
      builder.CreateRetVoid();
    else if (funcDecl->returnType == "int")
      builder.CreateRet(
          llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0));
    else if (funcDecl->returnType == "float")
      builder.CreateRet(
          llvm::ConstantFP::get(llvm::Type::getFloatTy(context), 0.0f));
    else if (funcDecl->returnType == "double")
      builder.CreateRet(
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(context), 0.0));
    else if (funcDecl->returnType == "char")
      builder.CreateRet(
          llvm::ConstantInt::get(llvm::Type::getInt8Ty(context), 0));
    else if (funcDecl->returnType == "bool")
      builder.CreateRet(
          llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), 0));
    else
      throw runtime_error("CodeGenerator Error: Unsupported return type '" +
                          funcDecl->returnType + "'.");
  }
  return function;
}
