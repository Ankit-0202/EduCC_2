#include "AST.hpp"
#include "Parser.hpp"
#include <stdexcept>
#include <string>
#include <vector>

using std::runtime_error;
using std::string;
using std::vector;

ExpressionPtr Parser::parseExpression() { return parseAssignment(); }

ExpressionPtr Parser::parseAssignment() {
  ExpressionPtr expr = parseLogicalOr();
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

// Modified parseUnary() to support cast expressions, address-of ('&'), and
// dereference ('*') operators.
ExpressionPtr Parser::parseUnary() {
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
  // Check for cast expression.
  if (match(TokenType::DELIM_LPAREN)) {
    // Check if this is a cast expression: ( type ) cast-expression
    if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
        check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
        check(TokenType::KW_BOOL)) {
      string castType;
      if (match(TokenType::KW_INT))
        castType = "int";
      else if (match(TokenType::KW_FLOAT))
        castType = "float";
      else if (match(TokenType::KW_CHAR))
        castType = "char";
      else if (match(TokenType::KW_DOUBLE))
        castType = "double";
      else if (match(TokenType::KW_BOOL))
        castType = "bool";
      consume(TokenType::DELIM_RPAREN, "Expected ')' after cast type");
      ExpressionPtr operand = parseUnary();
      return std::make_shared<CastExpression>(castType, operand);
    } else {
      // Not a cast; treat as a parenthesised expression.
      ExpressionPtr expr = parseExpression();
      consume(TokenType::DELIM_RPAREN, "Expected ')' after expression");
      return expr;
    }
  }
  return parsePostfix();
}

// Postfix (handles postfix ++/--)
ExpressionPtr Parser::parsePostfix() {
  ExpressionPtr expr = parsePrimary();
  while (!isAtEnd()) {
    if (match(TokenType::DOT)) {
      // Expect an identifier after the dot.
      if (!check(TokenType::IDENTIFIER))
        error("Expected identifier after '.' for member access");
      Token memberToken = advance();
      string memberName = memberToken.lexeme;
      expr = std::make_shared<MemberAccess>(expr, memberName);
    }
    // Array indexing support: parse '[' expression ']'
    else if (match(TokenType::DELIM_LBRACKET)) {
      ExpressionPtr indexExpr = parseExpression();
      consume(TokenType::DELIM_RBRACKET, "Expected ']' after array index");
      expr = std::make_shared<ArrayAccess>(expr, indexExpr);
    } else if (current + 1 < tokens.size() &&
               tokens[current].type == TokenType::OP_PLUS &&
               tokens[current + 1].type == TokenType::OP_PLUS) {
      advance();
      advance();
      expr = std::make_shared<PostfixExpression>(expr, "++");
    } else if (current + 1 < tokens.size() &&
               tokens[current].type == TokenType::OP_MINUS &&
               tokens[current + 1].type == TokenType::OP_MINUS) {
      advance();
      advance();
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
    char value = tokens[current - 1].lexeme[0];
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
  error("Expected expression");
  return nullptr;
}
