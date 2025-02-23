#include "AST.hpp"
#include "Parser.hpp"
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

using std::optional;
using std::runtime_error;
using std::string;
using std::vector;

DeclarationPtr Parser::parseDeclaration() {
  // Global declarations: check for struct, union, or enum definitions.
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
  // Otherwise, if the next token is a primitive type specifier...
  if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
      check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
      check(TokenType::KW_BOOL)) {
    size_t save = current;
    string type;
    if (match(TokenType::KW_INT)) {
      type = "int";
    } else if (match(TokenType::KW_FLOAT)) {
      type = "float";
    } else if (match(TokenType::KW_CHAR)) {
      type = "char";
    } else if (match(TokenType::KW_DOUBLE)) {
      type = "double";
    } else if (match(TokenType::KW_BOOL)) {
      type = "bool";
    } else {
      error("Expected type specifier");
    }
    if (check(TokenType::IDENTIFIER)) {
      Token identifier = advance();
      // NEW: Parse any array dimensions following the identifier.
      vector<ExpressionPtr> dimensions;
      while (match(TokenType::DELIM_LBRACKET)) {
        ExpressionPtr dimExpr = parseExpression();
        consume(TokenType::DELIM_RBRACKET,
                "Expected ']' after array dimension");
        dimensions.push_back(dimExpr);
      }
      if (check(TokenType::DELIM_LPAREN)) {
        current = save;
        return parseFunctionDeclaration();
      } else {
        current = save;
        return parseVariableDeclaration();
      }
    } else {
      error("Expected identifier after type");
    }
  }
  error("Expected declaration");
  return nullptr;
}

