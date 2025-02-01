#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "AST.hpp"
#include "SemanticAnalyzer.hpp"
#include "CodeGenerator.hpp"
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <system_error>
#include <string>

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::KW_INT: return "KW_INT";
        case TokenType::KW_FLOAT: return "KW_FLOAT";
        case TokenType::KW_CHAR: return "KW_CHAR";
        case TokenType::KW_DOUBLE: return "KW_DOUBLE";
        case TokenType::KW_BOOL: return "KW_BOOL";
        case TokenType::KW_RETURN: return "KW_RETURN";
        case TokenType::KW_IF: return "KW_IF";
        case TokenType::KW_ELSE: return "KW_ELSE";
        case TokenType::KW_WHILE: return "KW_WHILE";
        case TokenType::KW_FOR: return "KW_FOR";
        case TokenType::OP_PLUS: return "OP_PLUS";
        case TokenType::OP_MINUS: return "OP_MINUS";
        case TokenType::OP_MULTIPLY: return "OP_MULTIPLY";
        case TokenType::OP_DIVIDE: return "OP_DIVIDE";
        case TokenType::OP_ASSIGN: return "OP_ASSIGN";
        case TokenType::OP_EQUAL: return "OP_EQUAL";
        case TokenType::OP_NOT_EQUAL: return "OP_NOT_EQUAL";
        case TokenType::OP_LESS: return "OP_LESS";
        case TokenType::OP_GREATER: return "OP_GREATER";
        case TokenType::OP_LESS_EQUAL: return "OP_LESS_EQUAL";
        case TokenType::OP_GREATER_EQUAL: return "OP_GREATER_EQUAL";
        case TokenType::OP_LOGICAL_AND: return "OP_LOGICAL_AND";
        case TokenType::OP_LOGICAL_OR: return "OP_LOGICAL_OR";
        case TokenType::DELIM_SEMICOLON: return "DELIM_SEMICOLON";
        case TokenType::DELIM_COMMA: return "DELIM_COMMA";
        case TokenType::DELIM_LPAREN: return "DELIM_LPAREN";
        case TokenType::DELIM_RPAREN: return "DELIM_RPAREN";
        case TokenType::DELIM_LBRACE: return "DELIM_LBRACE";
        case TokenType::DELIM_RBRACE: return "DELIM_RBRACE";
        case TokenType::LITERAL_INT: return "LITERAL_INT";
        case TokenType::LITERAL_FLOAT: return "LITERAL_FLOAT";
        case TokenType::LITERAL_CHAR: return "LITERAL_CHAR";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::EOF_TOKEN: return "EOF_TOKEN";
        default: return "UNKNOWN";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: C99Compiler <source_file.c>\n";
        return 1;
    }

    // Read the source file
    std::ifstream sourceFile(argv[1]);
    if (!sourceFile.is_open()) {
        std::cerr << "Error: Cannot open source file " << argv[1] << "\n";
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
        std::cerr << "Lexer Error: " << e.what() << "\n";
        return 1;
    }

    std::cout << "===== Token Stream =====\n";
    for (const auto& token : tokens) {
        std::cout << "Type: " << tokenTypeToString(token.type)
                  << ", Lexeme: '" << token.lexeme
                  << "', Line: " << token.line
                  << ", Column: " << token.column << "\n";
    }
    std::cout << "========================\n\n";

    // Initialize Parser
    Parser parser(tokens);
    std::shared_ptr<Program> ast;
    try {
        ast = parser.parse();
    } catch (const std::exception& e) {
        std::cerr << "Parser Error: " << e.what() << "\n";
        return 1;
    }

    // Perform semantic analysis
    SemanticAnalyzer semanticAnalyzer;
    try {
        semanticAnalyzer.analyze(ast);
        std::cout << "Semantic analysis completed successfully.\n";
    } catch (const std::exception& e) {
        std::cerr << "Semantic Analysis Error: " << e.what() << "\n";
        return 1;
    }

    // Generate LLVM IR
    CodeGenerator codeGen;
    try {
        std::unique_ptr<llvm::Module> module = codeGen.generateCode(ast);
        std::error_code EC;
        llvm::raw_fd_ostream dest("output.ll", EC, static_cast<llvm::sys::fs::OpenFlags>(0));
        if (EC) {
            std::cerr << "Could not open file: " << EC.message() << "\n";
            return 1;
        }
        module->print(dest, nullptr);
        dest.flush();
        std::cout << "LLVM IR generated and written to 'output.ll'.\n";
    } catch (const std::exception& e) {
        std::cerr << "Code Generation Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
