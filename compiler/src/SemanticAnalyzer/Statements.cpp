#include "SemanticAnalyzer.hpp"
#include "AST.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <stdexcept>

using std::runtime_error;

void SemanticAnalyzer::analyzeStatement(const StatementPtr &stmt) {
  if (auto compound = std::dynamic_pointer_cast<CompoundStatement>(stmt)) {
    symbolTable.enterScope();
    for (const auto &s : compound->statements) {
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
    analyzeExpression(switchStmt->expression);
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
    auto tempVarDecl = std::make_shared<VariableDeclaration>(varDeclStmt->type, varDeclStmt->name, varDeclStmt->initializer);
    analyzeVariableDeclaration(tempVarDecl);
  } else if (auto multiVarDeclStmt = std::dynamic_pointer_cast<MultiVariableDeclarationStatement>(stmt)) {
    for (const auto &singleDeclStmt : multiVarDeclStmt->declarations) {
      auto tempVarDecl = std::make_shared<VariableDeclaration>(singleDeclStmt->type, singleDeclStmt->name, singleDeclStmt->initializer);
      analyzeVariableDeclaration(tempVarDecl);
    }
  } else {
    throw runtime_error("Semantic Analysis Error: Unsupported statement type encountered.");
  }
}
