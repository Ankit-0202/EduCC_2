#include "Parser.hpp"
#include "AST.hpp"
#include "Lexer.hpp"
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
    return current >= tokens.size() || tokens[current].type == TokenType::EOF_TOKEN;
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
        check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
        check(TokenType::KW_BOOL)) {
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
    std::vector<std::shared_ptr<VariableDeclaration>> decls;
    do {
        if (!check(TokenType::IDENTIFIER)) {
            error("Expected identifier after type");
        }
        Token varNameToken = advance();
        std::string varName = varNameToken.lexeme;
        std::optional<ExpressionPtr> initializer = std::nullopt;
        if (match(TokenType::OP_ASSIGN)) {
            initializer = parseExpression();
        }
        decls.push_back(std::make_shared<VariableDeclaration>(type, varName, initializer));
    } while (match(TokenType::DELIM_COMMA));
    consume(TokenType::DELIM_SEMICOLON, "Expected ';' after variable declaration");
    if (decls.size() == 1)
        return decls[0];
    else
        return std::make_shared<MultiVariableDeclaration>(decls);
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
    if (match(TokenType::DELIM_SEMICOLON)) {
        return std::make_shared<FunctionDeclaration>(returnType, funcName, parameters, nullptr);
    }
    consume(TokenType::DELIM_LBRACE, "Expected '{' before function body");
    StatementPtr body = parseCompoundStatement();
    return std::make_shared<FunctionDeclaration>(returnType, funcName, parameters, body);
}

std::vector<std::pair<std::string, std::string>> Parser::parseParameters() {
    std::vector<std::pair<std::string, std::string>> params;
    if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
        check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
        check(TokenType::KW_BOOL)) {
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
    } else if (match(TokenType::KW_SWITCH)) {
        return parseSwitchStatement();
    } else if (match(TokenType::DELIM_LBRACE)) {
        return parseCompoundStatement();
    } else if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
               check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
               check(TokenType::KW_BOOL)) {
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
    StatementPtr initializer = nullptr;
    if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
        check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
        check(TokenType::KW_BOOL)) {
        initializer = parseVariableDeclarationStatement();
    } else {
        initializer = parseExpressionStatement();
    }
    ExpressionPtr condition = nullptr;
    if (!check(TokenType::DELIM_SEMICOLON)) {
        condition = parseExpression();
    } else {
        condition = std::make_shared<Literal>(true);
    }
    consume(TokenType::DELIM_SEMICOLON, "Expected ';' after for-loop condition");
    ExpressionPtr increment = nullptr;
    if (!check(TokenType::DELIM_RPAREN)) {
        increment = parseExpression();
    }
    consume(TokenType::DELIM_RPAREN, "Expected ')' after for-loop increment");
    StatementPtr body = parseStatement();
    return std::make_shared<ForStatement>(initializer, condition, increment, body);
}

StatementPtr Parser::parseSwitchStatement() {
    // Assumes 'switch' keyword has been consumed.
    consume(TokenType::DELIM_LPAREN, "Expected '(' after 'switch'");
    ExpressionPtr expr = parseExpression();
    consume(TokenType::DELIM_RPAREN, "Expected ')' after switch expression");
    consume(TokenType::DELIM_LBRACE, "Expected '{' to begin switch block");
    std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>> cases;
    std::optional<StatementPtr> defaultCase = std::nullopt;
    while (!check(TokenType::DELIM_RBRACE) && !isAtEnd()) {
        if (match(TokenType::KW_CASE)) {
            ExpressionPtr caseExpr = parseExpression();
            consume(TokenType::DELIM_COLON, "Expected ':' after case label");
            StatementPtr caseStmt = parseStatement();
            cases.push_back({caseExpr, caseStmt});
        } else if (match(TokenType::KW_DEFAULT)) {
            consume(TokenType::DELIM_COLON, "Expected ':' after 'default'");
            defaultCase = parseStatement();
        } else {
            error("Expected 'case' or 'default' in switch statement");
        }
    }
    consume(TokenType::DELIM_RBRACE, "Expected '}' after switch block");
    return std::make_shared<SwitchStatement>(expr, cases, defaultCase);
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
    std::vector<std::shared_ptr<VariableDeclarationStatement>> decls;
    do {
        if (!check(TokenType::IDENTIFIER)) {
            error("Expected variable name in variable declaration");
        }
        Token varNameToken = advance();
        std::string varName = varNameToken.lexeme;
        std::optional<ExpressionPtr> initializer = std::nullopt;
        if (match(TokenType::OP_ASSIGN)) {
            initializer = parseExpression();
        }
        decls.push_back(std::make_shared<VariableDeclarationStatement>(type, varName, initializer));
    } while (match(TokenType::DELIM_COMMA));
    consume(TokenType::DELIM_SEMICOLON, "Expected ';' after variable declaration");
    if (decls.size() == 1)
        return decls[0];
    else
        return std::make_shared<MultiVariableDeclarationStatement>(decls);
}

// =====================================================
// Expression parsing productions with new bitwise/shift support
// =====================================================

ExpressionPtr Parser::parseExpression() {
    return parseAssignment();
}

