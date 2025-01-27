// Parser.hpp
#ifndef PARSER_HPP
#define PARSER_HPP

#include "AST.hpp"
#include "Lexer.hpp"
#include <vector>
#include <memory>

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

    DeclarationPtr parseDeclaration();
    DeclarationPtr parseVariableDeclaration();
    DeclarationPtr parseFunctionDeclaration();
    std::vector<std::pair<std::string, std::string>> parseParameters();
    StatementPtr parseCompoundStatement();
    StatementPtr parseStatement();
    StatementPtr parseIfStatement();
    StatementPtr parseReturnStatement();
    StatementPtr parseExpressionStatement();
    StatementPtr parseVariableDeclarationStatement();

    ExpressionPtr parseExpression();
    ExpressionPtr parseAssignment();
    ExpressionPtr parseEquality();
    ExpressionPtr parseComparison();
    ExpressionPtr parseTerm();
    ExpressionPtr parseFactor();
    ExpressionPtr parseUnary();
    ExpressionPtr parsePrimary();

    void error(const std::string& message) const;
};

#endif // PARSER_HPP
