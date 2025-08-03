#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "CodeGenerator/Helpers.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <iostream>
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
  std::cerr << "[DEBUG] generateVariableDeclaration: Processing variable '"
            << varDecl->name << "' of type '" << varDecl->type << "'"
            << std::endl;
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
  else if (varDecl->initializer.has_value()) {
    if (auto lit =
            std::dynamic_pointer_cast<Literal>(varDecl->initializer.value())) {
      if (lit->type == Literal::LiteralType::String) {
        // Infer array size from string length + 1 (for null terminator)
        uint64_t arraySize = lit->stringValue.size() + 1;
        varType = ArrayType::get(baseType, arraySize);
        // Re-create the alloca with the correct type
        AllocaInst *alloc =
            builder.CreateAlloca(varType, nullptr, varDecl->name.c_str());
        localVarStack.back()[varDecl->name] = alloc;
        declaredVarStack.back().insert(varDecl->name);
        declaredTypes[varDecl->name] = varType;
        // Build the type string including array dimensions
        string typeWithDimensions = varDecl->type;
        for (auto &dimExpr : varDecl->dimensions) {
          if (auto lit = std::dynamic_pointer_cast<Literal>(dimExpr)) {
            typeWithDimensions += "[" + std::to_string(lit->intValue) + "]";
          }
        }
        declaredTypeStrings[varDecl->name] = typeWithDimensions;
      }
    }
  }

  AllocaInst *alloc =
      builder.CreateAlloca(varType, nullptr, varDecl->name.c_str());
  localVarStack.back()[varDecl->name] = alloc;
  declaredVarStack.back().insert(varDecl->name);
  declaredTypes[varDecl->name] = varType;

  // Build the type string including array dimensions
  string typeWithDimensions = varDecl->type;
  for (auto &dimExpr : varDecl->dimensions) {
    if (auto lit = std::dynamic_pointer_cast<Literal>(dimExpr)) {
      typeWithDimensions += "[" + std::to_string(lit->intValue) + "]";
    }
  }
  declaredTypeStrings[varDecl->name] = typeWithDimensions;

  std::cerr << "[DEBUG] generateVariableDeclaration: Variable '"
            << varDecl->name << "' registered with type '"
            << declaredTypeStrings[varDecl->name] << "'" << std::endl;

  // Handle string literal initializer for char arrays
  if (varDecl->initializer.has_value()) {
    if (auto lit =
            std::dynamic_pointer_cast<Literal>(varDecl->initializer.value())) {
      if (lit->type == Literal::LiteralType::String) {
        auto arrayTy = llvm::dyn_cast<llvm::ArrayType>(varType);
        std::string str = lit->stringValue;
        uint64_t arraySize =
            arrayTy ? arrayTy->getNumElements() : (str.size() + 1);
        if (!arrayTy) {
          varType = ArrayType::get(baseType, arraySize);
          alloc = builder.CreateAlloca(varType, nullptr, varDecl->name.c_str());
          localVarStack.back()[varDecl->name] = alloc;
          declaredVarStack.back().insert(varDecl->name);
          declaredTypes[varDecl->name] = varType;
          // Build the type string including array dimensions
          string typeWithDimensions = varDecl->type;
          for (auto &dimExpr : varDecl->dimensions) {
            if (auto lit = std::dynamic_pointer_cast<Literal>(dimExpr)) {
              typeWithDimensions += "[" + std::to_string(lit->intValue) + "]";
            }
          }
          declaredTypeStrings[varDecl->name] = typeWithDimensions;
          arrayTy = llvm::dyn_cast<llvm::ArrayType>(varType);
        }
        if (!arrayTy || !arrayTy->getElementType()->isIntegerTy(8))
          throw std::runtime_error("CodeGenerator Error: String literal "
                                   "initializer for non-char array.");
        for (uint64_t i = 0; i < arrayTy->getNumElements(); ++i) {
          char c = (i < str.size()) ? str[i] : '\0';
          llvm::Value *elemVal =
              llvm::ConstantInt::get(Type::getInt8Ty(context), c);
          std::vector<llvm::Value *> indices = {
              llvm::ConstantInt::get(Type::getInt32Ty(context), 0),
              llvm::ConstantInt::get(Type::getInt32Ty(context), i)};
          llvm::Value *elemPtr =
              builder.CreateGEP(alloc->getAllocatedType(), alloc, indices,
                                varDecl->name + "_idx");
          builder.CreateStore(elemVal, elemPtr);
        }
        return;
      }
    }
  }

  if (varDecl->initializer.has_value()) {
    // If this is an array initializer (either with explicit dimensions or
    // inferred unsized)
    if (!varDecl->dimensions.empty() ||
        std::dynamic_pointer_cast<InitializerList>(
            varDecl->initializer.value())) {
      if (auto initList = std::dynamic_pointer_cast<InitializerList>(
              varDecl->initializer.value())) {
        auto arrayTy = dyn_cast<ArrayType>(varType);
        auto structTy = dyn_cast<StructType>(varType);
        
        if (arrayTy) {
          // Handle array initializer
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
        } else if (structTy) {
          // Handle struct initializer
          for (size_t i = 0; i < initList->elements.size() && i < structTy->getNumElements(); i++) {
            llvm::Value *elemVal = generateExpression(initList->elements[i]);
            vector<llvm::Value *> indices;
            indices.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
            indices.push_back(ConstantInt::get(Type::getInt32Ty(context), i));
            llvm::Value *elemPtr =
                builder.CreateGEP(alloc->getAllocatedType(), alloc, indices,
                                  varDecl->name + "_member");
            builder.CreateStore(elemVal, elemPtr);
          }
        } else {
          throw runtime_error(
              "CodeGenerator Error: Initializer list used for non-array/non-struct "
              "variable in local variable declaration.");
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
        } else if (initVal->getType()->isFloatingPointTy() &&
                   varType->isIntegerTy()) {
          // Handle float-to-int conversion (truncation)
          initVal = builder.CreateFPToSI(initVal, varType, "fptosi");
        } else if (initVal->getType()->isIntegerTy() &&
                   varType->isFloatingPointTy()) {
          // Handle int-to-float conversion
          initVal = builder.CreateSIToFP(initVal, varType, "sitofp");
        } else {
          throw runtime_error("CodeGenerator Error: Incompatible initializer "
                              "type in local variable declaration.");
        }
      }
      builder.CreateStore(initVal, alloc);
    }
  } else if (varDecl->initializer.has_value()) {
    if (auto lit =
            std::dynamic_pointer_cast<Literal>(varDecl->initializer.value())) {
      std::cerr << "[DEBUG] (generateVariableDeclaration) found Literal "
                   "initializer, type="
                << (int)lit->type << std::endl;
      if (lit->type == Literal::LiteralType::String) {
        auto arrayTy = llvm::dyn_cast<llvm::ArrayType>(varType);
        if (!arrayTy || !arrayTy->getElementType()->isIntegerTy(8))
          throw std::runtime_error("CodeGenerator Error: String literal "
                                   "initializer for non-char array.");
        std::string str = lit->stringValue;
        for (uint64_t i = 0; i < arrayTy->getNumElements(); ++i) {
          char c = (i < str.size()) ? str[i] : '\0';
          llvm::Value *elemVal =
              llvm::ConstantInt::get(Type::getInt8Ty(context), c);
          std::vector<llvm::Value *> indices = {
              llvm::ConstantInt::get(Type::getInt32Ty(context), 0),
              llvm::ConstantInt::get(Type::getInt32Ty(context), i)};
          llvm::Value *elemPtr =
              builder.CreateGEP(alloc->getAllocatedType(), alloc, indices,
                                varDecl->name + "_idx");
          builder.CreateStore(elemVal, elemPtr);
        }
        return;
      }
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
  } else if (auto breakStmt = std::dynamic_pointer_cast<BreakStatement>(stmt)) {
    if (loopStack.empty()) {
      throw runtime_error(
          "CodeGenerator Error: 'break' statement not in a loop or switch");
    }
    // Branch to the loop exit block
    builder.CreateBr(loopStack.back().afterBlock);
    return true;
  } else if (auto continueStmt =
                 std::dynamic_pointer_cast<ContinueStatement>(stmt)) {
    if (loopStack.empty()) {
      throw runtime_error(
          "CodeGenerator Error: 'continue' statement not in a loop");
    }
    // Branch to the loop condition block
    builder.CreateBr(loopStack.back().conditionBlock);
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

    // Push loop context for break/continue
    loopStack.push_back({condBB, bodyBB, afterBB});

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

    // Pop loop context
    loopStack.pop_back();
    return false;
  } else if (auto forStmt = std::dynamic_pointer_cast<ForStatement>(stmt)) {
    if (forStmt->initializer)
      generateStatement(forStmt->initializer);
    Function *theFunction = builder.GetInsertBlock()->getParent();
    BasicBlock *condBB = BasicBlock::Create(context, "for.cond", theFunction);
    BasicBlock *bodyBB = BasicBlock::Create(context, "for.body", theFunction);
    BasicBlock *incrBB = BasicBlock::Create(context, "for.incr", theFunction);
    BasicBlock *afterBB = BasicBlock::Create(context, "for.after", theFunction);

    // Push loop context for break/continue
    loopStack.push_back({condBB, bodyBB, afterBB});

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

    // Pop loop context
    loopStack.pop_back();
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
  } else if (auto declStmt = std::dynamic_pointer_cast<DeclarationStatement>(stmt)) {
    // Handle local declarations (struct, union, enum)
    if (auto structDecl = std::dynamic_pointer_cast<StructDeclaration>(declStmt->declaration)) {
      // Handle local struct declaration
      if (structDecl->tag.has_value()) {
        // Create LLVM struct type for the struct
        std::vector<Type *> memberTypes;
        for (const auto &member : structDecl->members) {
          Type *memberType = getLLVMType(member->type);
          memberTypes.push_back(memberType);
        }

        StructType *structType = StructType::create(context, structDecl->tag.value());
        structType->setBody(memberTypes, /*isPacked=*/false);

        // Register the type in our type registry
        declaredTypes[structDecl->tag.value()] = structType;
      }
    } else if (auto unionDecl = std::dynamic_pointer_cast<UnionDeclaration>(declStmt->declaration)) {
      // Handle local union declaration
      if (unionDecl->tag.has_value()) {
        // Create LLVM struct type for the union
        std::vector<Type *> memberTypes;
        for (const auto &member : unionDecl->members) {
          Type *memberType = getLLVMType(member->type);
          memberTypes.push_back(memberType);
        }

        StructType *unionType = StructType::create(context, unionDecl->tag.value());
        unionType->setBody(memberTypes, /*isPacked=*/true); // Packed for union-like behavior

        // Register the type in our type registry
        declaredTypes[unionDecl->tag.value()] = unionType;
      }
    } else if (auto enumDecl = std::dynamic_pointer_cast<EnumDeclaration>(declStmt->declaration)) {
      // Handle local enum declaration
      for (size_t i = 0; i < enumDecl->enumerators.size(); ++i) {
        string enumName = enumDecl->enumerators[i].first;
        int value = enumDecl->enumeratorValues[i];
        Constant *initVal = ConstantInt::get(Type::getInt32Ty(context), value);
        GlobalVariable *gEnum = new GlobalVariable(*module, Type::getInt32Ty(context), true,
                                                   GlobalValue::ExternalLinkage, initVal, enumName);
      }
    }
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
    std::cerr << "[DEBUG] generateLValue: Processing member access for member: "
              << mem->member << std::endl;
    string baseEffectiveType = getEffectiveType(*this, mem->base);
    std::cerr << "[DEBUG] generateLValue: Base effective type: "
              << baseEffectiveType << std::endl;
    llvm::Value *basePtr = generateLValue(mem->base);
    std::cerr << "[DEBUG] generateLValue: Got base pointer" << std::endl;

    if (baseEffectiveType.rfind("struct ", 0) == 0) {
      string tag = baseEffectiveType.substr(7);
      tag = normalizeTag(tag);

      // Get the struct type from our local registry
      auto it = declaredTypes.find(tag);
      if (it == declaredTypes.end())
        throw runtime_error("Unknown struct type '" + tag + "'.");

      StructType *structTy = dyn_cast<StructType>(it->second);
      if (!structTy)
        throw runtime_error("Type '" + tag + "' is not a struct type.");

      // Find the member index using the enhanced type registry
      AggregateTypeInfo *typeInfo = getAggregateTypeInfo(tag);
      if (!typeInfo) {
        throw runtime_error("Struct type info not found for '" + tag + "'.");
      }

      MemberInfo *memberInfo = getMemberInfo(tag, mem->member);
      if (!memberInfo) {
        throw runtime_error("Struct type '" + tag +
                            "' does not contain member '" + mem->member + "'.");
      }

      return builder.CreateStructGEP(structTy, basePtr, memberInfo->index,
                                     mem->member);
    } else if (baseEffectiveType.rfind("union ", 0) == 0) {
      string tag = baseEffectiveType.substr(6);
      tag = normalizeTag(tag);

      // Get the union type from our local registry
      auto it = declaredTypes.find(tag);
      if (it == declaredTypes.end())
        throw runtime_error("Unknown union type '" + tag + "'.");

      StructType *unionTy = dyn_cast<StructType>(it->second);
      if (!unionTy)
        throw runtime_error("Type '" + tag + "' is not a union type.");

      // Find the member index using the enhanced type registry
      AggregateTypeInfo *typeInfo = getAggregateTypeInfo(tag);
      if (!typeInfo) {
        throw runtime_error("Union type info not found for '" + tag + "'.");
      }

      MemberInfo *memberInfo = getMemberInfo(tag, mem->member);
      if (!memberInfo) {
        throw runtime_error("Union type '" + tag +
                            "' does not contain member '" + mem->member + "'.");
      }

      // For unions, all members share the same memory location
      // We'll use index 0 since all members start at the same offset
      return builder.CreateStructGEP(unionTy, basePtr, 0, mem->member);
    }
    // non-struct/union => just get LValue of the base
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
    llvm::Value *newVal = nullptr;

    if (oldVal->getType()->isIntegerTy()) {
      one = ConstantInt::get(oldVal->getType(), 1);
    } else if (oldVal->getType()->isFloatingPointTy()) {
      one = ConstantFP::get(oldVal->getType(), 1.0);
    } else if (oldVal->getType()->isPointerTy()) {
      // For pointers, increment/decrement by the size of the pointed-to type
      // Since we're using opaque pointers, we need to determine the size
      // differently For now, assume int* (4 bytes) - this is a simplified
      // approach
      one = ConstantInt::get(Type::getInt32Ty(context), 4);
    } else {
      throw runtime_error("Unsupported type for postfix operator.");
    }

    if (post->op == "++") {
      if (oldVal->getType()->isFloatingPointTy())
        newVal = builder.CreateFAdd(oldVal, one, "postinc");
      else if (oldVal->getType()->isPointerTy()) {
        // For pointer increment, use GEP with int8* and cast
        llvm::Value *ptrAsInt8 = builder.CreateBitCast(
            oldVal, PointerType::get(Type::getInt8Ty(context), 0), "ptrcast");
        newVal = builder.CreateGEP(Type::getInt8Ty(context), ptrAsInt8, one,
                                   "postinc");
        newVal = builder.CreateBitCast(newVal, oldVal->getType(), "ptrrestore");
      } else
        newVal = builder.CreateAdd(oldVal, one, "postinc");
    } else {
      // op == "--"
      if (oldVal->getType()->isFloatingPointTy())
        newVal = builder.CreateFSub(oldVal, one, "postdec");
      else if (oldVal->getType()->isPointerTy()) {
        llvm::Value *negOne = builder.CreateNeg(one, "negindex");
        // For pointer decrement, use GEP with int8* and cast
        llvm::Value *ptrAsInt8 = builder.CreateBitCast(
            oldVal, PointerType::get(Type::getInt8Ty(context), 0), "ptrcast");
        newVal = builder.CreateGEP(Type::getInt8Ty(context), ptrAsInt8, negOne,
                                   "postdec");
        newVal = builder.CreateBitCast(newVal, oldVal->getType(), "ptrrestore");
      } else
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
// getLLVMType: convert a string type (which may contain pointer stars) into an
// LLVM type. Updated to support multiple pointer levels (e.g. "int **").
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
    auto it = declaredTypes.find(tag);
    if (it == declaredTypes.end()) {
      throw runtime_error("CodeGenerator Error: Unknown union type '" + type +
                          "'.");
    }
    ty = it->second;
  } else if (baseType.rfind("struct ", 0) == 0) {
    string tag = baseType.substr(7);
    auto it = declaredTypes.find(tag);
    if (it == declaredTypes.end()) {
      throw runtime_error("CodeGenerator Error: Unknown struct type '" + type +
                          "'.");
    }
    ty = it->second;
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
