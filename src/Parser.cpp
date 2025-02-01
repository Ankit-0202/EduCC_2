#include "Parser.hpp"
#include "AST.hpp"
#include <stdexcept>
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), current(0) {}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return tokens[current - 1];
}

Token Parser::peek() const {
    if (isAtEnd()) {
        static Token eofToken = { TokenType::EOF_TOKEN, "EOF", 0, 0 };
        return eofToken;
    }
    return tokens[current];
}

bool Parser::isAtEnd() const {
    if (current >= tokens.size()) return true;
    return tokens[current].type == TokenType::EOF_TOKEN;
}

void Parser::consume(TokenType type, const std::string& errorMessage) {
    if (check(type)) {
        advance();
        return;
    }
    error(errorMessage);
}

void Parser::error(const std::string& message) const {
    if (current < tokens.size()) {
        const Token& tok = tokens[current];
        throw std::runtime_error("Parser Error at Line " + std::to_string(tok.line) +
                                 ", Column " + std::to_string(tok.column) + ": " + message);
    } else {
        throw std::runtime_error("Parser Error: " + message + " at end of input.");
    }
}

std::shared_ptr<Program> Parser::parse() {
    auto program = std::make_shared<Program>();
    while (!isAtEnd()) {
        DeclarationPtr decl = parseDeclaration();
        program->addDeclaration(decl);
    }
    return program;
}

DeclarationPtr Parser::parseDeclaration() {
    if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
        check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) || check(TokenType::KW_BOOL)) {
        size_t save = current;
        std::string type;
        if (match(TokenType::KW_INT)) {
            type = "int";
        } else if (match(TokenType::KW_FLOAT)) {
            type = "float";
        } else if (match(TokenType::KW_CHAR)) {
            type = "char";
        } else if (match(TokenType::KW_DOUBLE)) {
            type = "double";
        } else if (match(TokenType::KW_BOOL)) {
            type = "bool";
        } else {
            error("Expected type specifier");
        }
        if (check(TokenType::IDENTIFIER)) {
            Token identifier = advance();
            if (check(TokenType::DELIM_LPAREN)) {
                current = save;
                return parseFunctionDeclaration();
            } else {
                current = save;
                return parseVariableDeclaration();
            }
        } else {
            error("Expected identifier after type");
        }
    }
    error("Expected declaration");
    return nullptr;
}

DeclarationPtr Parser::parseVariableDeclaration() {
    std::string type;
    if (match(TokenType::KW_INT)) {
        type = "int";
    } else if (match(TokenType::KW_FLOAT)) {
        type = "float";
    } else if (match(TokenType::KW_CHAR)) {
        type = "char";
    } else if (match(TokenType::KW_DOUBLE)) {
        type = "double";
    } else if (match(TokenType::KW_BOOL)) {
        type = "bool";
    } else {
        error("Expected type specifier");
    }
    if (!check(TokenType::IDENTIFIER)) {
        error("Expected variable name");
    }
    Token varNameToken = advance();
    std::string varName = varNameToken.lexeme;
    std::optional<ExpressionPtr> initializer = std::nullopt;
    if (match(TokenType::OP_ASSIGN)) {
        initializer = parseExpression();
    }
    consume(TokenType::DELIM_SEMICOLON, "Expected ';' after variable declaration");
    return std::make_shared<VariableDeclaration>(type, varName, initializer);
}

DeclarationPtr Parser::parseFunctionDeclaration() {
    std::string returnType;
    if (match(TokenType::KW_INT)) {
        returnType = "int";
    } else if (match(TokenType::KW_FLOAT)) {
        returnType = "float";
    } else if (match(TokenType::KW_CHAR)) {
        returnType = "char";
    } else if (match(TokenType::KW_DOUBLE)) {
        returnType = "double";
    } else if (match(TokenType::KW_BOOL)) {
        returnType = "bool";
    } else {
        error("Expected return type");
    }
    if (!check(TokenType::IDENTIFIER)) {
        error("Expected function name");
    }
    Token funcNameToken = advance();
    std::string funcName = funcNameToken.lexeme;
    consume(TokenType::DELIM_LPAREN, "Expected '(' after function name");
    std::vector<std::pair<std::string, std::string>> parameters = parseParameters();
    consume(TokenType::DELIM_RPAREN, "Expected ')' after parameters");
    consume(TokenType::DELIM_LBRACE, "Expected '{' before function body");
    StatementPtr body = parseCompoundStatement();
    return std::make_shared<FunctionDeclaration>(returnType, funcName, parameters, body);
}

std::vector<std::pair<std::string, std::string>> Parser::parseParameters() {
    std::vector<std::pair<std::string, std::string>> params;
    if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
        check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) || check(TokenType::KW_BOOL)) {
        do {
            std::string type;
            if (match(TokenType::KW_INT)) {
                type = "int";
            } else if (match(TokenType::KW_FLOAT)) {
                type = "float";
            } else if (match(TokenType::KW_CHAR)) {
                type = "char";
            } else if (match(TokenType::KW_DOUBLE)) {
                type = "double";
            } else if (match(TokenType::KW_BOOL)) {
                type = "bool";
            } else {
                error("Expected parameter type");
            }
            if (!check(TokenType::IDENTIFIER)) {
                error("Expected parameter name");
            }
            Token paramNameToken = advance();
            std::string paramName = paramNameToken.lexeme;
            params.emplace_back(type, paramName);
        } while (match(TokenType::DELIM_COMMA));
    }
    return params;
}

