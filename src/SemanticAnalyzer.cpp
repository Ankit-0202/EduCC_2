#include "SemanticAnalyzer.hpp"
#include <stdexcept>

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
    } else {
        throw std::runtime_error("SemanticAnalyzer Error: Unknown declaration type.");
    }
}

void SemanticAnalyzer::analyzeVariableDeclaration(const std::shared_ptr<VariableDeclaration>& varDecl) {
    Symbol symbol(varDecl->name, varDecl->type);
    if (!symbolTable.declare(symbol)) {
        throw std::runtime_error("SemanticAnalyzer Error: Variable '" + varDecl->name + "' already declared in this scope.");
    }
    if (varDecl->initializer) {
        // Simplified type checking.
    }
}

void SemanticAnalyzer::analyzeFunctionDeclaration(const std::shared_ptr<FunctionDeclaration>& funcDecl) {
    Symbol symbol(funcDecl->name, funcDecl->returnType, true, getParameterTypes(funcDecl->parameters));
    if (!symbolTable.declare(symbol)) {
        throw std::runtime_error("SemanticAnalyzer Error: Function '" + funcDecl->name + "' already declared.");
    }
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

std::vector<std::string> SemanticAnalyzer::getParameterTypes(const std::vector<std::pair<std::string, std::string>>& parameters) {
    std::vector<std::string> types;
    for (const auto& param : parameters) {
        types.push_back(param.first);
    }
    return types;
}

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
    } else if (auto varDeclStmt = std::dynamic_pointer_cast<VariableDeclarationStatement>(stmt)) {
        auto tempVarDecl = std::make_shared<VariableDeclaration>(varDeclStmt->type, varDeclStmt->name, varDeclStmt->initializer);
        analyzeVariableDeclaration(tempVarDecl);
    } else {
        throw std::runtime_error("SemanticAnalyzer Error: Unsupported statement type.");
    }
}

void SemanticAnalyzer::analyzeExpression(const ExpressionPtr& expr) {
    if (auto binExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
        analyzeExpression(binExpr->left);
        analyzeExpression(binExpr->right);
    } else if (auto unExpr = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
        analyzeExpression(unExpr->operand);
    } else if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
        // Literals are fine.
    } else if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
        if (!symbolTable.lookup(id->name).has_value()) {
            throw std::runtime_error("SemanticAnalyzer Error: Undefined variable '" + id->name + "'.");
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
            throw std::runtime_error("SemanticAnalyzer Error: Function '" + funcCall->functionName + "' called with incorrect number of arguments.");
        }
        for (const auto& arg : funcCall->arguments) {
            analyzeExpression(arg);
        }
    } else {
        throw std::runtime_error("SemanticAnalyzer Error: Unsupported expression type.");
    }
}
