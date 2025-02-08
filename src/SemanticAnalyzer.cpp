#include "SemanticAnalyzer.hpp"
#include "AST.hpp"
#include "SymbolTable.hpp"
#include <stdexcept>
#include <iostream>

SemanticAnalyzer::SemanticAnalyzer() {
    symbolTable.enterScope();
}

void SemanticAnalyzer::analyze(const std::shared_ptr<Program>& program) {
    for (const auto& decl : program->declarations) {
        analyzeDeclaration(decl);
    }
}

void SemanticAnalyzer::analyzeDeclaration(const DeclarationPtr& decl) {
    if (auto varDecl = std::dynamic_pointer_cast<VariableDeclaration>(decl)) {
        analyzeVariableDeclaration(varDecl);
    } else if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclaration>(decl)) {
        analyzeFunctionDeclaration(funcDecl);
    } else if (auto multiVarDecl = std::dynamic_pointer_cast<MultiVariableDeclaration>(decl)) {
        for (const auto& singleDecl : multiVarDecl->declarations) {
            analyzeVariableDeclaration(singleDecl);
        }
    } else {
        throw std::runtime_error("SemanticAnalyzer Error: Unknown declaration type.");
    }
}

void SemanticAnalyzer::analyzeVariableDeclaration(const std::shared_ptr<VariableDeclaration>& varDecl) {
    // A variable is simpler: just ensure no conflicting declaration in the current scope.
    Symbol symbol(varDecl->name, varDecl->type);
    if (!symbolTable.declare(symbol)) {
        throw std::runtime_error("SemanticAnalyzer Error: Variable '" + varDecl->name + "' already declared in this scope.");
    }
    // If there is an initializer, analyze it.
    if (varDecl->initializer) {
        analyzeExpression(varDecl->initializer.value());
    }
}

void SemanticAnalyzer::analyzeFunctionDeclaration(const std::shared_ptr<FunctionDeclaration>& funcDecl) {
    const std::string& fnName = funcDecl->name;
    const std::string& retType = funcDecl->returnType;
    bool hasBody = (funcDecl->body != nullptr);
    std::vector<std::string> paramTypes = getParameterTypes(funcDecl->parameters);

    // See if it's already declared.
    auto existingOpt = symbolTable.lookup(fnName);
    if (!existingOpt.has_value()) {
        Symbol newFunc(fnName, retType, true, paramTypes, hasBody);
        if (!symbolTable.declare(newFunc)) {
            throw std::runtime_error("SemanticAnalyzer Error: Could not declare function '" + fnName + "'.");
        }
    } else {
        Symbol existingSym = existingOpt.value();
        if (!existingSym.isFunction) {
            throw std::runtime_error("SemanticAnalyzer Error: '" + fnName + "' already declared as a variable.");
        }
        // Check signature match.
        if (!isFunctionSignatureCompatible(existingSym, retType, paramTypes)) {
            throw std::runtime_error("SemanticAnalyzer Error: Conflicting declaration for function '" + fnName +
                                     "'. Parameter list or return type does not match previous declaration.");
        }
        if (existingSym.isDefined && hasBody) {
            throw std::runtime_error("SemanticAnalyzer Error: Function '" + fnName + "' is already defined.");
        } else if (!existingSym.isDefined && hasBody) {
            symbolTable.exitScope();
            symbolTable.enterScope();
            Symbol newSym(fnName, retType, true, paramTypes, true);
            if (!symbolTable.declare(newSym)) {
                throw std::runtime_error("SemanticAnalyzer Error: Could not update definition of function '" + fnName + "'.");
            }
        }
    }

    // If there is a body, analyze it in a new scope (for parameters).
    if (hasBody) {
        symbolTable.enterScope();
        for (const auto& param : funcDecl->parameters) {
            Symbol paramSymbol(param.second, param.first);
            if (!symbolTable.declare(paramSymbol)) {
                throw std::runtime_error("SemanticAnalyzer Error: Parameter '" + param.second + "' already declared.");
            }
        }
        if (auto compound = std::dynamic_pointer_cast<CompoundStatement>(funcDecl->body)) {
            for (const auto& stmt : compound->statements) {
                analyzeStatement(stmt);
            }
        }
        symbolTable.exitScope();
    }
}

std::vector<std::string> SemanticAnalyzer::getParameterTypes(const std::vector<std::pair<std::string, std::string>>& parameters) {
    std::vector<std::string> types;
    for (const auto& param : parameters) {
        types.push_back(param.first);
    }
    return types;
}

bool SemanticAnalyzer::isFunctionSignatureCompatible(const Symbol& existing,
                                                     const std::string& returnType,
                                                     const std::vector<std::string>& paramTypes) const {
    if (existing.type != returnType) {
        return false;
    }
    if (existing.parameterTypes.size() != paramTypes.size()) {
        return false;
    }
    for (size_t i = 0; i < paramTypes.size(); ++i) {
        if (existing.parameterTypes[i] != paramTypes[i]) {
            return false;
        }
    }
    return true;
}

