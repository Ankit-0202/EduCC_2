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
                                 ", Column " + std::to_string(tok.column) +
                                 " (token: '" + tok.lexeme + "'): " + message);
    } else {
        throw std::runtime_error("Parser Error at end of input: " + message);
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
    // Handle union declarations (both tagged and anonymous)
    if (check(TokenType::KW_UNION)) {
        return parseUnionDeclaration();
    }
    // Handle enum declarations (both tagged and anonymous)
    if (check(TokenType::KW_ENUM)) {
        size_t save = current;
        advance(); // consume KW_ENUM
        if (check(TokenType::IDENTIFIER)) {
            advance(); // consume tag
            if (check(TokenType::DELIM_LBRACE)) {
                current = save;
                return parseEnumDeclaration();
            }
            current = save; // Not followed by '{', so treat as part of a variable declaration.
        } else if (check(TokenType::DELIM_LBRACE)) {
            current = save;
            return parseEnumDeclaration();
        }
        current = save;
    }
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
        error("Expected return type for function declaration");
    }
    if (!check(TokenType::IDENTIFIER)) {
        error("Expected function name after return type");
    }
    Token funcNameToken = advance();
    std::string funcName = funcNameToken.lexeme;
    consume(TokenType::DELIM_LPAREN, "Expected '(' after function name");
    std::vector<std::pair<std::string, std::string>> parameters = parseParameters();
    consume(TokenType::DELIM_RPAREN, "Expected ')' after parameter list");
    if (match(TokenType::DELIM_SEMICOLON)) {
        return std::make_shared<FunctionDeclaration>(returnType, funcName, parameters, nullptr);
    }
    consume(TokenType::DELIM_LBRACE, "Expected '{' to begin function body");
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
                error("Expected parameter name after type");
            }
            Token paramNameToken = advance();
            std::string paramName = paramNameToken.lexeme;
            params.emplace_back(type, paramName);
        } while (match(TokenType::DELIM_COMMA));
    }
    return params;
}

DeclarationPtr Parser::parseEnumDeclaration() {
    consume(TokenType::KW_ENUM, "Expected 'enum' keyword");
    std::optional<std::string> tag = std::nullopt;
    if (check(TokenType::IDENTIFIER)) {
        Token tagToken = advance();
        tag = tagToken.lexeme;
    }
    consume(TokenType::DELIM_LBRACE, "Expected '{' to start enum body");
    std::vector<std::pair<std::string, std::optional<ExpressionPtr>>> enumerators;
    bool first = true;
    while (!check(TokenType::DELIM_RBRACE) && !isAtEnd()) {
        if (!first) {
            if (!match(TokenType::DELIM_COMMA)) {
                error("Expected ',' between enumerators in enum declaration");
            }
        }
        first = false;
        if (!check(TokenType::IDENTIFIER)) {
            error("Expected enumerator name in enum declaration");
        }
        Token enumToken = advance();
        std::string enumeratorName = enumToken.lexeme;
        std::optional<ExpressionPtr> initializer = std::nullopt;
        if (match(TokenType::OP_ASSIGN)) {
            initializer = parseExpression();
        }
        enumerators.push_back({enumeratorName, initializer});
    }
    consume(TokenType::DELIM_RBRACE, "Expected '}' to close enum declaration");
    consume(TokenType::DELIM_SEMICOLON, "Expected ';' after enum declaration");
    return std::make_shared<EnumDeclaration>(tag, enumerators);
}

std::shared_ptr<VariableDeclaration> Parser::parseUnionMemberDeclaration() {
    // Parse a union member declaration.
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
    } else if (match(TokenType::KW_ENUM)) {
        if (!check(TokenType::IDENTIFIER))
            error("Expected enum tag after 'enum' in union member declaration");
        std::string tag = advance().lexeme;
        type = "enum " + tag;
    } else {
        error("Expected type specifier in union member declaration");
    }
    std::string name;
    if (check(TokenType::IDENTIFIER)) {
        Token nameToken = advance();
        name = nameToken.lexeme;
    } else {
        static int anonCounter = 0;
        name = "anon_" + type + "_" + std::to_string(anonCounter++);
    }
    consume(TokenType::DELIM_SEMICOLON, "Expected ';' after union member declaration");
    return std::make_shared<VariableDeclaration>(type, name, std::nullopt);
}

