#include "Parser.hpp"
#include <iostream>

// Constructor
Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), current(0) {}

// Entry point for parsing
std::shared_ptr<Program> Parser::parse() {
    auto program = std::make_shared<Program>();

    while (!isAtEnd()) {
        DeclarationPtr decl = parseDeclaration();
        program->addDeclaration(decl);
    }

    return program;
}

// Check if the current token matches the expected type
bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

// Check if the current token is of the specified type
bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

// Consume and return the current token
Token Parser::advance() {
    if (!isAtEnd()) current++;
    return tokens[current - 1];
}

// Return the current token without consuming it
Token Parser::peek() const {
    if (isAtEnd()) {
        static Token eofToken = { TokenType::EOF_TOKEN, "EOF", 0, 0 };
        return eofToken;
    }
    return tokens[current];
}

// Check if we've reached the end of the token stream
bool Parser::isAtEnd() const {
    if (current >= tokens.size()) return true;
    return tokens[current].type == TokenType::EOF_TOKEN;
}

// Consume a token of the expected type or throw an error
void Parser::consume(TokenType type, const std::string& errorMessage) {
    if (check(type)) {
        advance();
        return;
    }
    error(errorMessage);
}

// Parse a declaration (variable or function)
DeclarationPtr Parser::parseDeclaration() {
    if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT)) {
        // Save the current state for potential rewind
        size_t save = current;
        std::string type;
        if (match(TokenType::KW_INT)) {
            type = "int";
        }
        else if (match(TokenType::KW_FLOAT)) {
            type = "float";
        }
        else {
            error("Expected type specifier");
        }

        if (check(TokenType::IDENTIFIER)) {
            Token identifier = advance(); // consume identifier
            if (check(TokenType::DELIM_LPAREN)) {
                // Function declaration
                current = save; // Rewind to include the type and identifier
                return parseFunctionDeclaration();
            } else {
                // Variable declaration
                current = save; // Rewind to include the type and identifier
                return parseVariableDeclaration();
            }
        } else {
            error("Expected identifier after type");
        }
    }

    error("Expected declaration");
    return nullptr;
}

// Parse a variable declaration (top-level)
DeclarationPtr Parser::parseVariableDeclaration() {
    std::string type;
    if (match(TokenType::KW_INT)) {
        type = "int";
    }
    else if (match(TokenType::KW_FLOAT)) {
        type = "float";
    }
    else {
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

// Parse a function declaration
DeclarationPtr Parser::parseFunctionDeclaration() {
    std::string returnType;
    if (match(TokenType::KW_INT)) {
        returnType = "int";
    }
    else if (match(TokenType::KW_FLOAT)) {
        returnType = "float";
    }
    else {
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

// Parse function parameters
std::vector<std::pair<std::string, std::string>> Parser::parseParameters() {
    std::vector<std::pair<std::string, std::string>> params;

    if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT)) {
        do {
            std::string type;
            if (match(TokenType::KW_INT)) {
                type = "int";
            }
            else if (match(TokenType::KW_FLOAT)) {
                type = "float";
            }
            else {
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

// Parse a compound statement (block of statements)
StatementPtr Parser::parseCompoundStatement() {
    auto compound = std::make_shared<CompoundStatement>();

    while (!check(TokenType::DELIM_RBRACE) && !isAtEnd()) {
        StatementPtr stmt = parseStatement();
        compound->addStatement(stmt);
    }

    consume(TokenType::DELIM_RBRACE, "Expected '}' after compound statement");

    return compound;
}

// Parse a single statement
StatementPtr Parser::parseStatement() {
    if (match(TokenType::KW_IF)) {
        return parseIfStatement();
    }
    else if (match(TokenType::KW_RETURN)) {
        return parseReturnStatement();
    }
    else if (match(TokenType::DELIM_LBRACE)) {
        return parseCompoundStatement();
    }
    else if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT)) {
        return parseVariableDeclarationStatement();
    }
    else {
        return parseExpressionStatement();
    }
}

// Parse an if statement
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

// Parse a return statement
StatementPtr Parser::parseReturnStatement() {
    ExpressionPtr expr = parseExpression();
    consume(TokenType::DELIM_SEMICOLON, "Expected ';' after return value");
    return std::make_shared<ReturnStatement>(expr);
}

// Parse an expression statement
StatementPtr Parser::parseExpressionStatement() {
    ExpressionPtr expr = parseExpression();
    consume(TokenType::DELIM_SEMICOLON, "Expected ';' after expression");
    return std::make_shared<ExpressionStatement>(expr);
}

// Parse Variable Declaration as Statement (Local Declaration)
StatementPtr Parser::parseVariableDeclarationStatement() {
    std::string type;
    if (match(TokenType::KW_INT)) {
        type = "int";
    }
    else if (match(TokenType::KW_FLOAT)) {
        type = "float";
    }
    else {
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

// Parse an expression
ExpressionPtr Parser::parseExpression() {
    return parseAssignment();
}

// Parse an assignment expression
ExpressionPtr Parser::parseAssignment() {
    ExpressionPtr expr = parseEquality();

    if (match(TokenType::OP_ASSIGN)) {
        if (auto identifier = std::dynamic_pointer_cast<Identifier>(expr)) {
            std::string varName = identifier->name;
            ExpressionPtr value = parseAssignment();
            return std::make_shared<Assignment>(varName, value);
        }
        else {
            error("Invalid assignment target");
        }
    }

    return expr;
}

// Parse equality expressions (==, !=)
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

// Parse comparison expressions (<, >, <=, >=)
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

// Parse term expressions (+, -)
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

// Parse factor expressions (*, /)
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

// Parse unary expressions (currently limited to primary)
ExpressionPtr Parser::parseUnary() {
    // Extend here for unary operators like !, -, etc.
    return parsePrimary();
}

// Parse primary expressions (literals, identifiers, grouped expressions, function calls)
ExpressionPtr Parser::parsePrimary() {
    if (match(TokenType::LITERAL_INT)) {
        int value = std::stoi(tokens[current - 1].lexeme);
        return std::make_shared<Literal>(value);
    }

    if (match(TokenType::LITERAL_FLOAT)) {
        float value = std::stof(tokens[current - 1].lexeme);
        return std::make_shared<Literal>(value);
    }

    if (match(TokenType::IDENTIFIER)) {
        std::string name = tokens[current - 1].lexeme;
        if (match(TokenType::DELIM_LPAREN)) {
            // It's a function call
            std::vector<ExpressionPtr> args;
            if (!check(TokenType::DELIM_RPAREN)) {
                do {
                    args.push_back(parseExpression());
                } while (match(TokenType::DELIM_COMMA));
            }
            consume(TokenType::DELIM_RPAREN, "Expected ')' after function arguments");
            return std::make_shared<FunctionCall>(name, args);
        }
        else {
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

// Error handling: throw an exception with a message
void Parser::error(const std::string& message) const {
    if (current < tokens.size()) {
        const Token& tok = tokens[current];
        throw std::runtime_error("Parser Error at Line " + std::to_string(tok.line) +
                                 ", Column " + std::to_string(tok.column) + ": " + message);
    }
    else {
        throw std::runtime_error("Parser Error: " + message + " at end of input.");
    }
}
