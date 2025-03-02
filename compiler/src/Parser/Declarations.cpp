#include "AST.hpp"
#include "Parser.hpp"
#include "TypeRegistry.hpp"
#include <algorithm>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

using std::optional;
using std::runtime_error;
using std::string;
using std::vector;

// Helper: consume any "*" tokens that immediately follow a type specifier.
static string consumePointerTokens(Parser &parser, const string &baseType) {
  string newType = baseType;
  while (!parser.isAtEnd()) {
    auto token = parser.peek();
    // Debug printing if needed:
    // std::cerr << "consumePointerTokens: peek token lexeme='" << token.lexeme
    //           << "' type=" << static_cast<int>(token.type) << "\n";
    if (token.type == TokenType::OP_MULTIPLY && token.lexeme == "*") {
      parser.advance();
      newType += "*";
    } else {
      break;
    }
  }
  return newType;
}

static bool isIdentifier(const Token &token) {
  return (token.type == TokenType::IDENTIFIER ||
          token.type == TokenType::LITERAL_STRING);
}

// NEW: Helper: returns true if the token represents a type specifier.
// We consider built-in type keywords and typedef aliases (represented as
// LITERAL_STRING whose lexeme is found in typedefRegistry).
static bool isTypeSpecifierToken(const Token &token) {
  if (token.type == TokenType::KW_INT || token.type == TokenType::KW_FLOAT ||
      token.type == TokenType::KW_CHAR || token.type == TokenType::KW_DOUBLE ||
      token.type == TokenType::KW_BOOL || token.type == TokenType::KW_ENUM ||
      token.type == TokenType::KW_UNION || token.type == TokenType::KW_STRUCT)
    return true;
  if (token.type == TokenType::LITERAL_STRING) {
    if (typedefRegistry.find(token.lexeme) != typedefRegistry.end())
      return true;
  }
  return false;
}

// NEW: parseTypedefDeclaration:
//    Parses a typedef declaration of the form:
//       typedef <underlying-type> <alias>;
// For example: typedef int myint;
DeclarationPtr Parser::parseTypedefDeclaration() {
  // Consume the 'typedef' keyword.
  advance(); // consume typedef

  // Check for optional signed/unsigned modifier.
  string signMod = "";
  if (!isAtEnd() &&
      (peek().lexeme == "unsigned" || peek().lexeme == "signed")) {
    signMod = advance().lexeme + " ";
  }
  // Check for optional long/short modifier.
  string sizeMod = "";
  if (!isAtEnd() && (peek().lexeme == "long" || peek().lexeme == "short")) {
    sizeMod = advance().lexeme + " ";
  }

  string baseType;
  if (match(TokenType::KW_INT))
    baseType = signMod + sizeMod + "int";
  else if (match(TokenType::KW_FLOAT)) {
    if (!signMod.empty() || !sizeMod.empty())
      error("Modifiers cannot be applied to float");
    baseType = "float";
  } else if (match(TokenType::KW_CHAR))
    baseType = signMod + sizeMod + "char";
  else if (match(TokenType::KW_DOUBLE)) {
    if (!signMod.empty() || !sizeMod.empty())
      error("Modifiers cannot be applied to double");
    baseType = "double";
  } else if (match(TokenType::KW_BOOL)) {
    if (!signMod.empty() || !sizeMod.empty())
      error("Modifiers cannot be applied to bool");
    baseType = "bool";
  } else if (!isAtEnd() && peek().lexeme == "void") {
    if (!signMod.empty() || !sizeMod.empty())
      error("Modifiers cannot be applied to void");
    advance();
    baseType = "void";
  } else if (peek().lexeme == "struct") {
    advance(); // consume "struct"
    if (isIdentifier(peek()))
      baseType = "struct " + advance().lexeme;
    else
      error("Typedef error: Inline struct must have a tag.");
  } else if (peek().lexeme == "union") {
    advance(); // consume "union"
    if (isIdentifier(peek()))
      baseType = "union " + advance().lexeme;
    else
      error("Typedef error: Anonymous union cannot be typedef'd.");
  } else if (peek().lexeme == "enum") {
    advance(); // consume "enum"
    if (isIdentifier(peek()))
      baseType = "enum " + advance().lexeme;
    else
      error("Typedef error: Anonymous enum cannot be typedef'd.");
  } else {
    error("Typedef error: Unknown type specifier in typedef declaration.");
  }

  string underlyingType = consumePointerTokens(*this, baseType);
  if (!isIdentifier(peek()))
    error("Typedef error: Expected identifier for typedef alias.");
  string aliasName = advance().lexeme;
  consume(TokenType::DELIM_SEMICOLON, "Expected ';' after typedef declaration");

  typedefRegistry[aliasName] = underlyingType;
  return std::make_shared<TypedefDeclaration>(underlyingType, aliasName);
}

