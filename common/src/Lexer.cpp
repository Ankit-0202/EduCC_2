#include "Lexer.hpp"
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <cctype>

// Constructor
Lexer::Lexer(const std::string& source)
    : sourceCode(source), currentPos(0), line(1), column(1) {}

// Return true if at end of input.
bool Lexer::isAtEnd() const {
    return currentPos >= sourceCode.length();
}

// Peek the current character without consuming it.
char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return sourceCode[currentPos];
}

// Peek the next character (after the current one) without consuming it.
char Lexer::peekNext() const {
    if (currentPos + 1 >= sourceCode.length()) return '\0';
    return sourceCode[currentPos + 1];
}

// Consume and return the current character.
char Lexer::get() {
    if (isAtEnd()) return '\0';
    char c = sourceCode[currentPos++];
    if (c == '\n') {
        line++;
        column = 1;
    } else {
        column++;
    }
    return c;
}

// Skip whitespace (and comments).
void Lexer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        if (std::isspace(static_cast<unsigned char>(c))) {
            get();
        } else if (c == '/' && peekNext() == '/') {
            // Single-line comment.
            get(); // consume '/'
            get(); // consume second '/'
            while (peek() != '\n' && !isAtEnd())
                get();
        } else {
            break;
        }
    }
}

// Produce an identifier or keyword token.
Token Lexer::identifier() {
    int startLine = line;
    int startColumn = column;
    std::string lexeme;
    while (!isAtEnd() && (std::isalnum(static_cast<unsigned char>(peek())) || peek() == '_')) {
        lexeme.push_back(get());
    }
    Token token;
    // Check for keywords.
    if (lexeme == "int")
        token.type = TokenType::KW_INT;
    else if (lexeme == "float")
        token.type = TokenType::KW_FLOAT;
    else if (lexeme == "char")
        token.type = TokenType::KW_CHAR;
    else if (lexeme == "double")
        token.type = TokenType::KW_DOUBLE;
    else if (lexeme == "bool")
        token.type = TokenType::KW_BOOL;
    else if (lexeme == "return")
        token.type = TokenType::KW_RETURN;
    else if (lexeme == "if")
        token.type = TokenType::KW_IF;
    else if (lexeme == "else")
        token.type = TokenType::KW_ELSE;
    else if (lexeme == "while")
        token.type = TokenType::KW_WHILE;
    else if (lexeme == "for")
        token.type = TokenType::KW_FOR;
    else if (lexeme == "switch")
        token.type = TokenType::KW_SWITCH;
    else if (lexeme == "case")
        token.type = TokenType::KW_CASE;
    else if (lexeme == "default")
        token.type = TokenType::KW_DEFAULT;
    else
        token.type = TokenType::IDENTIFIER;
    token.lexeme = lexeme;
    token.line = startLine;
    token.column = startColumn;
    return token;
}

Token Lexer::number() {
    int startLine = line;
    int startColumn = column;
    std::string lexeme;
    bool sawDot = false;
    while (!isAtEnd() && std::isdigit(static_cast<unsigned char>(peek()))) {
        lexeme.push_back(get());
    }
    if (!isAtEnd() && peek() == '.') {
        sawDot = true;
        lexeme.push_back(get());
        while (!isAtEnd() && std::isdigit(static_cast<unsigned char>(peek()))) {
            lexeme.push_back(get());
        }
    }
    bool isFloatLiteral = false;
    if (!isAtEnd() && (peek() == 'f' || peek() == 'F')) {
        isFloatLiteral = true;
        lexeme.push_back(get());
    }
    Token token;
    if (!sawDot) {
        token.type = TokenType::LITERAL_INT;
    } else if (isFloatLiteral) {
        token.type = TokenType::LITERAL_FLOAT;
    } else {
        token.type = TokenType::LITERAL_DOUBLE;
    }
    token.lexeme = lexeme;
    token.line = startLine;
    token.column = startColumn;
    return token;
}

Token Lexer::character() {
    int startLine = line;
    int startColumn = column;
    std::string lexeme;
    char openingQuote = get(); // Expect '
    if (openingQuote != '\'')
        throw std::runtime_error("Lexer Error: Expected opening single quote for char literal");
    char ch = get();
    lexeme.push_back(ch);
    if (peek() != '\'')
        throw std::runtime_error("Lexer Error: Unterminated char literal");
    get(); // consume closing '
    Token token;
    token.type = TokenType::LITERAL_CHAR;
    token.lexeme = lexeme;
    token.line = startLine;
    token.column = startColumn;
    return token;
}

