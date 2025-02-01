#ifndef SEMANTIC_ANALYZER_HPP
#define SEMANTIC_ANALYZER_HPP

#include "AST.hpp"
#include "SymbolTable.hpp"
#include <memory>
#include <stdexcept>
#include <vector>

class SemanticAnalyzer {
public:
    SemanticAnalyzer();
    void analyze(const std::shared_ptr<Program>& program);

private:
    SymbolTable symbolTable;

    void analyzeDeclaration(const DeclarationPtr& decl);
    void analyzeVariableDeclaration(const std::shared_ptr<VariableDeclaration>& varDecl);
    void analyzeFunctionDeclaration(const std::shared_ptr<FunctionDeclaration>& funcDecl);
    std::vector<std::string> getParameterTypes(const std::vector<std::pair<std::string, std::string>>& parameters);
    void analyzeStatement(const StatementPtr& stmt);
    void analyzeExpression(const ExpressionPtr& expr);
};

#endif // SEMANTIC_ANALYZER_HPP