DeclarationPtr Parser::parseUnionDeclaration() {
    consume(TokenType::KW_UNION, "Expected 'union' keyword");
    std::optional<std::string> tag = std::nullopt;
    if (check(TokenType::IDENTIFIER)) {
        Token tagToken = advance();
        tag = tagToken.lexeme;
    }
    consume(TokenType::DELIM_LBRACE, "Expected '{' to begin union declaration");
    std::vector<std::shared_ptr<VariableDeclaration>> members;
    while (!check(TokenType::DELIM_RBRACE) && !isAtEnd()) {
        auto memberDecl = parseUnionMemberDeclaration();
        members.push_back(memberDecl);
    }
    consume(TokenType::DELIM_RBRACE, "Expected '}' to close union declaration");
    consume(TokenType::DELIM_SEMICOLON, "Expected ';' after union declaration");
    return std::make_shared<UnionDeclaration>(tag, members);
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
             check(TokenType::KW_BOOL) || check(TokenType::KW_ENUM) || check(TokenType::KW_UNION)) {
        return parseVariableDeclarationStatement();
    } else {
        return parseExpressionStatement();
    }
}

StatementPtr Parser::parseIfStatement() {
    consume(TokenType::DELIM_LPAREN, "Expected '(' after 'if'");
    ExpressionPtr condition = parseExpression();
    consume(TokenType::DELIM_RPAREN, "Expected ')' after 'if' condition");
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
    consume(TokenType::DELIM_RPAREN, "Expected ')' after 'while' condition");
    StatementPtr body = parseStatement();
    return std::make_shared<WhileStatement>(condition, body);
}

StatementPtr Parser::parseForStatement() {
    consume(TokenType::DELIM_LPAREN, "Expected '(' after 'for'");
    StatementPtr initializer = nullptr;
    if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
        check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
        check(TokenType::KW_BOOL) || check(TokenType::KW_ENUM) || check(TokenType::KW_UNION)) {
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
    consume(TokenType::DELIM_SEMICOLON, "Expected ';' after return statement");
    return std::make_shared<ReturnStatement>(expr);
}

StatementPtr Parser::parseExpressionStatement() {
    ExpressionPtr expr = parseExpression();
    consume(TokenType::DELIM_SEMICOLON, "Expected ';' after expression");
    return std::make_shared<ExpressionStatement>(expr);
}

StatementPtr Parser::parseVariableDeclarationStatement() {
    std::string type;
    // Allow "enum" and "union" as type specifiers.
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
    } else if (match(TokenType::KW_ENUM)) {
        if (!check(TokenType::IDENTIFIER)) {
            error("Expected enum tag after 'enum' in variable declaration");
        }
        std::string tag = advance().lexeme;
        type = "enum " + tag;
    } else if (match(TokenType::KW_UNION)) {
        if (!check(TokenType::IDENTIFIER)) {
            error("Expected union tag after 'union' in variable declaration");
        }
        std::string tag = advance().lexeme;
        type = "union " + tag;
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

//
// Expression parsing productions
//
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
         ExpressionPtr rhs = parseAssignment();
         std::string op = opToken.lexeme.substr(0, 1);
         ExpressionPtr binaryExpr = std::make_shared<BinaryExpression>(op, expr, rhs);
         return std::make_shared<Assignment>(expr, binaryExpr);
    }
    else if (match(TokenType::OP_ASSIGN)) {
         ExpressionPtr value = parseAssignment();
         return std::make_shared<Assignment>(expr, value);
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

//
// Modified parseUnary() to support cast expressions.
//
ExpressionPtr Parser::parseUnary() {
    if (match(TokenType::DELIM_LPAREN)) {
        // Check if this is a cast expression: ( type ) cast-expression
        if (check(TokenType::KW_INT) || check(TokenType::KW_FLOAT) ||
            check(TokenType::KW_CHAR) || check(TokenType::KW_DOUBLE) ||
            check(TokenType::KW_BOOL)) {
            std::string castType;
            if (match(TokenType::KW_INT))
                castType = "int";
            else if (match(TokenType::KW_FLOAT))
                castType = "float";
            else if (match(TokenType::KW_CHAR))
                castType = "char";
            else if (match(TokenType::KW_DOUBLE))
                castType = "double";
            else if (match(TokenType::KW_BOOL))
                castType = "bool";
            consume(TokenType::DELIM_RPAREN, "Expected ')' after cast type");
            ExpressionPtr operand = parseUnary();
            return std::make_shared<CastExpression>(castType, operand);
        } else {
            // Not a cast; treat as a parenthesized (grouped) expression.
            ExpressionPtr expr = parseExpression();
            consume(TokenType::DELIM_RPAREN, "Expected ')' after expression");
            return expr;
        }
    }
    return parsePostfix();
}

// Postfix (handles postfix ++/--)
ExpressionPtr Parser::parsePostfix() {
    ExpressionPtr expr = parsePrimary();
    while (!isAtEnd()) {
        if (match(TokenType::DOT)) {
            // Expect an identifier after the dot.
            if (!check(TokenType::IDENTIFIER))
                error("Expected identifier after '.' for member access");
            Token memberToken = advance();
            std::string memberName = memberToken.lexeme;
            expr = std::make_shared<MemberAccess>(expr, memberName);
        }
        else if (current + 1 < tokens.size() &&
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
