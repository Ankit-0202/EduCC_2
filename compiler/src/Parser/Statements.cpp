#include "AST.hpp"
#include "Parser.hpp"
#include "TypeRegistry.hpp"
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

using std::optional;
using std::runtime_error;
using std::string;
using std::vector;

StatementPtr Parser::parseStatement() {
  std::cerr << "[DEBUG] (parseStatement) current=" << current << " token='"
            << peek().lexeme << "'\n";
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
  } else if (match(TokenType::KW_BREAK)) {
    return parseBreakStatement();
  } else if (match(TokenType::KW_CONTINUE)) {
    return parseContinueStatement();
  } else if (match(TokenType::KW_GOTO)) {
    return parseGotoStatement();
  } else if (match(TokenType::KW_DO)) {
    return parseDoWhileStatement();
  } else if (match(TokenType::DELIM_LBRACE)) {
    // If a compound statement is encountered.
    return parseCompoundStatement();
  }

  // Check for a local enum/struct/union definition in statement context.
  if (check(TokenType::KW_ENUM)) {
    size_t save = current;
    advance(); // consume KW_ENUM
    if (check(TokenType::DELIM_LBRACE) ||
        (check(TokenType::IDENTIFIER) &&
         (current + 1 < tokens.size() &&
          tokens[current + 1].type == TokenType::DELIM_LBRACE))) {
      current = save; // revert
      DeclarationPtr enumDecl = parseEnumDeclaration();
      return std::make_shared<DeclarationStatement>(enumDecl);
    } else {
      current = save; // revert pointer to handle in variable-decl logic below
    }
  }
  if (check(TokenType::KW_STRUCT)) {
    size_t save = current;
    advance(); // consume KW_STRUCT
    if (check(TokenType::DELIM_LBRACE) ||
        (check(TokenType::IDENTIFIER) &&
         (current + 1 < tokens.size() &&
          tokens[current + 1].type == TokenType::DELIM_LBRACE))) {
      current = save; // revert
      DeclarationPtr structDecl = parseStructDeclaration();
      return std::make_shared<DeclarationStatement>(structDecl);
    } else {
      current = save; // revert pointer to handle in variable-decl logic below
    }
  }
  if (check(TokenType::KW_UNION)) {
    size_t save = current;
    advance(); // consume KW_UNION
    if (check(TokenType::DELIM_LBRACE) ||
        (check(TokenType::IDENTIFIER) &&
         (current + 1 < tokens.size() &&
          tokens[current + 1].type == TokenType::DELIM_LBRACE))) {
      current = save; // revert
      DeclarationPtr unionDecl = parseUnionDeclaration();
      return std::make_shared<DeclarationStatement>(unionDecl);
    } else {
      current = save; // revert pointer to handle in variable-decl logic below
    }
  }

  auto startsWithType = [this]() {
    if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
        check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
        check(TokenType::KW_BOOL) || check(TokenType::KW_VOID) ||
        check(TokenType::KW_ENUM) || check(TokenType::KW_UNION) ||
        check(TokenType::KW_STRUCT) ||
        (check(TokenType::IDENTIFIER) &&
         (peek().lexeme == "struct" || isTypedefName(peek().lexeme))))
      return true;
    if (check(TokenType::IDENTIFIER)) {
      std::string lex = peek().lexeme;
      if (lex == "const" || lex == "volatile" || lex == "static" ||
          lex == "unsigned" || lex == "signed" || lex == "long" ||
          lex == "short")
        return true;
      if (lex == "size_t" || lex == "uintptr_t" || lex == "intptr_t" ||
          lex == "ptrdiff_t" || lex == "ssize_t" || lex == "uint8_t" ||
          lex == "uint16_t" || lex == "uint32_t" || lex == "uint64_t" ||
          lex == "int8_t" || lex == "int16_t" || lex == "int32_t" ||
          lex == "int64_t")
        return true;
    }
    std::string lx = peek().lexeme;
    if (lx == "size_t" || lx == "uintptr_t" || lx == "intptr_t" ||
        lx == "ptrdiff_t" || lx == "ssize_t" || lx == "uint8_t" ||
        lx == "uint16_t" || lx == "uint32_t" || lx == "uint64_t" ||
        lx == "int8_t" || lx == "int16_t" || lx == "int32_t" ||
        lx == "int64_t")
      return true;
    return false;
  };

  // Otherwise, if the next token is a type specifier...
  if (startsWithType()) {
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
  auto startsWithType = [this]() {
    if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
        check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
        check(TokenType::KW_BOOL) || check(TokenType::KW_VOID) ||
        check(TokenType::KW_ENUM) || check(TokenType::KW_UNION) ||
        check(TokenType::KW_STRUCT) ||
        (check(TokenType::IDENTIFIER) &&
         (peek().lexeme == "struct" || isTypedefName(peek().lexeme))))
      return true;
    if (check(TokenType::IDENTIFIER)) {
      std::string lex = peek().lexeme;
      if (lex == "const" || lex == "volatile" || lex == "static" ||
          lex == "unsigned" || lex == "signed" || lex == "long" ||
          lex == "short")
        return true;
    }
    return false;
  };
  if (startsWithType()) {
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
  std::cerr << "[DEBUG] (parseReturnStatement) start token='" << peek().lexeme
            << "'\n";
  ExpressionPtr expr = parseExpression();
  std::cerr << "[DEBUG] (parseReturnStatement) after expr token='"
            << peek().lexeme << "'\n";
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
  bool hasConstQualifier = false;
  bool hasStaticQualifier = false;
  bool hasVolatileQualifier = false;
  string baseType = parseSimpleType(*this, hasConstQualifier,
                                    hasStaticQualifier, hasVolatileQualifier);

  vector<std::shared_ptr<VariableDeclarationStatement>> decls;
  do {
    ParsedDeclarator declInfo = parseDeclarator(*this, baseType, true);

    // Detect a function declaration/definition that appears inside a compound
    // statement. After parsing the declarator, a '(' means we're looking at a
    // parameter list rather than an initialiser.
    if (check(TokenType::DELIM_LPAREN)) {
      consume(TokenType::DELIM_LPAREN, "Expected '(' after function name");
      vector<std::pair<string, string>> parameters = parseParameters();
      consume(TokenType::DELIM_RPAREN, "Expected ')' after parameter list");

      StatementPtr body = nullptr;
      if (!match(TokenType::DELIM_SEMICOLON)) {
        consume(TokenType::DELIM_LBRACE, "Expected '{' to begin function body");
        body = parseCompoundStatement();
      }
      auto funcDecl = std::make_shared<FunctionDeclaration>(
          declInfo.type, declInfo.name, parameters, body);
      return std::make_shared<DeclarationStatement>(funcDecl);
    }

    optional<ExpressionPtr> initializer = std::nullopt;
    if (match(TokenType::OP_ASSIGN)) {
      if (check(TokenType::DELIM_LBRACE)) {
        initializer = parseInitializerList();
      } else {
        initializer = parseExpression();
      }
    }

    decls.push_back(std::make_shared<VariableDeclarationStatement>(
        declInfo.type, declInfo.name, std::nullopt, initializer,
        declInfo.dimensions));

  } while (match(TokenType::DELIM_COMMA));

  consume(TokenType::DELIM_SEMICOLON,
          "Expected ';' after variable declaration");

  if (decls.size() == 1)
    return decls[0];
  else
    return std::make_shared<MultiVariableDeclarationStatement>(decls);
}

StatementPtr Parser::parseBreakStatement() {
  consume(TokenType::DELIM_SEMICOLON, "Expected ';' after 'break'");
  return std::make_shared<BreakStatement>();
}

StatementPtr Parser::parseContinueStatement() {
  consume(TokenType::DELIM_SEMICOLON, "Expected ';' after 'continue'");
  return std::make_shared<ContinueStatement>();
}

StatementPtr Parser::parseGotoStatement() {
  if (!check(TokenType::IDENTIFIER)) {
    error("Expected label name after 'goto'");
  }
  string label = advance().lexeme;
  consume(TokenType::DELIM_SEMICOLON, "Expected ';' after goto statement");
  return std::make_shared<GotoStatement>(label);
}

StatementPtr Parser::parseDoWhileStatement() {
  StatementPtr body = parseStatement();
  consume(TokenType::KW_WHILE, "Expected 'while' after do-while body");
  consume(TokenType::DELIM_LPAREN, "Expected '(' after 'while'");
  ExpressionPtr condition = parseExpression();
  consume(TokenType::DELIM_RPAREN, "Expected ')' after while condition");
  consume(TokenType::DELIM_SEMICOLON, "Expected ';' after do-while statement");
  return std::make_shared<DoWhileStatement>(body, condition);
}
