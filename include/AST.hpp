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

struct PostfixExpression : public Expression {
    ExpressionPtr operand;
    std::string op; // "++" or "--"
    PostfixExpression(ExpressionPtr operand, const std::string& op)
        : operand(operand), op(op) {}
};

// Literal: the variant order is: char, bool, int, float, double.
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
    IfStatement(ExpressionPtr cond, StatementPtr thenStmt,
                std::optional<StatementPtr> elseStmt = std::nullopt)
        : condition(cond), thenBranch(thenStmt), elseBranch(elseStmt) {}
};

struct WhileStatement : public Statement {
    ExpressionPtr condition;
    StatementPtr body;
    WhileStatement(ExpressionPtr cond, StatementPtr body)
        : condition(cond), body(body) {}
};

struct ForStatement : public Statement {
    StatementPtr initializer;
    ExpressionPtr condition;
    ExpressionPtr increment;
    StatementPtr body;
    ForStatement(StatementPtr init, ExpressionPtr cond,
                 ExpressionPtr incr, StatementPtr body)
        : initializer(init), condition(cond), increment(incr), body(body) {}
};

// NEW: SwitchStatement node
struct SwitchStatement : public Statement {
    ExpressionPtr condition;
    std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>> cases;
    std::optional<StatementPtr> defaultCase;
    SwitchStatement(ExpressionPtr cond,
                    const std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>>& cases,
                    const std::optional<StatementPtr>& defaultCase = std::nullopt)
        : condition(cond), cases(cases), defaultCase(defaultCase) {}
};

// Declaration Nodes
struct Declaration : public ASTNode {
    virtual ~Declaration() = default;
};

struct VariableDeclaration : public Declaration {
    std::string type;
    std::string name;
    std::optional<ExpressionPtr> initializer;
    VariableDeclaration(const std::string& ty, const std::string& nm,
                        std::optional<ExpressionPtr> init = std::nullopt)
        : type(ty), name(nm), initializer(init) {}
};

struct MultiVariableDeclaration : public Declaration {
    std::vector<std::shared_ptr<VariableDeclaration>> declarations;
    MultiVariableDeclaration(const std::vector<std::shared_ptr<VariableDeclaration>>& decls)
        : declarations(decls) {}
};

struct FunctionDeclaration : public Declaration {
    std::string returnType;
    std::string name;
    std::vector<std::pair<std::string, std::string>> parameters;
    StatementPtr body;  // If nullptr, it's just a prototype.
    FunctionDeclaration(const std::string& retType,
                        const std::string& nm,
                        const std::vector<std::pair<std::string, std::string>>& params,
                        StatementPtr stmt)
        : returnType(retType), name(nm), parameters(params), body(stmt) {}
};

struct Program : public ASTNode {
    std::vector<DeclarationPtr> declarations;
    void addDeclaration(DeclarationPtr decl) {
        declarations.push_back(decl);
    }
};

struct VariableDeclarationStatement : public Statement {
    std::string type;
    std::string name;
    std::optional<ExpressionPtr> initializer;
    VariableDeclarationStatement(const std::string& ty, const std::string& nm,
                                 std::optional<ExpressionPtr> init = std::nullopt)
        : type(ty), name(nm), initializer(init) {}
};

struct MultiVariableDeclarationStatement : public Statement {
    std::vector<std::shared_ptr<VariableDeclarationStatement>> declarations;
    MultiVariableDeclarationStatement(const std::vector<std::shared_ptr<VariableDeclarationStatement>>& decls)
        : declarations(decls) {}
};

#endif // AST_HPP