DeclarationPtr
Parser::parseVariableDeclarationWithType(const string &givenType) {
  string type = givenType;
  vector<std::shared_ptr<VariableDeclaration>> decls;
  do {
    if (!isIdentifier(peek()))
      error("Expected identifier after type/pointer specifiers");
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

DeclarationPtr
Parser::parseFunctionDeclarationWithType(const string &givenType) {
  string returnType = givenType;
  if (!isIdentifier(peek()))
    error("Expected function name after return type");
  string funcName = advance().lexeme; // function name
  consume(TokenType::DELIM_LPAREN, "Expected '(' after function name");
  vector<std::pair<string, string>> parameters = parseParameters();
  consume(TokenType::DELIM_RPAREN, "Expected ')' after parameter list");

  // If next is a semicolon => forward-declaration.
  if (match(TokenType::DELIM_SEMICOLON)) {
    return std::make_shared<FunctionDeclaration>(returnType, funcName,
                                                 parameters, nullptr);
  }

  // Otherwise parse the function body.
  consume(TokenType::DELIM_LBRACE, "Expected '{' to begin function body");
  StatementPtr body = parseCompoundStatement();
  return std::make_shared<FunctionDeclaration>(returnType, funcName, parameters,
                                               body);
}

DeclarationPtr Parser::parseDeclaration() {
  // NEW: Check for typedef declarations first.
  if (peek().type == TokenType::KW_TYPEDEF || peek().lexeme == "typedef") {
    return parseTypedefDeclaration();
  }

  // 1) Check for struct / union / enum definitions.
  if (peek().lexeme == "struct") {
    return parseStructDeclaration();
  }
  if (peek().type == TokenType::KW_UNION) {
    return parseUnionDeclaration();
  }
  if (peek().type == TokenType::KW_ENUM) {
    size_t save = current;
    advance(); // consume KW_ENUM
    if (check(TokenType::DELIM_LBRACE) ||
        (isIdentifier(peek()) &&
         (current + 1 < tokens.size() &&
          tokens[current + 1].type == TokenType::DELIM_LBRACE))) {
      current = save;
      return parseEnumDeclaration();
    } else {
      current = save;
    }
  }

  // 2) Otherwise, if the next token is a recognized type specifier.
  if (isTypeSpecifierToken(peek())) {
    size_t save = current;
    string baseType;
    // If the token is a built-in type keyword, match it.
    if (peek().type == TokenType::KW_INT) {
      match(TokenType::KW_INT);
      baseType = "int";
    } else if (peek().type == TokenType::KW_FLOAT) {
      match(TokenType::KW_FLOAT);
      baseType = "float";
    } else if (peek().type == TokenType::KW_CHAR) {
      match(TokenType::KW_CHAR);
      baseType = "char";
    } else if (peek().type == TokenType::KW_DOUBLE) {
      match(TokenType::KW_DOUBLE);
      baseType = "double";
    } else if (peek().type == TokenType::KW_BOOL) {
      match(TokenType::KW_BOOL);
      baseType = "bool";
    } else {
      // Otherwise, it must be a typedef alias.
      baseType = advance().lexeme;
    }
    string type = consumePointerTokens(*this, baseType);

    // Now, expect an identifier (function or variable name).
    if (!isIdentifier(peek()))
      error("Expected identifier after type/pointer specifiers");

    // If the token following the identifier is "(" then it is a function
    // declaration.
    if (current + 1 < tokens.size() && tokens[current + 1].lexeme == "(")
      return parseFunctionDeclarationWithType(type);
    else
      return parseVariableDeclarationWithType(type);
  }

  // 3) Possibly "void" as a type.
  if (!isAtEnd() && peek().lexeme == "void") {
    advance(); // consume "void"
    string baseType = "void";
    baseType = consumePointerTokens(*this, baseType);
    if (!(isIdentifier(peek()) || peek().lexeme == "(")) {
      error("Expected function or variable name after 'void'");
    }
    if (current + 1 < tokens.size() && tokens[current + 1].lexeme == "(")
      return parseFunctionDeclarationWithType(baseType);
    else
      return parseVariableDeclarationWithType(baseType);
  }

  // 4) Possibly "struct" or "union" or "enum" typed.
  if (peek().lexeme == "struct") {
    return parseStructDeclaration();
  }
  if (peek().type == TokenType::KW_UNION) {
    return parseUnionDeclaration();
  }
  if (peek().type == TokenType::KW_ENUM) {
    return parseEnumDeclaration();
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
        string mtag = advance().lexeme;
        memberType = "struct " + mtag;
      } else if (match(TokenType::KW_ENUM)) {
        if (!check(TokenType::IDENTIFIER))
          error("Expected enum tag after 'enum' in member declaration");
        string etag = advance().lexeme;
        memberType = "enum " + etag;
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
    string etag = advance().lexeme;
    type = "enum " + etag;
  } else {
    error("Expected type specifier in union member declaration");
  }
  // pointer tokens
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
  // We also might add "if (match(TokenType::KW_VOID)) baseType= 'void';" here
  // if we like, but let's keep it consistent with parseDeclaration().
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

      // pointer tokens
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
