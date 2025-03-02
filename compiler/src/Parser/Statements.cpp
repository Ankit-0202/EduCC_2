// compiler/src/Parser/Statements.cpp

#include "AST.hpp"
#include "Parser.hpp"
#include "TypeRegistry.hpp"
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

using std::optional;
using std::runtime_error;
using std::string;
using std::vector;

// NEW: Helper function to check if a token represents a type specifier.
// It returns true for built-in type keywords and for tokens that are
// identifiers (or literal strings) that match a typedef alias (stored in
// typedefRegistry).
static bool isTypeSpecifierToken(const Token &token) {
  if (token.type == TokenType::KW_INT || token.type == TokenType::KW_FLOAT ||
      token.type == TokenType::KW_CHAR || token.type == TokenType::KW_DOUBLE ||
      token.type == TokenType::KW_BOOL || token.type == TokenType::KW_ENUM ||
      token.type == TokenType::KW_UNION || token.type == TokenType::KW_STRUCT)
    return true;
  // Check for typedef alias stored as LITERAL_STRING.
  if (token.type == TokenType::LITERAL_STRING) {
    if (typedefRegistry.find(token.lexeme) != typedefRegistry.end())
      return true;
  }
  // Also check if the token is an IDENTIFIER that matches a typedef alias.
  if (token.type == TokenType::IDENTIFIER) {
    if (typedefRegistry.find(token.lexeme) != typedefRegistry.end())
      return true;
  }
  return false;
}

StatementPtr Parser::parseStatement() {
  // NEW: Check for typedef declarations in statement context.
  if (peek().lexeme == "typedef")
    return std::make_shared<DeclarationStatement>(parseTypedefDeclaration());

  if (check(TokenType::KW_TYPEDEF) ||
      (check(TokenType::LITERAL_STRING) && peek().lexeme == "typedef"))
    return std::make_shared<DeclarationStatement>(parseTypedefDeclaration());

  // First check for control-flow keywords.
  if (match(TokenType::KW_IF)) {
    return parseIfStatement();
  } else if (match(TokenType::KW_RETURN)) {
    return parseReturnStatement();
  } else if (match(TokenType::KW_WHILE)) {
    return parseWhileStatement();
  } else if (match(TokenType::KW_FOR)) {
    return parseForStatement();
  } else if (match(TokenType::KW_SWITCH)) {
    return parseSwitchStatement();
  } else if (match(TokenType::DELIM_LBRACE)) {
    // If a compound statement is encountered.
    return parseCompoundStatement();
  }

  // NEW: Instead of checking only for built-in type keywords, we use our
  // helper.
  if (isTypeSpecifierToken(peek())) {
    return parseVariableDeclarationStatement();
  }

  // Fall back to an expression statement.
  return parseExpressionStatement();
}

std::shared_ptr<CompoundStatement> Parser::parseCompoundStatement() {
  auto compound = std::make_shared<CompoundStatement>();
  while (!check(TokenType::DELIM_RBRACE) && !isAtEnd()) {
    StatementPtr stmt = parseStatement();
    compound->addStatement(stmt);
  }
  consume(TokenType::DELIM_RBRACE, "Expected '}' after compound statement");
  return compound;
}

StatementPtr Parser::parseIfStatement() {
  consume(TokenType::DELIM_LPAREN, "Expected '(' after 'if'");
  ExpressionPtr condition = parseExpression();
  consume(TokenType::DELIM_RPAREN, "Expected ')' after 'if' condition");
  StatementPtr thenBranch = parseStatement();
  optional<StatementPtr> elseBranch = std::nullopt;
  if (match(TokenType::KW_ELSE)) {
    elseBranch = parseStatement();
  }
  return std::make_shared<IfStatement>(condition, thenBranch, elseBranch);
}

StatementPtr Parser::parseWhileStatement() {
  consume(TokenType::DELIM_LPAREN, "Expected '(' after 'while'");
  ExpressionPtr condition = parseExpression();
  consume(TokenType::DELIM_RPAREN, "Expected ')' after 'while' condition");
  StatementPtr body = parseStatement();
  return std::make_shared<WhileStatement>(condition, body);
}

StatementPtr Parser::parseForStatement() {
  consume(TokenType::DELIM_LPAREN, "Expected '(' after 'for'");
  StatementPtr initializer = nullptr;
  if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
      check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
      check(TokenType::KW_BOOL) || check(TokenType::KW_ENUM) ||
      check(TokenType::KW_UNION) ||
      (check(TokenType::KW_STRUCT) ||
       (check(TokenType::IDENTIFIER) && peek().lexeme == "struct"))) {
    initializer = parseVariableDeclarationStatement();
  } else {
    initializer = parseExpressionStatement();
  }
  ExpressionPtr condition = nullptr;
  if (!check(TokenType::DELIM_SEMICOLON)) {
    condition = parseExpression();
  } else {
    // If condition is empty, default to true.
    condition = std::make_shared<Literal>(true);
  }
  consume(TokenType::DELIM_SEMICOLON, "Expected ';' after for-loop condition");
  ExpressionPtr increment = nullptr;
  if (!check(TokenType::DELIM_RPAREN)) {
    increment = parseExpression();
  }
  consume(TokenType::DELIM_RPAREN, "Expected ')' after for-loop increment");
  StatementPtr body = parseStatement();
  return std::make_shared<ForStatement>(initializer, condition, increment,
                                        body);
}

