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

// parseVariableDeclarationWithType:
//   parses a variable declaration given an already-determined type name (like
//   "int" or "void*").
DeclarationPtr
Parser::parseVariableDeclarationWithType(const string &givenType) {
  std::cerr << "[DEBUG] (parseVariableDeclarationWithType) current=" << current
            << ", next tokens: ";
  for (int i = 0; i < 3 && current + i < tokens.size(); ++i) {
    std::cerr << static_cast<int>(tokens[current + i].type) << "('"
              << tokens[current + i].lexeme << "') ";
  }
  std::cerr << std::endl;
  string type = givenType;
  vector<std::shared_ptr<VariableDeclaration>> decls;
  do {
    std::cerr << "[DEBUG] Current token: type=" << static_cast<int>(peek().type)
              << ", lexeme='" << peek().lexeme << "'\n";
    if (!check(TokenType::IDENTIFIER)) {
      error("Expected identifier after type/pointer specifiers");
    }
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
        type, varName, std::nullopt, initializer, dimensions));
  } while (match(TokenType::DELIM_COMMA));
  consume(TokenType::DELIM_SEMICOLON,
          "Expected ';' after variable declaration");
  if (decls.size() == 1)
    return decls[0];
  else
    return std::make_shared<MultiVariableDeclaration>(decls);
}

// parseFunctionDeclarationWithType:
//   when we already have e.g. "int" or "void*" as the base type, parse a
//   function name (identifier), then the parameter list, then either a function
//   body or semicolon.
DeclarationPtr
Parser::parseFunctionDeclarationWithType(const string &givenType) {
  std::cerr << "[DEBUG] (parseFunctionDeclarationWithType) current=" << current
            << ", next tokens: ";
  for (int i = 0; i < 3 && current + i < tokens.size(); ++i) {
    std::cerr << static_cast<int>(tokens[current + i].type) << "('"
              << tokens[current + i].lexeme << "') ";
  }
  std::cerr << std::endl;
  string returnType = givenType;
  if (!check(TokenType::IDENTIFIER))
    error("Expected function name after return type");
  string funcName = advance().lexeme; // function name
  consume(TokenType::DELIM_LPAREN, "Expected '(' after function name");
  vector<std::pair<string, string>> parameters = parseParameters();
  consume(TokenType::DELIM_RPAREN, "Expected ')' after parameter list");

  // If next is a semicolon => forward-decl
  if (match(TokenType::DELIM_SEMICOLON)) {
    return std::make_shared<FunctionDeclaration>(returnType, funcName,
                                                 parameters, nullptr);
  }

  // Otherwise parse the function body
  consume(TokenType::DELIM_LBRACE, "Expected '{' to begin function body");
  StatementPtr body = parseCompoundStatement();
  return std::make_shared<FunctionDeclaration>(returnType, funcName, parameters,
                                               body);
}

