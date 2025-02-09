#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include "Token.hpp"

class Lexer {
public:
    Lexer(const std::string &source);
    std::vector<Token> tokenize();

private:
    bool isAtEnd() const;
    char peek() const;
    char peekNext() const;
    char get();
    void skipWhitespace();
    Token identifier();
    Token number();
    Token character();
    Token opOrDelim();

    std::string sourceCode;
    size_t currentPos;
    int line;
    int column;
};

#endif // LEXER_HPP
