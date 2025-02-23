#include "AST.hpp"
#include "Parser.hpp"
#include <iostream> // For debug printing if needed
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

using std::optional;
using std::runtime_error;
using std::string;
using std::vector;

// Helper: consume any "*" tokens that immediately follow a type specifier.
// (Our lexer produces the '*' token as an operator, with type OP_MULTIPLY.)
static string consumePointerTokens(Parser &parser, const string &baseType) {
  string newType = baseType;
  // Consume any tokens that are '*' (by both type and lexeme).
  while (!parser.isAtEnd()) {
    auto token = parser.peek();
    // Debug: Uncomment the following line to see token details
    std::cerr << "consumePointerTokens: peek token lexeme='" << token.lexeme
              << "' type=" << static_cast<int>(token.type) << "\n";
    if (token.type == TokenType::OP_MULTIPLY && token.lexeme == "*") {
      parser.advance();
      newType += "*";
    } else {
      break;
    }
  }
  return newType;
}

// New helper: parse a variable declaration given an already-determined type.
// Assumes that pointer tokens have already been consumed.
DeclarationPtr
Parser::parseVariableDeclarationWithType(const string &givenType) {
  string type = givenType; // already includes any "*" tokens
  vector<std::shared_ptr<VariableDeclaration>> decls;
  do {
    if (!check(TokenType::IDENTIFIER))
      error("Expected identifier after type/pointer specifiers");
    string varName = advance().lexeme;
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
    decls.push_back(std::make_shared<VariableDeclaration>(
        type, varName, initializer, dimensions));
  } while (match(TokenType::DELIM_COMMA));
  consume(TokenType::DELIM_SEMICOLON,
          "Expected ';' after variable declaration");
  if (decls.size() == 1)
    return decls[0];
  else
    return std::make_shared<MultiVariableDeclaration>(decls);
}

// New helper: parse a function declaration when the return type (with any
// pointer tokens) has already been consumed.
DeclarationPtr
Parser::parseFunctionDeclarationWithType(const string &givenType) {
  string returnType = givenType;
  if (!check(TokenType::IDENTIFIER))
    error("Expected function name after return type");
  string funcName = advance().lexeme;
  consume(TokenType::DELIM_LPAREN, "Expected '(' after function name");
  vector<std::pair<string, string>> parameters = parseParameters();
  consume(TokenType::DELIM_RPAREN, "Expected ')' after parameter list");
  if (match(TokenType::DELIM_SEMICOLON))
    return std::make_shared<FunctionDeclaration>(returnType, funcName,
                                                 parameters, nullptr);
  consume(TokenType::DELIM_LBRACE, "Expected '{' to begin function body");
  StatementPtr body = parseCompoundStatement();
  return std::make_shared<FunctionDeclaration>(returnType, funcName, parameters,
                                               body);
}

DeclarationPtr Parser::parseDeclaration() {
  // Check for struct, union, or enum definitions.
  if (peek().lexeme == "struct") {
    return parseStructDeclaration();
  }
  if (check(TokenType::KW_UNION)) {
    return parseUnionDeclaration();
  }
  if (check(TokenType::KW_ENUM)) {
    size_t save = current;
    advance(); // consume KW_ENUM
    if (check(TokenType::DELIM_LBRACE) ||
        (check(TokenType::IDENTIFIER) &&
         (current + 1 < tokens.size() &&
          tokens[current + 1].type == TokenType::DELIM_LBRACE))) {
      current = save;
      return parseEnumDeclaration();
    } else {
      current = save;
    }
  }
  // Otherwise, if the next token is a primitive type specifier…
  if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
      check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
      check(TokenType::KW_BOOL)) {
    size_t save = current;
    string baseType;
    if (match(TokenType::KW_INT))
      baseType = "int";
    else if (match(TokenType::KW_FLOAT))
      baseType = "float";
    else if (match(TokenType::KW_CHAR))
      baseType = "char";
    else if (match(TokenType::KW_DOUBLE))
      baseType = "double";
    else if (match(TokenType::KW_BOOL))
      baseType = "bool";
    else
      error("Expected type specifier");

    // Consume any "*" tokens immediately following the type specifier.
    string type = consumePointerTokens(*this, baseType);

    // Now expect an identifier.
    if (!check(TokenType::IDENTIFIER))
      error("Expected identifier after type/pointer specifiers");

    // Peek ahead: if the token following the identifier is a '(' then this is a
    // function declaration.
    if (current + 1 < tokens.size() &&
        tokens[current + 1].type == TokenType::DELIM_LPAREN)
      return parseFunctionDeclarationWithType(type);
    else
      return parseVariableDeclarationWithType(type);
  }
  error("Expected declaration");
  return nullptr;
}

