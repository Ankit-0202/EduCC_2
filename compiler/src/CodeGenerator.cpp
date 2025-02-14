#include "CodeGenerator.hpp"
#include "AST.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"

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
#include <iostream>

using namespace llvm;
using std::runtime_error;
using std::string;
using std::shared_ptr;
using std::vector;

// Helper: generate an lvalue pointer for assignable expressions.
llvm::Value* CodeGenerator::generateLValue(const ExpressionPtr &expr) {
    if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
         auto it = localVariables.find(id->name);
         if (it != localVariables.end()) {
              return it->second;
         }
         GlobalVariable* gVar = module->getGlobalVariable(id->name);
         if (gVar)
              return gVar;
         throw runtime_error("CodeGenerator Error: Undefined variable '" + id->name + "' in lvalue generation.");
    }
    else if (auto memberAccess = std::dynamic_pointer_cast<MemberAccess>(expr)) {
         llvm::Value* basePtr = generateLValue(memberAccess->base);
         llvm::Type* varType = nullptr;
         if (auto allocaInst = dyn_cast<AllocaInst>(basePtr))
             varType = allocaInst->getAllocatedType();
         else if (auto globalVar = dyn_cast<GlobalVariable>(basePtr))
             varType = globalVar->getValueType();
         else
             throw runtime_error("CodeGenerator Error: Unexpected variable pointer type in member access.");

         if (varType->isStructTy()) {
             StructType* stTy = cast<StructType>(varType);
             string typeName = stTy->getName().str();
             // Handle union types (named as "union.<tag>").
             if (typeName.rfind("union.", 0) == 0) {
                 Value* ptrToArray = builder.CreateStructGEP(stTy, basePtr, 0, "union_array");
                 // For demonstration, assume union member accesses yield an int.
                 return builder.CreateBitCast(ptrToArray, PointerType::getUnqual(Type::getInt32Ty(context)));
             }
             // Otherwise, treat as a struct.
             else if (typeName.rfind("struct.", 0) == 0) {
                 string tag = typeName.substr(7);
                 auto it = structRegistry.find(tag);
                 if (it == structRegistry.end())
                     throw runtime_error("CodeGenerator Error: Unknown struct type '" + tag + "'");
             auto structDecl = it->second;
             int index = -1;
                 // Find the member index by name.
             for (size_t i = 0; i < structDecl->members.size(); i++) {
                if (structDecl->members[i]->name == memberAccess->member) {
                    index = i;
                    break;
                }
             }
             if (index < 0)
                     throw runtime_error("CodeGenerator Error: Struct '" + tag + "' has no member named '" + memberAccess->member + "'");
                 return builder.CreateStructGEP(stTy, basePtr, index, "memberptr");
         }
         }
         // If not a struct type, we do not support member access.
         throw runtime_error("CodeGenerator Error: Member access on unsupported type.");
    }
    else {
         throw runtime_error("CodeGenerator Error: Expression is not a valid lvalue.");
    }
}

//
// Constructor: initializes the IRBuilder and creates a new module.
//
CodeGenerator::CodeGenerator()
    : builder(context),
      module(std::make_unique<Module>("main_module", context)) {
}

