#ifndef PARSER_HPP
#define PARSER_HPP

#include "AST.hpp"
#include "Token.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

class Parser {
public:
  // Constructor: takes the token stream.
  Parser(const std::vector<Token> &tokens);

  // Main entry point to start parsing.
  std::shared_ptr<Program> parse();

  // Expression parsing methods.
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
  StatementPtr parseBreakStatement();
  StatementPtr parseContinueStatement();
  StatementPtr parseGotoStatement();
  StatementPtr parseDoWhileStatement();
  StatementPtr parseExpressionStatement();
  StatementPtr parseVariableDeclarationStatement();

  // Declaration parsing methods.
  DeclarationPtr parseDeclaration();
  DeclarationPtr parseStructDeclaration();
  DeclarationPtr parseVariableDeclaration();
  DeclarationPtr parseVariableDeclarationWithType(
      const std::string &givenType,
      const std::vector<ExpressionPtr> &typeDimensions = {},
      std::shared_ptr<StructDeclaration> inlineStructDecl = nullptr,
      std::shared_ptr<UnionDeclaration> inlineUnionDecl = nullptr);
  DeclarationPtr parseFunctionDeclaration();
  DeclarationPtr parseFunctionDeclarationWithType(const std::string &givenType);
  std::vector<std::pair<std::string, std::string>> parseParameters();
  DeclarationPtr parseEnumDeclaration();
  DeclarationPtr parseUnionDeclaration();
  std::shared_ptr<VariableDeclaration> parseUnionMemberDeclaration();
  DeclarationPtr parseTypedefDeclaration();
  std::vector<Token> tokens;

  size_t current;
  std::string currentFunctionName;
  std::optional<int> pendingAlignment;
  bool structPackedFlag;
  bool varArgsPending;

  // Utility parsing methods.
  Token advance();
  bool match(TokenType type);
  bool check(TokenType type) const;
  Token peek() const;
  bool isAtEnd() const;
  void consume(TokenType type, const std::string &errorMessage);
  void error(const std::string &message) const;
};

struct ParsedDeclarator {
  std::string type;
  std::string name;
  std::vector<ExpressionPtr> dimensions;
  bool isFunctionPointer{false};
  std::vector<std::string> functionParamTypes;
  bool hasEmptyArrayDimension{false};
};

std::string
parseSimpleType(Parser &parser, bool &hasConstQualifier,
                bool &hasStaticQualifier, bool &hasVolatileQualifier,
                std::shared_ptr<StructDeclaration> *inlineStructDecl = nullptr,
                std::shared_ptr<UnionDeclaration> *inlineUnionDecl = nullptr);
ParsedDeclarator parseDeclarator(Parser &parser, const std::string &baseType,
                                 bool requireName);

#endif // PARSER_HPP