ExpressionPtr Parser::parseAssignment() {
    ExpressionPtr expr = parseLogicalOr();
    if (!isAtEnd() &&
        (peek().type == TokenType::OP_PLUS_ASSIGN ||
         peek().type == TokenType::OP_MINUS_ASSIGN ||
         peek().type == TokenType::OP_MULTIPLY_ASSIGN ||
         peek().type == TokenType::OP_DIVIDE_ASSIGN)) {
         Token opToken = advance();
         auto identifier = std::dynamic_pointer_cast<Identifier>(expr);
         if (!identifier) {
              error("Invalid compound assignment target");
         }
         ExpressionPtr rhs = parseAssignment();
         std::string op = opToken.lexeme.substr(0, 1);
         ExpressionPtr binaryExpr = std::make_shared<BinaryExpression>(op, expr, rhs);
         return std::make_shared<Assignment>(identifier->name, binaryExpr);
    }
    else if (match(TokenType::OP_ASSIGN)) {
         auto identifier = std::dynamic_pointer_cast<Identifier>(expr);
         if (!identifier) {
             error("Invalid assignment target");
         }
         ExpressionPtr value = parseAssignment();
         return std::make_shared<Assignment>(identifier->name, value);
    }
    return expr;
}

// Logical OR (||)
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

// Logical AND (&&)
ExpressionPtr Parser::parseLogicalAnd() {
    ExpressionPtr expr = parseBitwiseOr();
    while (match(TokenType::OP_LOGICAL_AND)) {
        Token oper = tokens[current - 1];
        std::string op = oper.lexeme;
        ExpressionPtr right = parseBitwiseOr();
        expr = std::make_shared<BinaryExpression>(op, expr, right);
    }
    return expr;
}

// Bitwise OR (|)
ExpressionPtr Parser::parseBitwiseOr() {
    ExpressionPtr expr = parseBitwiseXor();
    while (match(TokenType::OP_BITWISE_OR)) {
        Token oper = tokens[current - 1];
        std::string op = oper.lexeme;
        ExpressionPtr right = parseBitwiseXor();
        expr = std::make_shared<BinaryExpression>(op, expr, right);
    }
    return expr;
}

// Bitwise XOR (^)
ExpressionPtr Parser::parseBitwiseXor() {
    ExpressionPtr expr = parseBitwiseAnd();
    while (match(TokenType::OP_BITWISE_XOR)) {
        Token oper = tokens[current - 1];
        std::string op = oper.lexeme;
        ExpressionPtr right = parseBitwiseAnd();
        expr = std::make_shared<BinaryExpression>(op, expr, right);
    }
    return expr;
}

// Bitwise AND (&)
ExpressionPtr Parser::parseBitwiseAnd() {
    ExpressionPtr expr = parseEquality();
    while (match(TokenType::OP_BITWISE_AND)) {
        Token oper = tokens[current - 1];
        std::string op = oper.lexeme;
        ExpressionPtr right = parseEquality();
        expr = std::make_shared<BinaryExpression>(op, expr, right);
    }
    return expr;
}

// Equality (==, !=)
ExpressionPtr Parser::parseEquality() {
    ExpressionPtr expr = parseRelational();
    while (match(TokenType::OP_EQUAL) || match(TokenType::OP_NOT_EQUAL)) {
        Token oper = tokens[current - 1];
        std::string op = oper.lexeme;
        ExpressionPtr right = parseRelational();
        expr = std::make_shared<BinaryExpression>(op, expr, right);
    }
    return expr;
}

// Relational (<, <=, >, >=)
ExpressionPtr Parser::parseRelational() {
    ExpressionPtr expr = parseShift();
    while (match(TokenType::OP_LESS) || match(TokenType::OP_LESS_EQUAL) ||
           match(TokenType::OP_GREATER) || match(TokenType::OP_GREATER_EQUAL)) {
        Token oper = tokens[current - 1];
        std::string op = oper.lexeme;
        ExpressionPtr right = parseShift();
        expr = std::make_shared<BinaryExpression>(op, expr, right);
    }
    return expr;
}

// Shift (<<, >>)
ExpressionPtr Parser::parseShift() {
    ExpressionPtr expr = parseTerm();
    while (match(TokenType::OP_LEFT_SHIFT) || match(TokenType::OP_RIGHT_SHIFT)) {
        Token oper = tokens[current - 1];
        std::string op = oper.lexeme;
        ExpressionPtr right = parseTerm();
        expr = std::make_shared<BinaryExpression>(op, expr, right);
    }
    return expr;
}

// Term (additive +, -)
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

// Factor (multiplicative *, /)
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

// Unary (currently just defers to postfix)
ExpressionPtr Parser::parseUnary() {
    return parsePostfix();
}

// Postfix (handles postfix ++/--)
ExpressionPtr Parser::parsePostfix() {
    ExpressionPtr expr = parsePrimary();
    while (!isAtEnd()) {
        if (current + 1 < tokens.size() &&
            tokens[current].type == TokenType::OP_PLUS &&
            tokens[current + 1].type == TokenType::OP_PLUS) {
            advance();
            advance();
            expr = std::make_shared<PostfixExpression>(expr, "++");
        } else if (current + 1 < tokens.size() &&
                   tokens[current].type == TokenType::OP_MINUS &&
                   tokens[current + 1].type == TokenType::OP_MINUS) {
            advance();
            advance();
            expr = std::make_shared<PostfixExpression>(expr, "--");
        } else {
            break;
        }
    }
    return expr;
}

// Primary (literals, identifiers, grouping)
ExpressionPtr Parser::parsePrimary() {
    if (match(TokenType::LITERAL_INT)) {
        int value = std::stoi(tokens[current - 1].lexeme);
        return std::make_shared<Literal>(value);
    }
    if (match(TokenType::LITERAL_FLOAT)) {
        float value = std::stof(tokens[current - 1].lexeme);
        return std::make_shared<Literal>(value);
    }
    if (match(TokenType::LITERAL_DOUBLE)) {
        double value = std::stod(tokens[current - 1].lexeme);
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
