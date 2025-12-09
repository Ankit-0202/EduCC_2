#include "AST.hpp"
#include "Debug.hpp"
#include "Parser.hpp"
#include "TypeRegistry.hpp"
#include <iostream> // For debug printing if needed
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

using std::optional;
using std::runtime_error;
using std::string;
using std::vector;

static std::shared_ptr<StructDeclaration>
parseStructDefinition(Parser &parser, std::optional<std::string> tag);
static std::string consumePointerTokens(Parser &parser,
                                        const std::string &baseType);
static int anonymousStructCounter = 0;
static int anonymousUnionCounter = 0;

bool isIntLiteral(const ExpressionPtr &expr, int &value) {
  if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
    if (lit->type == Literal::LiteralType::Int) {
      value = lit->intValue;
      return true;
    }
  }
  return false;
}

std::string appendArrayToType(Parser &parser, const std::string &baseType,
                              const std::vector<ExpressionPtr> &dims) {
  std::string type = baseType;
  auto dimToString = [](const ExpressionPtr &expr) -> std::string {
    if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
      if (lit->type == Literal::LiteralType::Int)
        return std::to_string(lit->intValue);
    }
    if (auto id = std::dynamic_pointer_cast<Identifier>(expr))
      return id->name;
    return "";
  };
  for (const auto &dim : dims) {
    std::string asStr = dimToString(dim);
    type += "[" + asStr + "]";
  }
  return type;
}

bool tokenIsTypedefName(const Token &tok) {
  return tok.type == TokenType::IDENTIFIER && isTypedefName(tok.lexeme);
}

