#include "AST.hpp"
#include "Parser.hpp"
#include "TypeRegistry.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::runtime_error;
using std::string;
using std::vector;

std::string parseSimpleType(Parser &parser, bool &hasConstQualifier,
                            bool &hasStaticQualifier,
                            bool &hasVolatileQualifier);

ExpressionPtr Parser::parseExpression() {
  std::string startLex = peek().lexeme;
  ExpressionPtr expr = parseAssignment();
  std::cerr << "[DEBUG] (parseExpression) start='" << startLex << "' end='"
            << peek().lexeme << "'\n";
  return expr;
}

ExpressionPtr Parser::parseAssignment() {
  ExpressionPtr expr = parseLogicalOr();

  // Check for ternary operator
  if (match(TokenType::DELIM_QUESTION)) {
    ExpressionPtr trueExpr = parseAssignment();
    consume(TokenType::DELIM_COLON, "Expected ':' in ternary operator");
    ExpressionPtr falseExpr = parseAssignment();
    return std::make_shared<TernaryExpression>(expr, trueExpr, falseExpr);
  }

  if (!isAtEnd() && (peek().type == TokenType::OP_PLUS_ASSIGN ||
                     peek().type == TokenType::OP_MINUS_ASSIGN ||
                     peek().type == TokenType::OP_MULTIPLY_ASSIGN ||
                     peek().type == TokenType::OP_DIVIDE_ASSIGN)) {
    Token opToken = advance();
    ExpressionPtr rhs = parseAssignment();
    string op = opToken.lexeme.substr(0, 1);
    ExpressionPtr binaryExpr =
        std::make_shared<BinaryExpression>(op, expr, rhs);
    return std::make_shared<Assignment>(expr, binaryExpr);
  } else if (match(TokenType::OP_ASSIGN)) {
    ExpressionPtr value = parseAssignment();
    return std::make_shared<Assignment>(expr, value);
  }
  return expr;
}

// Logical OR (||)
ExpressionPtr Parser::parseLogicalOr() {
  ExpressionPtr expr = parseLogicalAnd();
  while (match(TokenType::OP_LOGICAL_OR)) {
    Token oper = tokens[current - 1];
    string op = oper.lexeme;
    ExpressionPtr right = parseLogicalAnd();
    expr = std::make_shared<BinaryExpression>(op, expr, right);
  }
  return expr;
}

// Logical AND (&&)
ExpressionPtr Parser::parseLogicalAnd() {
  ExpressionPtr expr = parseBitwiseOr();
  while (match(TokenType::OP_LOGICAL_AND)) {
    Token oper = tokens[current - 1];
    string op = oper.lexeme;
    ExpressionPtr right = parseBitwiseOr();
    expr = std::make_shared<BinaryExpression>(op, expr, right);
  }
  return expr;
}

// Bitwise OR (|)
ExpressionPtr Parser::parseBitwiseOr() {
  ExpressionPtr expr = parseBitwiseXor();
  while (match(TokenType::OP_BITWISE_OR)) {
    Token oper = tokens[current - 1];
    string op = oper.lexeme;
    ExpressionPtr right = parseBitwiseXor();
    expr = std::make_shared<BinaryExpression>(op, expr, right);
  }
  return expr;
}

// Bitwise XOR (^)
ExpressionPtr Parser::parseBitwiseXor() {
  ExpressionPtr expr = parseBitwiseAnd();
  while (match(TokenType::OP_BITWISE_XOR)) {
    Token oper = tokens[current - 1];
    string op = oper.lexeme;
    ExpressionPtr right = parseBitwiseAnd();
    expr = std::make_shared<BinaryExpression>(op, expr, right);
  }
  return expr;
}

// Bitwise AND (&)
ExpressionPtr Parser::parseBitwiseAnd() {
  ExpressionPtr expr = parseEquality();
  while (match(TokenType::OP_BITWISE_AND)) {
    Token oper = tokens[current - 1];
    string op = oper.lexeme;
    ExpressionPtr right = parseEquality();
    expr = std::make_shared<BinaryExpression>(op, expr, right);
  }
  return expr;
}

// Equality (==, !=)
ExpressionPtr Parser::parseEquality() {
  ExpressionPtr expr = parseRelational();
  while (match(TokenType::OP_EQUAL) || match(TokenType::OP_NOT_EQUAL)) {
    Token oper = tokens[current - 1];
    string op = oper.lexeme;
    ExpressionPtr right = parseRelational();
    expr = std::make_shared<BinaryExpression>(op, expr, right);
  }
  return expr;
}