//
// generateCode: Walk through the Program AST and generate IR.
// Global declarations are processed first (including enum, union, and struct declarations),
// then function declarations.
//
std::unique_ptr<Module> CodeGenerator::generateCode(const shared_ptr<Program>& program) {
    // Process global declarations.
    for (const auto& decl : program->declarations) {
        if (auto varDecl = std::dynamic_pointer_cast<VariableDeclaration>(decl)) {
            llvm::Type* varType = getLLVMType(varDecl->type);
            GlobalVariable* gVar = new GlobalVariable(
                *module,
                varType,
                false,
                GlobalValue::ExternalLinkage,
                nullptr,
                varDecl->name
            );
            // For unions, set a minimum alignment (e.g. 4 bytes).
            if (varDecl->type.rfind("union ", 0) == 0)
                gVar->setAlignment(Align(4));
            if (varDecl->initializer) {
                if (auto lit = std::dynamic_pointer_cast<Literal>(varDecl->initializer.value())) {
                    Constant* initVal = nullptr;
                    if (std::holds_alternative<int>(lit->value))
                        initVal = ConstantInt::get(Type::getInt32Ty(context), std::get<int>(lit->value));
                    else if (std::holds_alternative<float>(lit->value))
                        initVal = ConstantFP::get(Type::getFloatTy(context), std::get<float>(lit->value));
                    else if (std::holds_alternative<double>(lit->value))
                        initVal = ConstantFP::get(Type::getDoubleTy(context), std::get<double>(lit->value));
                    else if (std::holds_alternative<char>(lit->value))
                        initVal = ConstantInt::get(Type::getInt8Ty(context), std::get<char>(lit->value));
                    else if (std::holds_alternative<bool>(lit->value))
                        initVal = ConstantInt::get(Type::getInt1Ty(context), std::get<bool>(lit->value));
                    else
                        throw runtime_error("CodeGenerator Error: Unsupported literal type in global initializer.");

                    // If the initializer type doesn't match the variable type, insert a conversion.
                    if (initVal->getType() != varType) {
                        if (initVal->getType()->isFloatingPointTy() && varType->isFloatingPointTy()) {
                            // If converting from double to float, truncate.
                            if (initVal->getType()->getFPMantissaWidth() > varType->getFPMantissaWidth())
                                initVal = ConstantFP::get(varType, (float)std::get<double>(lit->value));
                            else
                                initVal = ConstantFP::get(varType, (double)std::get<float>(lit->value));
                        } else {
                            throw runtime_error("CodeGenerator Error: Incompatible initializer type in global variable declaration.");
                        }
                    }
                    gVar->setInitializer(initVal);
                } else {
                    throw runtime_error("CodeGenerator Error: Global variable initializer must be a literal.");
                }
            } else {
                Constant* defaultVal = nullptr;
                if (varDecl->type == "int")
                    defaultVal = ConstantInt::get(Type::getInt32Ty(context), 0);
                else if (varDecl->type == "float")
                    defaultVal = ConstantFP::get(Type::getFloatTy(context), 0.0f);
                else if (varDecl->type == "char")
                    defaultVal = ConstantInt::get(Type::getInt8Ty(context), 0);
                else if (varDecl->type == "double")
                    defaultVal = ConstantFP::get(Type::getDoubleTy(context), 0.0);
                else if (varDecl->type == "bool")
                    defaultVal = ConstantInt::get(Type::getInt1Ty(context), 0);
                else
                    throw runtime_error("CodeGenerator Error: Unsupported type in global variable declaration.");
                gVar->setInitializer(defaultVal);
            }
        }
        else if (auto multiDecl = std::dynamic_pointer_cast<MultiVariableDeclaration>(decl)) {
            for (const auto& singleDecl : multiDecl->declarations) {
                llvm::Type* varType = getLLVMType(singleDecl->type);
                GlobalVariable* gVar = new GlobalVariable(
                    *module,
                    varType,
                    false,
                    GlobalValue::ExternalLinkage,
                    nullptr,
                    singleDecl->name
                );
                if (singleDecl->type.rfind("union ", 0) == 0)
                    gVar->setAlignment(Align(4));
                if (singleDecl->initializer) {
                    if (auto lit = std::dynamic_pointer_cast<Literal>(singleDecl->initializer.value())) {
                        Constant* initVal = nullptr;
                        if (std::holds_alternative<int>(lit->value))
                            initVal = ConstantInt::get(Type::getInt32Ty(context), std::get<int>(lit->value));
                        else if (std::holds_alternative<float>(lit->value))
                            initVal = ConstantFP::get(Type::getFloatTy(context), std::get<float>(lit->value));
                        else if (std::holds_alternative<double>(lit->value))
                            initVal = ConstantFP::get(Type::getDoubleTy(context), std::get<double>(lit->value));
                        else if (std::holds_alternative<char>(lit->value))
                            initVal = ConstantInt::get(Type::getInt8Ty(context), std::get<char>(lit->value));
                        else if (std::holds_alternative<bool>(lit->value))
                            initVal = ConstantInt::get(Type::getInt1Ty(context), std::get<bool>(lit->value));
                        else
                            throw runtime_error("CodeGenerator Error: Unsupported literal type in global initializer.");
                        if (initVal->getType() != varType) {
                            if (initVal->getType()->isFloatingPointTy() && varType->isFloatingPointTy()) {
                                if (initVal->getType()->getFPMantissaWidth() > varType->getFPMantissaWidth())
                                    initVal = ConstantFP::get(varType, (float)std::get<double>(lit->value));
                                else
                                    initVal = ConstantFP::get(varType, (double)std::get<float>(lit->value));
                            } else {
                                throw runtime_error("CodeGenerator Error: Incompatible initializer type in global variable declaration.");
                            }
                        }
                        gVar->setInitializer(initVal);
                    } else {
                        throw runtime_error("CodeGenerator Error: Global variable initializer must be a literal.");
                    }
                } else {
                    Constant* defaultVal = nullptr;
                    if (singleDecl->type == "int")
                        defaultVal = ConstantInt::get(Type::getInt32Ty(context), 0);
                    else if (singleDecl->type == "float")
                        defaultVal = ConstantFP::get(Type::getFloatTy(context), 0.0f);
                    else if (singleDecl->type == "char")
                        defaultVal = ConstantInt::get(Type::getInt8Ty(context), 0);
                    else if (singleDecl->type == "double")
                        defaultVal = ConstantFP::get(Type::getDoubleTy(context), 0.0);
                    else if (singleDecl->type == "bool")
                        defaultVal = ConstantInt::get(Type::getInt1Ty(context), 0);
                    else
                        throw runtime_error("CodeGenerator Error: Unsupported type in global variable declaration.");
                    gVar->setInitializer(defaultVal);
                }
            }
        }
        // Process enum declarations.
        else if (auto enumDecl = std::dynamic_pointer_cast<EnumDeclaration>(decl)) {
            // For each enumerator, create a global constant variable of type i32.
            for (size_t i = 0; i < enumDecl->enumerators.size(); ++i) {
                string enumName = enumDecl->enumerators[i].first;
                int value = enumDecl->enumeratorValues[i];
                Constant* initVal = ConstantInt::get(Type::getInt32Ty(context), value);
                GlobalVariable* gEnum = new GlobalVariable(
                    *module,
                    Type::getInt32Ty(context),
                    true,
                    GlobalValue::ExternalLinkage,
                    initVal,
                    enumName
                );
                (void)gEnum; // Silence unused variable warning.
            }
        }
        // For union and struct declarations, no global variable is created.
    }

    for (const auto& decl : program->declarations) {
        if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclaration>(decl))
            generateFunction(funcDecl);
    }

    if (verifyModule(*module, &errs()))
        throw runtime_error("CodeGenerator Error: Module verification failed.");
    return std::move(module);
}

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
    // Support enum types (treated as int)
    else if (type.rfind("enum ", 0) == 0)
        return Type::getInt32Ty(context);
    // Support union types.
    else if (type.rfind("union ", 0) == 0) {
        std::string tag = type.substr(6);
        std::string unionName = "union." + tag;
        // Instead of getTypeByName, iterate over identified struct types.
        llvm::StructType* unionStruct = nullptr;
        for (auto* ST : module->getIdentifiedStructTypes()) {
            if (ST->getName() == unionName) {
                unionStruct = ST;
                break;
            }
        }
        if (unionStruct)
            return unionStruct;
        auto it = unionRegistry.find(tag);
        if (it == unionRegistry.end())
            throw runtime_error("CodeGenerator Error: Unknown union type '" + type + "'");
        int maxSize = 0;
        for (auto &member : it->second->members) {
            int memberSize = 0;
            if (member->type == "int") memberSize = 4;
            else if (member->type == "float") memberSize = 4;
            else if (member->type == "char") memberSize = 1;
            else if (member->type == "double") memberSize = 8;
            else if (member->type == "bool") memberSize = 1;
            else if (member->type.rfind("enum ", 0) == 0) memberSize = 4;
            else if (member->type.rfind("union ", 0) == 0)
                throw runtime_error("CodeGenerator Error: Nested unions not supported.");
            else
                throw runtime_error("CodeGenerator Error: Unsupported union member type '" + member->type + "'.");
            if (memberSize > maxSize)
                maxSize = memberSize;
        }
        vector<Type*> elements;
        elements.push_back(ArrayType::get(Type::getInt8Ty(context), maxSize));
        unionStruct = StructType::create(context, elements, unionName, false);
        return unionStruct;
    }
    // Support struct types.
    else if (type.rfind("struct ", 0) == 0) {
        std::string tag = type.substr(7);
        auto it = structRegistry.find(tag);
        if (it == structRegistry.end())
            throw runtime_error("CodeGenerator Error: Unknown struct type '" + type + "'");
        auto structDecl = it->second;
        vector<Type*> memberTypes;
        for (auto &member : structDecl->members)
            memberTypes.push_back(getLLVMType(member->type));
        std::string llvmStructName = "struct." + tag;
        return StructType::create(context, memberTypes, llvmStructName, false);
    }
    else
        throw runtime_error("CodeGenerator Error: Unsupported type '" + type + "'.");
}

