#ifndef SEMANTIC_ANALYZER_HPP
#define SEMANTIC_ANALYZER_HPP

#include <memory>
#include <vector>
#include <string>
#include "AST.hpp"
#include "SymbolTable.hpp"

class SemanticAnalyzer {
public:
    SemanticAnalyzer();
    void analyze(const std::shared_ptr<Program>& program);

private:
    SymbolTable symbolTable;

    void analyzeDeclaration(const DeclarationPtr& decl);
    void analyzeVariableDeclaration(const std::shared_ptr<VariableDeclaration>& varDecl);
    void analyzeFunctionDeclaration(const std::shared_ptr<FunctionDeclaration>& funcDecl);
    void analyzeEnumDeclaration(const std::shared_ptr<EnumDeclaration>& enumDecl);
    void analyzeUnionDeclaration(const std::shared_ptr<UnionDeclaration>& unionDecl);
    void analyzeStructDeclaration(const std::shared_ptr<StructDeclaration>& structDecl); // NEW

    std::vector<std::string> getParameterTypes(const std::vector<std::pair<std::string, std::string>>& parameters);
    bool isFunctionSignatureCompatible(const Symbol& existing,
                                       const std::string& returnType,
                                       const std::vector<std::string>& paramTypes) const;

    void analyzeStatement(const StatementPtr& stmt);
    void analyzeExpression(const ExpressionPtr& expr);
};

#endif // SEMANTIC_ANALYZER_HPP
