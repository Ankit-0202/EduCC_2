#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <optional>

// Forward declarations
struct ASTNode;
struct Expression;
struct Statement;
struct Declaration;

// Type aliases for convenience
using ASTNodePtr = std::shared_ptr<ASTNode>;
using ExpressionPtr = std::shared_ptr<Expression>;
using StatementPtr = std::shared_ptr<Statement>;
using DeclarationPtr = std::shared_ptr<Declaration>;

// Base AST Node
struct ASTNode {
    virtual ~ASTNode() = default;
};

// Expression Nodes
struct Expression : public ASTNode {
    virtual ~Expression() = default;
};

struct BinaryExpression : public Expression {
    std::string op;
    ExpressionPtr left;
    ExpressionPtr right;

    BinaryExpression(const std::string& oper, ExpressionPtr lhs, ExpressionPtr rhs)
        : op(oper), left(lhs), right(rhs) {}
};

struct UnaryExpression : public Expression {
    std::string op;
    ExpressionPtr operand;

    UnaryExpression(const std::string& oper, ExpressionPtr opd)
        : op(oper), operand(opd) {}
};

// --- UPDATED: Literal now holds a variant with an explicit order to avoid ambiguity ---
// The order is: char, bool, int, float, double.
struct Literal : public Expression {
    std::variant<char, bool, int, float, double> value;

    Literal(int val) : value(val) {}
    Literal(float val) : value(val) {}
    Literal(char val) : value(val) {}
    Literal(double val) : value(val) {}
    Literal(bool val) : value(val) {}
};

struct Identifier : public Expression {
    std::string name;

    Identifier(const std::string& n) : name(n) {}
};

struct Assignment : public Expression {
    std::string lhs;
    ExpressionPtr rhs;

    Assignment(const std::string& left, ExpressionPtr right)
        : lhs(left), rhs(right) {}
};

struct FunctionCall : public Expression {
    std::string functionName;
    std::vector<ExpressionPtr> arguments;

    FunctionCall(const std::string& name, const std::vector<ExpressionPtr>& args)
        : functionName(name), arguments(args) {}
};

// Statement Nodes
struct Statement : public ASTNode {
    virtual ~Statement() = default;
};

struct CompoundStatement : public Statement {
    std::vector<StatementPtr> statements;

    void addStatement(StatementPtr stmt) {
        statements.push_back(stmt);
    }
};

struct ExpressionStatement : public Statement {
    ExpressionPtr expression;

    ExpressionStatement(ExpressionPtr expr) : expression(expr) {}
};

struct ReturnStatement : public Statement {
    ExpressionPtr expression;

    ReturnStatement(ExpressionPtr expr) : expression(expr) {}
};

struct IfStatement : public Statement {
    ExpressionPtr condition;
    StatementPtr thenBranch;
    std::optional<StatementPtr> elseBranch;

    IfStatement(ExpressionPtr cond, StatementPtr thenStmt, std::optional<StatementPtr> elseStmt = std::nullopt)
        : condition(cond), thenBranch(thenStmt), elseBranch(elseStmt) {}
};

// Declaration Nodes
struct Declaration : public ASTNode {
    virtual ~Declaration() = default;
};

struct VariableDeclaration : public Declaration {
    std::string type;
    std::string name;
    std::optional<ExpressionPtr> initializer;

    VariableDeclaration(const std::string& ty, const std::string& nm, std::optional<ExpressionPtr> init = std::nullopt)
        : type(ty), name(nm), initializer(init) {}
};

struct FunctionDeclaration : public Declaration {
    std::string returnType;
    std::string name;
    std::vector<std::pair<std::string, std::string>> parameters; // pair<type, name>
    StatementPtr body;

    FunctionDeclaration(const std::string& retType, const std::string& nm,
                        const std::vector<std::pair<std::string, std::string>>& params,
                        StatementPtr stmt)
        : returnType(retType), name(nm), parameters(params), body(stmt) {}
};

// Program Node
struct Program : public ASTNode {
    std::vector<DeclarationPtr> declarations;

    void addDeclaration(DeclarationPtr decl) {
        declarations.push_back(decl);
    }
};

// New AST Node for local variable declarations (as statements)
struct VariableDeclarationStatement : public Statement {
    std::string type;
    std::string name;
    std::optional<ExpressionPtr> initializer;

    VariableDeclarationStatement(const std::string& ty, const std::string& nm, std::optional<ExpressionPtr> init = std::nullopt)
        : type(ty), name(nm), initializer(init) {}
};

#endif // AST_HPP
