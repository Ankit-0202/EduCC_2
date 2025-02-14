#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <utility>

// Forward declarations for statements and expressions
class Statement;
using StatementPtr = std::shared_ptr<Statement>;

class Expression;
using ExpressionPtr = std::shared_ptr<Expression>;

// Base class for all declarations
class Declaration {
public:
    virtual ~Declaration() = default;
};

using DeclarationPtr = std::shared_ptr<Declaration>;

// Program holds a list of declarations
class Program {
public:
    std::vector<DeclarationPtr> declarations;
    void addDeclaration(const DeclarationPtr& decl) {
        declarations.push_back(decl);
    }
};

// Variable Declaration
class VariableDeclaration : public Declaration {
public:
    std::string type;
    std::string name;
    std::optional<ExpressionPtr> initializer;
    VariableDeclaration(const std::string &type, const std::string &name, std::optional<ExpressionPtr> init)
        : type(type), name(name), initializer(init) {}
};

// Multi-variable Declaration
class MultiVariableDeclaration : public Declaration {
public:
    std::vector<std::shared_ptr<VariableDeclaration>> declarations;
    MultiVariableDeclaration(const std::vector<std::shared_ptr<VariableDeclaration>> &decls)
        : declarations(decls) {}
};

// Function Declaration
class FunctionDeclaration : public Declaration {
public:
    std::string returnType;
    std::string name;
    std::vector<std::pair<std::string, std::string>> parameters; // pair<type, name>
    StatementPtr body;
    FunctionDeclaration(const std::string &retType, const std::string &name,
                        const std::vector<std::pair<std::string, std::string>> &params,
                        StatementPtr body)
        : returnType(retType), name(name), parameters(params), body(body) {}
};

// Enum Declaration
class EnumDeclaration : public Declaration {
public:
    std::optional<std::string> tag;
    std::vector<std::pair<std::string, std::optional<ExpressionPtr>>> enumerators;
    std::vector<int> enumeratorValues;
    EnumDeclaration(const std::optional<std::string>& tag,
                    const std::vector<std::pair<std::string, std::optional<ExpressionPtr>>> &enumerators)
        : tag(tag), enumerators(enumerators) {}
};

// Union Declaration
class UnionDeclaration : public Declaration {
public:
    std::optional<std::string> tag;
    std::vector<std::shared_ptr<VariableDeclaration>> members;
    UnionDeclaration(const std::optional<std::string>& tag,
                     const std::vector<std::shared_ptr<VariableDeclaration>> &members)
        : tag(tag), members(members) {}
};

// New: Struct Declaration
class StructDeclaration : public Declaration {
public:
    std::optional<std::string> tag;
    std::vector<std::shared_ptr<VariableDeclaration>> members;
    StructDeclaration(const std::optional<std::string>& tag,
                      const std::vector<std::shared_ptr<VariableDeclaration>> &members)
        : tag(tag), members(members) {}
};

// Statements

class Statement {
public:
    virtual ~Statement() = default;
};

using StatementPtr = std::shared_ptr<Statement>;

class CompoundStatement : public Statement {
public:
    std::vector<StatementPtr> statements;
    void addStatement(const StatementPtr& stmt) {
        statements.push_back(stmt);
    }
};

class ExpressionStatement : public Statement {
public:
    ExpressionPtr expression;
    ExpressionStatement(ExpressionPtr expr) : expression(expr) {}
};

class VariableDeclarationStatement : public Statement {
public:
    std::string type;
    std::string name;
    std::optional<ExpressionPtr> initializer;
    VariableDeclarationStatement(const std::string &type, const std::string &name, std::optional<ExpressionPtr> init)
        : type(type), name(name), initializer(init) {}
};

class MultiVariableDeclarationStatement : public Statement {
public:
    std::vector<std::shared_ptr<VariableDeclarationStatement>> declarations;
    MultiVariableDeclarationStatement(const std::vector<std::shared_ptr<VariableDeclarationStatement>> &decls)
        : declarations(decls) {}
};

class IfStatement : public Statement {
public:
    ExpressionPtr condition;
    StatementPtr thenBranch;
    std::optional<StatementPtr> elseBranch;
    IfStatement(ExpressionPtr cond, StatementPtr thenBranch, std::optional<StatementPtr> elseBranch)
        : condition(cond), thenBranch(thenBranch), elseBranch(elseBranch) {}
};

class WhileStatement : public Statement {
public:
    ExpressionPtr condition;
    StatementPtr body;
    WhileStatement(ExpressionPtr cond, StatementPtr body)
        : condition(cond), body(body) {}
};

class ForStatement : public Statement {
public:
    StatementPtr initializer;
    ExpressionPtr condition;
    ExpressionPtr increment;
    StatementPtr body;
    ForStatement(StatementPtr init, ExpressionPtr cond, ExpressionPtr incr, StatementPtr body)
        : initializer(init), condition(cond), increment(incr), body(body) {}
};

class SwitchStatement : public Statement {
public:
    ExpressionPtr expression;
    std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>> cases;
    std::optional<StatementPtr> defaultCase;
    SwitchStatement(ExpressionPtr expr,
                    const std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>> &cases,
                    std::optional<StatementPtr> defaultCase)
        : expression(expr), cases(cases), defaultCase(defaultCase) {}
};

class ReturnStatement : public Statement {
public:
    ExpressionPtr expression;
    ReturnStatement(ExpressionPtr expr) : expression(expr) {}
};

// Expressions

class Expression {
public:
    virtual ~Expression() = default;
};

using ExpressionPtr = std::shared_ptr<Expression>;

class Literal : public Expression {
public:
    std::variant<int, float, double, char, bool> value;
    Literal(int v) : value(v) {}
    Literal(float v) : value(v) {}
    Literal(double v) : value(v) {}
    Literal(char v) : value(v) {}
    Literal(bool v) : value(v) {}
};

class Identifier : public Expression {
public:
    std::string name;
    Identifier(const std::string &name) : name(name) {}
};

class BinaryExpression : public Expression {
public:
    std::string op;
    ExpressionPtr left;
    ExpressionPtr right;
    BinaryExpression(const std::string &op, ExpressionPtr left, ExpressionPtr right)
        : op(op), left(left), right(right) {}
};

class UnaryExpression : public Expression {
public:
    std::string op;
    ExpressionPtr operand;
    UnaryExpression(const std::string &op, ExpressionPtr operand)
        : op(op), operand(operand) {}
};

class PostfixExpression : public Expression {
public:
    ExpressionPtr operand;
    std::string op;
    PostfixExpression(ExpressionPtr operand, const std::string &op)
        : operand(operand), op(op) {}
};

class Assignment : public Expression {
public:
    ExpressionPtr lhs;
    ExpressionPtr rhs;
    Assignment(ExpressionPtr lhs, ExpressionPtr rhs)
        : lhs(lhs), rhs(rhs) {}
};

class CastExpression : public Expression {
public:
    std::string castType;
    ExpressionPtr operand;
    CastExpression(const std::string &castType, ExpressionPtr operand)
        : castType(castType), operand(operand) {}
};

class FunctionCall : public Expression {
public:
    std::string functionName;
    std::vector<ExpressionPtr> arguments;
    FunctionCall(const std::string &name, const std::vector<ExpressionPtr> &args)
        : functionName(name), arguments(args) {}
};

class MemberAccess : public Expression {
public:
    ExpressionPtr base;
    std::string member;
    MemberAccess(ExpressionPtr base, const std::string &member)
        : base(base), member(member) {}
};

#endif // AST_HPP
