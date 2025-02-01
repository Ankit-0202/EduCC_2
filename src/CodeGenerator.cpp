#include "CodeGenerator.hpp"
#include "AST.hpp"
#include "SymbolTable.hpp"

#include <llvm/IR/Verifier.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/raw_ostream.h>
#include <stdexcept>
#include <unordered_map>
#include <vector>

using namespace llvm;
using std::runtime_error;
using std::string;
using std::shared_ptr;
using std::vector;

//
// Constructor: initializes the IRBuilder and creates a new module.
//
CodeGenerator::CodeGenerator()
    : builder(context),
      module(std::make_unique<Module>("main_module", context)) {
}

//
// generateCode: Walks the AST (Program) and generates an LLVM Module.
// Throws a runtime_error if verification fails.
//
std::unique_ptr<Module> CodeGenerator::generateCode(const shared_ptr<Program>& program) {
    for (const auto& decl : program->declarations) {
        if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclaration>(decl)) {
            generateFunction(funcDecl);
        }
    }
    if (verifyModule(*module, &errs())) {
        throw runtime_error("CodeGenerator Error: Module verification failed.");
    }
    return std::move(module);
}

//
// getLLVMType: Maps a C type (as string) to an LLVM type.
//
Type* CodeGenerator::getLLVMType(const string& type) {
    if (type == "int")
        return Type::getInt32Ty(context);
    else if (type == "float")
        return Type::getFloatTy(context);
    else if (type == "char")
        return Type::getInt8Ty(context);
    else if (type == "double")
        return Type::getDoubleTy(context);
    else if (type == "bool")
        return Type::getInt1Ty(context);
    else if (type == "void")
        return Type::getVoidTy(context);
    else
        throw runtime_error("CodeGenerator Error: Unsupported type '" + type + "'.");
}

//
// generateStatement: Generates LLVM IR for a statement AST node.
// Returns true if the statement is “terminating” (e.g. a return).
//
bool CodeGenerator::generateStatement(const StatementPtr& stmt) {
    if (auto compound = std::dynamic_pointer_cast<CompoundStatement>(stmt)) {
        bool terminated = false;
        for (const auto& substmt : compound->statements) {
            terminated = generateStatement(substmt);
            if (terminated)
                break;
        }
        return terminated;
    }
    else if (auto exprStmt = std::dynamic_pointer_cast<ExpressionStatement>(stmt)) {
        generateExpression(exprStmt->expression);
        return false;
    }
    else if (auto varDeclStmt = std::dynamic_pointer_cast<VariableDeclarationStatement>(stmt)) {
        generateVariableDeclarationStatement(varDeclStmt);
        return false;
    }
    else if (auto retStmt = std::dynamic_pointer_cast<ReturnStatement>(stmt)) {
        Value* retVal = generateExpression(retStmt->expression);
        builder.CreateRet(retVal);
        return true;
    }
    else if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(stmt)) {
        Value* cond = generateExpression(ifStmt->condition);
        if (cond->getType() != Type::getInt1Ty(context))
            cond = builder.CreateICmpNE(cond, ConstantInt::get(cond->getType(), 0), "ifcond");
        Function* theFunction = builder.GetInsertBlock()->getParent();
        BasicBlock* thenBB  = BasicBlock::Create(context, "then", theFunction);
        BasicBlock* elseBB  = BasicBlock::Create(context, "else", theFunction);
        BasicBlock* mergeBB = BasicBlock::Create(context, "ifcont", theFunction);
        builder.CreateCondBr(cond, thenBB, elseBB);
        builder.SetInsertPoint(thenBB);
        bool thenTerminated = generateStatement(ifStmt->thenBranch);
        if (!thenTerminated)
            builder.CreateBr(mergeBB);
        builder.SetInsertPoint(elseBB);
        bool elseTerminated = false;
        if (ifStmt->elseBranch.has_value())
            elseTerminated = generateStatement(ifStmt->elseBranch.value());
        if (!elseTerminated)
            builder.CreateBr(mergeBB);
        builder.SetInsertPoint(mergeBB);
        return false;
    }
    else if (auto whileStmt = std::dynamic_pointer_cast<WhileStatement>(stmt)) {
        Function* theFunction = builder.GetInsertBlock()->getParent();
        BasicBlock* condBB = BasicBlock::Create(context, "while.cond", theFunction);
        BasicBlock* loopBB = BasicBlock::Create(context, "while.body", theFunction);
        BasicBlock* afterBB = BasicBlock::Create(context, "while.after", theFunction);
        builder.CreateBr(condBB);
        builder.SetInsertPoint(condBB);
        Value* cond = generateExpression(whileStmt->condition);
        if (cond->getType() != Type::getInt1Ty(context))
            cond = builder.CreateICmpNE(cond, ConstantInt::get(cond->getType(), 0), "whilecond");
        builder.CreateCondBr(cond, loopBB, afterBB);
        builder.SetInsertPoint(loopBB);
        generateStatement(whileStmt->body);
        if (!builder.GetInsertBlock()->getTerminator())
            builder.CreateBr(condBB);
        builder.SetInsertPoint(afterBB);
        return false;
    }
    else if (auto forStmt = std::dynamic_pointer_cast<ForStatement>(stmt)) {
        Function* theFunction = builder.GetInsertBlock()->getParent();
        // Process initializer.
        if (forStmt->initializer)
            generateStatement(forStmt->initializer);
        BasicBlock* condBB = BasicBlock::Create(context, "for.cond", theFunction);
        BasicBlock* loopBB = BasicBlock::Create(context, "for.body", theFunction);
        BasicBlock* incrBB = BasicBlock::Create(context, "for.incr", theFunction);
        BasicBlock* afterBB = BasicBlock::Create(context, "for.after", theFunction);
        builder.CreateBr(condBB);
        builder.SetInsertPoint(condBB);
        Value* cond = generateExpression(forStmt->condition);
        if (cond->getType() != Type::getInt1Ty(context))
            cond = builder.CreateICmpNE(cond, ConstantInt::get(cond->getType(), 0), "forcond");
        builder.CreateCondBr(cond, loopBB, afterBB);
        builder.SetInsertPoint(loopBB);
        generateStatement(forStmt->body);
        builder.CreateBr(incrBB);
        builder.SetInsertPoint(incrBB);
        if (forStmt->increment)
            generateExpression(forStmt->increment);
        builder.CreateBr(condBB);
        builder.SetInsertPoint(afterBB);
        return false;
    }
    else {
        throw runtime_error("CodeGenerator Error: Unsupported statement type.");
    }
}

