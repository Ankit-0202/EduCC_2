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
  void analyze(const std::shared_ptr<Program> &program);

private:
  SymbolTable symbolTable;

  void analyzeDeclaration(const DeclarationPtr &decl);
  void analyzeVariableDeclaration(
      const std::shared_ptr<VariableDeclaration> &varDecl);
  void analyzeFunctionDeclaration(
      const std::shared_ptr<FunctionDeclaration> &funcDecl);
  void analyzeEnumDeclaration(const std::shared_ptr<EnumDeclaration> &enumDecl);
  void analyzeUnionDeclaration(
      const std::shared_ptr<UnionDeclaration> &unionDecl); // NEW

  std::vector<std::string> getParameterTypes(
      const std::vector<std::pair<std::string, std::string>> &parameters);
  void analyzeStatement(const StatementPtr &stmt);
  void analyzeExpression(const ExpressionPtr &expr);
  bool isFunctionSignatureCompatible(
      const Symbol &existing, const std::string &returnType,
      const std::vector<std::string> &paramTypes) const;
};

#endif // SEMANTIC_ANALYZER_HPP