static bool functionSignaturesMatch(FunctionType* existing, FunctionType* candidate) {
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

llvm::Function* CodeGenerator::getOrCreateFunctionInModule(
    const std::string& name,
    Type* returnType,
    const vector<Type*>& paramTypes,
    bool isDefinition
) {
    FunctionType* fType = FunctionType::get(returnType, paramTypes, false);
    if (Function* existingFn = module->getFunction(name)) {
        FunctionType* existingType = existingFn->getFunctionType();
        if (!functionSignaturesMatch(existingType, fType))
            throw runtime_error("CodeGenerator Error: Conflicting function signature for '" + name + "'.");
        if (isDefinition && !existingFn->empty())
            throw runtime_error("CodeGenerator Error: Function '" + name + "' is already defined.");
        return existingFn;
    }
    Function* newFn = Function::Create(fType, Function::ExternalLinkage, name, module.get());
    return newFn;
}

//
// generateFunction: 
//   - If body==nullptr => we only create/merge a 'declare' in IR.
//   - If body!=nullptr => define the function IR (entry block, etc.)
//
void CodeGenerator::generateFunction(const shared_ptr<FunctionDeclaration>& funcDecl) {
    llvm::Type* retTy = getLLVMType(funcDecl->returnType);
    vector<Type*> paramTys;
    for (auto& param : funcDecl->parameters)
        paramTys.push_back(getLLVMType(param.first));
    bool hasBody = (funcDecl->body != nullptr);
    Function* function = getOrCreateFunctionInModule(funcDecl->name, retTy, paramTys, hasBody);
    if (!hasBody)
        return;
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
            // For union parameters, set alignment to 4.
            if (funcDecl->parameters[i].first.rfind("union ", 0) == 0)
                alloc->setAlignment(Align(4));
            builder.CreateStore(&arg, alloc);
            // keep track in localVariables
            localVariables[paramName] = alloc;
            i++;
        }

        // Must be a CompoundStatement
        auto compound = std::dynamic_pointer_cast<CompoundStatement>(funcDecl->body);
        if (!compound)
            throw runtime_error("CodeGenerator Error: Function body is not a CompoundStatement.");
        generateStatement(compound);

        // If no terminator, create a default 'return' (e.g. return 0 for int)
        if (!builder.GetInsertBlock()->getTerminator()) {
            if (funcDecl->returnType == "void")
                builder.CreateRetVoid();
            else if (funcDecl->returnType == "int")
                builder.CreateRet(ConstantInt::get(Type::getInt32Ty(context), 0));
            else if (funcDecl->returnType == "float")
                builder.CreateRet(ConstantFP::get(Type::getFloatTy(context), 0.0f));
            else if (funcDecl->returnType == "double")
                builder.CreateRet(ConstantFP::get(Type::getDoubleTy(context), 0.0));
            else if (funcDecl->returnType == "char")
                builder.CreateRet(ConstantInt::get(Type::getInt8Ty(context), 0));
            else if (funcDecl->returnType == "bool")
                builder.CreateRet(ConstantInt::get(Type::getInt1Ty(context), 0));
            else
                throw runtime_error("CodeGenerator Error: Unsupported return type '" + funcDecl->returnType + "'.");
        }
    } else {
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
    else if (auto multiVarDeclStmt = std::dynamic_pointer_cast<MultiVariableDeclarationStatement>(stmt)) {
        for (auto& singleDeclStmt : multiVarDeclStmt->declarations)
            generateVariableDeclarationStatement(singleDeclStmt);
        return false;
    }
    else if (auto retStmt = std::dynamic_pointer_cast<ReturnStatement>(stmt)) {
        llvm::Value* retVal = generateExpression(retStmt->expression);
        llvm::Function* currentFunction = builder.GetInsertBlock()->getParent();
        llvm::Type* expectedType = currentFunction->getReturnType();
        if (retVal->getType() != expectedType) {
            if (retVal->getType()->isIntegerTy(1) && expectedType->isIntegerTy(32))
                retVal = builder.CreateZExt(retVal, expectedType, "zexttmp");
            else if (retVal->getType()->isIntegerTy() && expectedType->isIntegerTy())
                retVal = builder.CreateIntCast(retVal, expectedType, false, "intcasttmp");
            else
                throw runtime_error("CodeGenerator Error: Return value type does not match function return type.");
        }
        builder.CreateRet(retVal);
        return true;
    }
    else if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(stmt)) {
        llvm::Value* condVal = generateExpression(ifStmt->condition);
        if (condVal->getType() != llvm::Type::getInt1Ty(context))
            condVal = builder.CreateICmpNE(condVal, ConstantInt::get(condVal->getType(), 0), "ifcond");
        llvm::Function* theFunction = builder.GetInsertBlock()->getParent();
        llvm::BasicBlock* thenBB = llvm::BasicBlock::Create(context, "then", theFunction);
        llvm::BasicBlock* elseBB = llvm::BasicBlock::Create(context, "else", theFunction);
        llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(context, "ifcont", theFunction);
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
    }
    else if (auto whileStmt = std::dynamic_pointer_cast<WhileStatement>(stmt)) {
        llvm::Function* theFunction = builder.GetInsertBlock()->getParent();
        llvm::BasicBlock* condBB = llvm::BasicBlock::Create(context, "while.cond", theFunction);
        llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(context, "while.body", theFunction);
        llvm::BasicBlock* afterBB = llvm::BasicBlock::Create(context, "while.after", theFunction);
        builder.CreateBr(condBB);
        builder.SetInsertPoint(condBB);
        llvm::Value* condVal = generateExpression(whileStmt->condition);
        if (condVal->getType() != llvm::Type::getInt1Ty(context))
            condVal = builder.CreateICmpNE(condVal, ConstantInt::get(condVal->getType(), 0), "whilecond");
        builder.CreateCondBr(condVal, bodyBB, afterBB);
        builder.SetInsertPoint(bodyBB);
        bool bodyTerminated = generateStatement(whileStmt->body);
        if (!bodyTerminated)
            builder.CreateBr(condBB);
        builder.SetInsertPoint(afterBB);
        return false;
    }
    else if (auto forStmt = std::dynamic_pointer_cast<ForStatement>(stmt)) {
        if (forStmt->initializer)
            generateStatement(forStmt->initializer);
        llvm::Function* theFunction = builder.GetInsertBlock()->getParent();
        llvm::BasicBlock* condBB = llvm::BasicBlock::Create(context, "for.cond", theFunction);
        llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(context, "for.body", theFunction);
        llvm::BasicBlock* incrBB = llvm::BasicBlock::Create(context, "for.incr", theFunction);
        llvm::BasicBlock* afterBB = llvm::BasicBlock::Create(context, "for.after", theFunction);
        builder.CreateBr(condBB);

        // cond
        builder.SetInsertPoint(condBB);
        llvm::Value* condVal = nullptr;
        if (forStmt->condition) {
            condVal = generateExpression(forStmt->condition);
            if (condVal->getType() != llvm::Type::getInt1Ty(context))
                condVal = builder.CreateICmpNE(condVal, ConstantInt::get(condVal->getType(), 0), "forcond");
        } else {
            condVal = ConstantInt::get(llvm::Type::getInt1Ty(context), 1);
        }
        builder.CreateCondBr(condVal, bodyBB, afterBB);

        // body
        builder.SetInsertPoint(bodyBB);
        bool bodyTerminated = generateStatement(forStmt->body);
        if (!bodyTerminated)
            builder.CreateBr(incrBB);
        builder.SetInsertPoint(incrBB);
        if (forStmt->increment)
            generateExpression(forStmt->increment);
        builder.CreateBr(condBB);

        // after
        builder.SetInsertPoint(afterBB);
        return false;
    }
    else if (auto switchStmt = std::dynamic_pointer_cast<SwitchStatement>(stmt)) {
        llvm::Value* condVal = generateExpression(switchStmt->expression);
        if (!condVal->getType()->isIntegerTy())
            throw runtime_error("CodeGenerator Error: Switch expression must be of integer type.");
        llvm::Function* theFunction = builder.GetInsertBlock()->getParent();
        llvm::BasicBlock* defaultBB = llvm::BasicBlock::Create(context, "switch.default", theFunction);
        
        SwitchInst* switchInst = builder.CreateSwitch(condVal, defaultBB, switchStmt->cases.size());
        for (auto &casePair : switchStmt->cases) {
            if (!casePair.first.has_value())
                throw runtime_error("CodeGenerator Error: Case label missing in case clause.");
            llvm::Value* caseVal = generateExpression(casePair.first.value());
            if (!isa<ConstantInt>(caseVal))
                throw runtime_error("CodeGenerator Error: Case label must be a constant integer.");
            llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "switch.case", theFunction);
            switchInst->addCase(cast<ConstantInt>(caseVal), caseBB);
            builder.SetInsertPoint(caseBB);
            bool terminated = generateStatement(casePair.second);
            if (!terminated)
                builder.CreateBr(defaultBB);
        }
        builder.SetInsertPoint(defaultBB);
        if (switchStmt->defaultCase.has_value()) {
            bool terminated = generateStatement(switchStmt->defaultCase.value());
            if (!terminated)
                builder.CreateUnreachable();
        } else {
            builder.CreateUnreachable();
        }
        return false;
    }
    else {
        throw runtime_error("CodeGenerator Error: Unsupported statement type.");
    }
}