DeclarationPtr Parser::parseStructDeclaration() {
  // Consume the "struct" keyword.
  if (peek().lexeme == "struct")
    advance();
  else
    error("Expected 'struct' keyword");

  // Optionally, get the struct tag.
  optional<string> tag = std::nullopt;
  if (check(TokenType::IDENTIFIER)) {
    tag = advance().lexeme;
  }
  // If the next token is a left brace, this is a struct definition.
  if (check(TokenType::DELIM_LBRACE)) {
    consume(TokenType::DELIM_LBRACE,
            "Expected '{' to begin struct declaration");
    vector<std::shared_ptr<VariableDeclaration>> members;
    while (!check(TokenType::DELIM_RBRACE) && !isAtEnd()) {
      // Parse a member declaration.
      string memberType;
      // Check if the member's type specifier starts with "struct"
      if ((check(TokenType::KW_STRUCT)) ||
          (check(TokenType::IDENTIFIER) && peek().lexeme == "struct")) {
        // Consume the "struct" keyword.
        advance();
        if (!check(TokenType::IDENTIFIER)) {
          error("Expected struct tag after 'struct' in member declaration");
        }
        string tag = advance().lexeme;
        memberType = "struct " + tag;
      } else if (match(TokenType::KW_ENUM)) {
        // Handle enum types in struct members.
        if (!check(TokenType::IDENTIFIER))
          error("Expected enum tag after 'enum' in member declaration");
        string tag = advance().lexeme;
        memberType = "enum " + tag;
      } else if (match(TokenType::KW_INT)) {
        memberType = "int";
      } else if (match(TokenType::KW_FLOAT)) {
        memberType = "float";
      } else if (match(TokenType::KW_CHAR)) {
        memberType = "char";
      } else if (match(TokenType::KW_DOUBLE)) {
        memberType = "double";
      } else if (match(TokenType::KW_BOOL)) {
        memberType = "bool";
      } else {
        error("Expected type specifier in struct member declaration");
      }
      if (!check(TokenType::IDENTIFIER)) {
        error("Expected member name in struct declaration");
      }
      string memberName = advance().lexeme;
      // NEW: Parse possible array dimensions for struct members.
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
    // No struct definition body; treat as a type specifier.
    return nullptr;
  }
}

DeclarationPtr Parser::parseVariableDeclaration() {
  string type;
  if (match(TokenType::KW_INT)) {
    type = "int";
  } else if (match(TokenType::KW_FLOAT)) {
    type = "float";
  } else if (match(TokenType::KW_CHAR)) {
    type = "char";
  } else if (match(TokenType::KW_DOUBLE)) {
    type = "double";
  } else if (match(TokenType::KW_BOOL)) {
    type = "bool";
  } else if (match(TokenType::KW_ENUM)) {
    if (check(TokenType::DELIM_LBRACE) ||
        (check(TokenType::IDENTIFIER) &&
         (current + 1 < tokens.size() &&
          tokens[current + 1].type == TokenType::DELIM_LBRACE))) {
      current--;
      return parseEnumDeclaration();
    } else {
      if (!check(TokenType::IDENTIFIER))
        error("Expected enum tag after 'enum' in variable declaration");
      string tag = advance().lexeme;
      type = "enum " + tag;
    }
  } else if (match(TokenType::KW_UNION)) {
    if (!check(TokenType::IDENTIFIER))
      error("Expected union tag after 'union' in variable declaration");
    string tag = advance().lexeme;
    type = "union " + tag;
  } else if (match(TokenType::KW_STRUCT) ||
             (check(TokenType::IDENTIFIER) && peek().lexeme == "struct")) {
    if (peek().lexeme == "struct")
      advance();
    else
      advance();
    if (!check(TokenType::IDENTIFIER)) {
      error("Expected struct tag after 'struct' in variable declaration");
    }
    string tag = advance().lexeme;
    type = "struct " + tag;
  } else {
    error("Expected type specifier in variable declaration");
  }
  vector<std::shared_ptr<VariableDeclaration>> decls;
  do {
    if (!check(TokenType::IDENTIFIER)) {
      error("Expected identifier after type");
    }
    Token varNameToken = advance();
    string varName = varNameToken.lexeme;
    // NEW: Parse any array dimensions.
    vector<ExpressionPtr> dimensions;
    while (match(TokenType::DELIM_LBRACKET)) {
      ExpressionPtr dimExpr = parseExpression();
      consume(TokenType::DELIM_RBRACKET, "Expected ']' after array dimension");
      dimensions.push_back(dimExpr);
    }
    optional<ExpressionPtr> initializer = std::nullopt;
    if (match(TokenType::OP_ASSIGN)) {
      if (check(TokenType::DELIM_LBRACE)) {
        initializer = parseInitializerList();
      } else {
        initializer = parseExpression();
      }
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

DeclarationPtr Parser::parseFunctionDeclaration() {
  string returnType;
  if (match(TokenType::KW_INT)) {
    returnType = "int";
  } else if (match(TokenType::KW_FLOAT)) {
    returnType = "float";
  } else if (match(TokenType::KW_CHAR)) {
    returnType = "char";
  } else if (match(TokenType::KW_DOUBLE)) {
    returnType = "double";
  } else if (match(TokenType::KW_BOOL)) {
    returnType = "bool";
  } else {
    error("Expected return type for function declaration");
  }
  if (!check(TokenType::IDENTIFIER)) {
    error("Expected function name after return type");
  }
  Token funcNameToken = advance();
  string funcName = funcNameToken.lexeme;
  consume(TokenType::DELIM_LPAREN, "Expected '(' after function name");
  vector<std::pair<string, string>> parameters = parseParameters();
  consume(TokenType::DELIM_RPAREN, "Expected ')' after parameter list");
  if (match(TokenType::DELIM_SEMICOLON)) {
    return std::make_shared<FunctionDeclaration>(returnType, funcName,
                                                 parameters, nullptr);
  }
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
      if (match(TokenType::KW_INT)) {
        type = "int";
      } else if (match(TokenType::KW_FLOAT)) {
        type = "float";
      } else if (match(TokenType::KW_CHAR)) {
        type = "char";
      } else if (match(TokenType::KW_DOUBLE)) {
        type = "double";
      } else if (match(TokenType::KW_BOOL)) {
        type = "bool";
      } else {
        error("Expected parameter type");
      }
      if (!check(TokenType::IDENTIFIER)) {
        error("Expected parameter name after type");
      }
      Token paramNameToken = advance();
      string paramName = paramNameToken.lexeme;
      params.emplace_back(type, paramName);
    } while (match(TokenType::DELIM_COMMA));
  }
  return params;
}

DeclarationPtr Parser::parseEnumDeclaration() {
  consume(TokenType::KW_ENUM, "Expected 'enum' keyword");
  optional<string> tag = std::nullopt;
  if (check(TokenType::IDENTIFIER)) {
    Token tagToken = advance();
    tag = tagToken.lexeme;
  }
  consume(TokenType::DELIM_LBRACE, "Expected '{' to start enum body");
  vector<std::pair<string, optional<ExpressionPtr>>> enumerators;
  bool first = true;
  while (!check(TokenType::DELIM_RBRACE) && !isAtEnd()) {
    if (!first) {
      if (!match(TokenType::DELIM_COMMA)) {
        error("Expected ',' between enumerators in enum declaration");
      }
    }
    first = false;
    if (!check(TokenType::IDENTIFIER)) {
      error("Expected enumerator name in enum declaration");
    }
    Token enumToken = advance();
    string enumeratorName = enumToken.lexeme;
    optional<ExpressionPtr> initializer = std::nullopt;
    if (match(TokenType::OP_ASSIGN)) {
      initializer = parseExpression();
    }
    enumerators.push_back({enumeratorName, initializer});
  }
  consume(TokenType::DELIM_RBRACE, "Expected '}' to close enum declaration");
  consume(TokenType::DELIM_SEMICOLON, "Expected ';' after enum declaration");
  return std::make_shared<EnumDeclaration>(tag, enumerators);
}

std::shared_ptr<VariableDeclaration> Parser::parseUnionMemberDeclaration() {
  // Parse a union member declaration.
  string type;
  if (peek().lexeme == "struct") {
    advance(); // consume "struct"
    if (!check(TokenType::IDENTIFIER))
      error("Expected struct tag after 'struct' in union member declaration");
    string tag = advance().lexeme;
    type = "struct " + tag;
  } else if (match(TokenType::KW_INT)) {
    type = "int";
  } else if (match(TokenType::KW_FLOAT)) {
    type = "float";
  } else if (match(TokenType::KW_CHAR)) {
    type = "char";
  } else if (match(TokenType::KW_DOUBLE)) {
    type = "double";
  } else if (match(TokenType::KW_BOOL)) {
    type = "bool";
  } else if (match(TokenType::KW_ENUM)) {
    if (!check(TokenType::IDENTIFIER))
      error("Expected enum tag after 'enum' in union member declaration");
    string tag = advance().lexeme;
    type = "enum " + tag;
  } else {
    error("Expected type specifier in union member declaration");
  }
  string name;
  if (check(TokenType::IDENTIFIER)) {
    Token nameToken = advance();
    name = nameToken.lexeme;
  } else {
    static int anonCounter = 0;
    name = "anon_" + type + "_" + std::to_string(anonCounter++);
  }
  consume(TokenType::DELIM_SEMICOLON,
          "Expected ';' after union member declaration");
  return std::make_shared<VariableDeclaration>(type, name, std::nullopt);
}

DeclarationPtr Parser::parseUnionDeclaration() {
  consume(TokenType::KW_UNION, "Expected 'union' keyword");
  optional<string> tag = std::nullopt;
  if (check(TokenType::IDENTIFIER)) {
    Token tagToken = advance();
    tag = tagToken.lexeme;
  }
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

// NEW: parseInitializerList
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
