#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: C99Compiler <source_file.c>" << std::endl;
        return 1;
    }

    // Read the source file
    std::ifstream sourceFile(argv[1]);
    if (!sourceFile.is_open()) {
        std::cerr << "Error: Cannot open source file " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << sourceFile.rdbuf();
    std::string sourceCode = buffer.str();

    // Initialize Lexer
    Lexer lexer(sourceCode);
    std::vector<Token> tokens;

    try {
        tokens = lexer.tokenize();
    } catch (const std::exception& e) {
        std::cerr << "Lexer Error: " << e.what() << std::endl;
        return 1;
    }

    // Print Tokens
    for (const auto& token : tokens) {
        std::cout << "Line " << token.line << ", Column " << token.column << ": ";
        switch (token.type) {
            case TokenType::KW_INT: std::cout << "KW_INT"; break;
            case TokenType::KW_FLOAT: std::cout << "KW_FLOAT"; break;
            case TokenType::KW_RETURN: std::cout << "KW_RETURN"; break;
            case TokenType::KW_IF: std::cout << "KW_IF"; break;
            case TokenType::KW_ELSE: std::cout << "KW_ELSE"; break;
            case TokenType::KW_WHILE: std::cout << "KW_WHILE"; break;
            case TokenType::KW_FOR: std::cout << "KW_FOR"; break;
            case TokenType::OP_PLUS: std::cout << "OP_PLUS"; break;
            case TokenType::OP_MINUS: std::cout << "OP_MINUS"; break;
            case TokenType::OP_MULTIPLY: std::cout << "OP_MULTIPLY"; break;
            case TokenType::OP_DIVIDE: std::cout << "OP_DIVIDE"; break;
            case TokenType::OP_ASSIGN: std::cout << "OP_ASSIGN"; break;
            case TokenType::OP_EQUAL: std::cout << "OP_EQUAL"; break;
            case TokenType::OP_NOT_EQUAL: std::cout << "OP_NOT_EQUAL"; break;
            case TokenType::OP_LESS: std::cout << "OP_LESS"; break;
            case TokenType::OP_GREATER: std::cout << "OP_GREATER"; break;
            case TokenType::OP_LESS_EQUAL: std::cout << "OP_LESS_EQUAL"; break;
            case TokenType::OP_GREATER_EQUAL: std::cout << "OP_GREATER_EQUAL"; break;
            case TokenType::DELIM_SEMICOLON: std::cout << "DELIM_SEMICOLON"; break;
            case TokenType::DELIM_COMMA: std::cout << "DELIM_COMMA"; break;
            case TokenType::DELIM_LPAREN: std::cout << "DELIM_LPAREN"; break;
            case TokenType::DELIM_RPAREN: std::cout << "DELIM_RPAREN"; break;
            case TokenType::DELIM_LBRACE: std::cout << "DELIM_LBRACE"; break;
            case TokenType::DELIM_RBRACE: std::cout << "DELIM_RBRACE"; break;
            case TokenType::LITERAL_INT: std::cout << "LITERAL_INT"; break;
            case TokenType::LITERAL_FLOAT: std::cout << "LITERAL_FLOAT"; break;
            case TokenType::IDENTIFIER: std::cout << "IDENTIFIER"; break;
            case TokenType::EOF_TOKEN: std::cout << "EOF"; break;
            case TokenType::UNKNOWN: std::cout << "UNKNOWN"; break;
            default: std::cout << "UNKNOWN"; break;
        }
        std::cout << " (" << token.lexeme << ")" << std::endl;
    }

    return 0;
}