std::string
parseSimpleType(Parser &parser, bool &hasConstQualifier,
                bool &hasStaticQualifier, bool &hasVolatileQualifier,
                std::shared_ptr<StructDeclaration> *inlineStructDecl,
                std::shared_ptr<UnionDeclaration> *inlineUnionDecl) {
  bool sawUnsigned = false;
  bool sawSigned = false;
  bool sawAtomic = false;
  while (!parser.isAtEnd() && parser.check(TokenType::IDENTIFIER)) {
    std::string lex = parser.peek().lexeme;
    if (lex == "__attribute__") {
      parser.advance();
      if (parser.match(TokenType::DELIM_LPAREN)) {
        int depth = 1;
        while (depth > 0 && !parser.isAtEnd()) {
          Token t = parser.advance();
          if (t.type == TokenType::DELIM_LPAREN)
            depth++;
          else if (t.type == TokenType::DELIM_RPAREN)
            depth--;
        }
      }
      continue;
    }
    if (lex == "_Atomic") {
      parser.advance();
      sawAtomic = true;
      if (parser.match(TokenType::DELIM_LPAREN)) {
        bool innerConst = false, innerStatic = false, innerVolatile = false;
        std::string inner =
            parseSimpleType(parser, innerConst, innerStatic, innerVolatile);
        parser.consume(TokenType::DELIM_RPAREN,
                       "Expected ')' after _Atomic type-specifier");
        if (innerConst)
          inner = "const " + inner;
        if (innerVolatile)
          inner = "volatile " + inner;
        if (innerStatic)
          inner = "static " + inner;
        return "_Atomic " + inner;
      }
      continue;
    }
    if (lex == "alignas" || lex == "_Alignas") {
      parser.advance();
      parser.consume(TokenType::DELIM_LPAREN, "Expected '(' after alignas");
      ExpressionPtr alignExpr = parser.parseExpression();
      if (auto lit = std::dynamic_pointer_cast<Literal>(alignExpr)) {
        if (lit->type == Literal::LiteralType::Int && lit->intValue > 0) {
          parser.pendingAlignment = lit->intValue;
        }
      }
      parser.consume(TokenType::DELIM_RPAREN, "Expected ')' after alignas");
      continue;
    }
    if (lex == "_Noreturn") {
      parser.advance();
      continue;
    }
    if (lex == "_Thread_local") {
      parser.advance();
      hasStaticQualifier = true;
      continue;
    }
    if (lex == "const") {
      hasConstQualifier = true;
      parser.advance();
      continue;
    }
    if (lex == "static") {
      hasStaticQualifier = true;
      parser.advance();
      continue;
    }
    if (lex == "extern") {
      parser.advance();
      continue;
    }
    if (lex == "inline") {
      parser.advance();
      continue;
    }
    if (lex == "volatile") {
      hasVolatileQualifier = true;
      parser.advance();
      continue;
    }
    if (lex == "unsigned") {
      sawUnsigned = true;
      parser.advance();
      continue;
    }
    if (lex == "signed") {
      sawSigned = true;
      parser.advance();
      continue;
    }
    break;
  }

  string baseType;
  if (parser.match(TokenType::KW_INT))
    baseType = "int";
  else if (parser.match(TokenType::KW_FLOAT))
    baseType = "float";
  else if (parser.match(TokenType::KW_CHAR))
    baseType = "char";
  else if (parser.match(TokenType::KW_DOUBLE))
    baseType = "double";
  else if (parser.match(TokenType::KW_BOOL))
    baseType = "bool";
  else if (parser.match(TokenType::KW_VOID))
    baseType = "void";
  else if (parser.check(TokenType::IDENTIFIER) &&
           (parser.peek().lexeme == "double" ||
            parser.peek().lexeme == "float" ||
            parser.peek().lexeme == "void")) {
    baseType = parser.advance().lexeme;
  } else if (parser.check(TokenType::IDENTIFIER) &&
             (parser.peek().lexeme == "long" ||
              parser.peek().lexeme == "short")) {
    baseType = parser.advance().lexeme;
    if (baseType == "long" && parser.check(TokenType::IDENTIFIER) &&
        parser.peek().lexeme == "long") {
      parser.advance();
      baseType = "long long";
    }
    if (baseType == "long" &&
        ((parser.check(TokenType::IDENTIFIER) &&
          parser.peek().lexeme == "double") ||
         parser.check(TokenType::KW_DOUBLE))) {
      parser.advance();
      baseType = "long double";
    }
  } else if (parser.peek().lexeme == "size_t" ||
             parser.peek().lexeme == "uintptr_t" ||
             parser.peek().lexeme == "intptr_t" ||
             parser.peek().lexeme == "ptrdiff_t" ||
             parser.peek().lexeme == "ssize_t" ||
             parser.peek().lexeme == "max_align_t" ||
             parser.peek().lexeme == "uint8_t" ||
             parser.peek().lexeme == "uint16_t" ||
             parser.peek().lexeme == "uint32_t" ||
             parser.peek().lexeme == "uint64_t" ||
             parser.peek().lexeme == "int8_t" ||
             parser.peek().lexeme == "int16_t" ||
             parser.peek().lexeme == "int32_t" ||
             parser.peek().lexeme == "int64_t" ||
             parser.peek().lexeme == "__builtin_va_list" ||
             parser.peek().lexeme == "va_list") {
    baseType = parser.advance().lexeme;
  } else if (parser.check(TokenType::KW_STRUCT) ||
             (parser.check(TokenType::IDENTIFIER) &&
              parser.peek().lexeme == "struct")) {
    parser.advance(); // consume 'struct'
    auto skipAttributes = [&parser]() {
      while (parser.check(TokenType::IDENTIFIER) &&
             parser.peek().lexeme == "__attribute__") {
        parser.advance();
        parser.consume(TokenType::DELIM_LPAREN,
                       "Expected '(' after __attribute__");
        int depth = 1;
        while (depth > 0 && !parser.isAtEnd()) {
          Token t = parser.advance();
          if (t.lexeme == "packed")
            parser.structPackedFlag = true;
          if (t.type == TokenType::DELIM_LPAREN)
            depth++;
          else if (t.type == TokenType::DELIM_RPAREN)
            depth--;
        }
      }
    };
    skipAttributes();
    std::optional<string> tag = std::nullopt;
    if (parser.check(TokenType::IDENTIFIER) &&
        parser.current + 1 < parser.tokens.size() &&
        parser.tokens[parser.current + 1].type == TokenType::DELIM_LBRACE) {
      tag = parser.advance().lexeme;
    }
    if (parser.check(TokenType::DELIM_LBRACE)) {
      auto structDecl = parseStructDefinition(parser, tag);
      if (inlineStructDecl)
        *inlineStructDecl = structDecl;
      baseType = "struct " + structDecl->tag.value();
    } else {
      skipAttributes();
      if (!parser.check(TokenType::IDENTIFIER))
        parser.error("Expected struct tag after 'struct'");
      string tagName = parser.advance().lexeme;
      baseType = "struct " + tagName;
    }
    parser.structPackedFlag = false;
  } else if (parser.check(TokenType::KW_UNION) ||
             (parser.check(TokenType::IDENTIFIER) &&
              parser.peek().lexeme == "union")) {
    parser.advance(); // consume 'union'
    std::optional<string> tag = std::nullopt;
    if (parser.check(TokenType::IDENTIFIER) &&
        parser.current + 1 < parser.tokens.size() &&
        parser.tokens[parser.current + 1].type == TokenType::DELIM_LBRACE) {
      tag = parser.advance().lexeme;
    }
    if (parser.check(TokenType::DELIM_LBRACE)) {
      parser.consume(TokenType::DELIM_LBRACE,
                     "Expected '{' to begin union declaration");
      vector<std::shared_ptr<VariableDeclaration>> unionMembers;
      while (!parser.check(TokenType::DELIM_RBRACE) && !parser.isAtEnd()) {
        unionMembers.push_back(parser.parseUnionMemberDeclaration());
      }
      parser.consume(TokenType::DELIM_RBRACE,
                     "Expected '}' to close union declaration");
      string generatedTag =
          tag.has_value() ? tag.value()
                          : ("__anon_union_" +
                             std::to_string(anonymousUnionCounter++));
      auto unionDecl =
          std::make_shared<UnionDeclaration>(generatedTag, unionMembers);
      if (inlineUnionDecl)
        *inlineUnionDecl = unionDecl;
      baseType = "union " + generatedTag;
    } else {
      if (!parser.check(TokenType::IDENTIFIER))
        parser.error("Expected union tag after 'union'");
      string tagName = parser.advance().lexeme;
      baseType = "union " + tagName;
    }
  } else if (parser.check(TokenType::KW_ENUM) ||
             (parser.check(TokenType::IDENTIFIER) &&
              parser.peek().lexeme == "enum")) {
    parser.advance(); // consume 'enum'
    if (!parser.check(TokenType::IDENTIFIER))
      parser.error("Expected enum tag after 'enum'");
    string tag = parser.advance().lexeme;
    baseType = "enum " + tag;
  } else if (tokenIsTypedefName(parser.peek())) {
    string alias = parser.advance().lexeme;
    TypedefInfo info = resolveTypedef(alias);
    baseType = info.underlyingType.empty() ? alias : info.underlyingType;
    if (!info.dimensions.empty())
      baseType = appendArrayToType(parser, baseType, info.dimensions);
    if (info.isFunctionPointer && baseType.rfind("fnptr:", 0) != 0)
      baseType = makeFunctionPointerType(baseType, info.functionParamTypes);
  } else {
    parser.error("Expected type specifier in declaration");
  }
  if (!baseType.empty() &&
      (baseType.find("float") != string::npos ||
       baseType.find("double") != string::npos) &&
      parser.check(TokenType::IDENTIFIER) &&
      (parser.peek().lexeme == "complex" ||
       parser.peek().lexeme == "_Complex")) {
    parser.advance();
    baseType += " complex";
  }

  if (sawUnsigned)
    baseType = "unsigned " + baseType;
  else if (sawSigned)
    baseType = "signed " + baseType;
  if (hasConstQualifier)
    baseType = "const " + baseType;
  if (hasVolatileQualifier)
    baseType = "volatile " + baseType;
  if (hasStaticQualifier)
    baseType = "static " + baseType;
  if (sawAtomic)
    baseType = "_Atomic " + baseType;
  return baseType;
}

std::vector<std::string> parseParameterTypeList(Parser &parser);