DeclarationPtr Parser::parseDeclaration() {
  std::cerr << "[DEBUG] (parseDeclaration) current=" << current
            << ", next tokens: ";
  for (int i = 0; i < 3 && current + i < tokens.size(); ++i) {
    std::cerr << static_cast<int>(tokens[current + i].type) << "('"
              << tokens[current + i].lexeme << "') ";
  }
  std::cerr << std::endl;
  bool hasConstQualifier = false;
  bool hasStaticQualifier = false;
  while (!isAtEnd() && check(TokenType::IDENTIFIER) &&
         (peek().lexeme == "const" || peek().lexeme == "static")) {
    if (peek().lexeme == "const")
      hasConstQualifier = true;
    else if (peek().lexeme == "static")
      hasStaticQualifier = true;
    advance();
  }
  // 1) Check for struct / union / enum definitions
  if (peek().lexeme == "struct") {
    std::cerr << "[DEBUG] (parseDeclaration) Found struct keyword" << std::endl;
    // Check if this is actually a struct definition (has '{' after tag)
    size_t save = current;
    advance(); // consume "struct"
    if (check(TokenType::IDENTIFIER)) {
      string structTag = advance().lexeme;
      if (check(TokenType::DELIM_LBRACE)) {
        // It's a struct definition
        current = save;
        return parseStructDeclaration();
      } else {
        // It's not a struct definition, fall through to section 4
        current = save;
      }
    } else {
      // No identifier after struct, fall through to section 4
      current = save;
    }
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

  // 2) Otherwise, if the next token is a recognized type specifier:
  //    (int, float, char, double, bool or "void" or user-defined "ident
  //    struct"? etc.)
  if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
      check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
      check(TokenType::KW_BOOL) || check(TokenType::KW_VOID)) {
    bool sawUnsigned = false;
    bool sawSigned = false;
    while (!isAtEnd() && check(TokenType::IDENTIFIER) &&
           (peek().lexeme == "unsigned" || peek().lexeme == "signed")) {
      if (peek().lexeme == "unsigned")
        sawUnsigned = true;
      else
        sawSigned = true;
      advance();
    }
    // e.g. int main(...) or int x; ...
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
    else if (match(TokenType::KW_VOID))
      baseType = "void";
    else if (check(TokenType::IDENTIFIER)) {
      string lex = peek().lexeme;
      if (lex == "int" || lex == "char" || lex == "float" ||
          lex == "double" || lex == "bool" || lex == "void") {
        advance();
        baseType = lex;
      }
    }
    if (baseType.empty())
      error("Expected type specifier in declaration");
    if (sawUnsigned)
      baseType = "unsigned " + baseType;
    else if (sawSigned)
      baseType = "signed " + baseType;
    if (hasConstQualifier)
      baseType = "const " + baseType;
    if (hasStaticQualifier)
      baseType = "static " + baseType;
    // consume any pointer tokens
    string type = consumePointerTokens(*this, baseType);

    // Now see if next is an identifier => function or variable
    std::cerr << "[DEBUG] (parseDeclaration) Current token: type="
              << static_cast<int>(peek().type) << ", lexeme='" << peek().lexeme
              << "'\n";
    if (!check(TokenType::IDENTIFIER))
      error("Expected identifier after type/pointer specifiers");

    // If next+1 is '(' => function
    if (current + 1 < tokens.size() &&
        tokens[current + 1].type == TokenType::DELIM_LPAREN) {
      return parseFunctionDeclarationWithType(type);
    } else {
      return parseVariableDeclarationWithType(type);
    }
  }

  // 3) Possibly "void" as a type (recognized as IDENTIFIER in the token stream)
  //    We handle it as a special case if (peek().lexeme == "void")
  if (!isAtEnd() && peek().lexeme == "void") {
    // treat it as type "void"
    advance(); // consume the "void" token (which is currently IDENTIFIER type)
    string baseType = "void";

    // consume pointer tokens: e.g. "void*"
    baseType = consumePointerTokens(*this, baseType);

    // Now must see an identifier => function name or variable name
    if (!check(TokenType::IDENTIFIER)) {
      error("Expected function or variable name after 'void'");
    }
    // If next+1 is '(' => function
    if (current + 1 < tokens.size() &&
        tokens[current + 1].type == TokenType::DELIM_LPAREN) {
      return parseFunctionDeclarationWithType(baseType);
    } else {
      // e.g. "void var;" is not valid in standard C unless we do "void *var;"
      // but we'll parse anyway:
      return parseVariableDeclarationWithType(baseType);
    }
  }

  // 4) Possibly "struct" or "union" or "enum" typed
  if (peek().lexeme == "struct") {
    std::cerr << "[DEBUG] (parseDeclaration) Found struct keyword in section 4" << std::endl;
    size_t save = current;
    advance(); // consume "struct"
    if (check(TokenType::IDENTIFIER)) {
      string structTag = advance().lexeme;
      std::cerr << "[DEBUG] (parseDeclaration) Struct tag: " << structTag << std::endl;
      // Look ahead: if next token is '{', it's a struct definition
      if (check(TokenType::DELIM_LBRACE)) {
        std::cerr << "[DEBUG] (parseDeclaration) Found '{', parsing as struct definition" << std::endl;
        current = save;
        return parseStructDeclaration();
      } else if (check(TokenType::IDENTIFIER)) {
        std::cerr << "[DEBUG] (parseDeclaration) Found identifier after struct tag" << std::endl;
        // struct IDENT IDENT ... => variable or function declaration
        string type = "struct " + structTag;
        type = consumePointerTokens(*this, type);
        if (!check(TokenType::IDENTIFIER))
          error("Expected identifier after struct type");
        
        // Check if next token is '(' to determine if it's a function
        if (current + 1 < tokens.size() && tokens[current + 1].type == TokenType::DELIM_LPAREN) {
          std::cerr << "[DEBUG] (parseDeclaration) Next token is '(', parsing as function declaration" << std::endl;
          return parseFunctionDeclarationWithType(type);
        } else {
          std::cerr << "[DEBUG] (parseDeclaration) Next token is not '(', parsing as variable declaration" << std::endl;
          return parseVariableDeclarationWithType(type);
        }
      } else {
        // struct IDENT ... (not followed by '{' or identifier): error
        error("Expected '{' for struct definition or identifier for variable declaration after struct tag");
      }
    } else if (check(TokenType::DELIM_LBRACE)) {
      // struct { ... } (anonymous struct definition)
      current = save;
      return parseStructDeclaration();
    } else {
      error("Expected struct tag or '{' after 'struct'");
    }
  }
  if (check(TokenType::KW_UNION)) {
    return parseUnionDeclaration();
  }
  if (check(TokenType::KW_ENUM)) {
    return parseEnumDeclaration();
  }

  // Otherwise, we do not recognize the next token as a declaration
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
      bool hasConst = false;
      bool hasStatic = false;
      bool sawUnsigned = false;
      bool sawSigned = false;
      while (!isAtEnd() && check(TokenType::IDENTIFIER)) {
        std::string lex = peek().lexeme;
        if (lex == "const") {
          hasConst = true;
          advance();
          continue;
        }
        if (lex == "static") {
          hasStatic = true;
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

      if (sawUnsigned)
        memberType = "unsigned " + memberType;
      else if (sawSigned)
        memberType = "signed " + memberType;
      if (hasConst)
        memberType = "const " + memberType;
      if (hasStatic)
        memberType = "static " + memberType;

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
      std::optional<int> bitWidth = std::nullopt;
      if (match(TokenType::DELIM_COLON)) {
        ExpressionPtr widthExpr = parseExpression();
        if (auto lit = std::dynamic_pointer_cast<Literal>(widthExpr)) {
          bitWidth = lit->intValue;
        } else {
          error("Expected constant expression for bitfield width");
        }
      }
      consume(TokenType::DELIM_SEMICOLON,
              "Expected ';' after struct member declaration");
      members.push_back(std::make_shared<VariableDeclaration>(
          memberType, memberName, bitWidth, std::nullopt, dimensions));
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
  std::cerr
      << "[DEBUG] parseUnionDeclaration: Starting union declaration parsing"
      << std::endl;
  consume(TokenType::KW_UNION, "Expected 'union' keyword");
  optional<string> tag = std::nullopt;
  if (check(TokenType::IDENTIFIER))
    tag = advance().lexeme;
  std::cerr << "[DEBUG] parseUnionDeclaration: Tag is "
            << (tag.has_value() ? "'" + tag.value() + "'" : "nullopt")
            << std::endl;
  consume(TokenType::DELIM_LBRACE, "Expected '{' to begin union declaration");
  vector<std::shared_ptr<VariableDeclaration>> members;
  while (!check(TokenType::DELIM_RBRACE) && !isAtEnd()) {
    auto memberDecl = parseUnionMemberDeclaration();
    members.push_back(memberDecl);
  }
  consume(TokenType::DELIM_RBRACE, "Expected '}' to close union declaration");
  consume(TokenType::DELIM_SEMICOLON, "Expected ';' after union declaration");
  std::cerr << "[DEBUG] parseUnionDeclaration: Creating UnionDeclaration with "
            << members.size() << " members" << std::endl;
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
  
  // Handle array dimensions
  vector<ExpressionPtr> dimensions;
  while (match(TokenType::DELIM_LBRACKET)) {
    ExpressionPtr dimExpr = parseExpression();
    consume(TokenType::DELIM_RBRACKET, "Expected ']' after array dimension");
    dimensions.push_back(dimExpr);
  }
  
  consume(TokenType::DELIM_SEMICOLON,
          "Expected ';' after union member declaration");
  return std::make_shared<VariableDeclaration>(type, name, std::nullopt,
                                               std::nullopt, dimensions);
}

DeclarationPtr Parser::parseFunctionDeclaration() {
  // This version is used when no pointer tokens have yet been consumed.
  // We also might add "if match(TokenType::KW_VOID)) baseType= "void"; here" if
  // we like, but let's keep it consistent with parseDeclaration().
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
      check(TokenType::KW_BOOL) || check(TokenType::KW_VOID) ||
      peek().lexeme == "struct") {
    do {
      string type;
      if (match(TokenType::KW_VOID)) {
        // Handle "void" as an empty parameter list (e.g., int main(void)).
        if (check(TokenType::DELIM_RPAREN)) {
          return params;
        }
        type = "void";
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
      else if (match(TokenType::KW_VOID))
        type = "void";
      else if (peek().lexeme == "struct") {
        advance(); // consume "struct"
        if (!check(TokenType::IDENTIFIER))
          error("Expected struct tag after 'struct'");
        string structTag = advance().lexeme;
        type = "struct " + structTag;
      } else
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