std::shared_ptr<CompoundStatement> Parser::parseCompoundStatement() {
    auto compound = std::make_shared<CompoundStatement>();
    while (!check(TokenType::DELIM_RBRACE) && !isAtEnd()) {
        StatementPtr stmt = parseStatement();
        compound->addStatement(stmt);
    }
    consume(TokenType::DELIM_RBRACE, "Expected '}' after compound statement");
    return compound;
}

StatementPtr Parser::parseStatement() {
    if (match(TokenType::KW_IF)) {
        return parseIfStatement();
    } else if (match(TokenType::KW_RETURN)) {
        return parseReturnStatement();
    } else if (match(TokenType::KW_WHILE)) {
        return parseWhileStatement();
    } else if (match(TokenType::KW_FOR)) {
        return parseForStatement();
    } else if (match(TokenType::DELIM_LBRACE)) {
        return parseCompoundStatement();
    } else if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
               check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) || check(TokenType::KW_BOOL)) {
        return parseVariableDeclarationStatement();
    } else {
        return parseExpressionStatement();
    }
}

StatementPtr Parser::parseIfStatement() {
    consume(TokenType::DELIM_LPAREN, "Expected '(' after 'if'");
    ExpressionPtr condition = parseExpression();
    consume(TokenType::DELIM_RPAREN, "Expected ')' after condition");
    StatementPtr thenBranch = parseStatement();
    std::optional<StatementPtr> elseBranch = std::nullopt;
    if (match(TokenType::KW_ELSE)) {
        elseBranch = parseStatement();
    }
    return std::make_shared<IfStatement>(condition, thenBranch, elseBranch);
}

StatementPtr Parser::parseWhileStatement() {
    consume(TokenType::DELIM_LPAREN, "Expected '(' after 'while'");
    ExpressionPtr condition = parseExpression();
    consume(TokenType::DELIM_RPAREN, "Expected ')' after while condition");
    StatementPtr body = parseStatement();
    return std::make_shared<WhileStatement>(condition, body);
}

StatementPtr Parser::parseForStatement() {
    consume(TokenType::DELIM_LPAREN, "Expected '(' after 'for'");
    // For initializer: either a variable declaration statement or an expression statement.
    StatementPtr initializer = nullptr;
    if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
        check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) || check(TokenType::KW_BOOL)) {
        initializer = parseVariableDeclarationStatement();
    } else {
        initializer = parseExpressionStatement();
    }
    // Condition expression: optional. If missing, assume true.
    ExpressionPtr condition = nullptr;
    if (!check(TokenType::DELIM_SEMICOLON)) {
        condition = parseExpression();
    } else {
        condition = std::make_shared<Literal>(true);
    }
    consume(TokenType::DELIM_SEMICOLON, "Expected ';' after for loop condition");
    // Increment expression: optional.
    ExpressionPtr increment = nullptr;
    if (!check(TokenType::DELIM_RPAREN)) {
        increment = parseExpression();
    }
    consume(TokenType::DELIM_RPAREN, "Expected ')' after for loop increment");
    StatementPtr body = parseStatement();
    return std::make_shared<ForStatement>(initializer, condition, increment, body);
}

StatementPtr Parser::parseReturnStatement() {
    ExpressionPtr expr = parseExpression();
    consume(TokenType::DELIM_SEMICOLON, "Expected ';' after return value");
    return std::make_shared<ReturnStatement>(expr);
}

StatementPtr Parser::parseExpressionStatement() {
    ExpressionPtr expr = parseExpression();
    consume(TokenType::DELIM_SEMICOLON, "Expected ';' after expression");
    return std::make_shared<ExpressionStatement>(expr);
}

StatementPtr Parser::parseVariableDeclarationStatement() {
    std::string type;
    if (match(TokenType::KW_INT)) {
        type = "int";
    } else if (match(TokenType::KW_FLOAT)) {
        type = "float";
    } else if (match(TokenType::KW_CHAR)) {
        type = "char";
    } else if (match(TokenType::KW_DOUBLE)) {
        type = "double";
    } else if (match(TokenType::KW_BOOL)) {
        type = "bool";
    } else {
        error("Expected type specifier in variable declaration");
    }
    if (!check(TokenType::IDENTIFIER)) {
        error("Expected variable name in variable declaration");
    }
    Token varNameToken = advance();
    std::string varName = varNameToken.lexeme;
    std::optional<ExpressionPtr> initializer = std::nullopt;
    if (match(TokenType::OP_ASSIGN)) {
        initializer = parseExpression();
    }
    consume(TokenType::DELIM_SEMICOLON, "Expected ';' after variable declaration");
    return std::make_shared<VariableDeclarationStatement>(type, varName, initializer);
}