ParsedDeclarator parseDeclarator(Parser &parser, const std::string &baseType,
                                 bool requireName) {
  ParsedDeclarator result;
  bool sawEmptyArrayDimension = false;

  auto skipAttributes = [&parser]() {
    while (parser.check(TokenType::IDENTIFIER) &&
           parser.peek().lexeme == "__attribute__") {
      parser.advance();
      parser.consume(TokenType::DELIM_LPAREN,
                     "Expected '(' after __attribute__");
      int depth = 1;
      while (depth > 0 && !parser.isAtEnd()) {
        Token t = parser.advance();
        if (t.type == TokenType::DELIM_LPAREN)
          depth++;
        else if (t.type == TokenType::DELIM_RPAREN)
          depth--;
      }
    }
  };

  size_t outerPointerCount = 0;
  while (parser.match(TokenType::OP_MULTIPLY)) {
    outerPointerCount++;
    while (!parser.isAtEnd() && parser.check(TokenType::IDENTIFIER)) {
      string lex = parser.peek().lexeme;
      if (lex == "const" || lex == "volatile" || lex == "static" ||
          lex == "restrict") {
        parser.advance();
        continue;
      }
      break;
    }
  }

  skipAttributes();

  if (!parser.check(TokenType::IDENTIFIER) &&
      !parser.check(TokenType::DELIM_LPAREN)) {
    if (!requireName) {
      result.type = baseType + string(outerPointerCount, '*');
      result.hasEmptyArrayDimension = sawEmptyArrayDimension;
      return result;
    }
    parser.error("Expected identifier after type/pointer specifiers");
  }

  if (parser.match(TokenType::DELIM_LPAREN)) {
    size_t pointerCount = 0;
    while (parser.match(TokenType::OP_MULTIPLY)) {
      pointerCount++;
      while (!parser.isAtEnd() && parser.check(TokenType::IDENTIFIER)) {
        string lex = parser.peek().lexeme;
        if (lex == "const" || lex == "volatile" || lex == "static" ||
            lex == "restrict") {
          parser.advance();
          continue;
        }
        break;
      }
    }
    skipAttributes();
    if (parser.check(TokenType::IDENTIFIER)) {
      result.name = parser.advance().lexeme;
    } else if (requireName) {
      parser.error("Expected identifier in declarator");
    }

    vector<ExpressionPtr> innerDims;
    while (parser.match(TokenType::DELIM_LBRACKET)) {
      if (parser.check(TokenType::DELIM_RBRACKET)) {
        parser.advance();
        sawEmptyArrayDimension = true;
      } else {
        ExpressionPtr dimExpr = parser.parseExpression();
        parser.consume(TokenType::DELIM_RBRACKET,
                       "Expected ']' after array dimension");
        innerDims.push_back(dimExpr);
      }
    }

    parser.consume(TokenType::DELIM_RPAREN, "Expected ')' in declarator");

    if (parser.match(TokenType::DELIM_LPAREN)) {
      auto paramTypes = parseParameterTypeList(parser);
      parser.consume(TokenType::DELIM_RPAREN,
                     "Expected ')' after parameter list");
      string fnType = makeFunctionPointerType(baseType, paramTypes);
      if (pointerCount > 1)
        fnType += string(pointerCount - 1, '*');
      result.type = fnType;
      result.isFunctionPointer = true;
      result.functionParamTypes = paramTypes;
      result.dimensions = innerDims;
      result.hasEmptyArrayDimension = sawEmptyArrayDimension;
      if (outerPointerCount > 0)
        result.type += string(outerPointerCount, '*');
      return result;
    }

    vector<ExpressionPtr> outerDims;
    while (parser.match(TokenType::DELIM_LBRACKET)) {
      if (parser.check(TokenType::DELIM_RBRACKET)) {
        parser.advance();
        sawEmptyArrayDimension = true;
      } else {
        ExpressionPtr dimExpr = parser.parseExpression();
        parser.consume(TokenType::DELIM_RBRACKET,
                       "Expected ']' after array dimension");
        outerDims.push_back(dimExpr);
      }
    }

    if (!outerDims.empty()) {
      string typeWithArrays = appendArrayToType(parser, baseType, outerDims);
      typeWithArrays += string(pointerCount, '*');
      if (outerPointerCount > 0)
        typeWithArrays += string(outerPointerCount, '*');
      result.type = typeWithArrays;
      result.dimensions = innerDims;
      result.hasEmptyArrayDimension = sawEmptyArrayDimension;
      return result;
    }

    result.type = baseType + string(pointerCount + outerPointerCount, '*');
    result.dimensions = innerDims;
    result.hasEmptyArrayDimension = sawEmptyArrayDimension;
    return result;
  }

  if (parser.check(TokenType::IDENTIFIER)) {
    result.name = parser.advance().lexeme;
  } else if (requireName) {
    parser.error("Expected identifier after type/pointer specifiers");
  }

  while (parser.match(TokenType::DELIM_LBRACKET)) {
    if (parser.check(TokenType::DELIM_RBRACKET)) {
      parser.advance();
      sawEmptyArrayDimension = true;
    } else {
      ExpressionPtr dimExpr = parser.parseExpression();
      parser.consume(TokenType::DELIM_RBRACKET,
                     "Expected ']' after array dimension");
      result.dimensions.push_back(dimExpr);
    }
  }

  result.type = baseType + string(outerPointerCount, '*');
  result.hasEmptyArrayDimension = sawEmptyArrayDimension;
  return result;
}

std::vector<std::string> parseParameterTypeList(Parser &parser) {
  std::vector<std::string> params;
  if (parser.check(TokenType::DELIM_RPAREN))
    return params;
  do {
    bool hasConst = false;
    bool hasStatic = false;
    bool hasVolatile = false;
    string paramBase =
        parseSimpleType(parser, hasConst, hasStatic, hasVolatile);
    ParsedDeclarator decl = parseDeclarator(parser, paramBase, false);
    string paramType = appendArrayToType(parser, decl.type, decl.dimensions);
    params.push_back(paramType);
  } while (parser.match(TokenType::DELIM_COMMA));
  return params;
}

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

