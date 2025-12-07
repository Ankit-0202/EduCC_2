#include "AST.hpp"
#include "SemanticAnalyzer.hpp"
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
  } else if (auto exprStmt =
                 std::dynamic_pointer_cast<ExpressionStatement>(stmt)) {
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
    symbolTable.enterScope();
    if (forStmt->initializer)
      analyzeStatement(forStmt->initializer);
    if (forStmt->condition)
      analyzeExpression(forStmt->condition);
    if (forStmt->increment)
      analyzeExpression(forStmt->increment);
    analyzeStatement(forStmt->body);
    symbolTable.exitScope();
  } else if (auto switchStmt =
                 std::dynamic_pointer_cast<SwitchStatement>(stmt)) {
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
  } else if (auto varDeclStmt =
                 std::dynamic_pointer_cast<VariableDeclarationStatement>(
                     stmt)) {
    // Convert the local variable declaration statement into a
    // VariableDeclaration node.
    auto varDecl = std::make_shared<VariableDeclaration>(
        varDeclStmt->type, varDeclStmt->name, varDeclStmt->bitWidth,
        varDeclStmt->initializer, varDeclStmt->dimensions);
    analyzeVariableDeclaration(varDecl);
  } else if (auto multiVarDeclStmt =
                 std::dynamic_pointer_cast<MultiVariableDeclarationStatement>(
                     stmt)) {
    for (const auto &singleDecl : multiVarDeclStmt->declarations) {
      auto varDecl = std::make_shared<VariableDeclaration>(
          singleDecl->type, singleDecl->name, singleDecl->bitWidth,
          singleDecl->initializer, singleDecl->dimensions);
      analyzeVariableDeclaration(varDecl);
    }
  } else if (auto declStmt =
                 std::dynamic_pointer_cast<DeclarationStatement>(stmt)) {
    analyzeDeclaration(declStmt->declaration);
  } else if (auto breakStmt = std::dynamic_pointer_cast<BreakStatement>(stmt)) {
    // Break statements are valid in loops and switch statements
    // For now, we'll just accept them
  } else if (auto continueStmt =
                 std::dynamic_pointer_cast<ContinueStatement>(stmt)) {
    // Continue statements are valid in loops
    // For now, we'll just accept them
  } else if (auto gotoStmt = std::dynamic_pointer_cast<GotoStatement>(stmt)) {
    // Goto statements are valid
    // For now, we'll just accept them
  } else if (auto doWhileStmt =
                 std::dynamic_pointer_cast<DoWhileStatement>(stmt)) {
    analyzeStatement(doWhileStmt->body);
    analyzeExpression(doWhileStmt->condition);
  } else {
    throw runtime_error(
        "Semantic Analysis Error: Unsupported statement type encountered.");
  }
}
