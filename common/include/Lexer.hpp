#ifndef LEXER_HPP
#define LEXER_HPP

#include "Token.hpp"
#include <string>
#include <vector>

class Lexer {
public:
  // Constructor
  Lexer(const std::string &source);

  // Tokenize the source code and return a vector of tokens.
  std::vector<Token> tokenize();

private:
  std::string sourceCode;
  size_t currentPos;
  int line;
  int column;

  // Helper methods.
  bool isAtEnd() const;
  char peek() const;
  char peekNext() const;
  char get();
  void skipWhitespace();

  // Lexing routines.
  Token identifier();
  Token number();
  Token character();
  Token stringLiteral(); // <<-- New declaration for string literal handling.
  Token opOrDelim();
};

#endif // LEXER_HPP