static std::shared_ptr<StructDeclaration>
parseStructDefinition(Parser &parser, std::optional<std::string> tag) {
  parser.consume(TokenType::DELIM_LBRACE,
                 "Expected '{' to begin struct declaration");
  bool isPackedStruct = parser.structPackedFlag;
  vector<std::shared_ptr<VariableDeclaration>> members;
  vector<std::shared_ptr<UnionDeclaration>> nestedUnions;
  vector<std::shared_ptr<StructDeclaration>> nestedStructs;
  while (!parser.check(TokenType::DELIM_RBRACE) && !parser.isAtEnd()) {
    string memberType;
    bool hasConst = false;
    bool hasStatic = false;
    bool hasVolatile = false;
    bool sawUnsigned = false;
    bool sawSigned = false;
    std::vector<ExpressionPtr> typedefDims;
    while (!parser.isAtEnd() && parser.check(TokenType::IDENTIFIER)) {
      std::string lex = parser.peek().lexeme;
      if (lex == "const") {
        hasConst = true;
        parser.advance();
        continue;
      }
      if (lex == "static") {
        hasStatic = true;
        parser.advance();
        continue;
      }
      if (lex == "extern") {
        parser.advance();
        continue;
      }
      if (lex == "inline") {
        parser.advance();
        continue;
      }
      if (lex == "volatile") {
        hasVolatile = true;
        parser.advance();
        continue;
      }
      if (lex == "unsigned") {
        sawUnsigned = true;
        parser.advance();
        continue;
      }
      if (lex == "signed") {
        sawSigned = true;
        parser.advance();
        continue;
      }
      if (lex == "alignas" || lex == "_Alignas") {
        parser.advance();
        parser.consume(TokenType::DELIM_LPAREN, "Expected '(' after alignas");
        ExpressionPtr alignExpr = parser.parseExpression();
        if (auto lit = std::dynamic_pointer_cast<Literal>(alignExpr)) {
          if (lit->type == Literal::LiteralType::Int && lit->intValue > 0)
            parser.pendingAlignment = lit->intValue;
        }
        parser.consume(TokenType::DELIM_RPAREN, "Expected ')' after alignas");
        continue;
      }
      break;
    }
    bool isInlineUnion = false;
    bool isAnonymousUnionField = false;
    bool isInlineStruct = false;
    bool isAnonymousStructField = false;
    std::shared_ptr<StructDeclaration> inlineStructDecl = nullptr;
    std::shared_ptr<UnionDeclaration> inlineUnionDecl = nullptr;
    if ((parser.check(TokenType::KW_STRUCT)) ||
        (parser.check(TokenType::IDENTIFIER) &&
         parser.peek().lexeme == "struct")) {
      parser.advance(); // consume "struct"
      optional<string> mtag = std::nullopt;
      if (parser.check(TokenType::IDENTIFIER))
        mtag = parser.advance().lexeme;
      if (parser.check(TokenType::DELIM_LBRACE)) {
        auto nestedStruct = parseStructDefinition(parser, mtag);
        if (!nestedStruct->tag.has_value()) {
          nestedStruct->tag =
              "__anon_struct_" + std::to_string(anonymousStructCounter++);
        }
        inlineStructDecl = nestedStruct;
        nestedStructs.push_back(nestedStruct);
        memberType = "struct " + nestedStruct->tag.value();
        isInlineStruct = true;
      } else if (mtag.has_value()) {
        memberType = "struct " + mtag.value();
      } else {
        parser.error(
            "Expected struct tag after 'struct' in member declaration");
      }
    } else if (parser.check(TokenType::KW_UNION) ||
               (parser.check(TokenType::IDENTIFIER) &&
                parser.peek().lexeme == "union")) {
      parser.advance(); // consume identifier lexeme "union"
      optional<string> utag = std::nullopt;
      if (parser.check(TokenType::IDENTIFIER))
        utag = parser.advance().lexeme;

      if (parser.check(TokenType::DELIM_LBRACE)) {
        parser.consume(TokenType::DELIM_LBRACE,
                       "Expected '{' to begin union declaration in struct");
        vector<std::shared_ptr<VariableDeclaration>> unionMembers;
        while (!parser.check(TokenType::DELIM_RBRACE) && !parser.isAtEnd()) {
          unionMembers.push_back(parser.parseUnionMemberDeclaration());
        }
        parser.consume(TokenType::DELIM_RBRACE,
                       "Expected '}' to close inline union declaration");
        string generatedTag =
            utag.has_value()
                ? utag.value()
                : ("__anon_union_" + std::to_string(anonymousUnionCounter++));
        auto unionDecl =
            std::make_shared<UnionDeclaration>(generatedTag, unionMembers);
        nestedUnions.push_back(unionDecl);
        inlineUnionDecl = unionDecl;
        memberType = "union " + generatedTag;
        isInlineUnion = true;
      } else if (utag.has_value()) {
        memberType = "union " + utag.value();
      } else {
        parser.error(
            "Expected union tag after 'union' in struct member declaration");
      }
    } else if (parser.match(TokenType::KW_ENUM)) {
      if (!parser.check(TokenType::IDENTIFIER))
        parser.error("Expected enum tag after 'enum' in member declaration");
      string etag = parser.advance().lexeme;
      memberType = "enum " + etag;
    } else if (parser.match(TokenType::KW_INT))
      memberType = "int";
    else if (parser.match(TokenType::KW_FLOAT))
      memberType = "float";
    else if (parser.match(TokenType::KW_CHAR))
      memberType = "char";
    else if (parser.match(TokenType::KW_DOUBLE))
      memberType = "double";
    else if (parser.match(TokenType::KW_BOOL))
      memberType = "bool";
    else if (parser.check(TokenType::IDENTIFIER) &&
             (parser.peek().lexeme == "long" ||
              parser.peek().lexeme == "short")) {
      memberType = parser.advance().lexeme;
      if (memberType == "long" && parser.check(TokenType::IDENTIFIER) &&
          parser.peek().lexeme == "long") {
        parser.advance();
        memberType = "long long";
      }
    } else if (parser.peek().lexeme == "__builtin_va_list" ||
               parser.peek().lexeme == "va_list") {
      memberType = parser.advance().lexeme;
    } else if (isTypedefName(parser.peek().lexeme)) {
      TypedefInfo info = resolveTypedef(parser.advance().lexeme);
      memberType = info.underlyingType;
      typedefDims = info.dimensions;
    } else
      parser.error("Expected type specifier in struct member declaration");

    if (sawUnsigned)
      memberType = "unsigned " + memberType;
    else if (sawSigned)
      memberType = "signed " + memberType;
    if (hasConst)
      memberType = "const " + memberType;
    if (hasVolatile)
      memberType = "volatile " + memberType;
    if (hasStatic)
      memberType = "static " + memberType;

    memberType = consumePointerTokens(parser, memberType);

    ParsedDeclarator memberDecl = parseDeclarator(parser, memberType, true);
    std::string memberName = memberDecl.name;
    std::vector<ExpressionPtr> dimensions = memberDecl.dimensions;
    dimensions.insert(dimensions.end(), typedefDims.begin(), typedefDims.end());
    memberType = memberDecl.type;
    bool hasEmptyArrayDimension = memberDecl.hasEmptyArrayDimension;
    std::optional<int> bitWidth = std::nullopt;
    if (parser.match(TokenType::DELIM_COLON)) {
      ExpressionPtr widthExpr = parser.parseExpression();
      if (auto lit = std::dynamic_pointer_cast<Literal>(widthExpr)) {
        bitWidth = lit->intValue;
      } else {
        parser.error("Expected constant expression for bitfield width");
      }
    }
    parser.consume(TokenType::DELIM_SEMICOLON,
                   "Expected ';' after struct member declaration");
    std::optional<int> align = parser.pendingAlignment;
    parser.pendingAlignment = std::nullopt;
    members.push_back(std::make_shared<VariableDeclaration>(
        memberType, memberName, bitWidth, std::nullopt, dimensions, align,
        hasEmptyArrayDimension, isAnonymousUnionField, isAnonymousStructField,
        inlineStructDecl, inlineUnionDecl));
  }
  parser.consume(TokenType::DELIM_RBRACE,
                 "Expected '}' to close struct declaration");
  if (!tag.has_value()) {
    tag = "__anon_struct_" + std::to_string(anonymousStructCounter++);
  }
  auto structDecl = std::make_shared<StructDeclaration>(
      tag, members, nestedUnions, nestedStructs, isPackedStruct);
  structDecl->tag = tag;
  structDecl->isPacked = isPackedStruct;
  parser.structPackedFlag = false;
  return structDecl;
}

