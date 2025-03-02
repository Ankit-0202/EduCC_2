#include "Parser.hpp"
#include <stdexcept>
#include <string>

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens), current(0) {}

bool Parser::match(TokenType type) {
  if (check(type)) {
    advance();
    return true;
  }
  // Fallback: if the expected token is an operator or punctuation and its
  // lexeme matches.
  std::string expected;
  switch (type) {
  case TokenType::OP_ASSIGN:
    expected = "=";
    break;
  case TokenType::DELIM_SEMICOLON:
    expected = ";";
    break;
  case TokenType::DELIM_LPAREN:
    expected = "(";
    break;
  case TokenType::DELIM_RPAREN:
    expected = ")";
    break;
  case TokenType::DELIM_LBRACE:
    expected = "{";
    break;
  case TokenType::DELIM_RBRACE:
    expected = "}";
    break;
  case TokenType::DELIM_LBRACKET:
    expected = "[";
    break;
  case TokenType::DELIM_RBRACKET:
    expected = "]";
    break;
  default:
    break;
  }
  if (!expected.empty() && peek().lexeme == expected) {
    advance();
    return true;
  }
  return false;
}

bool Parser::check(TokenType type) const {
  if (isAtEnd())
    return false;
  Token t = peek();
  if (t.type == type)
    return true;
  // NEW: If we expect a semicolon but the token’s lexeme is ";" then accept it.
  if (type == TokenType::DELIM_SEMICOLON && t.lexeme == ";")
    return true;
  // (You can add additional cases here if needed.)
  return false;
}

Token Parser::advance() {
  if (!isAtEnd())
    current++;
  return tokens[current - 1];
}

Token Parser::peek() const {
  if (isAtEnd()) {
    static Token eofToken = {TokenType::EOF_TOKEN, "EOF", 0, 0};
    return eofToken;
  }
  return tokens[current];
}

bool Parser::isAtEnd() const {
  return current >= tokens.size() ||
         tokens[current].type == TokenType::EOF_TOKEN;
}

void Parser::consume(TokenType type, const std::string &errorMessage) {
  if (check(type)) {
    advance();
    return;
  }
  // Fallback: if we expect punctuation or an operator, check its lexeme.
  std::string expected;
  switch (type) {
  case TokenType::OP_ASSIGN:
    expected = "=";
    break;
  case TokenType::DELIM_SEMICOLON:
    expected = ";";
    break;
  case TokenType::DELIM_LPAREN:
    expected = "(";
    break;
  case TokenType::DELIM_RPAREN:
    expected = ")";
    break;
  case TokenType::DELIM_LBRACE:
    expected = "{";
    break;
  case TokenType::DELIM_RBRACE:
    expected = "}";
    break;
  case TokenType::DELIM_LBRACKET:
    expected = "[";
    break;
  case TokenType::DELIM_RBRACKET:
    expected = "]";
    break;
  default:
    break;
  }
  if (!expected.empty() && peek().lexeme == expected) {
    advance();
    return;
  }
  error(errorMessage);
}

void Parser::error(const std::string &message) const {
  if (current < tokens.size()) {
    const Token &tok = tokens[current];
    throw std::runtime_error("Parser Error at Line " +
                             std::to_string(tok.line) + ", Column " +
                             std::to_string(tok.column) + " (token: '" +
                             tok.lexeme + "'): " + message);
  } else {
    throw std::runtime_error("Parser Error at end of input: " + message);
  }
}

std::shared_ptr<Program> Parser::parse() {
  auto program = std::make_shared<Program>();
  while (!isAtEnd()) {
    DeclarationPtr decl = parseDeclaration();
    if (decl)
      program->addDeclaration(decl);
    else
      break;
  }
  return program;
}
