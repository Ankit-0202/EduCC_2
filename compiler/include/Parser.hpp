#ifndef PARSER_HPP
#define PARSER_HPP

#include "AST.hpp"
#include "Lexer.hpp"
#include "Token.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// The Parser class converts a token stream into an AST.
class Parser {
public:
  // Constructor: takes a vector of tokens.
  Parser(const std::vector<Token> &tokens) : tokens(tokens), current(0) {}

  // Parse the tokens and return the AST representing the program.
  std::shared_ptr<Program> parse();

  // Utility functions:
  // If the next token matches the given type, consume it and return true.
  bool match(TokenType type);

  // Check if the next token is of the given type.
  bool check(TokenType type) const;

  // Consume and return the next token.
  Token advance();

  // Return the next token without consuming it.
  Token peek() const;

  // Return true if we have consumed all tokens.
  bool isAtEnd() const;

  // NEW: Return the last token that was consumed.
  Token previous() const { return tokens[current - 1]; }

  // Consume the next token if it matches the given type; otherwise, throw an
  // error.
  void consume(TokenType type, const std::string &errorMessage);

  // Report an error with a given message.
  void error(const std::string &message) const;

  // Expression parsing functions:
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
  ExpressionPtr parseInitializerList();

  // Statement parsing methods.
  StatementPtr parseStatement();
  std::shared_ptr<CompoundStatement> parseCompoundStatement();
  StatementPtr parseIfStatement();
  StatementPtr parseWhileStatement();
  StatementPtr parseForStatement();
  StatementPtr parseSwitchStatement();
  StatementPtr parseReturnStatement();
  StatementPtr parseExpressionStatement();
  StatementPtr parseVariableDeclarationStatement();

  // Declaration parsing methods.
  DeclarationPtr parseDeclaration();
  DeclarationPtr parseStructDeclaration();
  DeclarationPtr parseVariableDeclaration();
  DeclarationPtr parseVariableDeclarationWithType(const std::string &givenType);
  DeclarationPtr parseFunctionDeclaration();
  DeclarationPtr parseFunctionDeclarationWithType(const std::string &givenType);
  std::vector<std::pair<std::string, std::string>> parseParameters();
  DeclarationPtr parseEnumDeclaration();
  DeclarationPtr parseUnionDeclaration();
  std::shared_ptr<VariableDeclaration> parseUnionMemberDeclaration();
  std::vector<Token> tokens;

  size_t current;
};

#endif // PARSER_HPP