static std::string
appendDimensionsToTypeString(const std::string &base,
                             const std::vector<ExpressionPtr> &dimensions) {
  std::string result = base;
  for (const auto &dim : dimensions) {
    if (auto lit = std::dynamic_pointer_cast<Literal>(dim)) {
      result += "[" + std::to_string(lit->intValue) + "]";
    } else {
      result += "[]";
    }
  }
  return result;
}

static std::string parseTypeNameOnly(Parser &parser) {
  bool hasConst = false;
  bool hasStatic = false;
  bool sawUnsigned = false;
  bool sawSigned = false;
  bool sawAtomic = false;
  while (!parser.isAtEnd() && parser.check(TokenType::IDENTIFIER)) {
    std::string lex = parser.peek().lexeme;
    if (lex == "_Atomic") {
      parser.advance();
      sawAtomic = true;
      if (parser.match(TokenType::DELIM_LPAREN)) {
        std::string inner = parseTypeNameOnly(parser);
        parser.consume(TokenType::DELIM_RPAREN,
                       "Expected ')' after _Atomic type name");
        return "_Atomic " + inner;
      }
      continue;
    }
    if (lex == "_Noreturn") {
      parser.advance();
      continue;
    }
    if (lex == "const") {
      hasConst = true;
      parser.advance();
      continue;
    }
    if (lex == "static") {
      hasStatic = true;
      parser.advance();
      continue;
    }
    if (lex == "inline") {
      parser.advance();
      continue;
    }
    if (lex == "unsigned") {
      sawUnsigned = true;
      parser.advance();
      continue;
    }
    if (lex == "signed") {
      sawSigned = true;
      parser.advance();
      continue;
    }
    break;
  }

  std::string type;
  if (parser.match(TokenType::KW_INT))
    type = "int";
  else if (parser.match(TokenType::KW_FLOAT))
    type = "float";
  else if (parser.match(TokenType::KW_CHAR))
    type = "char";
  else if (parser.match(TokenType::KW_DOUBLE))
    type = "double";
  else if (parser.match(TokenType::KW_BOOL))
    type = "bool";
  else if (parser.match(TokenType::KW_VOID))
    type = "void";
  else if (parser.peek().lexeme == "max_align_t" ||
           parser.peek().lexeme == "__builtin_va_list" ||
           parser.peek().lexeme == "va_list")
    type = parser.advance().lexeme;
  else if (parser.check(TokenType::KW_STRUCT) ||
           parser.peek().lexeme == "struct") {
    parser.advance();
    if (!parser.check(TokenType::IDENTIFIER))
      parser.error("Expected struct tag after 'struct'");
    std::string structTag = parser.advance().lexeme;
    type = "struct " + structTag;
  } else if (parser.check(TokenType::KW_UNION) ||
             parser.peek().lexeme == "union") {
    parser.advance();
    if (!parser.check(TokenType::IDENTIFIER))
      parser.error("Expected union tag after 'union'");
    std::string unionTag = parser.advance().lexeme;
    type = "union " + unionTag;
  } else if (parser.check(TokenType::KW_ENUM) ||
             parser.peek().lexeme == "enum") {
    parser.advance();
    if (!parser.check(TokenType::IDENTIFIER))
      parser.error("Expected enum tag after 'enum'");
    std::string enumTag = parser.advance().lexeme;
    type = "enum " + enumTag;
  } else if (parser.check(TokenType::IDENTIFIER) &&
             isTypedefName(parser.peek().lexeme)) {
    TypedefInfo info = resolveTypedef(parser.advance().lexeme);
    type = appendDimensionsToTypeString(info.underlyingType, info.dimensions);
  } else {
    parser.error("Expected type");
  }

  if (!type.empty() &&
      (type.find("float") != string::npos ||
       type.find("double") != string::npos) &&
      parser.check(TokenType::IDENTIFIER) &&
      (parser.peek().lexeme == "complex" ||
       parser.peek().lexeme == "_Complex")) {
    parser.advance();
    type += " complex";
  }

  if (sawUnsigned)
    type = "unsigned " + type;
  else if (sawSigned)
    type = "signed " + type;
  if (hasConst)
    type = "const " + type;
  if (hasStatic)
    type = "static " + type;
  if (sawAtomic)
    type = "_Atomic " + type;

  type = consumePointerTokens(parser, type);
  return type;
}

static std::vector<std::string> parseTypeList(Parser &parser) {
  std::vector<std::string> params;
  if (parser.check(TokenType::DELIM_RPAREN))
    return params;

  std::string firstType = parseTypeNameOnly(parser);
  if (firstType == "void" && parser.check(TokenType::DELIM_RPAREN))
    return params;
  params.push_back(firstType);
  while (parser.match(TokenType::DELIM_COMMA)) {
    params.push_back(parseTypeNameOnly(parser));
  }
  return params;
}

// parseVariableDeclarationWithType:
//   parses a variable declaration given an already-determined type name (like
//   "int" or "void*").
DeclarationPtr Parser::parseVariableDeclarationWithType(
    const string &givenType, const std::vector<ExpressionPtr> &typeDimensions,
    std::shared_ptr<StructDeclaration> inlineStructDecl,
    std::shared_ptr<UnionDeclaration> inlineUnionDecl) {
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] (parseVariableDeclarationWithType) current="
              << current << ", next tokens: ";
  for (int i = 0; i < 3 && current + i < tokens.size(); ++i) {
    std::cerr << static_cast<int>(tokens[current + i].type) << "('"
              << tokens[current + i].lexeme << "') ";
  }
  std::cerr << std::endl;
  vector<std::shared_ptr<VariableDeclaration>> decls;
  std::optional<int> align = pendingAlignment;
  do {
    ParsedDeclarator declInfo = parseDeclarator(*this, givenType, true);
    vector<ExpressionPtr> dimensions = declInfo.dimensions;
    dimensions.insert(dimensions.end(), typeDimensions.begin(),
                      typeDimensions.end());
    optional<ExpressionPtr> initializer = std::nullopt;
    if (match(TokenType::OP_ASSIGN)) {
      if (check(TokenType::DELIM_LBRACE))
        initializer = parseInitializerList();
      else
        initializer = parseAssignment();
    }
    decls.push_back(std::make_shared<VariableDeclaration>(
        declInfo.type, declInfo.name, std::nullopt, initializer, dimensions,
        align, declInfo.hasEmptyArrayDimension, false, false, inlineStructDecl,
        inlineUnionDecl));
  } while (match(TokenType::DELIM_COMMA));
  consume(TokenType::DELIM_SEMICOLON,
          "Expected ';' after variable declaration");
  pendingAlignment = std::nullopt;
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
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] (parseFunctionDeclarationWithType) current="
              << current << ", next tokens: ";
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
    return std::make_shared<FunctionDeclaration>(
        returnType, funcName, parameters, nullptr, varArgsPending);
  }

  // Otherwise parse the function body
  consume(TokenType::DELIM_LBRACE, "Expected '{' to begin function body");
  std::string prevFunc = currentFunctionName;
  currentFunctionName = funcName;
  StatementPtr body = parseCompoundStatement();
  currentFunctionName = prevFunc;
  return std::make_shared<FunctionDeclaration>(returnType, funcName, parameters,
                                               body, varArgsPending);
}

