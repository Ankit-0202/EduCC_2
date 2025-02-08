#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

// Enumeration of possible token types.
enum class TokenType {
    // Keywords
    KW_INT,
    KW_FLOAT,
    KW_CHAR,
    KW_DOUBLE,
    KW_BOOL,
    KW_RETURN,
    KW_IF,
    KW_ELSE,
    KW_WHILE,
    KW_FOR,
    KW_SWITCH,    // NEW
    KW_CASE,      // NEW
    KW_DEFAULT,   // NEW
    // Operators
    OP_PLUS,
    OP_MINUS,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_ASSIGN,
    OP_PLUS_ASSIGN,
    OP_MINUS_ASSIGN,
    OP_MULTIPLY_ASSIGN,
    OP_DIVIDE_ASSIGN,
    OP_EQUAL,
    OP_NOT_EQUAL,
    OP_LESS,
    OP_GREATER,
    OP_LESS_EQUAL,
    OP_GREATER_EQUAL,
    OP_LOGICAL_AND,
    OP_LOGICAL_OR,
    // New Bitwise and Shift operators
    OP_BITWISE_AND,
    OP_BITWISE_OR,
    OP_BITWISE_XOR,
    OP_LEFT_SHIFT,
    OP_RIGHT_SHIFT,
    // Delimiters
    DELIM_SEMICOLON,
    DELIM_COMMA,
    DELIM_LPAREN,
    DELIM_RPAREN,
    DELIM_LBRACE,
    DELIM_RBRACE,
    DELIM_COLON, // for switch-case labels
    // Literals
    LITERAL_INT,
    LITERAL_FLOAT,    // with trailing f/F
    LITERAL_DOUBLE,   // without f suffix (default for decimals)
    LITERAL_CHAR,
    // Identifier
    IDENTIFIER,
    // End of File
    EOF_TOKEN,
    // Unknown
    UNKNOWN
};

// Structure to represent a token.
struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;
};

// Lexer class.
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
    Token character(); // For character literals.
    Token opOrDelim();
    bool isAtEnd() const;

    std::string sourceCode;
    size_t currentPos;
    int line;
    int column;
};

#endif // LEXER_HPP
