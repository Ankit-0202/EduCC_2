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

    // Overhauled function analysis
    void analyzeFunctionDeclaration(const std::shared_ptr<FunctionDeclaration>& funcDecl);

    // Utility: returns the list of parameter types as strings
    std::vector<std::string> getParameterTypes(const std::vector<std::pair<std::string, std::string>>& parameters);

    // Statements/Expressions
    void analyzeStatement(const StatementPtr& stmt);
    void analyzeExpression(const ExpressionPtr& expr);

    // NEW: Check function signature compatibility
    bool isFunctionSignatureCompatible(const Symbol& existing, 
                                       const std::string& returnType,
                                       const std::vector<std::string>& paramTypes) const;
};

#endif // SEMANTIC_ANALYZER_HPP