//
// generateExpression: Recursively generates LLVM IR for an expression AST node.
//
Value* CodeGenerator::generateExpression(const shared_ptr<Expression>& expr) {
    if (auto binExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
        Value* left  = generateExpression(binExpr->left);
        Value* right = generateExpression(binExpr->right);
        if (left->getType() != right->getType()) {
            if (left->getType()->isIntegerTy() && right->getType()->isFloatingPointTy())
                left = builder.CreateSIToFP(left, right->getType(), "sitofp");
            else if (left->getType()->isFloatingPointTy() && right->getType()->isIntegerTy())
                right = builder.CreateSIToFP(right, left->getType(), "sitofp");
            else
                throw runtime_error("CodeGenerator Error: Incompatible types in binary expression.");
        }
        if (binExpr->op == "+") {
            if (left->getType()->isFloatingPointTy())
                return builder.CreateFAdd(left, right, "faddtmp");
            else
                return builder.CreateAdd(left, right, "addtmp");
        }
        else if (binExpr->op == "-") {
            if (left->getType()->isFloatingPointTy())
                return builder.CreateFSub(left, right, "fsubtmp");
            else
                return builder.CreateSub(left, right, "subtmp");
        }
        else if (binExpr->op == "*") {
            if (left->getType()->isFloatingPointTy())
                return builder.CreateFMul(left, right, "fmultmp");
            else
                return builder.CreateMul(left, right, "multmp");
        }
        else if (binExpr->op == "/") {
            if (left->getType()->isFloatingPointTy())
                return builder.CreateFDiv(left, right, "fdivtmp");
            else
                return builder.CreateSDiv(left, right, "divtmp");
        }
        else if (binExpr->op == "<=") {
            if (left->getType()->isFloatingPointTy())
                return builder.CreateFCmpOLE(left, right, "cmptmp");
            else
                return builder.CreateICmpSLE(left, right, "cmptmp");
        }
        else if (binExpr->op == "<") {
            if (left->getType()->isFloatingPointTy())
                return builder.CreateFCmpOLT(left, right, "cmptmp");
            else
                return builder.CreateICmpSLT(left, right, "cmptmp");
        }
        else if (binExpr->op == ">=") {
            if (left->getType()->isFloatingPointTy())
                return builder.CreateFCmpOGE(left, right, "cmptmp");
            else
                return builder.CreateICmpSGE(left, right, "cmptmp");
        }
        else if (binExpr->op == ">") {
            if (left->getType()->isFloatingPointTy())
                return builder.CreateFCmpOGT(left, right, "cmptmp");
            else
                return builder.CreateICmpSGT(left, right, "cmptmp");
        }
        else if (binExpr->op == "==") {
            if (left->getType()->isFloatingPointTy())
                return builder.CreateFCmpOEQ(left, right, "cmptmp");
            else
                return builder.CreateICmpEQ(left, right, "cmptmp");
        }
        else if (binExpr->op == "!=") {
            if (left->getType()->isFloatingPointTy())
                return builder.CreateFCmpONE(left, right, "cmptmp");
            else
                return builder.CreateICmpNE(left, right, "cmptmp");
        }
        else {
            throw runtime_error("CodeGenerator Error: Unsupported binary operator '" + binExpr->op + "'.");
        }
    }
    else if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
        if (std::holds_alternative<char>(lit->value))
            return ConstantInt::get(Type::getInt8Ty(context), std::get<char>(lit->value));
        else if (std::holds_alternative<bool>(lit->value))
            return ConstantInt::get(Type::getInt1Ty(context), std::get<bool>(lit->value));
        else if (std::holds_alternative<int>(lit->value))
            return ConstantInt::get(Type::getInt32Ty(context), std::get<int>(lit->value));
        else if (std::holds_alternative<float>(lit->value))
            return ConstantFP::get(Type::getFloatTy(context), std::get<float>(lit->value));
        else if (std::holds_alternative<double>(lit->value))
            return ConstantFP::get(Type::getDoubleTy(context), std::get<double>(lit->value));
    }
    else if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
        auto it = localVariables.find(id->name);
        if (it != localVariables.end()) {
            Value* varPtr = it->second;
            if (auto allocaInst = dyn_cast<AllocaInst>(varPtr)) {
                Type* allocatedType = allocaInst->getAllocatedType();
                return builder.CreateLoad(allocatedType, varPtr, id->name.c_str());
            } else {
                throw runtime_error("CodeGenerator Error: Variable '" + id->name + "' is not allocated.");
            }
        } else {
            throw runtime_error("CodeGenerator Error: Undefined variable '" + id->name + "'.");
        }
    }
    else if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
        Value* value = generateExpression(assign->rhs);
        auto it = localVariables.find(assign->lhs);
        if (it == localVariables.end())
            throw runtime_error("CodeGenerator Error: Undefined variable '" + assign->lhs + "'.");
        Value* varPtr = it->second;
        builder.CreateStore(value, varPtr);
        return value;
    }
    else if (auto funcCall = std::dynamic_pointer_cast<FunctionCall>(expr)) {
        Function* callee = module->getFunction(funcCall->functionName);
        if (!callee)
            throw runtime_error("CodeGenerator Error: Undefined function '" + funcCall->functionName + "'.");
        vector<Value*> args;
        for (const auto& arg : funcCall->arguments) {
            args.push_back(generateExpression(arg));
        }
        return builder.CreateCall(callee, args, "calltmp");
    }
    throw runtime_error("CodeGenerator Error: Unsupported expression type.");
}

