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
struct Expression : ASTNode {
    virtual ~Expression() = default;
};

struct BinaryExpression : Expression {
    std::string op;
    ExpressionPtr left;
    ExpressionPtr right;

    BinaryExpression(const std::string& oper, ExpressionPtr lhs, ExpressionPtr rhs)
        : op(oper), left(lhs), right(rhs) {}
};

struct Literal : Expression {
    std::variant<int, float> value;

    Literal(int val) : value(val) {}
    Literal(float val) : value(val) {}
};

struct Identifier : Expression {
    std::string name;

    Identifier(const std::string& n) : name(n) {}
};

struct Assignment : Expression {
    std::string lhs;
    ExpressionPtr rhs;

    Assignment(const std::string& left, ExpressionPtr right)
        : lhs(left), rhs(right) {}
};

// Function Call Expression
struct FunctionCall : Expression {
    std::string functionName;
    std::vector<ExpressionPtr> arguments;

    FunctionCall(const std::string& name, const std::vector<ExpressionPtr>& args)
        : functionName(name), arguments(args) {}
};

// Statement Nodes
struct Statement : ASTNode {
    virtual ~Statement() = default;
};

struct CompoundStatement : Statement {
    std::vector<StatementPtr> statements;

    void addStatement(StatementPtr stmt) {
        statements.push_back(stmt);
    }
};

struct ExpressionStatement : Statement {
    ExpressionPtr expression;

    ExpressionStatement(ExpressionPtr expr) : expression(expr) {}
};

struct ReturnStatement : Statement {
    ExpressionPtr expression;

    ReturnStatement(ExpressionPtr expr) : expression(expr) {}
};

struct IfStatement : Statement {
    ExpressionPtr condition;
    StatementPtr thenBranch;
    std::optional<StatementPtr> elseBranch;

    IfStatement(ExpressionPtr cond, StatementPtr thenStmt, std::optional<StatementPtr> elseStmt = std::nullopt)
        : condition(cond), thenBranch(thenStmt), elseBranch(elseStmt) {}
};

// Declaration Nodes
struct Declaration : ASTNode {
    virtual ~Declaration() = default;
};

struct VariableDeclaration : Declaration {
    std::string type;
    std::string name;
    std::optional<ExpressionPtr> initializer;

    VariableDeclaration(const std::string& ty, const std::string& nm, std::optional<ExpressionPtr> init = std::nullopt)
        : type(ty), name(nm), initializer(init) {}
};

struct FunctionDeclaration : Declaration {
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
struct Program : ASTNode {
    std::vector<DeclarationPtr> declarations;

    void addDeclaration(DeclarationPtr decl) {
        declarations.push_back(decl);
    }
};

// **New AST Node for Local Variable Declarations**
struct VariableDeclarationStatement : Statement {
    std::string type;
    std::string name;
    std::optional<ExpressionPtr> initializer;

    VariableDeclarationStatement(const std::string& ty, const std::string& nm, std::optional<ExpressionPtr> init = std::nullopt)
        : type(ty), name(nm), initializer(init) {}
};

#endif // AST_HPP