// Relational (<, <=, >, >=)
ExpressionPtr Parser::parseRelational() {
  ExpressionPtr expr = parseShift();
  while (match(TokenType::OP_LESS) || match(TokenType::OP_LESS_EQUAL) ||
         match(TokenType::OP_GREATER) || match(TokenType::OP_GREATER_EQUAL)) {
    Token oper = tokens[current - 1];
    string op = oper.lexeme;
    ExpressionPtr right = parseShift();
    expr = std::make_shared<BinaryExpression>(op, expr, right);
  }
  return expr;
}

// Shift (<<, >>)
ExpressionPtr Parser::parseShift() {
  ExpressionPtr expr = parseTerm();
  while (match(TokenType::OP_LEFT_SHIFT) || match(TokenType::OP_RIGHT_SHIFT)) {
    Token oper = tokens[current - 1];
    string op = oper.lexeme;
    ExpressionPtr right = parseTerm();
    expr = std::make_shared<BinaryExpression>(op, expr, right);
  }
  return expr;
}

// Term (additive +, -)
ExpressionPtr Parser::parseTerm() {
  ExpressionPtr expr = parseFactor();
  while (match(TokenType::OP_PLUS) || match(TokenType::OP_MINUS)) {
    Token oper = tokens[current - 1];
    string op = oper.lexeme;
    ExpressionPtr right = parseFactor();
    expr = std::make_shared<BinaryExpression>(op, expr, right);
  }
  return expr;
}

// Factor (multiplicative *, /, %)
ExpressionPtr Parser::parseFactor() {
  ExpressionPtr expr = parseUnary();
  while (match(TokenType::OP_MULTIPLY) || match(TokenType::OP_DIVIDE) ||
         match(TokenType::OP_MODULO)) {
    Token oper = tokens[current - 1];
    string op = oper.lexeme;
    ExpressionPtr right = parseUnary();
    expr = std::make_shared<BinaryExpression>(op, expr, right);
  }
  return expr;
}

// Modified parseUnary() to support cast expressions, address-of ('&'),
// dereference ('*'), logical NOT ('!'), and unary minus ('-') operators.
ExpressionPtr Parser::parseUnary() {
  // Handle cast expressions of the form "(type) expr"
  size_t save = current;
  if (match(TokenType::DELIM_LPAREN)) {
    bool hasConst = false;
    bool hasStatic = false;
    bool hasVolatile = false;
    if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
        check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
        check(TokenType::KW_BOOL) || check(TokenType::KW_VOID) ||
        peek().lexeme == "struct" || peek().lexeme == "union" ||
        isTypedefName(peek().lexeme) ||
        peek().lexeme == "size_t" || peek().lexeme == "uintptr_t" ||
        peek().lexeme == "intptr_t" || peek().lexeme == "ptrdiff_t" ||
        peek().lexeme == "ssize_t" || peek().lexeme == "uint8_t" ||
        peek().lexeme == "uint16_t" || peek().lexeme == "uint32_t" ||
        peek().lexeme == "uint64_t" || peek().lexeme == "int8_t" ||
        peek().lexeme == "int16_t" || peek().lexeme == "int32_t" ||
        peek().lexeme == "int64_t") {
      std::string castType =
          parseSimpleType(*this, hasConst, hasStatic, hasVolatile);
      while (match(TokenType::OP_MULTIPLY))
        castType += "*";
      if (match(TokenType::DELIM_RPAREN)) {
        ExpressionPtr operand = parseUnary();
        return std::make_shared<CastExpression>(castType, operand);
      }
    }
    current = save; // Not a cast; rewind and parse normally.
  }
  // Handle logical NOT operator '!'
  if (match(TokenType::OP_LOGICAL_NOT)) {
    ExpressionPtr operand = parseUnary();
    return std::make_shared<UnaryExpression>("!", operand);
  }
  // Handle unary minus operator '-'
  if (match(TokenType::OP_MINUS)) {
    ExpressionPtr operand = parseUnary();
    return std::make_shared<UnaryExpression>("-", operand);
  }
  // Handle unary plus operator '+'
  if (match(TokenType::OP_PLUS)) {
    ExpressionPtr operand = parseUnary();
    return std::make_shared<UnaryExpression>("+", operand);
  }
  // Handle bitwise NOT operator '~'
  if (match(TokenType::OP_BITWISE_NOT)) {
    ExpressionPtr operand = parseUnary();
    return std::make_shared<UnaryExpression>("~", operand);
  }
  // Handle address-of operator '&'
  if (!isAtEnd() && peek().lexeme == "&") {
    advance();
    ExpressionPtr operand = parseUnary();
    return std::make_shared<UnaryExpression>("&", operand);
  }
  // Handle dereference operator '*'
  if (!isAtEnd() && peek().lexeme == "*") {
    advance();
    ExpressionPtr operand = parseUnary();
    return std::make_shared<UnaryExpression>("*", operand);
  }
  return parsePostfix();
}

