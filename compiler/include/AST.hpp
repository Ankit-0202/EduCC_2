#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <utility>

//
// Forward declarations for pointer types
//
class Expression;
using ExpressionPtr = std::shared_ptr<Expression>;

class Statement;
using StatementPtr = std::shared_ptr<Statement>;

class Declaration;
using DeclarationPtr = std::shared_ptr<Declaration>;

//
// Program
//
class Program {
public:
    std::vector<DeclarationPtr> declarations;
    void addDeclaration(DeclarationPtr decl) { declarations.push_back(decl); }
};

//
// Declaration Base Class (complete definition)
//
class Declaration {
public:
    virtual ~Declaration() = default;
};

//
// Expression Base Class
//
class Expression {
public:
    virtual ~Expression() = default;
};

//
// Literal Expression
//
// Now the literal value is stored in a variant rather than as a string,
// so that calls to std::holds_alternative<T> and std::get<T> work properly.
class Literal : public Expression {
public:
    enum class Type { INT, FLOAT, DOUBLE, CHAR, BOOL };
    Type literalType;
    std::variant<int, float, double, char, bool> value;

    Literal(int v) : literalType(Type::INT), value(v) {}
    Literal(float v) : literalType(Type::FLOAT), value(v) {}
    Literal(double v) : literalType(Type::DOUBLE), value(v) {}
    Literal(char v) : literalType(Type::CHAR), value(v) {}
    Literal(bool v) : literalType(Type::BOOL), value(v) {}
};

//
// Identifier Expression
//
class Identifier : public Expression {
public:
    std::string name;
    Identifier(const std::string &name) : name(name) {}
};

//
// Unary Expression
//
class UnaryExpression : public Expression {
public:
    std::string op;
    ExpressionPtr operand;
    UnaryExpression(const std::string &op, ExpressionPtr operand)
        : op(op), operand(operand) {}
};

//
// Binary Expression
//
class BinaryExpression : public Expression {
public:
    std::string op;
    ExpressionPtr left, right;
    BinaryExpression(const std::string &op, ExpressionPtr left, ExpressionPtr right)
        : op(op), left(left), right(right) {}
};

//
// Postfix Expression (e.g., i++ or i--)
//
class PostfixExpression : public Expression {
public:
    ExpressionPtr operand;
    std::string op;
    PostfixExpression(ExpressionPtr operand, const std::string &op)
        : operand(operand), op(op) {}
};

//
// Assignment Expression
//
class Assignment : public Expression {
public:
    std::string lhs;
    ExpressionPtr rhs;
    Assignment(const std::string &lhs, ExpressionPtr rhs)
        : lhs(lhs), rhs(rhs) {}
};

//
// Function Call Expression
//
class FunctionCall : public Expression {
public:
    std::string functionName;
    std::vector<ExpressionPtr> arguments;
    FunctionCall(const std::string &functionName, const std::vector<ExpressionPtr>& arguments)
        : functionName(functionName), arguments(arguments) {}
};

//
// Cast Expression (e.g., (int)f)
//
class CastExpression : public Expression {
public:
    std::string castType;
    ExpressionPtr operand;
    CastExpression(const std::string &castType, ExpressionPtr operand)
        : castType(castType), operand(operand) {}
};

//
// Statement Base Class
//
class Statement {
public:
    virtual ~Statement() = default;
};

//
// Expression Statement
//
class ExpressionStatement : public Statement {
public:
    ExpressionPtr expression;
    ExpressionStatement(ExpressionPtr expression)
        : expression(expression) {}
};

//
// Compound Statement (a block { ... })
//
class CompoundStatement : public Statement {
public:
    std::vector<StatementPtr> statements;
    void addStatement(StatementPtr stmt) { statements.push_back(stmt); }
};

//
// If Statement
//
class IfStatement : public Statement {
public:
    ExpressionPtr condition;
    StatementPtr thenBranch;
    std::optional<StatementPtr> elseBranch;
    IfStatement(ExpressionPtr condition,
                StatementPtr thenBranch,
                std::optional<StatementPtr> elseBranch)
        : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}
};

//
// While Statement
//
class WhileStatement : public Statement {
public:
    ExpressionPtr condition;
    StatementPtr body;
    WhileStatement(ExpressionPtr condition, StatementPtr body)
        : condition(condition), body(body) {}
};

//
// For Statement
//
class ForStatement : public Statement {
public:
    StatementPtr initializer;
    ExpressionPtr condition;
    ExpressionPtr increment;
    StatementPtr body;
    ForStatement(StatementPtr initializer,
                 ExpressionPtr condition,
                 ExpressionPtr increment,
                 StatementPtr body)
        : initializer(initializer), condition(condition),
          increment(increment), body(body) {}
};

//
// Switch Statement
//
class SwitchStatement : public Statement {
public:
    ExpressionPtr expression;
    // Each case is a pair: an optional expression (the case label) and a statement
    std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>> cases;
    std::optional<StatementPtr> defaultCase;
    SwitchStatement(ExpressionPtr expression,
                    const std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>> &cases,
                    std::optional<StatementPtr> defaultCase)
        : expression(expression), cases(cases), defaultCase(defaultCase) {}
};

//
// Return Statement
//
class ReturnStatement : public Statement {
public:
    ExpressionPtr expression;
    ReturnStatement(ExpressionPtr expression)
        : expression(expression) {}
};

//
// Global Variable Declaration
//
class VariableDeclaration : public Declaration {
public:
    std::string type;
    std::string name;
    std::optional<ExpressionPtr> initializer;
    VariableDeclaration(const std::string &type,
                        const std::string &name,
                        std::optional<ExpressionPtr> initializer)
        : type(type), name(name), initializer(initializer) {}
};

//
// Multiple Global Variable Declarations (e.g., int a, b, c;)
//
class MultiVariableDeclaration : public Declaration {
public:
    std::vector<std::shared_ptr<VariableDeclaration>> declarations;
    MultiVariableDeclaration(const std::vector<std::shared_ptr<VariableDeclaration>> &declarations)
        : declarations(declarations) {}
};

//
// Function Declaration
//
class FunctionDeclaration : public Declaration {
public:
    std::string returnType;
    std::string name;
    // Each parameter is a pair: <type, name>
    std::vector<std::pair<std::string, std::string>> parameters;
    StatementPtr body; // may be nullptr if it’s only a prototype
    FunctionDeclaration(const std::string &returnType,
                        const std::string &name,
                        const std::vector<std::pair<std::string, std::string>> &parameters,
                        StatementPtr body)
        : returnType(returnType), name(name), parameters(parameters), body(body) {}
};

//
// Local Variable Declaration Statement
//
class VariableDeclarationStatement : public Statement {
public:
    std::string type;
    std::string name;
    std::optional<ExpressionPtr> initializer;
    VariableDeclarationStatement(const std::string &type,
                                 const std::string &name,
                                 std::optional<ExpressionPtr> initializer)
        : type(type), name(name), initializer(initializer) {}
};

//
// Multiple Local Variable Declarations Statement
//
class MultiVariableDeclarationStatement : public Statement {
public:
    std::vector<std::shared_ptr<VariableDeclarationStatement>> declarations;
    MultiVariableDeclarationStatement(const std::vector<std::shared_ptr<VariableDeclarationStatement>> &declarations)
        : declarations(declarations) {}
};

#endif // AST_HPP