DeclarationPtr Parser::parseDeclaration() {
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] (parseDeclaration) current=" << current
              << ", next tokens: ";
  for (int i = 0; i < 3 && current + i < tokens.size(); ++i) {
    std::cerr << static_cast<int>(tokens[current + i].type) << "('"
              << tokens[current + i].lexeme << "') ";
  }
  std::cerr << std::endl;
  if (peek().lexeme == "_Static_assert") {
    advance();
    consume(TokenType::DELIM_LPAREN, "Expected '(' after _Static_assert");
    ExpressionPtr cond = parseExpression();
    std::string msg;
    if (match(TokenType::DELIM_COMMA) && check(TokenType::LITERAL_STRING)) {
      msg = advance().lexeme;
      if (msg.size() >= 2 && msg.front() == '"' && msg.back() == '"')
        msg = msg.substr(1, msg.size() - 2);
    }
    consume(TokenType::DELIM_RPAREN, "Expected ')' after _Static_assert");
    consume(TokenType::DELIM_SEMICOLON,
            "Expected ';' after _Static_assert declaration");
    return std::make_shared<StaticAssertDeclaration>(cond, msg);
  }
  if (peek().lexeme == "typedef") {
    advance();
    return parseTypedefDeclaration();
  }
  if (match(TokenType::KW_TYPEDEF)) {
    return parseTypedefDeclaration();
  }

  auto skipAttributesLookahead = [this](size_t idx) {
    while (idx < tokens.size() && tokens[idx].lexeme == "__attribute__") {
      idx++; // consume __attribute__
      if (idx < tokens.size() && tokens[idx].type == TokenType::DELIM_LPAREN) {
        int depth = 1;
        idx++;
        while (idx < tokens.size() && depth > 0) {
          if (tokens[idx].type == TokenType::DELIM_LPAREN)
            depth++;
          else if (tokens[idx].type == TokenType::DELIM_RPAREN)
            depth--;
          idx++;
        }
      }
    }
    return idx;
  };

  if (peek().type == TokenType::KW_STRUCT || peek().lexeme == "struct") {
    size_t save = current;
    advance();
    bool looksLikeStandaloneStruct = false;
    size_t idx = skipAttributesLookahead(current);
    if (idx < tokens.size() && tokens[idx].type == TokenType::IDENTIFIER) {
      idx++;
      idx = skipAttributesLookahead(idx);
    }
    if (idx < tokens.size() && tokens[idx].type == TokenType::DELIM_LBRACE) {
      int depth = 0;
      for (size_t i = idx; i < tokens.size(); ++i) {
        if (tokens[i].type == TokenType::DELIM_LBRACE)
          depth++;
        else if (tokens[i].type == TokenType::DELIM_RBRACE) {
          depth--;
          if (depth == 0) {
            if (i + 1 < tokens.size() &&
                tokens[i + 1].type == TokenType::DELIM_SEMICOLON)
              looksLikeStandaloneStruct = true;
            break;
          }
        }
      }
      if (looksLikeStandaloneStruct) {
        current = save;
        return parseStructDeclaration();
      }
    }
    current = save;
  }
  if (check(TokenType::KW_UNION) || peek().lexeme == "union") {
    size_t save = current;
    advance();
    if (check(TokenType::DELIM_LBRACE) ||
        (check(TokenType::IDENTIFIER) && current + 1 < tokens.size() &&
         tokens[current + 1].type == TokenType::DELIM_LBRACE)) {
      current = save;
      return parseUnionDeclaration();
    }
    current = save;
  }
  if (check(TokenType::KW_ENUM) || peek().lexeme == "enum") {
    size_t save = current;
    advance();
    if (check(TokenType::DELIM_LBRACE) ||
        (check(TokenType::IDENTIFIER) && current + 1 < tokens.size() &&
         tokens[current + 1].type == TokenType::DELIM_LBRACE)) {
      current = save;
      return parseEnumDeclaration();
    }
    current = save;
  }

  bool hasConstQualifier = false;
  bool hasStaticQualifier = false;
  bool hasVolatileQualifier = false;
  std::shared_ptr<StructDeclaration> inlineStructDecl = nullptr;
  std::shared_ptr<UnionDeclaration> inlineUnionDecl = nullptr;
  string baseType = parseSimpleType(*this, hasConstQualifier,
                                    hasStaticQualifier, hasVolatileQualifier,
                                    &inlineStructDecl, &inlineUnionDecl);

  // Handle functions returning function pointers, e.g.
  // int (*fn(char c))(int, int)
  {
    size_t save = current;
    if (match(TokenType::DELIM_LPAREN) && match(TokenType::OP_MULTIPLY)) {
      if (check(TokenType::IDENTIFIER)) {
        string funcName = advance().lexeme;
        consume(TokenType::DELIM_LPAREN, "Expected '(' after function name");
        auto parameters = parseParameters();
        consume(TokenType::DELIM_RPAREN, "Expected ')' after parameter list");
        consume(TokenType::DELIM_RPAREN,
                "Expected ')' to close function pointer declarator");
        if (match(TokenType::DELIM_LPAREN)) {
          auto retParamTypes = parseParameterTypeList(*this);
          consume(TokenType::DELIM_RPAREN,
                  "Expected ')' after return function parameters");
          string returnType = makeFunctionPointerType(baseType, retParamTypes);
          if (match(TokenType::DELIM_SEMICOLON)) {
            return std::make_shared<FunctionDeclaration>(returnType, funcName,
                                                         parameters, nullptr);
          }
          consume(TokenType::DELIM_LBRACE,
                  "Expected '{' to begin function body");
          StatementPtr body = parseCompoundStatement();
          return std::make_shared<FunctionDeclaration>(returnType, funcName,
                                                       parameters, body);
        }
      }
    }
    current = save;
  }

  size_t tmp = current;
  size_t pointerBeforeFunc = 0;
  while (tmp < tokens.size() && tokens[tmp].type == TokenType::OP_MULTIPLY) {
    pointerBeforeFunc++;
    tmp++;
  }
  if (tmp + 1 < tokens.size()) {
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] (parseDeclaration) lookahead token="
                << tokens[tmp].lexeme << " ("
                << static_cast<int>(tokens[tmp].type)
                << ") next=" << tokens[tmp + 1].lexeme << " ("
                << static_cast<int>(tokens[tmp + 1].type)
                << ") pointerBeforeFunc=" << pointerBeforeFunc << std::endl;
  }
  if (tmp < tokens.size() && tokens[tmp].type == TokenType::IDENTIFIER &&
      tmp + 1 < tokens.size() &&
      tokens[tmp + 1].type == TokenType::DELIM_LPAREN) {
    string returnType = baseType + string(pointerBeforeFunc, '*');
    for (size_t i = 0; i < pointerBeforeFunc; ++i)
      advance();
    return parseFunctionDeclarationWithType(returnType);
  }

  return parseVariableDeclarationWithType(baseType, {}, inlineStructDecl,
                                          inlineUnionDecl);
}

