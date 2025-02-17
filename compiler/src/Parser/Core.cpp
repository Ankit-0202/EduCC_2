#include "Parser.hpp"
#include <stdexcept>
#include <string>

// --- Basic Parser utilities and the overall parse() method ---

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens), current(0) {}

bool Parser::match(TokenType type) {
  if (check(type)) {
    advance();
    return true;
  }
  return false;
}

bool Parser::check(TokenType type) const {
  if (isAtEnd())
    return false;
  return peek().type == type;
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
