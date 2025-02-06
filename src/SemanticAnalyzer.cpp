#include "SemanticAnalyzer.hpp"
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
    } 
    else if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclaration>(decl)) {
        analyzeFunctionDeclaration(funcDecl);
    } 
    else {
        throw std::runtime_error("SemanticAnalyzer Error: Unknown declaration type.");
    }
}

void SemanticAnalyzer::analyzeVariableDeclaration(const std::shared_ptr<VariableDeclaration>& varDecl) {
    // A variable is simpler: just ensure no conflicting declaration in the current scope
    Symbol symbol(varDecl->name, varDecl->type);
    if (!symbolTable.declare(symbol)) {
        throw std::runtime_error("SemanticAnalyzer Error: Variable '" + varDecl->name + "' already declared in this scope.");
    }
    // Optionally: check initializer type compatibility, etc.
}

void SemanticAnalyzer::analyzeFunctionDeclaration(const std::shared_ptr<FunctionDeclaration>& funcDecl) {
    // Gather info
    const std::string& fnName = funcDecl->name;
    const std::string& retType = funcDecl->returnType;
    bool hasBody = (funcDecl->body != nullptr);
    std::vector<std::string> paramTypes = getParameterTypes(funcDecl->parameters);

    // See if it's already declared
    auto existingOpt = symbolTable.lookup(fnName);
    if (!existingOpt.has_value()) {
        // Not declared at all, so insert a new symbol
        Symbol newFunc(fnName, retType, /*isFunction=*/true, paramTypes, /*isDefined=*/hasBody);
        if (!symbolTable.declare(newFunc)) {
            // theoretically can't happen if not in any scope, but just in case:
            throw std::runtime_error("SemanticAnalyzer Error: Could not declare function '" + fnName + "'.");
        }
    }
    else {
        // Already declared or defined in some scope
        Symbol existingSym = existingOpt.value();

        if (!existingSym.isFunction) {
            // There's a variable with the same name, conflict
            throw std::runtime_error("SemanticAnalyzer Error: '" + fnName + "' already declared as a variable.");
        }
        // It's a function, check signature match
        if (!isFunctionSignatureCompatible(existingSym, retType, paramTypes)) {
            throw std::runtime_error("SemanticAnalyzer Error: Conflicting declaration for function '" + fnName + 
                                     "'. Parameter list or return type does not match previous declaration.");
        }

        // If the existing symbol is already defined:
        if (existingSym.isDefined) {
            // We are seeing another definition:
            if (hasBody) {
                // It's a redefinition error
                throw std::runtime_error("SemanticAnalyzer Error: Function '" + fnName + "' is already defined.");
            }
            else {
                // It's a repeated prototype, which is okay in C if identical,
                // so do nothing
            }
        }
        else {
            // The existing symbol is not defined yet
            if (hasBody) {
                // This new declaration provides a definition => upgrade
                // But we must re-declare or update. Because we are in *some* scope, 
                // we do want to re-declare in the current scope or update the existing.
                // Easiest approach: 
                symbolTable.exitScope();  // exit the top scope
                symbolTable.enterScope(); // re-enter a fresh top scope
                Symbol newSym(fnName, retType, true, paramTypes, true);
                // We forcibly declare the "updated" symbol
                if (!symbolTable.declare(newSym)) {
                    // This can happen if the current scope already had it? 
                    throw std::runtime_error("SemanticAnalyzer Error: Could not update definition of function '" + fnName + "'.");
                }
            }
            else {
                // It's just another prototype, do nothing
            }
        }
    }

    // If there's an actual body, we analyze its statements in a new scope for parameters
    if (hasBody) {
        // Enter function scope
        symbolTable.enterScope();
        // Declare parameters
        for (const auto& param : funcDecl->parameters) {
            Symbol paramSymbol(param.second, param.first);
            if (!symbolTable.declare(paramSymbol)) {
                throw std::runtime_error("SemanticAnalyzer Error: Parameter '" + param.second + "' already declared.");
            }
        }
        // Analyze the body statements
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
                                                     const std::vector<std::string>& paramTypes) const
{
    // Compare return type
    if (existing.type != returnType) {
        return false;
    }
    // Compare param count
    if (existing.parameterTypes.size() != paramTypes.size()) {
        return false;
    }
    // Compare each param
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
    } 
    else if (auto exprStmt = std::dynamic_pointer_cast<ExpressionStatement>(stmt)) {
        analyzeExpression(exprStmt->expression);
    } 
    else if (auto retStmt = std::dynamic_pointer_cast<ReturnStatement>(stmt)) {
        analyzeExpression(retStmt->expression);
    } 
    else if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(stmt)) {
        analyzeExpression(ifStmt->condition);
        analyzeStatement(ifStmt->thenBranch);
        if (ifStmt->elseBranch)
            analyzeStatement(ifStmt->elseBranch.value());
    } 
    else if (auto whileStmt = std::dynamic_pointer_cast<WhileStatement>(stmt)) {
        analyzeExpression(whileStmt->condition);
        analyzeStatement(whileStmt->body);
    } 
    else if (auto forStmt = std::dynamic_pointer_cast<ForStatement>(stmt)) {
        if (forStmt->initializer)
            analyzeStatement(forStmt->initializer);
        if (forStmt->condition)
            analyzeExpression(forStmt->condition);
        if (forStmt->increment)
            analyzeExpression(forStmt->increment);
        analyzeStatement(forStmt->body);
    } 
    else if (auto varDeclStmt = std::dynamic_pointer_cast<VariableDeclarationStatement>(stmt)) {
        auto tempVarDecl = std::make_shared<VariableDeclaration>(varDeclStmt->type,
                                                                 varDeclStmt->name,
                                                                 varDeclStmt->initializer);
        analyzeVariableDeclaration(tempVarDecl);
    } 
    else {
        throw std::runtime_error("SemanticAnalyzer Error: Unsupported statement type.");
    }
}

void SemanticAnalyzer::analyzeExpression(const ExpressionPtr& expr) {
    if (!expr) return; // safety check

    if (auto binExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
        analyzeExpression(binExpr->left);
        analyzeExpression(binExpr->right);
    } 
    else if (auto unExpr = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
        analyzeExpression(unExpr->operand);
    } 
    else if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
        // no checks needed for raw literal
    } 
    else if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
        if (!symbolTable.lookup(id->name).has_value()) {
            throw std::runtime_error("SemanticAnalyzer Error: Undefined variable or function '" + id->name + "'.");
        }
    } 
    else if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
        if (!symbolTable.lookup(assign->lhs).has_value()) {
            throw std::runtime_error("SemanticAnalyzer Error: Undefined variable '" + assign->lhs + "'.");
        }
        analyzeExpression(assign->rhs);
    } 
    else if (auto funcCall = std::dynamic_pointer_cast<FunctionCall>(expr)) {
        auto sym = symbolTable.lookup(funcCall->functionName);
        if (!sym.has_value() || !sym->isFunction) {
            throw std::runtime_error("SemanticAnalyzer Error: Undefined function '" + funcCall->functionName + "'.");
        }
        // Check arg count
        if (sym->parameterTypes.size() != funcCall->arguments.size()) {
            throw std::runtime_error("SemanticAnalyzer Error: Function '" + funcCall->functionName +
                                     "' called with incorrect number of arguments.");
        }
        // Arg type-check is omitted in this example, but you could do it if desired.
        for (const auto& arg : funcCall->arguments) {
            analyzeExpression(arg);
        }
    } 
    else {
        throw std::runtime_error("SemanticAnalyzer Error: Unsupported expression type.");
    }
}
