#include "AST.hpp"
#include "Debug.hpp"
#include "Parser.hpp"
#include "TypeRegistry.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

using std::runtime_error;
using std::string;
using std::vector;

ExpressionPtr Parser::parseExpression() {
  std::string startLex = peek().lexeme;
  ExpressionPtr expr = parseAssignment();
  while (match(TokenType::DELIM_COMMA)) {
    ExpressionPtr rhs = parseAssignment();
    expr = std::make_shared<BinaryExpression>(",", expr, rhs);
  }
  if (educcDebugEnabled())
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

  TokenType t = peek().type;
  if (!isAtEnd() &&
      (t == TokenType::OP_PLUS_ASSIGN || t == TokenType::OP_MINUS_ASSIGN ||
       t == TokenType::OP_MULTIPLY_ASSIGN || t == TokenType::OP_DIVIDE_ASSIGN ||
       t == TokenType::OP_MODULO_ASSIGN ||
       t == TokenType::OP_BITWISE_AND_ASSIGN ||
       t == TokenType::OP_BITWISE_OR_ASSIGN ||
       t == TokenType::OP_BITWISE_XOR_ASSIGN ||
       t == TokenType::OP_LEFT_SHIFT_ASSIGN ||
       t == TokenType::OP_RIGHT_SHIFT_ASSIGN)) {
    Token opToken = advance();
    ExpressionPtr rhs = parseAssignment();
    string op;
    switch (opToken.type) {
    case TokenType::OP_PLUS_ASSIGN:
      op = "+";
      break;
    case TokenType::OP_MINUS_ASSIGN:
      op = "-";
      break;
    case TokenType::OP_MULTIPLY_ASSIGN:
      op = "*";
      break;
    case TokenType::OP_DIVIDE_ASSIGN:
      op = "/";
      break;
    case TokenType::OP_MODULO_ASSIGN:
      op = "%";
      break;
    case TokenType::OP_BITWISE_AND_ASSIGN:
      op = "&";
      break;
    case TokenType::OP_BITWISE_OR_ASSIGN:
      op = "|";
      break;
    case TokenType::OP_BITWISE_XOR_ASSIGN:
      op = "^";
      break;
    case TokenType::OP_LEFT_SHIFT_ASSIGN:
      op = "<<";
      break;
    case TokenType::OP_RIGHT_SHIFT_ASSIGN:
      op = ">>";
      break;
    default:
      op = opToken.lexeme;
      break;
    }
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
        peek().lexeme == "short" || peek().lexeme == "long" ||
        peek().lexeme == "unsigned" || peek().lexeme == "signed" ||
        peek().lexeme == "struct" || peek().lexeme == "union" ||
        isTypedefName(peek().lexeme) || peek().lexeme == "size_t" ||
        peek().lexeme == "uintptr_t" || peek().lexeme == "intptr_t" ||
        peek().lexeme == "ptrdiff_t" || peek().lexeme == "ssize_t" ||
        peek().lexeme == "uint8_t" || peek().lexeme == "uint16_t" ||
        peek().lexeme == "uint32_t" || peek().lexeme == "uint64_t" ||
        peek().lexeme == "int8_t" || peek().lexeme == "int16_t" ||
        peek().lexeme == "int32_t" || peek().lexeme == "int64_t") {
      std::string castType =
          parseSimpleType(*this, hasConst, hasStatic, hasVolatile);
      std::vector<ExpressionPtr> dimensions;
      while (match(TokenType::DELIM_LBRACKET)) {
        ExpressionPtr dimExpr = nullptr;
        if (!check(TokenType::DELIM_RBRACKET))
          dimExpr = parseExpression();
        consume(TokenType::DELIM_RBRACKET, "Expected ']' after array size");
        dimensions.push_back(dimExpr);
      }
      while (match(TokenType::OP_MULTIPLY))
        castType += "*";
      if (match(TokenType::DELIM_RPAREN)) {
        if (check(TokenType::DELIM_LBRACE)) {
          ExpressionPtr initList = parseInitializerList();
          return std::make_shared<CompoundLiteral>(castType, dimensions,
                                                   initList);
        }
        ExpressionPtr operand = parseUnary();
        return std::make_shared<CastExpression>(castType, operand);
      }
    }
    current = save; // Not a cast; rewind and parse normally.
  }
  // Handle prefix increment/decrement
  if (match(TokenType::OP_PLUS_PLUS)) {
    ExpressionPtr operand = parseUnary();
    return std::make_shared<UnaryExpression>("++", operand);
  }
  if (match(TokenType::OP_MINUS_MINUS)) {
    ExpressionPtr operand = parseUnary();
    return std::make_shared<UnaryExpression>("--", operand);
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
          args.push_back(parseAssignment());
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
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] (parsePrimary) peek type="
              << static_cast<int>(peek().type) << " lexeme='" << peek().lexeme
              << "'\n";
  if (match(TokenType::LITERAL_INT)) {
    std::string rawLexeme = tokens[current - 1].lexeme;
    std::string core = rawLexeme;
    bool hasU = false;
    int longCount = 0;
    // Peel off suffixes from the end to keep the core digits intact.
    while (!core.empty()) {
      char last = core.back();
      if (last == 'u' || last == 'U') {
        hasU = true;
        core.pop_back();
      } else if (last == 'l' || last == 'L') {
        longCount++;
        core.pop_back();
      } else {
        break;
      }
    }
    bool isBinary = core.rfind("0b", 0) == 0 || core.rfind("0B", 0) == 0;
    unsigned long long uvalue = 0;
    try {
      if (isBinary)
        uvalue = std::stoull(core.substr(2), nullptr, 2);
      else
        uvalue = std::stoull(core, nullptr, 0);
    } catch (...) {
      uvalue = 0;
    }

    auto setTypeForUnsigned =
        [&](unsigned long long limitInt, unsigned long long limitLong,
            unsigned long long limitLL, int longs) -> std::string {
      (void)limitLL;
      if (longs >= 2)
        return "unsigned long long";
      if (longs == 1)
        return "unsigned long";
      if (uvalue <= limitInt)
        return "unsigned int";
      if (uvalue <= limitLong)
        return "unsigned long";
      return "unsigned long long";
    };

    auto setTypeForSigned = [&](unsigned long long limitInt,
                                unsigned long long limitLong,
                                unsigned long long limitLL, int longs,
                                bool isDecimal) -> std::string {
      (void)limitLL;
      if (longs >= 2)
        return hasU ? "unsigned long long" : "long long";
      if (longs == 1)
        return hasU ? "unsigned long" : "long";
      if (hasU) {
        if (uvalue <= limitInt)
          return "unsigned int";
        if (uvalue <= limitLong)
          return "unsigned long";
        return "unsigned long long";
      }
      if (isDecimal) {
        if (uvalue <= limitInt)
          return "int";
        if (uvalue <= limitLong)
          return "long";
        return "long long";
      } else {
        if (uvalue <= limitInt)
          return "int";
        if (uvalue <= std::numeric_limits<unsigned int>::max())
          return "unsigned int";
        if (uvalue <= limitLong)
          return "long";
        if (uvalue <= std::numeric_limits<unsigned long>::max())
          return "unsigned long";
        return "long long";
      }
    };

    bool isDecimal = !(core.rfind("0x", 0) == 0 || core.rfind("0X", 0) == 0 ||
                       core.rfind("0b", 0) == 0 || core.rfind("0B", 0) == 0 ||
                       (core.size() > 1 && core[0] == '0'));

    unsigned long long intMaxU =
        static_cast<unsigned long long>(std::numeric_limits<int>::max());
    unsigned long long longMaxU =
        static_cast<unsigned long long>(std::numeric_limits<long>::max());
    unsigned long long llMaxU =
        static_cast<unsigned long long>(std::numeric_limits<long long>::max());

    std::string litType;
    if (hasU) {
      litType = setTypeForUnsigned(
          static_cast<unsigned long long>(
              std::numeric_limits<unsigned int>::max()),
          static_cast<unsigned long long>(
              std::numeric_limits<unsigned long>::max()),
          static_cast<unsigned long long>(
              std::numeric_limits<unsigned long long>::max()),
          longCount);
    } else {
      litType =
          setTypeForSigned(intMaxU, longMaxU, llMaxU, longCount, isDecimal);
    }

    long long value = static_cast<long long>(
        uvalue); // will preserve bit pattern for 32/64-bit
    auto lit = std::make_shared<Literal>(value, rawLexeme, litType,
                                         litType.find("unsigned") !=
                                             std::string::npos);
    lit->uintValue = uvalue;
    return lit;
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
    auto unescape = [](const string &raw) {
      string out;
      for (size_t i = 0; i < raw.size(); ++i) {
        char c = raw[i];
        if (c == '\\' && i + 1 < raw.size()) {
          char esc = raw[++i];
          switch (esc) {
          case 'n':
            out.push_back('\n');
            break;
          case 't':
            out.push_back('\t');
            break;
          case 'r':
            out.push_back('\r');
            break;
          case '\\':
            out.push_back('\\');
            break;
          case '"':
            out.push_back('"');
            break;
          case '\'':
            out.push_back('\'');
            break;
          default:
            out.push_back(esc);
            break;
          }
        } else {
          out.push_back(c);
        }
      }
      return out;
    };
    string value = unescape(stripQuotes(tokens[current - 1].lexeme));
    while (check(TokenType::LITERAL_STRING)) {
      advance();
      value += unescape(stripQuotes(tokens[current - 1].lexeme));
    }
    return std::make_shared<Literal>(value);
  }
  if (match(TokenType::IDENTIFIER)) {
    string name = tokens[current - 1].lexeme;
    if (name == "__func__" && !currentFunctionName.empty()) {
      auto lit = std::make_shared<Literal>(currentFunctionName);
      return lit;
    }
    if ((name == "__builtin_va_arg" || name == "va_arg") &&
        match(TokenType::DELIM_LPAREN)) {
      ExpressionPtr listExpr = parseAssignment();
      consume(TokenType::DELIM_COMMA, "Expected ',' after va_list argument");
      bool hasConst = false, hasStatic = false, hasVolatile = false;
      std::string typeName =
          parseSimpleType(*this, hasConst, hasStatic, hasVolatile);
      while (match(TokenType::OP_MULTIPLY))
        typeName += "*";
      consume(TokenType::DELIM_RPAREN, "Expected ')' after __builtin_va_arg");
      auto typeIdent = std::make_shared<Identifier>(typeName);
      return std::make_shared<FunctionCall>(
          name == "va_arg" ? "__builtin_va_arg" : name,
          std::vector<ExpressionPtr>{listExpr, typeIdent});
    }
    if (name == "_Generic") {
      consume(TokenType::DELIM_LPAREN, "Expected '(' after _Generic");
      ExpressionPtr selector = parseAssignment();
      consume(TokenType::DELIM_COMMA,
              "Expected ',' after _Generic controlling expression");
      std::vector<std::pair<std::string, ExpressionPtr>> associations;
      std::optional<ExpressionPtr> defaultExpr = std::nullopt;
      while (true) {
        if (peek().lexeme == "default") {
          advance();
          consume(TokenType::DELIM_COLON, "Expected ':' after default");
          defaultExpr = parseAssignment();
        } else {
          bool hasConst = false, hasStatic = false, hasVolatile = false;
          std::string assocType =
              parseSimpleType(*this, hasConst, hasStatic, hasVolatile);
          while (match(TokenType::OP_MULTIPLY))
            assocType += "*";
          consume(TokenType::DELIM_COLON,
                  "Expected ':' after generic association type");
          ExpressionPtr assocExpr = parseAssignment();
          associations.emplace_back(assocType, assocExpr);
        }
        if (!match(TokenType::DELIM_COMMA))
          break;
      }
      consume(TokenType::DELIM_RPAREN, "Expected ')' after _Generic");
      return std::make_shared<GenericSelection>(selector, associations,
                                                defaultExpr);
    }
    if (name == "alignof" || name == "_Alignof") {
      consume(TokenType::DELIM_LPAREN, "Expected '(' after alignof");
      size_t save = current;
      bool hasConst = false, hasStatic = false, hasVolatile = false;
      std::string typeName =
          parseSimpleType(*this, hasConst, hasStatic, hasVolatile);
      if (match(TokenType::DELIM_RPAREN)) {
        return std::make_shared<AlignOfExpression>(typeName);
      }
      current = save;
      ExpressionPtr operand = parseExpression();
      consume(TokenType::DELIM_RPAREN, "Expected ')' after alignof operand");
      return std::make_shared<AlignOfExpression>(operand);
    }
    if (name == "true") {
      return std::make_shared<Literal>(true);
    }
    if (name == "false") {
      return std::make_shared<Literal>(false);
    }
    if (name == "INFINITY") {
      auto lit =
          std::make_shared<Literal>(std::numeric_limits<double>::infinity());
      lit->rawLexeme = name;
      return lit;
    }
    if (name == "NAN" || name == "nan") {
      auto lit =
          std::make_shared<Literal>(std::numeric_limits<double>::quiet_NaN());
      lit->rawLexeme = name;
      return lit;
    }
    if (name == "DBL_MIN") {
      auto lit = std::make_shared<Literal>(std::numeric_limits<double>::min());
      lit->rawLexeme = name;
      return lit;
    }
    if (name == "DBL_MAX") {
      auto lit = std::make_shared<Literal>(std::numeric_limits<double>::max());
      lit->rawLexeme = name;
      return lit;
    }
    if (name == "FLT_MIN") {
      auto lit = std::make_shared<Literal>(std::numeric_limits<float>::min());
      lit->rawLexeme = name;
      return lit;
    }
    if (name == "FLT_MAX") {
      auto lit = std::make_shared<Literal>(std::numeric_limits<float>::max());
      lit->rawLexeme = name;
      return lit;
    }
    if (name == "FP_NAN") {
      return std::make_shared<Literal>(1);
    }
    if (name == "FP_INFINITE") {
      return std::make_shared<Literal>(2);
    }
    if (name == "FP_ZERO") {
      return std::make_shared<Literal>(3);
    }
    if (name == "FP_SUBNORMAL") {
      return std::make_shared<Literal>(5);
    }
    if (name == "FP_NORMAL") {
      return std::make_shared<Literal>(4);
    }
    if (match(TokenType::DELIM_LPAREN)) {
      vector<ExpressionPtr> args;
      if (!check(TokenType::DELIM_RPAREN)) {
        do {
          args.push_back(parseAssignment());
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
    bool hasParen = match(TokenType::DELIM_LPAREN);
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
        if (typeName == "long" && check(TokenType::IDENTIFIER) &&
            peek().lexeme == "long") {
          advance();
          typeName = "long long";
        }
      } else if (check(TokenType::IDENTIFIER) &&
                 (peek().lexeme == "size_t" || peek().lexeme == "uintptr_t" ||
                  peek().lexeme == "intptr_t" || peek().lexeme == "ptrdiff_t" ||
                  peek().lexeme == "ssize_t" || peek().lexeme == "uint8_t" ||
                  peek().lexeme == "uint16_t" || peek().lexeme == "uint32_t" ||
                  peek().lexeme == "uint64_t" || peek().lexeme == "int8_t" ||
                  peek().lexeme == "int16_t" || peek().lexeme == "int32_t" ||
                  peek().lexeme == "int64_t" ||
                  peek().lexeme == "max_align_t")) {
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
    if (hasParen && parseTypeName(parsedType)) {
      consume(TokenType::DELIM_RPAREN, "Expected ')' after sizeof type");
      return std::make_shared<SizeOfExpression>(parsedType);
    }
    current = beforeType;
    // sizeof(expression)
    ExpressionPtr operand = parseExpression();
    if (hasParen)
      consume(TokenType::DELIM_RPAREN, "Expected ')' after sizeof expression");
    return std::make_shared<SizeOfExpression>(operand);
  }
  error("Expected expression");
  return nullptr;
}