DeclarationPtr Parser::parseTypedefDeclaration() {
  if ((check(TokenType::KW_STRUCT) || peek().lexeme == "struct") &&
      ((current + 1 < tokens.size() &&
        tokens[current + 1].type == TokenType::DELIM_LBRACE) ||
       (current + 2 < tokens.size() &&
        tokens[current + 1].type == TokenType::IDENTIFIER &&
        tokens[current + 2].type == TokenType::DELIM_LBRACE) ||
       (current + 1 < tokens.size() &&
        tokens[current + 1].lexeme == "__attribute__"))) {
    advance(); // consume 'struct'
    auto consumeStructAttributes = [this]() {
      while (check(TokenType::IDENTIFIER) && peek().lexeme == "__attribute__") {
        advance();
        consume(TokenType::DELIM_LPAREN, "Expected '(' after __attribute__");
        int depth = 1;
        while (depth > 0 && !isAtEnd()) {
          Token t = advance();
          if (t.lexeme == "packed")
            structPackedFlag = true;
          if (t.type == TokenType::DELIM_LPAREN)
            depth++;
          else if (t.type == TokenType::DELIM_RPAREN)
            depth--;
        }
      }
    };
    consumeStructAttributes();
    optional<string> tag = std::nullopt;
    if (check(TokenType::IDENTIFIER) && current + 1 < tokens.size() &&
        tokens[current + 1].type == TokenType::DELIM_LBRACE) {
      tag = advance().lexeme;
    }
    consumeStructAttributes();
    auto structDecl = parseStructDefinition(*this, tag);
    if (!structDecl->tag.has_value()) {
      structDecl->tag =
          "__anon_struct_" + std::to_string(anonymousStructCounter++);
    }
    string baseType = "struct " + structDecl->tag.value();
    ParsedDeclarator declInfo = parseDeclarator(*this, baseType, true);
    consume(TokenType::DELIM_SEMICOLON,
            "Expected ';' after typedef declaration");
    TypedefInfo info{declInfo.type, declInfo.dimensions,
                     declInfo.isFunctionPointer ||
                         declInfo.type.rfind("fnptr:", 0) == 0,
                     declInfo.functionParamTypes};
    typedefRegistry[declInfo.name] = info;
    return std::make_shared<TypedefDeclaration>(
        declInfo.name, declInfo.type, declInfo.dimensions,
        info.isFunctionPointer, info.functionParamTypes, structDecl);
  }

  bool hasConstQualifier = false;
  bool hasStaticQualifier = false;
  bool hasVolatileQualifier = false;
  string baseType = parseSimpleType(*this, hasConstQualifier,
                                    hasStaticQualifier, hasVolatileQualifier);
  ParsedDeclarator declInfo = parseDeclarator(*this, baseType, true);
  consume(TokenType::DELIM_SEMICOLON, "Expected ';' after typedef declaration");

  TypedefInfo info;
  info.underlyingType = declInfo.type;
  info.dimensions = declInfo.dimensions;
  info.isFunctionPointer =
      declInfo.isFunctionPointer || declInfo.type.rfind("fnptr:", 0) == 0;
  info.functionParamTypes = declInfo.functionParamTypes;
  typedefRegistry[declInfo.name] = info;

  return std::make_shared<TypedefDeclaration>(
      declInfo.name, declInfo.type, declInfo.dimensions, info.isFunctionPointer,
      info.functionParamTypes);
}

vector<std::pair<string, string>> Parser::parseParameters() {
  vector<std::pair<string, string>> params;
  varArgsPending = false;
  if (check(TokenType::DELIM_RPAREN))
    return params;

  // Handle a lone 'void' indicating an empty parameter list.
  if (check(TokenType::KW_VOID) && current + 1 < tokens.size() &&
      tokens[current + 1].type == TokenType::DELIM_RPAREN) {
    advance();
    return params;
  }

  do {
    if (check(TokenType::DOT) && current + 2 < tokens.size() &&
        tokens[current + 1].type == TokenType::DOT &&
        tokens[current + 2].type == TokenType::DOT) {
      current += 3;
      varArgsPending = true;
      break;
    }
    bool hasConst = false;
    bool hasStatic = false;
    bool hasVolatile = false;
    string baseType = parseSimpleType(*this, hasConst, hasStatic, hasVolatile);
    ParsedDeclarator decl = parseDeclarator(*this, baseType, false);
    string paramName =
        decl.name.empty() ? "param" + std::to_string(params.size()) : decl.name;
    string paramType = appendArrayToType(*this, decl.type, decl.dimensions);
    if (decl.hasEmptyArrayDimension || !decl.dimensions.empty()) {
      size_t firstBracket = paramType.find('[');
      if (firstBracket != string::npos) {
        size_t endBracket = paramType.find(']', firstBracket);
        string tail = (endBracket != string::npos)
                          ? paramType.substr(endBracket + 1)
                          : "";
        string elementType = paramType.substr(0, firstBracket) + tail;
        paramType = elementType + "*";
      } else {
        paramType += "*";
      }
    }
    params.emplace_back(paramType, paramName);
  } while (match(TokenType::DELIM_COMMA));

  return params;
}

