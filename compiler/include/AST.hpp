#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <utility>

// Forward declarations for expressions and statements.
struct Expression;
using ExpressionPtr = std::shared_ptr<Expression>;

struct Statement;
using StatementPtr = std::shared_ptr<Statement>;

struct Declaration;
using DeclarationPtr = std::shared_ptr<Declaration>;

struct Program {
    std::vector<DeclarationPtr> declarations;
    void addDeclaration(const DeclarationPtr& decl) {
        declarations.push_back(decl);
    }
};

// Base class for declarations.
struct Declaration {
    virtual ~Declaration() = default;
};

// Variable Declaration
struct VariableDeclaration : public Declaration {
    std::string type;
    std::string name;
    std::optional<ExpressionPtr> initializer;
    VariableDeclaration(const std::string& type, const std::string& name, std::optional<ExpressionPtr> initializer)
        : type(type), name(name), initializer(initializer) {}
};

// Multiple Variable Declaration
struct MultiVariableDeclaration : public Declaration {
    std::vector<std::shared_ptr<VariableDeclaration>> declarations;
    MultiVariableDeclaration(const std::vector<std::shared_ptr<VariableDeclaration>>& decls)
        : declarations(decls) {}
};

// Function Declaration
struct FunctionDeclaration : public Declaration {
    std::string returnType;
    std::string name;
    std::vector<std::pair<std::string, std::string>> parameters; // (type, name)
    StatementPtr body; // nullptr if only prototype
    FunctionDeclaration(const std::string& retType, const std::string& name,
                        const std::vector<std::pair<std::string, std::string>>& params,
                        StatementPtr body)
        : returnType(retType), name(name), parameters(params), body(body) {}
};

// Enum Declaration
struct EnumDeclaration : public Declaration {
    // Optional tag for the enum.
    std::optional<std::string> name;
    // Vector of enumerators: each is a pair of enumerator name and an optional initializer expression.
    std::vector<std::pair<std::string, std::optional<ExpressionPtr>>> enumerators;
    // NEW: Computed integer values for each enumerator (filled during semantic analysis)
    std::vector<int> enumeratorValues;
    EnumDeclaration(const std::optional<std::string>& name,
                    const std::vector<std::pair<std::string, std::optional<ExpressionPtr>>>& enumerators)
        : name(name), enumerators(enumerators) {}
};

// Base class for statements.
struct Statement {
    virtual ~Statement() = default;
};

// Compound Statement
struct CompoundStatement : public Statement {
    std::vector<StatementPtr> statements;
    void addStatement(const StatementPtr& stmt) {
        statements.push_back(stmt);
    }
};

// Expression Statement
struct ExpressionStatement : public Statement {
    ExpressionPtr expression;
    ExpressionStatement(ExpressionPtr expr) : expression(expr) {}
};

// Variable Declaration Statement (for local variables)
struct VariableDeclarationStatement : public Statement {
    std::string type;
    std::string name;
    std::optional<ExpressionPtr> initializer;
    VariableDeclarationStatement(const std::string& type, const std::string& name, std::optional<ExpressionPtr> initializer)
        : type(type), name(name), initializer(initializer) {}
};

// Multiple Variable Declaration Statement
struct MultiVariableDeclarationStatement : public Statement {
    std::vector<std::shared_ptr<VariableDeclarationStatement>> declarations;
    MultiVariableDeclarationStatement(const std::vector<std::shared_ptr<VariableDeclarationStatement>>& decls)
        : declarations(decls) {}
};

// If Statement
struct IfStatement : public Statement {
    ExpressionPtr condition;
    StatementPtr thenBranch;
    std::optional<StatementPtr> elseBranch;
    IfStatement(ExpressionPtr condition, StatementPtr thenBranch, std::optional<StatementPtr> elseBranch)
        : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}
};

// While Statement
struct WhileStatement : public Statement {
    ExpressionPtr condition;
    StatementPtr body;
    WhileStatement(ExpressionPtr condition, StatementPtr body)
        : condition(condition), body(body) {}
};

// For Statement
struct ForStatement : public Statement {
    StatementPtr initializer;
    ExpressionPtr condition;
    ExpressionPtr increment;
    StatementPtr body;
    ForStatement(StatementPtr initializer, ExpressionPtr condition, ExpressionPtr increment, StatementPtr body)
        : initializer(initializer), condition(condition), increment(increment), body(body) {}
};

// Switch Statement
struct SwitchStatement : public Statement {
    ExpressionPtr expression;
    // Each case: a pair of an optional case expression and the associated statement.
    std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>> cases;
    std::optional<StatementPtr> defaultCase;
    SwitchStatement(ExpressionPtr expr,
                    const std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>>& cases,
                    std::optional<StatementPtr> defaultCase)
        : expression(expr), cases(cases), defaultCase(defaultCase) {}
};

// Return Statement
struct ReturnStatement : public Statement {
    ExpressionPtr expression;
    ReturnStatement(ExpressionPtr expr) : expression(expr) {}
};

// Base class for expressions.
struct Expression {
    virtual ~Expression() = default;
};

// Binary Expression
struct BinaryExpression : public Expression {
    std::string op;
    ExpressionPtr left;
    ExpressionPtr right;
    BinaryExpression(const std::string& op, ExpressionPtr left, ExpressionPtr right)
        : op(op), left(left), right(right) {}
};

// Unary Expression
struct UnaryExpression : public Expression {
    std::string op;
    ExpressionPtr operand;
    UnaryExpression(const std::string& op, ExpressionPtr operand)
        : op(op), operand(operand) {}
};

// Postfix Expression
struct PostfixExpression : public Expression {
    ExpressionPtr operand;
    std::string op;
    PostfixExpression(ExpressionPtr operand, const std::string& op)
        : operand(operand), op(op) {}
};

// Cast Expression
struct CastExpression : public Expression {
    std::string castType;
    ExpressionPtr operand;
    CastExpression(const std::string& castType, ExpressionPtr operand)
        : castType(castType), operand(operand) {}
};

// Literal Expression (supports int, float, double, char, bool)
struct Literal : public Expression {
    std::variant<int, float, double, char, bool> value;
    Literal(int v) : value(v) {}
    Literal(float v) : value(v) {}
    Literal(double v) : value(v) {}
    Literal(char v) : value(v) {}
    Literal(bool v) : value(v) {}
};

// Identifier Expression
struct Identifier : public Expression {
    std::string name;
    Identifier(const std::string& name) : name(name) {}
};

// Assignment Expression
struct Assignment : public Expression {
    std::string lhs;
    ExpressionPtr rhs;
    Assignment(const std::string& lhs, ExpressionPtr rhs)
        : lhs(lhs), rhs(rhs) {}
};

// Function Call Expression
struct FunctionCall : public Expression {
    std::string functionName;
    std::vector<ExpressionPtr> arguments;
    FunctionCall(const std::string& functionName, const std::vector<ExpressionPtr>& arguments)
        : functionName(functionName), arguments(arguments) {}
};

#endif // AST_HPP