DeclarationPtr Parser::parseStructDeclaration() {
  if (peek().lexeme == "struct")
    advance();
  else
    error("Expected 'struct' keyword");

  optional<string> tag = std::nullopt;
  if (check(TokenType::IDENTIFIER))
    tag = advance().lexeme;
  if (check(TokenType::DELIM_LBRACE)) {
    consume(TokenType::DELIM_LBRACE,
            "Expected '{' to begin struct declaration");
    vector<std::shared_ptr<VariableDeclaration>> members;
    while (!check(TokenType::DELIM_RBRACE) && !isAtEnd()) {
      string memberType;
      if ((check(TokenType::KW_STRUCT)) ||
          (check(TokenType::IDENTIFIER) && peek().lexeme == "struct")) {
        advance(); // consume "struct"
        if (!check(TokenType::IDENTIFIER))
          error("Expected struct tag after 'struct' in member declaration");
        string tag = advance().lexeme;
        memberType = "struct " + tag;
      } else if (match(TokenType::KW_ENUM)) {
        if (!check(TokenType::IDENTIFIER))
          error("Expected enum tag after 'enum' in member declaration");
        string tag = advance().lexeme;
        memberType = "enum " + tag;
      } else if (match(TokenType::KW_INT))
        memberType = "int";
      else if (match(TokenType::KW_FLOAT))
        memberType = "float";
      else if (match(TokenType::KW_CHAR))
        memberType = "char";
      else if (match(TokenType::KW_DOUBLE))
        memberType = "double";
      else if (match(TokenType::KW_BOOL))
        memberType = "bool";
      else
        error("Expected type specifier in struct member declaration");

      // Consume pointer tokens for the member type.
      memberType = consumePointerTokens(*this, memberType);

      if (!check(TokenType::IDENTIFIER))
        error("Expected member name in struct declaration");
      string memberName = advance().lexeme;
      vector<ExpressionPtr> dimensions;
      while (match(TokenType::DELIM_LBRACKET)) {
        ExpressionPtr dimExpr = parseExpression();
        consume(TokenType::DELIM_RBRACKET,
                "Expected ']' after array dimension");
        dimensions.push_back(dimExpr);
      }
      consume(TokenType::DELIM_SEMICOLON,
              "Expected ';' after struct member declaration");
      members.push_back(std::make_shared<VariableDeclaration>(
          memberType, memberName, std::nullopt, dimensions));
    }
    consume(TokenType::DELIM_RBRACE,
            "Expected '}' to close struct declaration");
    consume(TokenType::DELIM_SEMICOLON,
            "Expected ';' after struct declaration");
    return std::make_shared<StructDeclaration>(tag, members);
  } else {
    return nullptr;
  }
}

DeclarationPtr Parser::parseUnionDeclaration() {
  consume(TokenType::KW_UNION, "Expected 'union' keyword");
  optional<string> tag = std::nullopt;
  if (check(TokenType::IDENTIFIER))
    tag = advance().lexeme;
  consume(TokenType::DELIM_LBRACE, "Expected '{' to begin union declaration");
  vector<std::shared_ptr<VariableDeclaration>> members;
  while (!check(TokenType::DELIM_RBRACE) && !isAtEnd()) {
    auto memberDecl = parseUnionMemberDeclaration();
    members.push_back(memberDecl);
  }
  consume(TokenType::DELIM_RBRACE, "Expected '}' to close union declaration");
  consume(TokenType::DELIM_SEMICOLON, "Expected ';' after union declaration");
  return std::make_shared<UnionDeclaration>(tag, members);
}

DeclarationPtr Parser::parseEnumDeclaration() {
  consume(TokenType::KW_ENUM, "Expected 'enum' keyword");
  optional<string> tag = std::nullopt;
  if (check(TokenType::IDENTIFIER))
    tag = advance().lexeme;
  consume(TokenType::DELIM_LBRACE, "Expected '{' to start enum body");
  vector<std::pair<string, optional<ExpressionPtr>>> enumerators;
  bool first = true;
  while (!check(TokenType::DELIM_RBRACE) && !isAtEnd()) {
    if (!first) {
      if (!match(TokenType::DELIM_COMMA))
        error("Expected ',' between enumerators in enum declaration");
    }
    first = false;
    if (!check(TokenType::IDENTIFIER))
      error("Expected enumerator name in enum declaration");
    string enumeratorName = advance().lexeme;
    optional<ExpressionPtr> initializer = std::nullopt;
    if (match(TokenType::OP_ASSIGN))
      initializer = parseExpression();
    enumerators.push_back({enumeratorName, initializer});
  }
  consume(TokenType::DELIM_RBRACE, "Expected '}' to close enum declaration");
  consume(TokenType::DELIM_SEMICOLON, "Expected ';' after enum declaration");
  return std::make_shared<EnumDeclaration>(tag, enumerators);
}