// Postfix (handles postfix ++/--)
ExpressionPtr Parser::parsePostfix() {
  ExpressionPtr expr = parsePrimary();
  while (!isAtEnd()) {
    if (match(TokenType::DELIM_LPAREN)) {
      vector<ExpressionPtr> args;
      if (!check(TokenType::DELIM_RPAREN)) {
        do {
          args.push_back(parseExpression());
        } while (match(TokenType::DELIM_COMMA));
      }
      consume(TokenType::DELIM_RPAREN, "Expected ')' after function arguments");
      if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
        expr = std::make_shared<FunctionCall>(id->name, args);
      } else if (auto callExpr =
                     std::dynamic_pointer_cast<FunctionCall>(expr)) {
        expr = std::make_shared<FunctionCall>(expr, args);
      } else {
        expr = std::make_shared<FunctionCall>(expr, args);
      }
    } else if (match(TokenType::DOT)) {
      // Expect an identifier after the dot.
      if (!check(TokenType::IDENTIFIER))
        error("Expected identifier after '.' for member access");
      Token memberToken = advance();
      string memberName = memberToken.lexeme;
      expr = std::make_shared<MemberAccess>(expr, memberName);
    } else if (match(TokenType::OP_RIGHT_ARROW)) {
      // Expect an identifier after the arrow.
      if (!check(TokenType::IDENTIFIER))
        error("Expected identifier after '->' for pointer member access");
      Token memberToken = advance();
      string memberName = memberToken.lexeme;
      // For 'ptr->x', treat as MemberAccess(Dereference(ptr), x)
      expr = std::make_shared<MemberAccess>(
          std::make_shared<UnaryExpression>("*", expr), memberName);
    }
    // Array indexing support: parse '[' expression ']'
    else if (match(TokenType::DELIM_LBRACKET)) {
      ExpressionPtr indexExpr = parseExpression();
      consume(TokenType::DELIM_RBRACKET, "Expected ']' after array index");
      expr = std::make_shared<ArrayAccess>(expr, indexExpr);
    } else if (match(TokenType::OP_PLUS_PLUS)) {
      expr = std::make_shared<PostfixExpression>(expr, "++");
    } else if (match(TokenType::OP_MINUS_MINUS)) {
      expr = std::make_shared<PostfixExpression>(expr, "--");
    } else {
      break;
    }
  }
  return expr;
}

