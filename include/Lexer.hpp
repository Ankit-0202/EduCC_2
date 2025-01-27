#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

// Enumeration of possible token types
enum class TokenType {
    // Keywords
    KW_INT,
    KW_FLOAT,
    KW_RETURN,
    KW_IF,
    KW_ELSE,
    KW_WHILE,
    KW_FOR,
    // Operators
    OP_PLUS,
    OP_MINUS,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_ASSIGN,
    OP_EQUAL,
    OP_NOT_EQUAL,
    OP_LESS,
    OP_GREATER,
    OP_LESS_EQUAL,
    OP_GREATER_EQUAL,
    // Delimiters
    DELIM_SEMICOLON,
    DELIM_COMMA,
    DELIM_LPAREN,
    DELIM_RPAREN,
    DELIM_LBRACE,
    DELIM_RBRACE,
    // Literals
    LITERAL_INT,
    LITERAL_FLOAT,
    // Identifier
    IDENTIFIER,
    // End of File
    EOF_TOKEN,
    // Unknown
    UNKNOWN
};

// Structure to represent a token
struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;
};

// Lexer class
class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    char peek() const;
    char get();
    void skipWhitespace();
    Token identifier();
    Token number();
    Token opOrDelim();
    bool isAtEnd() const;

    std::string sourceCode;
    size_t currentPos;
    int line;
    int column;
};

#endif // LEXER_HPP
