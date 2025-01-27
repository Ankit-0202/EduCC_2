#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "AST.hpp"

// Function to create indentation
std::string indentStr(int indent) {
    return std::string(indent, ' ');
}

// Utility function to convert TokenType to string
std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::KW_INT: return "KW_INT";
        case TokenType::KW_FLOAT: return "KW_FLOAT";
        case TokenType::KW_IF: return "KW_IF";
        case TokenType::KW_ELSE: return "KW_ELSE";
        case TokenType::KW_RETURN: return "KW_RETURN";
        case TokenType::OP_ASSIGN: return "OP_ASSIGN";
        case TokenType::OP_PLUS: return "OP_PLUS";
        case TokenType::OP_MINUS: return "OP_MINUS";
        case TokenType::OP_MULTIPLY: return "OP_MULTIPLY";
        case TokenType::OP_DIVIDE: return "OP_DIVIDE";
        case TokenType::OP_LESS: return "OP_LESS";
        case TokenType::OP_GREATER: return "OP_GREATER";
        case TokenType::OP_EQUAL: return "OP_EQUAL";
        case TokenType::OP_NOT_EQUAL: return "OP_NOT_EQUAL";
        case TokenType::DELIM_LPAREN: return "DELIM_LPAREN";
        case TokenType::DELIM_RPAREN: return "DELIM_RPAREN";
        case TokenType::DELIM_LBRACE: return "DELIM_LBRACE";
        case TokenType::DELIM_RBRACE: return "DELIM_RBRACE";
        case TokenType::DELIM_SEMICOLON: return "DELIM_SEMICOLON";
        case TokenType::LITERAL_INT: return "LITERAL_INT";
        case TokenType::LITERAL_FLOAT: return "LITERAL_FLOAT";
        case TokenType::EOF_TOKEN: return "EOF_TOKEN";
        // Add other token types as needed
        default: return "UNKNOWN";
    }
}


// Forward declarations for printing functions
void printExpression(const ExpressionPtr& expr, int indent);
void printStatement(const StatementPtr& stmt, int indent);
void printDeclaration(const DeclarationPtr& decl, int indent);
void printAST(const std::shared_ptr<Program>& program, int indent);

// Function to print expressions
void printExpression(const ExpressionPtr& expr, int indent) {
    if (!expr) {
        std::cout << indentStr(indent) << "Null Expression\n";
        return;
    }
    std::string indentation = indentStr(indent);
    if (auto binExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
        std::cout << indentation << "BinaryExpression: " << binExpr->op << "\n";
        printExpression(binExpr->left, indent + 4);
        printExpression(binExpr->right, indent + 4);
    }
    else if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
        std::cout << indentation << "Literal: ";
        if (std::holds_alternative<int>(lit->value)) {
            std::cout << std::get<int>(lit->value) << "\n";
        }
        else if (std::holds_alternative<float>(lit->value)) {
            std::cout << std::get<float>(lit->value) << "\n";
        }
    }
    else if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
        std::cout << indentation << "Identifier: " << id->name << "\n";
    }
    else if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
        std::cout << indentation << "Assignment: " << assign->lhs << "\n";
        printExpression(assign->rhs, indent + 4);
    }
    else if (auto funcCall = std::dynamic_pointer_cast<FunctionCall>(expr)) {
        std::cout << indentation << "FunctionCall: " << funcCall->functionName << "\n";
        for (const auto& arg : funcCall->arguments) {
            printExpression(arg, indent + 4);
        }
    }
    else {
        std::cout << indentation << "Unknown Expression\n";
    }
}

// Function to print statements
void printStatement(const StatementPtr& stmt, int indent) {
    if (!stmt) {
        std::cout << indentStr(indent) << "Null Statement\n";
        return;
    }
    std::string indentation = indentStr(indent);
    if (auto compound = std::dynamic_pointer_cast<CompoundStatement>(stmt)) {
        std::cout << indentation << "CompoundStatement {\n";
        for (const auto& s : compound->statements) {
            printStatement(s, indent + 4);
        }
        std::cout << indentation << "}\n";
    }
    else if (auto exprStmt = std::dynamic_pointer_cast<ExpressionStatement>(stmt)) {
        std::cout << indentation << "ExpressionStatement:\n";
        printExpression(exprStmt->expression, indent + 4);
    }
    else if (auto retStmt = std::dynamic_pointer_cast<ReturnStatement>(stmt)) {
        std::cout << indentation << "ReturnStatement:\n";
        printExpression(retStmt->expression, indent + 4);
    }
    else if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(stmt)) {
        std::cout << indentation << "IfStatement:\n";
        std::cout << indentation << "Condition:\n";
        printExpression(ifStmt->condition, indent + 4);
        std::cout << indentation << "Then:\n";
        printStatement(ifStmt->thenBranch, indent + 4);
        if (ifStmt->elseBranch) {
            std::cout << indentation << "Else:\n";
            printStatement(ifStmt->elseBranch.value(), indent + 4);
        }
    }
    else if (auto varDeclStmt = std::dynamic_pointer_cast<VariableDeclarationStatement>(stmt)) {
        std::cout << indentation << "VariableDeclaration: " << varDeclStmt->type << " " << varDeclStmt->name;
        if (varDeclStmt->initializer) {
            std::cout << " = ";
            printExpression(varDeclStmt->initializer.value(), 0); // Pass indent=0 for initializer
        }
        std::cout << ";\n";
    }
    else {
        std::cout << indentation << "Unknown Statement\n";
    }
}

// Function to print declarations
void printDeclaration(const DeclarationPtr& decl, int indent) {
    if (!decl) {
        std::cout << indentStr(indent) << "Null Declaration\n";
        return;
    }
    std::string indentation = indentStr(indent);
    if (auto varDecl = std::dynamic_pointer_cast<VariableDeclaration>(decl)) {
        std::cout << indentation << "VariableDeclaration: " << varDecl->type << " " << varDecl->name;
        if (varDecl->initializer) {
            std::cout << " = ";
            printExpression(varDecl->initializer.value(), 0); // Pass indent=0 for initializer
        }
        std::cout << ";\n";
    }
    else if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclaration>(decl)) {
        std::cout << indentation << "FunctionDeclaration: " << funcDecl->returnType << " " << funcDecl->name << "(";
        for (size_t i = 0; i < funcDecl->parameters.size(); ++i) {
            std::cout << funcDecl->parameters[i].first << " " << funcDecl->parameters[i].second;
            if (i < funcDecl->parameters.size() - 1) std::cout << ", ";
        }
        std::cout << ")\n";
        printStatement(funcDecl->body, indent + 4);
    }
    else {
        std::cout << indentation << "Unknown Declaration\n";
    }
}

// Function to print the entire AST
void printAST(const std::shared_ptr<Program>& program, int indent) {
    if (!program) {
        std::cout << "Empty AST\n";
        return;
    }
    std::cout << "===== AST =====\n";
    for (const auto& decl : program->declarations) {
        printDeclaration(decl, indent);
    }
    std::cout << "==============\n";
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
    }
    catch (const std::exception& e) {
        std::cerr << "Lexer Error: " << e.what() << "\n";
        return 1;
    }

    // **Debugging: Print Token Stream**
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
    }
    catch (const std::exception& e) {
        std::cerr << "Parser Error: " << e.what() << "\n";
        return 1;
    }

    // Print AST
    try {
        printAST(ast, 0);
    }
    catch (const std::exception& e) {
        std::cerr << "Error while printing AST: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
