#include "Lexer.hpp"

// List of keywords
const std::vector<std::string> keywords = {
    "int", "float", "return", "if", "else", "while", "for"
};

// Constructor
Lexer::Lexer(const std::string& source)
    : sourceCode(source), currentPos(0), line(1), column(1) {}

// Check if end of source is reached
bool Lexer::isAtEnd() const {
    return currentPos >= sourceCode.length();
}

// Peek the current character without consuming it
char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return sourceCode[currentPos];
}

// Consume and return the current character
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

// Skip whitespace characters
void Lexer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        if (std::isspace(c)) {
            get();
        } else if (c == '/' && currentPos + 1 < sourceCode.length() && sourceCode[currentPos + 1] == '/') {
            // Single-line comment
            get(); // consume '/'
            get(); // consume second '/'
            while (peek() != '\n' && !isAtEnd()) {
                get();
            }
        } else {
            break;
        }
    }
}

// Tokenize identifiers and keywords
Token Lexer::identifier() {
    int startLine = line;
    int startColumn = column;
    std::string lexeme;
    while (std::isalnum(peek()) || peek() == '_') {
        lexeme += get();
    }

    Token token;
    // Check if the lexeme is a keyword
    if (std::find(keywords.begin(), keywords.end(), lexeme) != keywords.end()) {
        if (lexeme == "int") token.type = TokenType::KW_INT;
        else if (lexeme == "float") token.type = TokenType::KW_FLOAT;
        else if (lexeme == "return") token.type = TokenType::KW_RETURN;
        else if (lexeme == "if") token.type = TokenType::KW_IF;
        else if (lexeme == "else") token.type = TokenType::KW_ELSE;
        else if (lexeme == "while") token.type = TokenType::KW_WHILE;
        else if (lexeme == "for") token.type = TokenType::KW_FOR;
        else token.type = TokenType::IDENTIFIER; // Fallback
    } else {
        token.type = TokenType::IDENTIFIER;
    }

    token.lexeme = lexeme;
    token.line = startLine;
    token.column = startColumn;
    return token;
}

// Tokenize numbers (integers and floats)
Token Lexer::number() {
    int startLine = line;
    int startColumn = column;
    std::string lexeme;
    bool isFloat = false;

    while (std::isdigit(peek())) {
        lexeme += get();
    }

    if (peek() == '.') {
        isFloat = true;
        lexeme += get();
        while (std::isdigit(peek())) {
            lexeme += get();
        }
    }

    Token token;
    if (isFloat) {
        token.type = TokenType::LITERAL_FLOAT;
    } else {
        token.type = TokenType::LITERAL_INT;
    }
    token.lexeme = lexeme;
    token.line = startLine;
    token.column = startColumn;
    return token;
}

// Tokenize operators and delimiters
Token Lexer::opOrDelim() {
    int startLine = line;
    int startColumn = column;
    char c = get();
    std::string lexeme(1, c);
    Token token;

    switch (c) {
        // Single-character tokens
        case '+': token.type = TokenType::OP_PLUS; break;
        case '-': token.type = TokenType::OP_MINUS; break;
        case '*': token.type = TokenType::OP_MULTIPLY; break;
        case '/': token.type = TokenType::OP_DIVIDE; break;
        case ';': token.type = TokenType::DELIM_SEMICOLON; break;
        case ',': token.type = TokenType::DELIM_COMMA; break;
        case '(': token.type = TokenType::DELIM_LPAREN; break;
        case ')': token.type = TokenType::DELIM_RPAREN; break;
        case '{': token.type = TokenType::DELIM_LBRACE; break;
        case '}': token.type = TokenType::DELIM_RBRACE; break;
        case '=':
            if (peek() == '=') {
                get();
                lexeme += '=';
                token.type = TokenType::OP_EQUAL;
            } else {
                token.type = TokenType::OP_ASSIGN;
            }
            break;
        case '!':
            if (peek() == '=') {
                get();
                lexeme += '=';
                token.type = TokenType::OP_NOT_EQUAL;
            } else {
                token.type = TokenType::UNKNOWN;
            }
            break;
        case '<':
            if (peek() == '=') {
                get();
                lexeme += '=';
                token.type = TokenType::OP_LESS_EQUAL;
            } else {
                token.type = TokenType::OP_LESS;
            }
            break;
        case '>':
            if (peek() == '=') {
                get();
                lexeme += '=';
                token.type = TokenType::OP_GREATER_EQUAL;
            } else {
                token.type = TokenType::OP_GREATER;
            }
            break;
        default:
            token.type = TokenType::UNKNOWN;
            break;
    }

    token.lexeme = lexeme;
    token.line = startLine;
    token.column = startColumn;
    return token;
}

// Tokenize the entire source code
std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (!isAtEnd()) {
        skipWhitespace();
        if (isAtEnd()) break;

        char c = peek();
        if (std::isalpha(c) || c == '_') {
            tokens.push_back(identifier());
        } else if (std::isdigit(c)) {
            tokens.push_back(number());
        } else {
            tokens.push_back(opOrDelim());
        }
    }

    // End of File token
    Token eofToken;
    eofToken.type = TokenType::EOF_TOKEN;
    eofToken.lexeme = "EOF";
    eofToken.line = line;
    eofToken.column = column;
    tokens.push_back(eofToken);

    return tokens;
}