// Primary (literals, identifiers, grouping)
ExpressionPtr Parser::parsePrimary() {
  if (match(TokenType::LITERAL_INT)) {
    int value = std::stoi(tokens[current - 1].lexeme);
    return std::make_shared<Literal>(value);
  }
  if (match(TokenType::LITERAL_FLOAT)) {
    float value = std::stof(tokens[current - 1].lexeme);
    return std::make_shared<Literal>(value);
  }
  if (match(TokenType::LITERAL_DOUBLE)) {
    double value = std::stod(tokens[current - 1].lexeme);
    return std::make_shared<Literal>(value);
  }
  if (match(TokenType::LITERAL_CHAR)) {
    string lexeme = tokens[current - 1].lexeme;
    // Extract the character value from the lexeme (e.g., "'A'" -> 'A')
    if (lexeme.length() >= 3 && lexeme[0] == '\'' &&
        lexeme[lexeme.length() - 1] == '\'') {
      char value = lexeme[1]; // Get the character between the quotes
      return std::make_shared<Literal>(value);
    } else {
      // Fallback for malformed character literals
      char value = lexeme[0];
      return std::make_shared<Literal>(value);
    }
  }
  if (match(TokenType::LITERAL_STRING)) {
    auto stripQuotes = [](const string &raw) {
      if (raw.length() >= 2 && raw.front() == '"' && raw.back() == '"')
        return raw.substr(1, raw.length() - 2);
      return raw;
    };
    string value = stripQuotes(tokens[current - 1].lexeme);
    while (check(TokenType::LITERAL_STRING)) {
      advance();
      value += stripQuotes(tokens[current - 1].lexeme);
    }
    return std::make_shared<Literal>(value);
  }
  if (match(TokenType::IDENTIFIER)) {
    string name = tokens[current - 1].lexeme;
    if (name == "true") {
      return std::make_shared<Literal>(true);
    }
    if (name == "false") {
      return std::make_shared<Literal>(false);
    }
    if (match(TokenType::DELIM_LPAREN)) {
      vector<ExpressionPtr> args;
      if (!check(TokenType::DELIM_RPAREN)) {
        do {
          args.push_back(parseExpression());
        } while (match(TokenType::DELIM_COMMA));
      }
      consume(TokenType::DELIM_RPAREN, "Expected ')' after function arguments");
      return std::make_shared<FunctionCall>(name, args);
    } else {
      return std::make_shared<Identifier>(name);
    }
  }
  if (match(TokenType::DELIM_LPAREN)) {
    ExpressionPtr expr = parseExpression();
    consume(TokenType::DELIM_RPAREN, "Expected ')' after expression");
    return expr;
  }
  if (match(TokenType::KW_SIZEOF)) {
    consume(TokenType::DELIM_LPAREN, "Expected '(' after sizeof");

    auto parseTypeName = [this](string &out) -> bool {
      size_t save = current;
      bool hasConst = false;
      bool hasVolatile = false;
      bool hasStatic = false;
      bool sawUnsigned = false;
      bool sawSigned = false;
      while (!isAtEnd() && check(TokenType::IDENTIFIER)) {
        string lex = peek().lexeme;
        if (lex == "const") {
          hasConst = true;
          advance();
          continue;
        }
        if (lex == "volatile") {
          hasVolatile = true;
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

      string typeName;
      if (match(TokenType::KW_INT))
        typeName = "int";
      else if (match(TokenType::KW_FLOAT))
        typeName = "float";
      else if (match(TokenType::KW_CHAR))
        typeName = "char";
      else if (match(TokenType::KW_DOUBLE))
        typeName = "double";
      else if (match(TokenType::KW_BOOL))
        typeName = "bool";
      else if (match(TokenType::KW_VOID))
        typeName = "void";
      else if (match(TokenType::KW_STRUCT) ||
               (check(TokenType::IDENTIFIER) && peek().lexeme == "struct")) {
        if (!check(TokenType::IDENTIFIER)) {
          current = save;
          return false;
        }
        string tag = advance().lexeme;
        typeName = "struct " + tag;
      } else if (match(TokenType::KW_UNION) ||
                 (check(TokenType::IDENTIFIER) && peek().lexeme == "union")) {
        if (!check(TokenType::IDENTIFIER)) {
          current = save;
          return false;
        }
        string tag = advance().lexeme;
        typeName = "union " + tag;
      } else if (match(TokenType::KW_ENUM) ||
                 (check(TokenType::IDENTIFIER) && peek().lexeme == "enum")) {
        if (!check(TokenType::IDENTIFIER)) {
          current = save;
          return false;
        }
        string tag = advance().lexeme;
        typeName = "enum " + tag;
      } else if (check(TokenType::IDENTIFIER) &&
                 (peek().lexeme == "long" || peek().lexeme == "short")) {
        typeName = advance().lexeme;
      } else {
        current = save;
        return false;
      }

      if (sawUnsigned)
        typeName = "unsigned " + typeName;
      else if (sawSigned)
        typeName = "signed " + typeName;
      if (hasConst)
        typeName = "const " + typeName;
      if (hasVolatile)
        typeName = "volatile " + typeName;
      if (hasStatic)
        typeName = "static " + typeName;

      while (match(TokenType::OP_MULTIPLY) && tokens[current - 1].lexeme == "*")
        typeName += "*";

      out = typeName;
      return true;
    };

    string parsedType;
    size_t beforeType = current;
    if (parseTypeName(parsedType)) {
      consume(TokenType::DELIM_RPAREN, "Expected ')' after sizeof type");
      return std::make_shared<SizeOfExpression>(parsedType);
    }
    current = beforeType;
    // sizeof(expression)
    ExpressionPtr operand = parseExpression();
    consume(TokenType::DELIM_RPAREN, "Expected ')' after sizeof expression");
    return std::make_shared<SizeOfExpression>(operand);
  }
  error("Expected expression");
  return nullptr;
}