ExpressionPtr Parser::parseInitializerList() {
  consume(TokenType::DELIM_LBRACE, "Expected '{' to start initializer list");
  vector<ExpressionPtr> elems;
  std::vector<std::optional<std::string>> designators;
  std::optional<int> designatedIndex;
  std::optional<std::string> designatedField;

  auto parseOne = [this, &designatedIndex,
                   &designatedField]() -> ExpressionPtr {
    designatedField.reset();
    // Handle designated initializers; designators are consumed and ignored for
    // ordering purposes.
    while (true) {
      if (match(TokenType::DOT)) {
        if (!check(TokenType::IDENTIFIER))
          error("Expected identifier after '.' in designated initializer");
        designatedField = peek().lexeme;
        advance();
        consume(TokenType::OP_ASSIGN, "Expected '=' after designator");
        continue;
      }
      if (match(TokenType::DELIM_LBRACKET)) {
        int idx = 0;
        if (!check(TokenType::DELIM_RBRACKET)) {
          ExpressionPtr idxExpr = parseExpression();
          if (auto lit = std::dynamic_pointer_cast<Literal>(idxExpr))
            idx = lit->intValue;
        }
        consume(TokenType::DELIM_RBRACKET,
                "Expected ']' after array designator");
        consume(TokenType::OP_ASSIGN, "Expected '=' after designator");
        designatedIndex = idx;
        continue;
      }
      break;
    }

    if (check(TokenType::DELIM_LBRACE)) {
      return parseInitializerList();
    }
    return parseAssignment();
  };

  if (!check(TokenType::DELIM_RBRACE)) {
    auto elem = parseOne();
    if (designatedIndex.has_value()) {
      if (elems.size() <= static_cast<size_t>(designatedIndex.value())) {
        elems.resize(designatedIndex.value() + 1, std::make_shared<Literal>(0));
        designators.resize(designatedIndex.value() + 1);
      }
      elems[designatedIndex.value()] = elem;
      if (designatedField.has_value()) {
        designators[designatedIndex.value()] = designatedField;
      }
      designatedIndex.reset();
      designatedField.reset();
    } else {
      elems.push_back(elem);
      designators.push_back(designatedField);
      designatedField.reset();
    }
    while (match(TokenType::DELIM_COMMA)) {
      if (check(TokenType::DELIM_RBRACE))
        break;
      auto nextElem = parseOne();
      if (designatedIndex.has_value()) {
        if (elems.size() <= static_cast<size_t>(designatedIndex.value())) {
          elems.resize(designatedIndex.value() + 1,
                       std::make_shared<Literal>(0));
          designators.resize(designatedIndex.value() + 1);
        }
        elems[designatedIndex.value()] = nextElem;
        if (designatedField.has_value())
          designators[designatedIndex.value()] = designatedField;
        designatedIndex.reset();
        designatedField.reset();
      } else {
        elems.push_back(nextElem);
        designators.push_back(designatedField);
        designatedField.reset();
      }
    }
  }

  consume(TokenType::DELIM_RBRACE, "Expected '}' to end initializer list");
  return std::make_shared<InitializerList>(elems, designators);
}

DeclarationPtr Parser::parseStructDeclaration() {
  if (peek().lexeme == "struct")
    advance();
  else
    error("Expected 'struct' keyword");

  auto skipAttributes = [this]() {
    while (check(TokenType::IDENTIFIER) && peek().lexeme == "__attribute__") {
      advance(); // consume __attribute__
      consume(TokenType::DELIM_LPAREN, "Expected '(' after __attribute__");
      int depth = 1;
      while (depth > 0 && !isAtEnd()) {
        Token t = advance();
        if (t.lexeme == "packed")
          structPackedFlag = true;
        if (t.type == TokenType::DELIM_LPAREN)
          depth++;
        else if (t.type == TokenType::DELIM_RPAREN)
          depth--;
      }
    }
  };

  skipAttributes();

  optional<string> tag = std::nullopt;
  if (check(TokenType::IDENTIFIER))
    tag = advance().lexeme;
  skipAttributes();
  if (check(TokenType::DELIM_LBRACE)) {
    auto structDecl = parseStructDefinition(*this, tag);
    consume(TokenType::DELIM_SEMICOLON,
            "Expected ';' after struct declaration");
    return structDecl;
  } else {
    structPackedFlag = false;
    return nullptr;
  }
}

DeclarationPtr Parser::parseUnionDeclaration() {
  if (educcDebugEnabled())
    std::cerr
        << "[DEBUG] parseUnionDeclaration: Starting union declaration parsing"
        << std::endl;
  consume(TokenType::KW_UNION, "Expected 'union' keyword");
  optional<string> tag = std::nullopt;
  if (check(TokenType::IDENTIFIER))
    tag = advance().lexeme;
  if (educcDebugEnabled())
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
  if (educcDebugEnabled())
    std::cerr
        << "[DEBUG] parseUnionDeclaration: Creating UnionDeclaration with "
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
      initializer = parseAssignment();
    enumerators.push_back({enumeratorName, initializer});
  }
  consume(TokenType::DELIM_RBRACE, "Expected '}' to close enum declaration");
  consume(TokenType::DELIM_SEMICOLON, "Expected ';' after enum declaration");
  return std::make_shared<EnumDeclaration>(tag, enumerators);
}

std::shared_ptr<VariableDeclaration> Parser::parseUnionMemberDeclaration() {
  string type;
  bool hasConst = false;
  bool hasStatic = false;
  bool hasVolatile = false;
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
    if (lex == "volatile") {
      hasVolatile = true;
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
  if (peek().lexeme == "struct") {
    advance();
    if (!check(TokenType::IDENTIFIER))
      error("Expected struct tag after 'struct' in union member declaration");
    string tag = advance().lexeme;
    type = "struct " + tag;
  } else if (peek().lexeme == "union" || check(TokenType::KW_UNION)) {
    advance();
    if (!check(TokenType::IDENTIFIER))
      error("Expected union tag after 'union' in union member declaration");
    string utag = advance().lexeme;
    type = "union " + utag;
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
  } else if (check(TokenType::IDENTIFIER) &&
             (peek().lexeme == "long" || peek().lexeme == "short")) {
    type = advance().lexeme;
    if (type == "long" && check(TokenType::IDENTIFIER) &&
        peek().lexeme == "long") {
      advance();
      type = "long long";
    }
  } else if (check(TokenType::IDENTIFIER) && isTypedefName(peek().lexeme)) {
    TypedefInfo info = resolveTypedef(advance().lexeme);
    type = info.underlyingType;
  } else {
    error("Expected type specifier in union member declaration");
  }

  if (sawUnsigned)
    type = "unsigned " + type;
  else if (sawSigned)
    type = "signed " + type;
  if (hasConst)
    type = "const " + type;
  if (hasVolatile)
    type = "volatile " + type;
  if (hasStatic)
    type = "static " + type;
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
  std::optional<int> align = pendingAlignment;
  pendingAlignment = std::nullopt;
  return std::make_shared<VariableDeclaration>(type, name, std::nullopt,
                                               std::nullopt, dimensions, align);
}