void CodeGenerator::generateFunction(const shared_ptr<FunctionDeclaration>& funcDecl) {
    Type* retType = getLLVMType(funcDecl->returnType);
    vector<Type*> paramTypes;
    for (const auto& param : funcDecl->parameters) {
        paramTypes.push_back(getLLVMType(param.first));
    }
    FunctionType* funcType = FunctionType::get(retType, paramTypes, false);
    Function* function = Function::Create(funcType, Function::ExternalLinkage, funcDecl->name, module.get());

    size_t index = 0;
    for (auto& arg : function->args()) {
        arg.setName(funcDecl->parameters[index].second);
        index++;
    }

    BasicBlock* entry = BasicBlock::Create(context, "entry", function);
    builder.SetInsertPoint(entry);

    localVariables.clear();
    index = 0;
    for (auto& arg : function->args()) {
        AllocaInst* alloc = builder.CreateAlloca(arg.getType(), nullptr, arg.getName());
        builder.CreateStore(&arg, alloc);
        localVariables[arg.getName().str()] = alloc;
        index++;
    }

    if (auto compound = std::dynamic_pointer_cast<CompoundStatement>(funcDecl->body)) {
        generateStatement(compound);
    } else {
        throw runtime_error("CodeGenerator Error: Function body is not a compound statement.");
    }

    if (!builder.GetInsertBlock()->getTerminator()) {
        if (funcDecl->returnType == "void")
            builder.CreateRetVoid();
        else if (funcDecl->returnType == "int")
            builder.CreateRet(ConstantInt::get(Type::getInt32Ty(context), 0));
        else if (funcDecl->returnType == "float")
            builder.CreateRet(ConstantFP::get(Type::getFloatTy(context), 0.0f));
        else if (funcDecl->returnType == "char")
            builder.CreateRet(ConstantInt::get(Type::getInt8Ty(context), 0));
        else if (funcDecl->returnType == "double")
            builder.CreateRet(ConstantFP::get(Type::getDoubleTy(context), 0.0));
        else if (funcDecl->returnType == "bool")
            builder.CreateRet(ConstantInt::get(Type::getInt1Ty(context), 0));
        else
            throw runtime_error("CodeGenerator Error: Unsupported return type '" + funcDecl->returnType + "'.");
    }
}

void CodeGenerator::generateVariableDeclarationStatement(
    const shared_ptr<VariableDeclarationStatement>& varDeclStmt) {
    Type* varType = getLLVMType(varDeclStmt->type);
    AllocaInst* alloc = builder.CreateAlloca(varType, nullptr, varDeclStmt->name.c_str());
    localVariables[varDeclStmt->name] = alloc;
    if (varDeclStmt->initializer) {
        Value* initVal = generateExpression(varDeclStmt->initializer.value());
        builder.CreateStore(initVal, alloc);
    }
}
