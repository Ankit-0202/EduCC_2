#ifndef PARSER_HPP
#define PARSER_HPP

#include "AST.hpp"
#include "Lexer.hpp"
#include "Token.hpp"
#include <vector>
#include <memory>
#include <string>

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    std::shared_ptr<Program> parse();

private:
    std::vector<Token> tokens;
    size_t current;

    bool match(TokenType type);
    bool check(TokenType type) const;
    Token advance();
    Token peek() const;
    bool isAtEnd() const;
    void consume(TokenType type, const std::string& errorMessage);
    void error(const std::string& message) const;

    DeclarationPtr parseDeclaration();
    DeclarationPtr parseVariableDeclaration();
    DeclarationPtr parseFunctionDeclaration();
    std::vector<std::pair<std::string, std::string>> parseParameters();

    // Updated return type: now returns a shared pointer to CompoundStatement
    std::shared_ptr<CompoundStatement> parseCompoundStatement();
    StatementPtr parseStatement();
    StatementPtr parseIfStatement();
    StatementPtr parseWhileStatement();
    StatementPtr parseForStatement();
    StatementPtr parseSwitchStatement(); // NEW: switch statement
    StatementPtr parseReturnStatement();
    StatementPtr parseExpressionStatement();
    StatementPtr parseVariableDeclarationStatement();

    // Expression parsing productions.
    ExpressionPtr parseExpression();
    ExpressionPtr parseAssignment();

    // New productions for bitwise/shift operators.
    ExpressionPtr parseLogicalOr();
    ExpressionPtr parseLogicalAnd();
    ExpressionPtr parseBitwiseOr();
    ExpressionPtr parseBitwiseXor();
    ExpressionPtr parseBitwiseAnd();
    ExpressionPtr parseEquality();
    ExpressionPtr parseRelational();
    ExpressionPtr parseShift();
    ExpressionPtr parseTerm();
    ExpressionPtr parseFactor();
    ExpressionPtr parseUnary();
    ExpressionPtr parsePostfix();
    ExpressionPtr parsePrimary();
};

#endif // PARSER_HPP