llvm::Value* CodeGenerator::generateExpression(const ExpressionPtr& expr) {
    if (auto binExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
        llvm::Value* lhs = generateExpression(binExpr->left);
        llvm::Value* rhs = generateExpression(binExpr->right);

        // If types differ, do simple int->float promotions (unchanged code)
        if (lhs->getType() != rhs->getType()) {
            if (lhs->getType()->isIntegerTy() && rhs->getType()->isFloatingPointTy())
                lhs = builder.CreateSIToFP(lhs, rhs->getType(), "sitofp");
            else if (lhs->getType()->isFloatingPointTy() && rhs->getType()->isIntegerTy())
                rhs = builder.CreateSIToFP(rhs, lhs->getType(), "sitofp");
            else
                throw runtime_error("CodeGenerator Error: Incompatible types in binary expression.");
        }

        // Arithmetic and logical operators
        if (binExpr->op == "+") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFAdd(lhs, rhs, "faddtmp");
            else
                return builder.CreateAdd(lhs, rhs, "addtmp");
        } else if (binExpr->op == "-") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFSub(lhs, rhs, "fsubtmp");
            else
                return builder.CreateSub(lhs, rhs, "subtmp");
        } else if (binExpr->op == "*") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFMul(lhs, rhs, "fmultmp");
            else
                return builder.CreateMul(lhs, rhs, "multmp");
        } else if (binExpr->op == "/") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFDiv(lhs, rhs, "fdivtmp");
            else
                return builder.CreateSDiv(lhs, rhs, "divtmp");
        } else if (binExpr->op == "<=") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFCmpOLE(lhs, rhs, "cmptmp");
            else
                return builder.CreateICmpSLE(lhs, rhs, "cmptmp");
        } else if (binExpr->op == "<") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFCmpOLT(lhs, rhs, "cmptmp");
            else
                return builder.CreateICmpSLT(lhs, rhs, "cmptmp");
        } else if (binExpr->op == ">=") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFCmpOGE(lhs, rhs, "cmptmp");
            else
                return builder.CreateICmpSGE(lhs, rhs, "cmptmp");
        } else if (binExpr->op == ">") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFCmpOGT(lhs, rhs, "cmptmp");
            else
                return builder.CreateICmpSGT(lhs, rhs, "cmptmp");
        } else if (binExpr->op == "==") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFCmpOEQ(lhs, rhs, "cmptmp");
            else
                return builder.CreateICmpEQ(lhs, rhs, "cmptmp");
        } else if (binExpr->op == "!=") {
            if (lhs->getType()->isFloatingPointTy())
                return builder.CreateFCmpONE(lhs, rhs, "cmptmp");
            else
                return builder.CreateICmpNE(lhs, rhs, "cmptmp");
        } else if (binExpr->op == "&&") {
            if (!lhs->getType()->isIntegerTy(1))
                lhs = builder.CreateICmpNE(lhs, ConstantInt::get(lhs->getType(), 0), "booltmp");
            if (!rhs->getType()->isIntegerTy(1))
                rhs = builder.CreateICmpNE(rhs, ConstantInt::get(rhs->getType(), 0), "booltmp");
            return builder.CreateAnd(lhs, rhs, "andtmp");
        } else if (binExpr->op == "||") {
            if (!lhs->getType()->isIntegerTy(1))
                lhs = builder.CreateICmpNE(lhs, ConstantInt::get(lhs->getType(), 0), "booltmp");
            if (!rhs->getType()->isIntegerTy(1))
                rhs = builder.CreateICmpNE(rhs, ConstantInt::get(rhs->getType(), 0), "booltmp");
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
            throw runtime_error("CodeGenerator Error: Unsupported binary operator '" + binExpr->op + "'.");
        }
    }
    else if (auto castExpr = std::dynamic_pointer_cast<CastExpression>(expr)) {
        llvm::Value* operandVal = generateExpression(castExpr->operand);
        llvm::Type* targetType = getLLVMType(castExpr->castType);
        llvm::Type* operandType = operandVal->getType();
        if (operandType == targetType)
            return operandVal;
        if (operandType->isFloatingPointTy() && targetType->isIntegerTy())
            return builder.CreateFPToSI(operandVal, targetType, "casttmp");
        else if (operandType->isIntegerTy() && targetType->isFloatingPointTy())
            return builder.CreateSIToFP(operandVal, targetType, "casttmp");
        else if (operandType->isIntegerTy() && targetType->isIntegerTy())
            return builder.CreateIntCast(operandVal, targetType, false, "casttmp");
        else if (operandType->isFloatingPointTy() && targetType->isFloatingPointTy())
            return builder.CreateFPCast(operandVal, targetType, "casttmp");
        else
            throw runtime_error("CodeGenerator Error: Unsupported cast conversion.");
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
            llvm::Value* varPtr = it->second;
            if (auto allocaInst = dyn_cast<AllocaInst>(varPtr)) {
                llvm::Type* allocatedType = allocaInst->getAllocatedType();
                return builder.CreateLoad(allocatedType, varPtr, id->name.c_str());
            } else {
                throw runtime_error("CodeGenerator Error: '" + id->name + "' is not an alloca instruction.");
            }
        }
        GlobalVariable* gVar = module->getGlobalVariable(id->name);
        if (gVar)
            return builder.CreateLoad(gVar->getValueType(), gVar, id->name.c_str());
        throw runtime_error("CodeGenerator Error: Undefined variable '" + id->name + "'.");
    }
    else if (auto memberAccess = std::dynamic_pointer_cast<MemberAccess>(expr)) {
        llvm::Value* ptr = generateLValue(expr);
        // If this pointer is the union member pointer (bitcast to i32*), then use int32 as element type.
        if (ptr->getType() == PointerType::getUnqual(Type::getInt32Ty(context))) {
            return builder.CreateLoad(Type::getInt32Ty(context), ptr, "memberload");
        }
        llvm::Type* elemType = nullptr;
        if (ptr->getType()->isPointerTy()) {
            auto ptrType = cast<PointerType>(ptr->getType());
            elemType = ptrType->getContainedType(0);
        } else {
            throw runtime_error("CodeGenerator Error: Unable to determine element type for member load.");
        }
        return builder.CreateLoad(elemType, ptr, "memberload");
    }
    else if (auto post = std::dynamic_pointer_cast<PostfixExpression>(expr)) {
        auto id = std::dynamic_pointer_cast<Identifier>(post->operand);
        if (!id)
            throw runtime_error("CodeGenerator Error: Postfix operator applied to non-identifier.");
        auto it = localVariables.find(id->name);
        if (it == localVariables.end())
            throw runtime_error("CodeGenerator Error: Undefined variable '" + id->name + "' in postfix expression.");
        llvm::Value* varPtr = it->second;
        AllocaInst* allocaInst = dyn_cast<AllocaInst>(varPtr);
        if (!allocaInst)
            throw runtime_error("CodeGenerator Error: Postfix operator applied to non-alloca variable.");
        llvm::Value* oldVal = builder.CreateLoad(allocaInst->getAllocatedType(), varPtr, id->name.c_str());
        llvm::Value* one = nullptr;
        if (oldVal->getType()->isIntegerTy())
            one = ConstantInt::get(oldVal->getType(), 1);
        else if (oldVal->getType()->isFloatingPointTy())
            one = ConstantFP::get(oldVal->getType(), 1.0);
        else
            throw runtime_error("CodeGenerator Error: Unsupported type for postfix operator.");
        llvm::Value* newVal = nullptr;
        if (post->op == "++") {
            if (oldVal->getType()->isFloatingPointTy())
                newVal = builder.CreateFAdd(oldVal, one, "postinc");
            else
                newVal = builder.CreateAdd(oldVal, one, "postinc");
        } else if (post->op == "--") {
            if (oldVal->getType()->isFloatingPointTy())
                newVal = builder.CreateFSub(oldVal, one, "postdec");
            else
                newVal = builder.CreateSub(oldVal, one, "postdec");
        } else
            throw runtime_error("CodeGenerator Error: Unknown postfix operator '" + post->op + "'.");
        builder.CreateStore(newVal, varPtr);
        return oldVal;
    }
    else if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
        llvm::Value* ptr = generateLValue(assign->lhs);
        llvm::Value* rhsVal = generateExpression(assign->rhs);
        builder.CreateStore(rhsVal, ptr);
        return rhsVal;
    }
    else if (auto funcCall = std::dynamic_pointer_cast<FunctionCall>(expr)) {
        llvm::Function* callee = module->getFunction(funcCall->functionName);
        if (!callee)
            throw runtime_error("CodeGenerator Error: Undefined function '" + funcCall->functionName + "' in IR.");
        vector<llvm::Value*> args;
        for (auto& argExpr : funcCall->arguments)
            args.push_back(generateExpression(argExpr));
        return builder.CreateCall(callee, args, "calltmp");
    }
    throw runtime_error("CodeGenerator Error: Unsupported expression type in generateExpression().");
}

void CodeGenerator::generateVariableDeclarationStatement(const shared_ptr<VariableDeclarationStatement>& varDeclStmt) {
    llvm::Type* varTy = getLLVMType(varDeclStmt->type);
    AllocaInst* alloc = builder.CreateAlloca(varTy, nullptr, varDeclStmt->name.c_str());
    if (varDeclStmt->type.rfind("union ", 0) == 0)
        alloc->setAlignment(Align(4));
    localVariables[varDeclStmt->name] = alloc;

    if (varDeclStmt->initializer) {
        llvm::Value* initVal = generateExpression(varDeclStmt->initializer.value());
        if (initVal->getType() != varTy) {
            if (initVal->getType()->isFloatingPointTy() && varTy->isFloatingPointTy()) {
                // If converting from a larger FP type to a smaller FP type, truncate.
                if (initVal->getType()->getFPMantissaWidth() > varTy->getFPMantissaWidth())
                    initVal = builder.CreateFPTrunc(initVal, varTy, "fptrunc");
                else
                    initVal = builder.CreateFPExt(initVal, varTy, "fpext");
            } else {
                throw runtime_error("CodeGenerator Error: Incompatible initializer type in local variable declaration.");
            }
        }
        builder.CreateStore(initVal, alloc);
    }
}
