#ifndef PARSER_HPP
#define PARSER_HPP

#include "AST.hpp"
#include "Lexer.hpp"
#include <memory>
#include <string>
#include <vector>

class Parser {
public:
  Parser(const std::vector<Token> &tokens);

  // Returns the root AST node (the Program)
  std::shared_ptr<Program> parse();

private:
  std::vector<Token> tokens;
  size_t current;

  // Basic helper functions
  bool isAtEnd() const;
  Token peek() const;
  Token advance();
  bool match(TokenType type);
  bool check(TokenType type) const;
  void consume(TokenType type, const std::string &errorMessage);
  void error(const std::string &message) const;

  // Declaration parsing
  DeclarationPtr parseDeclaration();
  DeclarationPtr parseVariableDeclaration();
  DeclarationPtr parseFunctionDeclaration();
  DeclarationPtr parseEnumDeclaration();
  DeclarationPtr parseUnionDeclaration(); // NEW: union declaration
  std::shared_ptr<VariableDeclaration>
  parseUnionMemberDeclaration(); // NEW: union member parsing

  std::vector<std::pair<std::string, std::string>> parseParameters();

  // Statement parsing
  std::shared_ptr<CompoundStatement> parseCompoundStatement();
  StatementPtr parseStatement();
  StatementPtr parseIfStatement();
  StatementPtr parseWhileStatement();
  StatementPtr parseForStatement();
  StatementPtr parseSwitchStatement();
  StatementPtr parseReturnStatement();
  // (Break support removed)
  StatementPtr parseExpressionStatement();
  StatementPtr parseVariableDeclarationStatement();

  // Expression parsing
  ExpressionPtr parseExpression();
  ExpressionPtr parseAssignment();
  ExpressionPtr parseLogicalOr();
  ExpressionPtr parseLogicalAnd();
  ExpressionPtr parseBitwiseOr();
  ExpressionPtr parseBitwiseXor();
  ExpressionPtr parseBitwiseAnd();
  ExpressionPtr parseEquality();
  ExpressionPtr parseRelational();
  ExpressionPtr parseShift();
  ExpressionPtr parseTerm();
  ExpressionPtr parseFactor();
  ExpressionPtr parseUnary();
  ExpressionPtr parsePostfix();
  ExpressionPtr parsePrimary();
};

#endif // PARSER_HPP