//------------------------------------------//
//         Statement / Expression           //
//------------------------------------------//

void SemanticAnalyzer::analyzeStatement(const StatementPtr& stmt) {
    if (auto compound = std::dynamic_pointer_cast<CompoundStatement>(stmt)) {
        symbolTable.enterScope();
        for (const auto& s : compound->statements) {
            analyzeStatement(s);
        }
        symbolTable.exitScope();
    } else if (auto exprStmt = std::dynamic_pointer_cast<ExpressionStatement>(stmt)) {
        analyzeExpression(exprStmt->expression);
    } else if (auto retStmt = std::dynamic_pointer_cast<ReturnStatement>(stmt)) {
        analyzeExpression(retStmt->expression);
    } else if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(stmt)) {
        analyzeExpression(ifStmt->condition);
        analyzeStatement(ifStmt->thenBranch);
        if (ifStmt->elseBranch)
            analyzeStatement(ifStmt->elseBranch.value());
    } else if (auto whileStmt = std::dynamic_pointer_cast<WhileStatement>(stmt)) {
        analyzeExpression(whileStmt->condition);
        analyzeStatement(whileStmt->body);
    } else if (auto forStmt = std::dynamic_pointer_cast<ForStatement>(stmt)) {
        if (forStmt->initializer)
            analyzeStatement(forStmt->initializer);
        if (forStmt->condition)
            analyzeExpression(forStmt->condition);
        if (forStmt->increment)
            analyzeExpression(forStmt->increment);
        analyzeStatement(forStmt->body);
    } else if (auto switchStmt = std::dynamic_pointer_cast<SwitchStatement>(stmt)) {
        analyzeExpression(switchStmt->condition);
        for (const auto &caseClause : switchStmt->cases) {
            if (caseClause.first.has_value()) {
                analyzeExpression(caseClause.first.value());
            }
            analyzeStatement(caseClause.second);
        }
        if (switchStmt->defaultCase.has_value()) {
            analyzeStatement(switchStmt->defaultCase.value());
        }
    } else if (auto varDeclStmt = std::dynamic_pointer_cast<VariableDeclarationStatement>(stmt)) {
        auto tempVarDecl = std::make_shared<VariableDeclaration>(varDeclStmt->type,
                                                                 varDeclStmt->name,
                                                                 varDeclStmt->initializer);
        analyzeVariableDeclaration(tempVarDecl);
    } else if (auto multiVarDeclStmt = std::dynamic_pointer_cast<MultiVariableDeclarationStatement>(stmt)) {
        for (const auto& singleDeclStmt : multiVarDeclStmt->declarations) {
            auto tempVarDecl = std::make_shared<VariableDeclaration>(singleDeclStmt->type,
                                                                     singleDeclStmt->name,
                                                                     singleDeclStmt->initializer);
            analyzeVariableDeclaration(tempVarDecl);
        }
    } else {
        throw std::runtime_error("SemanticAnalyzer Error: Unsupported statement type.");
    }
}

void SemanticAnalyzer::analyzeExpression(const ExpressionPtr& expr) {
    if (!expr) return;
    if (auto binExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
        analyzeExpression(binExpr->left);
        analyzeExpression(binExpr->right);
    } else if (auto unExpr = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
        analyzeExpression(unExpr->operand);
    } else if (auto postExpr = std::dynamic_pointer_cast<PostfixExpression>(expr)) {
        analyzeExpression(postExpr->operand);
    } else if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
        // No analysis needed.
    } else if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
        if (!symbolTable.lookup(id->name).has_value()) {
            throw std::runtime_error("SemanticAnalyzer Error: Undefined variable or function '" + id->name + "'.");
        }
    } else if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
        if (!symbolTable.lookup(assign->lhs).has_value()) {
            throw std::runtime_error("SemanticAnalyzer Error: Undefined variable '" + assign->lhs + "'.");
        }
        analyzeExpression(assign->rhs);
    } else if (auto funcCall = std::dynamic_pointer_cast<FunctionCall>(expr)) {
        auto sym = symbolTable.lookup(funcCall->functionName);
        if (!sym.has_value() || !sym->isFunction) {
            throw std::runtime_error("SemanticAnalyzer Error: Undefined function '" + funcCall->functionName + "'.");
        }
        if (sym->parameterTypes.size() != funcCall->arguments.size()) {
            throw std::runtime_error("SemanticAnalyzer Error: Function '" + funcCall->functionName +
                                     "' called with incorrect number of arguments.");
        }
        for (const auto& arg : funcCall->arguments) {
            analyzeExpression(arg);
        }
    } else {
        throw std::runtime_error("SemanticAnalyzer Error: Unsupported expression type.");
    }
}
