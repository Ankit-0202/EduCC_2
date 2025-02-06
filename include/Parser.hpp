#ifndef PARSER_HPP
#define PARSER_HPP

#include "AST.hpp"
#include "Lexer.hpp"
#include <vector>
#include <memory>
#include <stdexcept>

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

    // Unify prototypes & definitions here.
    DeclarationPtr parseFunctionDeclaration();

    std::vector<std::pair<std::string, std::string>> parseParameters();
    std::shared_ptr<CompoundStatement> parseCompoundStatement();
    StatementPtr parseStatement();
    StatementPtr parseIfStatement();
    StatementPtr parseWhileStatement();
    StatementPtr parseForStatement();
    StatementPtr parseReturnStatement();
    StatementPtr parseExpressionStatement();
    StatementPtr parseVariableDeclarationStatement();

    ExpressionPtr parseExpression();
    ExpressionPtr parseAssignment();
    ExpressionPtr parseLogicalOr();
    ExpressionPtr parseLogicalAnd();
    ExpressionPtr parseEquality();
    ExpressionPtr parseComparison();
    ExpressionPtr parseTerm();
    ExpressionPtr parseFactor();
    ExpressionPtr parseUnary();
    ExpressionPtr parsePrimary();
};

#endif // PARSER_HPP