Token Lexer::opOrDelim() {
    int startLine = line;
    int startColumn = column;
    char c = get();
    std::string lexeme(1, c);
    Token token;
    switch (c) {
        case '+': {
            if (!isAtEnd() && peek() == '=') {
                get();
                lexeme = "+=";
                token.type = TokenType::OP_PLUS_ASSIGN;
            } else {
                token.type = TokenType::OP_PLUS;
            }
            break;
        }
        case '-': {
            if (!isAtEnd() && peek() == '=') {
                get();
                lexeme = "-=";
                token.type = TokenType::OP_MINUS_ASSIGN;
            } else {
                token.type = TokenType::OP_MINUS;
            }
            break;
        }
        case '*': {
            if (!isAtEnd() && peek() == '=') {
                get();
                lexeme = "*=";
                token.type = TokenType::OP_MULTIPLY_ASSIGN;
            } else {
                token.type = TokenType::OP_MULTIPLY;
            }
            break;
        }
        case '/': {
            if (!isAtEnd() && peek() == '=') {
                get();
                lexeme = "/=";
                token.type = TokenType::OP_DIVIDE_ASSIGN;
            } else {
                token.type = TokenType::OP_DIVIDE;
            }
            break;
        }
        case '=': {
            if (!isAtEnd() && peek() == '=') {
                get();
                lexeme += "=";
                token.type = TokenType::OP_EQUAL;
            } else {
                token.type = TokenType::OP_ASSIGN;
            }
            break;
        }
        case '!': {
            if (!isAtEnd() && peek() == '=') {
                get();
                lexeme += "=";
                token.type = TokenType::OP_NOT_EQUAL;
            } else {
                token.type = TokenType::UNKNOWN;
            }
            break;
        }
        case '<': {
            if (!isAtEnd() && peek() == '<') {
                get();
                lexeme = "<<";
                token.type = TokenType::OP_LEFT_SHIFT;
            } else if (!isAtEnd() && peek() == '=') {
                get();
                lexeme += "=";
                token.type = TokenType::OP_LESS_EQUAL;
            } else {
                token.type = TokenType::OP_LESS;
            }
            break;
        }
        case '>': {
            if (!isAtEnd() && peek() == '>') {
                get();
                lexeme = ">>";
                token.type = TokenType::OP_RIGHT_SHIFT;
            } else if (!isAtEnd() && peek() == '=') {
                get();
                lexeme += "=";
                token.type = TokenType::OP_GREATER_EQUAL;
            } else {
                token.type = TokenType::OP_GREATER;
            }
            break;
        }
        case '&': {
            if (!isAtEnd() && peek() == '&') {
                get();
                lexeme += "&";
                token.type = TokenType::OP_LOGICAL_AND;
            } else {
                token.type = TokenType::OP_BITWISE_AND;
            }
            break;
        }
        case '|': {
            if (!isAtEnd() && peek() == '|') {
                get();
                lexeme += "|";
                token.type = TokenType::OP_LOGICAL_OR;
            } else {
                token.type = TokenType::OP_BITWISE_OR;
            }
            break;
        }
        case '^': {
            token.type = TokenType::OP_BITWISE_XOR;
            break;
        }
        case ';':
            token.type = TokenType::DELIM_SEMICOLON;
            break;
        case ',':
            token.type = TokenType::DELIM_COMMA;
            break;
        case '(':
            token.type = TokenType::DELIM_LPAREN;
            break;
        case ')':
            token.type = TokenType::DELIM_RPAREN;
            break;
        case '{':
            token.type = TokenType::DELIM_LBRACE;
            break;
        case '}':
            token.type = TokenType::DELIM_RBRACE;
            break;
        case ':':
            token.type = TokenType::DELIM_COLON;
            break;
        case '\'':
            // Roll back and call character()
            currentPos--;
            column--;
            return character();
        default:
            token.type = TokenType::UNKNOWN;
            break;
    }
    token.lexeme = lexeme;
    token.line = startLine;
    token.column = startColumn;
    return token;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (!isAtEnd()) {
        skipWhitespace();
        if (isAtEnd())
            break;
        char c = peek();
        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
            tokens.push_back(identifier());
        } else if (std::isdigit(static_cast<unsigned char>(c))) {
            tokens.push_back(number());
        } else if (c == '\'') {
            tokens.push_back(character());
        } else {
            tokens.push_back(opOrDelim());
        }
    }
    Token eofToken;
    eofToken.type = TokenType::EOF_TOKEN;
    eofToken.lexeme = "EOF";
    eofToken.line = line;
    eofToken.column = column;
    tokens.push_back(eofToken);
    return tokens;
}
