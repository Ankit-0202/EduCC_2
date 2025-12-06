#include "AST.hpp"
#include "Parser.hpp"
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
         (current + 1 < tokens.size() && tokens[current + 1].type == TokenType::DELIM_LBRACE))) {
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
         (current + 1 < tokens.size() && tokens[current + 1].type == TokenType::DELIM_LBRACE))) {
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
         (current + 1 < tokens.size() && tokens[current + 1].type == TokenType::DELIM_LBRACE))) {
      current = save; // revert
      DeclarationPtr unionDecl = parseUnionDeclaration();
      return std::make_shared<DeclarationStatement>(unionDecl);
    } else {
      current = save; // revert pointer to handle in variable-decl logic below
    }
  }

  // Otherwise, if the next token is a type specifier...
  if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
      check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
      check(TokenType::KW_BOOL) || check(TokenType::KW_ENUM) ||
      check(TokenType::KW_UNION) ||
      (check(TokenType::KW_STRUCT) ||
       (check(TokenType::IDENTIFIER) && peek().lexeme == "struct"))) {
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

  bool hasConstQualifier = false;
  bool hasStaticQualifier = false;
  bool sawUnsigned = false;
  bool sawSigned = false;
  while (!isAtEnd() && check(TokenType::IDENTIFIER)) {
    std::string lex = peek().lexeme;
    if (lex == "const") {
      hasConstQualifier = true;
      advance();
      continue;
    }
    if (lex == "static") {
      hasStaticQualifier = true;
      advance();
      continue;
    }
    if (lex == "unsigned") {
      sawUnsigned = true;
      advance();
      continue;
    }
    if (lex == "signed") {
      sawSigned = true;
      advance();
      continue;
    }
    break;
  }

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
    // Otherwise, forward–declared enum: consume the tag token.
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
  } else {
    error("Expected type specifier in variable declaration");
  }

  if (sawUnsigned)
    type = "unsigned " + type;
  else if (sawSigned)
    type = "signed " + type;
  if (hasConstQualifier)
    type = "const " + type;
  if (hasStaticQualifier)
    type = "static " + type;

  // Now consume any pointer tokens
  while (check(TokenType::OP_MULTIPLY) && peek().lexeme == "*") {
    advance(); // consume '*'
    type += "*";
  }

  // We can now parse the variable name(s)
  vector<std::shared_ptr<VariableDeclarationStatement>> decls;
  do {
    if (!check(TokenType::IDENTIFIER)) {
      std::cerr << "[DEBUG] (parseVariableDeclarationStatement) current="
                << current << ", token: type=" << static_cast<int>(peek().type)
                << ", lexeme='" << peek().lexeme << "'\n";
      error("Expected variable name in variable declaration");
    }
    Token varNameToken = advance(); // e.g. 'col'
    string varName = varNameToken.lexeme;

    // check for array dimensions
    vector<ExpressionPtr> dimensions;
    while (match(TokenType::DELIM_LBRACKET)) {
      if (check(TokenType::DELIM_RBRACKET)) {
        // unsized array; consume the closing bracket without an expression.
        advance();
      } else {
        ExpressionPtr dimExpr = parseExpression();
        consume(TokenType::DELIM_RBRACKET,
                "Expected ']' after array dimension");
        dimensions.push_back(dimExpr);
      }
    }

    // optional initializer
    optional<ExpressionPtr> initializer = std::nullopt;
    if (match(TokenType::OP_ASSIGN)) {
      if (check(TokenType::DELIM_LBRACE)) {
        initializer = parseInitializerList();
      } else {
        initializer = parseExpression();
      }
    }

    decls.push_back(std::make_shared<VariableDeclarationStatement>(
        type, varName, std::nullopt, initializer, dimensions));

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
