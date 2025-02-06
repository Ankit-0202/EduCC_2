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
#include <iostream> // optional for debug prints

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
// generateCode: Walk through the Program AST and generate IR.
// We only explicitly handle top-level function declarations here.
// (If you want global variables, you can handle them similarly.)
//
std::unique_ptr<Module> CodeGenerator::generateCode(const shared_ptr<Program>& program) {
    for (const auto& decl : program->declarations) {
        // We only generate IR for function declarations and/or prototypes
        if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclaration>(decl)) {
            generateFunction(funcDecl);
        } 
        // If there's a top-level variable, you could handle it here, e.g. global variable code
    }

    // Verify the generated module
    if (verifyModule(*module, &errs())) {
        throw runtime_error("CodeGenerator Error: Module verification failed.");
    }
    return std::move(module);
}

//
// getLLVMType: Convert string type => LLVM Type
//
llvm::Type* CodeGenerator::getLLVMType(const string& type) {
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
// A helper to compare function signatures
// (param count, param types, return type) in IR
//
static bool functionSignaturesMatch(FunctionType* existing, FunctionType* candidate) {
    if (existing->getReturnType() != candidate->getReturnType()) {
        return false;
    }
    if (existing->getNumParams() != candidate->getNumParams()) {
        return false;
    }
    for (unsigned i = 0; i < existing->getNumParams(); ++i) {
        if (existing->getParamType(i) != candidate->getParamType(i)) {
            return false;
        }
    }
    return true;
}

//
// getOrCreateFunctionInModule: 
//   - If a function with this name & signature already exists, return it.
//   - If a function with this name but different signature exists => error.
//   - If it doesn't exist, create a new Function object in the module.
//
// 'isDefinition' indicates whether we intend to define a body now.
//
Function* CodeGenerator::getOrCreateFunctionInModule(
    const std::string& name,
    Type* returnType,
    const std::vector<Type*>& paramTypes,
    bool isDefinition
) {
    // Build the function type
    FunctionType* fType = FunctionType::get(returnType, paramTypes, false);

    // Check if there's an existing function by that name
    if (Function* existingFn = module->getFunction(name)) {
        // Ensure the signature is the same
        FunctionType* existingType = existingFn->getFunctionType();
        if (!functionSignaturesMatch(existingType, fType)) {
            throw runtime_error("CodeGenerator Error: Conflicting function signature for '" + name + "'.");
        }

        // If we're about to define it, but it's already got a body => redefinition error
        if (isDefinition && !existingFn->empty()) {
            throw runtime_error("CodeGenerator Error: Function '" + name + "' is already defined.");
        }

        // If it's just a prototype or re-using an existing prototype => return as is
        return existingFn;
    }

    // If we reach here, no function with that name => create it
    Function* newFn = Function::Create(
        fType,
        Function::ExternalLinkage,  // or InternalLinkage if you prefer
        name,
        module.get()
    );
    return newFn;
}

//
// generateFunction: 
//   - If body==nullptr => we only create/merge a 'declare' in IR.
//   - If body!=nullptr => define the function IR (entry block, etc.)
//
void CodeGenerator::generateFunction(const shared_ptr<FunctionDeclaration>& funcDecl) {
    // 1. Gather param types
    Type* retTy = getLLVMType(funcDecl->returnType);
    vector<Type*> paramTys;
    for (auto& param : funcDecl->parameters) {
        paramTys.push_back(getLLVMType(param.first));
    }

    // 2. Distinguish prototype (no body) vs. definition
    bool hasBody = (funcDecl->body != nullptr);

    // 3. Create or find the IR Function
    Function* function = getOrCreateFunctionInModule(
        funcDecl->name,
        retTy,
        paramTys,
        /*isDefinition=*/hasBody
    );

    // If there's no body => done (we have a "declare")
    if (!hasBody) {
        return;
    }

    // If we do have a body, define it now
    if (function->empty()) {
        // Create the entry block
        BasicBlock* entryBB = BasicBlock::Create(context, "entry", function);
        builder.SetInsertPoint(entryBB);

        // Clear old local variables
        localVariables.clear();

        // Allocate space for each param in the function
        // function->args() iterates over formal arguments
        size_t i = 0;
        for (auto& arg : function->args()) {
            const auto& paramName = funcDecl->parameters[i].second;
            arg.setName(paramName); 
            AllocaInst* alloc = builder.CreateAlloca(arg.getType(), nullptr, paramName);
            // store arg value into the alloca
            builder.CreateStore(&arg, alloc);
            // keep track in localVariables
            localVariables[paramName] = alloc;
            i++;
        }

        // Must be a CompoundStatement
        auto compound = std::dynamic_pointer_cast<CompoundStatement>(funcDecl->body);
        if (!compound) {
            throw runtime_error("CodeGenerator Error: Function body is not a CompoundStatement.");
        }

        // Emit IR for the function body statements
        generateStatement(compound);

        // If no terminator, create a default 'return' (e.g. return 0 for int)
        if (!builder.GetInsertBlock()->getTerminator()) {
            if (funcDecl->returnType == "void") {
                builder.CreateRetVoid();
            }
            else if (funcDecl->returnType == "int") {
                builder.CreateRet(ConstantInt::get(Type::getInt32Ty(context), 0));
            }
            else if (funcDecl->returnType == "float") {
                builder.CreateRet(ConstantFP::get(Type::getFloatTy(context), 0.0f));
            }
            else if (funcDecl->returnType == "double") {
                builder.CreateRet(ConstantFP::get(Type::getDoubleTy(context), 0.0));
            }
            else if (funcDecl->returnType == "char") {
                builder.CreateRet(ConstantInt::get(Type::getInt8Ty(context), 0));
            }
            else if (funcDecl->returnType == "bool") {
                builder.CreateRet(ConstantInt::get(Type::getInt1Ty(context), 0));
            }
            else {
                throw runtime_error("CodeGenerator Error: Unsupported return type '" + funcDecl->returnType + "'.");
            }
        }
    }
    else {
        // The function was already defined => we should have thrown above, but just in case:
        throw runtime_error("CodeGenerator Error: Unexpected redefinition encountered for '" + funcDecl->name + "'.");
    }
}

//
// generateStatement: Recursively build IR for each type of statement
// Returns true if the statement "terminates" (like a 'return')
//
bool CodeGenerator::generateStatement(const shared_ptr<Statement>& stmt) {
    if (auto compound = std::dynamic_pointer_cast<CompoundStatement>(stmt)) {
        bool terminated = false;
        for (auto& substmt : compound->statements) {
            terminated = generateStatement(substmt);
            if (terminated) break;
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
        Value* condVal = generateExpression(ifStmt->condition);
        if (condVal->getType() != Type::getInt1Ty(context)) {
            condVal = builder.CreateICmpNE(condVal, ConstantInt::get(condVal->getType(), 0), "ifcond");
        }

        Function* theFunction = builder.GetInsertBlock()->getParent();
        BasicBlock* thenBB = BasicBlock::Create(context, "then", theFunction);
        BasicBlock* elseBB = BasicBlock::Create(context, "else", theFunction);
        BasicBlock* mergeBB = BasicBlock::Create(context, "ifcont", theFunction);

        builder.CreateCondBr(condVal, thenBB, elseBB);

        // then branch
        builder.SetInsertPoint(thenBB);
        bool thenTerminated = generateStatement(ifStmt->thenBranch);
        if (!thenTerminated) {
            builder.CreateBr(mergeBB);
        }

        // else branch
        builder.SetInsertPoint(elseBB);
        bool elseTerminated = false;
        if (ifStmt->elseBranch) {
            elseTerminated = generateStatement(ifStmt->elseBranch.value());
        }
        if (!elseTerminated) {
            builder.CreateBr(mergeBB);
        }

        // merge
        builder.SetInsertPoint(mergeBB);
        return false;
    }
    else if (auto whileStmt = std::dynamic_pointer_cast<WhileStatement>(stmt)) {
        Function* theFunction = builder.GetInsertBlock()->getParent();
        BasicBlock* condBB = BasicBlock::Create(context, "while.cond", theFunction);
        BasicBlock* bodyBB = BasicBlock::Create(context, "while.body", theFunction);
        BasicBlock* afterBB = BasicBlock::Create(context, "while.after", theFunction);

        builder.CreateBr(condBB);
        builder.SetInsertPoint(condBB);
        Value* condVal = generateExpression(whileStmt->condition);
        if (condVal->getType() != Type::getInt1Ty(context)) {
            condVal = builder.CreateICmpNE(condVal, ConstantInt::get(condVal->getType(), 0), "whilecond");
        }
        builder.CreateCondBr(condVal, bodyBB, afterBB);

        builder.SetInsertPoint(bodyBB);
        bool bodyTerminated = generateStatement(whileStmt->body);
        if (!bodyTerminated) {
            builder.CreateBr(condBB);
        }

        builder.SetInsertPoint(afterBB);
        return false;
    }
    else if (auto forStmt = std::dynamic_pointer_cast<ForStatement>(stmt)) {
        // Initialize
        if (forStmt->initializer) {
            generateStatement(forStmt->initializer);
        }

        Function* theFunction = builder.GetInsertBlock()->getParent();
        BasicBlock* condBB = BasicBlock::Create(context, "for.cond", theFunction);
        BasicBlock* bodyBB = BasicBlock::Create(context, "for.body", theFunction);
        BasicBlock* incrBB = BasicBlock::Create(context, "for.incr", theFunction);
        BasicBlock* afterBB = BasicBlock::Create(context, "for.after", theFunction);

        // jump to cond
        builder.CreateBr(condBB);

        // cond
        builder.SetInsertPoint(condBB);
        Value* condVal = nullptr;
        if (forStmt->condition) {
            condVal = generateExpression(forStmt->condition);
            if (condVal->getType() != Type::getInt1Ty(context)) {
                condVal = builder.CreateICmpNE(condVal, ConstantInt::get(condVal->getType(), 0), "forcond");
            }
        } else {
            // if no condition, treat as 'true'
            condVal = ConstantInt::get(Type::getInt1Ty(context), 1);
        }
        builder.CreateCondBr(condVal, bodyBB, afterBB);

        // body
        builder.SetInsertPoint(bodyBB);
        bool bodyTerminated = generateStatement(forStmt->body);
        if (!bodyTerminated) {
            builder.CreateBr(incrBB);
        }

        // incr
        builder.SetInsertPoint(incrBB);
        if (forStmt->increment) {
            generateExpression(forStmt->increment);
        }
        builder.CreateBr(condBB);

        // after
        builder.SetInsertPoint(afterBB);
        return false;
    }
    else {
        throw runtime_error("CodeGenerator Error: Unsupported statement type.");
    }
}

//
// generateExpression: standard expression IR generation
//
Value* CodeGenerator::generateExpression(const shared_ptr<Expression>& expr) {
    if (auto binExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
        Value* lhs = generateExpression(binExpr->left);
        Value* rhs = generateExpression(binExpr->right);

        // If types differ, do simple int->float promotions
        if (lhs->getType() != rhs->getType()) {
            if (lhs->getType()->isIntegerTy() && rhs->getType()->isFloatingPointTy()) {
                lhs = builder.CreateSIToFP(lhs, rhs->getType(), "sitofp");
            } else if (lhs->getType()->isFloatingPointTy() && rhs->getType()->isIntegerTy()) {
                rhs = builder.CreateSIToFP(rhs, lhs->getType(), "sitofp");
            } else {
                throw runtime_error("CodeGenerator Error: Incompatible types in binary expression.");
            }
        }

        // Now do the actual op
        if (binExpr->op == "+") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFAdd(lhs, rhs, "faddtmp");
            else
                return builder.CreateAdd(lhs, rhs, "addtmp");
        }
        else if (binExpr->op == "-") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFSub(lhs, rhs, "fsubtmp");
            else
                return builder.CreateSub(lhs, rhs, "subtmp");
        }
        else if (binExpr->op == "*") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFMul(lhs, rhs, "fmultmp");
            else
                return builder.CreateMul(lhs, rhs, "multmp");
        }
        else if (binExpr->op == "/") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFDiv(lhs, rhs, "fdivtmp");
            else
                return builder.CreateSDiv(lhs, rhs, "divtmp");
        }
        // Comparisons
        else if (binExpr->op == "<=") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFCmpOLE(lhs, rhs, "cmptmp");
            else
                return builder.CreateICmpSLE(lhs, rhs, "cmptmp");
        }
        else if (binExpr->op == "<") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFCmpOLT(lhs, rhs, "cmptmp");
            else
                return builder.CreateICmpSLT(lhs, rhs, "cmptmp");
        }
        else if (binExpr->op == ">=") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFCmpOGE(lhs, rhs, "cmptmp");
            else
                return builder.CreateICmpSGE(lhs, rhs, "cmptmp");
        }
        else if (binExpr->op == ">") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFCmpOGT(lhs, rhs, "cmptmp");
            else
                return builder.CreateICmpSGT(lhs, rhs, "cmptmp");
        }
        else if (binExpr->op == "==") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFCmpOEQ(lhs, rhs, "cmptmp");
            else
                return builder.CreateICmpEQ(lhs, rhs, "cmptmp");
        }
        else if (binExpr->op == "!=") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFCmpONE(lhs, rhs, "cmptmp");
            else
                return builder.CreateICmpNE(lhs, rhs, "cmptmp");
        }
        else if (binExpr->op == "&&") {
            // ensure both sides are i1
            if (!lhs->getType()->isIntegerTy(1)) {
                lhs = builder.CreateICmpNE(lhs, ConstantInt::get(lhs->getType(), 0), "booltmp");
            }
            if (!rhs->getType()->isIntegerTy(1)) {
                rhs = builder.CreateICmpNE(rhs, ConstantInt::get(rhs->getType(), 0), "booltmp");
            }
            return builder.CreateAnd(lhs, rhs, "andtmp");
        }
        else if (binExpr->op == "||") {
            if (!lhs->getType()->isIntegerTy(1)) {
                lhs = builder.CreateICmpNE(lhs, ConstantInt::get(lhs->getType(), 0), "booltmp");
            }
            if (!rhs->getType()->isIntegerTy(1)) {
                rhs = builder.CreateICmpNE(rhs, ConstantInt::get(rhs->getType(), 0), "booltmp");
            }
            return builder.CreateOr(lhs, rhs, "ortmp");
        }
        else {
            throw runtime_error("CodeGenerator Error: Unsupported binary operator '" + binExpr->op + "'.");
        }
    }
    else if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
        // With our variant ordering: char, bool, int, float, double
        if (std::holds_alternative<char>(lit->value)) {
            return ConstantInt::get(Type::getInt8Ty(context), std::get<char>(lit->value));
        }
        else if (std::holds_alternative<bool>(lit->value)) {
            return ConstantInt::get(Type::getInt1Ty(context), std::get<bool>(lit->value));
        }
        else if (std::holds_alternative<int>(lit->value)) {
            return ConstantInt::get(Type::getInt32Ty(context), std::get<int>(lit->value));
        }
        else if (std::holds_alternative<float>(lit->value)) {
            return ConstantFP::get(Type::getFloatTy(context), std::get<float>(lit->value));
        }
        else if (std::holds_alternative<double>(lit->value)) {
            return ConstantFP::get(Type::getDoubleTy(context), std::get<double>(lit->value));
        }
    }
    else if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
        // Load from local variable
        auto it = localVariables.find(id->name);
        if (it == localVariables.end()) {
            throw runtime_error("CodeGenerator Error: Undefined variable '" + id->name + "'.");
        }
        Value* varPtr = it->second;
        if (auto allocaInst = dyn_cast<AllocaInst>(varPtr)) {
            Type* allocatedType = allocaInst->getAllocatedType();
            return builder.CreateLoad(allocatedType, varPtr, id->name.c_str());
        } else {
            throw runtime_error("CodeGenerator Error: '" + id->name + "' is not an alloca instruction.");
        }
    }
    else if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
        // Evaluate RHS
        Value* rhsVal = generateExpression(assign->rhs);
        // Store in LHS
        auto it = localVariables.find(assign->lhs);
        if (it == localVariables.end()) {
            throw runtime_error("CodeGenerator Error: Undefined variable '" + assign->lhs + "'.");
        }
        Value* varPtr = it->second;
        builder.CreateStore(rhsVal, varPtr);
        return rhsVal;
    }
    else if (auto funcCall = std::dynamic_pointer_cast<FunctionCall>(expr)) {
        // We expect the function to exist in the module
        Function* callee = module->getFunction(funcCall->functionName);
        if (!callee) {
            throw runtime_error("CodeGenerator Error: Undefined function '" + funcCall->functionName + "' in IR.");
        }
        vector<Value*> args;
        for (auto& argExpr : funcCall->arguments) {
            args.push_back(generateExpression(argExpr));
        }
        return builder.CreateCall(callee, args, "calltmp");
    }
    throw runtime_error("CodeGenerator Error: Unsupported expression type in generateExpression().");
}

//
// For local var declarations like "int x = 5;"
// We create an alloca, optionally store the initializer
//
void CodeGenerator::generateVariableDeclarationStatement(
    const shared_ptr<VariableDeclarationStatement>& varDeclStmt
) {
    Type* varTy = getLLVMType(varDeclStmt->type);
    AllocaInst* alloc = builder.CreateAlloca(varTy, nullptr, varDeclStmt->name.c_str());
    localVariables[varDeclStmt->name] = alloc;

    // If there's an initializer
    if (varDeclStmt->initializer) {
        Value* initVal = generateExpression(varDeclStmt->initializer.value());
        builder.CreateStore(initVal, alloc);
    }
}