// New: Parse logical AND (&&) operators.
ExpressionPtr Parser::parseLogicalAnd() {
    ExpressionPtr expr = parseEquality();
    while (match(TokenType::OP_LOGICAL_AND)) {
        Token oper = tokens[current - 1];
        std::string op = oper.lexeme;
        ExpressionPtr right = parseEquality();
        expr = std::make_shared<BinaryExpression>(op, expr, right);
    }
    return expr;
}

// New: Parse logical OR (||) operators.
ExpressionPtr Parser::parseLogicalOr() {
    ExpressionPtr expr = parseLogicalAnd();
    while (match(TokenType::OP_LOGICAL_OR)) {
        Token oper = tokens[current - 1];
        std::string op = oper.lexeme;
        ExpressionPtr right = parseLogicalAnd();
        expr = std::make_shared<BinaryExpression>(op, expr, right);
    }
    return expr;
}

ExpressionPtr Parser::parseExpression() {
    return parseAssignment();
}

ExpressionPtr Parser::parseAssignment() {
    ExpressionPtr expr = parseLogicalOr();
    if (match(TokenType::OP_ASSIGN)) {
        if (auto identifier = std::dynamic_pointer_cast<Identifier>(expr)) {
            std::string varName = identifier->name;
            ExpressionPtr value = parseAssignment();
            return std::make_shared<Assignment>(varName, value);
        } else {
            error("Invalid assignment target");
        }
    }
    return expr;
}

ExpressionPtr Parser::parseEquality() {
    ExpressionPtr expr = parseComparison();
    while (match(TokenType::OP_EQUAL) || match(TokenType::OP_NOT_EQUAL)) {
        Token oper = tokens[current - 1];
        std::string op = oper.lexeme;
        ExpressionPtr right = parseComparison();
        expr = std::make_shared<BinaryExpression>(op, expr, right);
    }
    return expr;
}

ExpressionPtr Parser::parseComparison() {
    ExpressionPtr expr = parseTerm();
    while (match(TokenType::OP_LESS) || match(TokenType::OP_LESS_EQUAL) ||
           match(TokenType::OP_GREATER) || match(TokenType::OP_GREATER_EQUAL)) {
        Token oper = tokens[current - 1];
        std::string op = oper.lexeme;
        ExpressionPtr right = parseTerm();
        expr = std::make_shared<BinaryExpression>(op, expr, right);
    }
    return expr;
}

ExpressionPtr Parser::parseTerm() {
    ExpressionPtr expr = parseFactor();
    while (match(TokenType::OP_PLUS) || match(TokenType::OP_MINUS)) {
        Token oper = tokens[current - 1];
        std::string op = oper.lexeme;
        ExpressionPtr right = parseFactor();
        expr = std::make_shared<BinaryExpression>(op, expr, right);
    }
    return expr;
}

ExpressionPtr Parser::parseFactor() {
    ExpressionPtr expr = parseUnary();
    while (match(TokenType::OP_MULTIPLY) || match(TokenType::OP_DIVIDE)) {
        Token oper = tokens[current - 1];
        std::string op = oper.lexeme;
        ExpressionPtr right = parseUnary();
        expr = std::make_shared<BinaryExpression>(op, expr, right);
    }
    return expr;
}

ExpressionPtr Parser::parseUnary() {
    return parsePrimary();
}

ExpressionPtr Parser::parsePrimary() {
    if (match(TokenType::LITERAL_INT)) {
        int value = std::stoi(tokens[current - 1].lexeme);
        return std::make_shared<Literal>(value);
    }
    if (match(TokenType::LITERAL_FLOAT)) {
        float value = std::stof(tokens[current - 1].lexeme);
        return std::make_shared<Literal>(value);
    }
    if (match(TokenType::LITERAL_CHAR)) {
        char value = tokens[current - 1].lexeme[0];
        return std::make_shared<Literal>(value);
    }
    if (match(TokenType::IDENTIFIER)) {
        std::string name = tokens[current - 1].lexeme;
        if (name == "true") {
            return std::make_shared<Literal>(true);
        }
        if (name == "false") {
            return std::make_shared<Literal>(false);
        }
        if (match(TokenType::DELIM_LPAREN)) {
            std::vector<ExpressionPtr> args;
            if (!check(TokenType::DELIM_RPAREN)) {
                do {
                    args.push_back(parseExpression());
                } while (match(TokenType::DELIM_COMMA));
            }
            consume(TokenType::DELIM_RPAREN, "Expected ')' after function arguments");
            return std::make_shared<FunctionCall>(name, args);
        } else {
            return std::make_shared<Identifier>(name);
        }
    }
    if (match(TokenType::DELIM_LPAREN)) {
        ExpressionPtr expr = parseExpression();
        consume(TokenType::DELIM_RPAREN, "Expected ')' after expression");
        return expr;
    }
    error("Expected expression");
    return nullptr;
}