std::shared_ptr<VariableDeclaration> Parser::parseUnionMemberDeclaration() {
  string type;
  if (peek().lexeme == "struct") {
    advance();
    if (!check(TokenType::IDENTIFIER))
      error("Expected struct tag after 'struct' in union member declaration");
    string tag = advance().lexeme;
    type = "struct " + tag;
  } else if (match(TokenType::KW_INT))
    type = "int";
  else if (match(TokenType::KW_FLOAT))
    type = "float";
  else if (match(TokenType::KW_CHAR))
    type = "char";
  else if (match(TokenType::KW_DOUBLE))
    type = "double";
  else if (match(TokenType::KW_BOOL))
    type = "bool";
  else if (match(TokenType::KW_ENUM)) {
    if (!check(TokenType::IDENTIFIER))
      error("Expected enum tag after 'enum' in union member declaration");
    string tag = advance().lexeme;
    type = "enum " + tag;
  } else {
    error("Expected type specifier in union member declaration");
  }
  // Consume pointer tokens for union members.
  type = consumePointerTokens(*this, type);
  string name;
  if (check(TokenType::IDENTIFIER))
    name = advance().lexeme;
  else {
    static int anonCounter = 0;
    name = "anon_" + type + "_" + std::to_string(anonCounter++);
  }
  consume(TokenType::DELIM_SEMICOLON,
          "Expected ';' after union member declaration");
  return std::make_shared<VariableDeclaration>(type, name, std::nullopt);
}

DeclarationPtr Parser::parseFunctionDeclaration() {
  // This version is used when no pointer tokens have yet been consumed.
  string returnType;
  if (match(TokenType::KW_INT))
    returnType = "int";
  else if (match(TokenType::KW_FLOAT))
    returnType = "float";
  else if (match(TokenType::KW_CHAR))
    returnType = "char";
  else if (match(TokenType::KW_DOUBLE))
    returnType = "double";
  else if (match(TokenType::KW_BOOL))
    returnType = "bool";
  else
    error("Expected return type for function declaration");
  // Consume any pointer tokens for the return type.
  returnType = consumePointerTokens(*this, returnType);
  if (!check(TokenType::IDENTIFIER))
    error("Expected function name after return type");
  string funcName = advance().lexeme;
  consume(TokenType::DELIM_LPAREN, "Expected '(' after function name");
  vector<std::pair<string, string>> parameters = parseParameters();
  consume(TokenType::DELIM_RPAREN, "Expected ')' after parameter list");
  if (match(TokenType::DELIM_SEMICOLON))
    return std::make_shared<FunctionDeclaration>(returnType, funcName,
                                                 parameters, nullptr);
  consume(TokenType::DELIM_LBRACE, "Expected '{' to begin function body");
  StatementPtr body = parseCompoundStatement();
  return std::make_shared<FunctionDeclaration>(returnType, funcName, parameters,
                                               body);
}

vector<std::pair<string, string>> Parser::parseParameters() {
  vector<std::pair<string, string>> params;
  if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
      check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
      check(TokenType::KW_BOOL)) {
    do {
      string type;
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
      else
        error("Expected parameter type");
      // Consume pointer tokens for parameters.
      type = consumePointerTokens(*this, type);
      if (!check(TokenType::IDENTIFIER))
        error("Expected parameter name after type");
      string paramName = advance().lexeme;
      params.emplace_back(type, paramName);
    } while (match(TokenType::DELIM_COMMA));
  }
  return params;
}

ExpressionPtr Parser::parseInitializerList() {
  consume(TokenType::DELIM_LBRACE, "Expected '{' to start initializer list");
  vector<ExpressionPtr> elems;
  if (!check(TokenType::DELIM_RBRACE)) {
    elems.push_back(parseExpression());
    while (match(TokenType::DELIM_COMMA)) {
      if (check(TokenType::DELIM_RBRACE))
        break;
      elems.push_back(parseExpression());
    }
  }
  consume(TokenType::DELIM_RBRACE, "Expected '}' to end initializer list");
  return std::make_shared<InitializerList>(elems);
}