StatementPtr Parser::parseSwitchStatement() {
  consume(TokenType::DELIM_LPAREN, "Expected '(' after 'switch'");
  ExpressionPtr expr = parseExpression();
  consume(TokenType::DELIM_RPAREN, "Expected ')' after switch expression");
  consume(TokenType::DELIM_LBRACE, "Expected '{' to begin switch block");
  vector<std::pair<optional<ExpressionPtr>, StatementPtr>> cases;
  optional<StatementPtr> defaultCase = std::nullopt;
  while (!check(TokenType::DELIM_RBRACE) && !isAtEnd()) {
    if (match(TokenType::KW_CASE)) {
      // Begin a group of one or more consecutive case labels.
      vector<ExpressionPtr> caseExprs;
      do {
        ExpressionPtr caseExpr = parseExpression();
        consume(TokenType::DELIM_COLON, "Expected ':' after case label");
        caseExprs.push_back(caseExpr);
      } while (check(TokenType::KW_CASE) && (advance(), true));
      // Parse the statement that follows the case labels.
      StatementPtr caseStmt = parseStatement();
      for (auto &e : caseExprs) {
        cases.push_back({e, caseStmt});
      }
    } else if (match(TokenType::KW_DEFAULT)) {
      consume(TokenType::DELIM_COLON, "Expected ':' after 'default'");
      defaultCase = parseStatement();
    } else {
      error("Expected 'case' or 'default' in switch statement");
    }
  }
  consume(TokenType::DELIM_RBRACE, "Expected '}' after switch block");
  return std::make_shared<SwitchStatement>(expr, cases, defaultCase);
}

StatementPtr Parser::parseReturnStatement() {
  ExpressionPtr expr = parseExpression();
  consume(TokenType::DELIM_SEMICOLON, "Expected ';' after return statement");
  return std::make_shared<ReturnStatement>(expr);
}

StatementPtr Parser::parseExpressionStatement() {
  ExpressionPtr expr = parseExpression();
  consume(TokenType::DELIM_SEMICOLON, "Expected ';' after expression");
  return std::make_shared<ExpressionStatement>(expr);
}

// parseVariableDeclarationStatement for local declarations
StatementPtr Parser::parseVariableDeclarationStatement() {
  string type;

  // Attempt to match basic type keywords...
  if (match(TokenType::KW_INT))
    type = "int";
  else if (match(TokenType::KW_FLOAT))
    type = "float";
  else if (match(TokenType::KW_CHAR))
    type = "char";
  else if (match(TokenType::KW_DOUBLE))
    type = "double";
  else if (match(TokenType::KW_BOOL))
    type = "bool";
  // Or match enum
  else if (match(TokenType::KW_ENUM)) {
    // If this is an inline enum definition, revert and parse the enum
    // declaration.
    if (check(TokenType::DELIM_LBRACE) ||
        (check(TokenType::IDENTIFIER) &&
         (current + 1 < tokens.size() &&
          tokens[current + 1].type == TokenType::DELIM_LBRACE))) {
      current--; // Revert the consumption of 'enum'
      DeclarationPtr enumDecl = parseEnumDeclaration();
      return std::make_shared<DeclarationStatement>(enumDecl);
    }
    // Otherwise, forward-declared enum: consume the tag token.
    string tag = "";
    if (check(TokenType::IDENTIFIER))
      tag = advance().lexeme; // Consume the enum tag (e.g. "Color")
    type = "enum " + tag;
  }
  // Or match union
  else if (match(TokenType::KW_UNION)) {
    if (!check(TokenType::IDENTIFIER))
      error("Expected union tag after 'union' in variable declaration");
    string tag = advance().lexeme;
    type = "union " + tag;
  }
  // Or match struct
  else if (match(TokenType::KW_STRUCT) ||
           (check(TokenType::IDENTIFIER) && peek().lexeme == "struct")) {
    if (peek().lexeme == "struct")
      advance(); // consume the literal "struct"
    if (!check(TokenType::IDENTIFIER)) {
      error("Expected struct tag after 'struct' in variable declaration");
    }
    string tag = advance().lexeme;
    type = "struct " + tag;
  }
  // NEW: Handle typedef alias identifiers.
  else if (check(TokenType::IDENTIFIER) &&
           typedefRegistry.find(peek().lexeme) != typedefRegistry.end()) {
    type = typedefRegistry[advance().lexeme];
  } else {
    error("Expected type specifier in variable declaration");
  }

  // Now consume any pointer tokens
  while (check(TokenType::OP_MULTIPLY) && peek().lexeme == "*") {
    advance(); // consume '*'
    type += "*";
  }

  // We can now parse the variable name(s)
  vector<std::shared_ptr<VariableDeclarationStatement>> decls;
  do {
    if (!(peek().type == TokenType::IDENTIFIER ||
          peek().type == TokenType::LITERAL_STRING))
      error("Expected variable name in variable declaration");
    string varName = advance().lexeme; // variable name
    vector<ExpressionPtr> dimensions;
    while (match(TokenType::DELIM_LBRACKET)) {
      ExpressionPtr dimExpr = parseExpression();
      consume(TokenType::DELIM_RBRACKET, "Expected ']' after array dimension");
      dimensions.push_back(dimExpr);
    }
    optional<ExpressionPtr> initializer = std::nullopt;
    if (match(TokenType::OP_ASSIGN)) {
      if (check(TokenType::DELIM_LBRACE))
        initializer = parseInitializerList();
      else
        initializer = parseExpression();
    }
    decls.push_back(std::make_shared<VariableDeclarationStatement>(
        type, varName, initializer, dimensions));
  } while (match(TokenType::DELIM_COMMA));
  consume(TokenType::DELIM_SEMICOLON,
          "Expected ';' after variable declaration");
  if (decls.size() == 1)
    return decls[0];
  else
    return std::make_shared<MultiVariableDeclarationStatement>(decls);
}
