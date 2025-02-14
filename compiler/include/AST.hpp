#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

// Forward declarations for expressions and statements.
struct Expression;
using ExpressionPtr = std::shared_ptr<Expression>;

struct Statement;
using StatementPtr = std::shared_ptr<Statement>;

struct Declaration;
using DeclarationPtr = std::shared_ptr<Declaration>;

struct Program {
  std::vector<DeclarationPtr> declarations;
  void addDeclaration(const DeclarationPtr &decl) {
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
  VariableDeclaration(const std::string &type, const std::string &name,
                      std::optional<ExpressionPtr> initializer)
      : type(type), name(name), initializer(initializer) {}
};

// Multiple Variable Declaration
struct MultiVariableDeclaration : public Declaration {
  std::vector<std::shared_ptr<VariableDeclaration>> declarations;
  MultiVariableDeclaration(
      const std::vector<std::shared_ptr<VariableDeclaration>> &decls)
      : declarations(decls) {}
};

// Function Declaration
struct FunctionDeclaration : public Declaration {
  std::string returnType;
  std::string name;
  std::vector<std::pair<std::string, std::string>> parameters; // (type, name)
  StatementPtr body; // nullptr if only prototype
  FunctionDeclaration(
      const std::string &retType, const std::string &name,
      const std::vector<std::pair<std::string, std::string>> &params,
      StatementPtr body)
      : returnType(retType), name(name), parameters(params), body(body) {}
};

// Enum Declaration
struct EnumDeclaration : public Declaration {
  std::optional<std::string> tag;
  // Each enumerator is a pair: (name, optional initializer)
  std::vector<std::pair<std::string, std::optional<ExpressionPtr>>> enumerators;
  // Computed integer values for each enumerator (filled during semantic
  // analysis)
  std::vector<int> enumeratorValues;
  EnumDeclaration(
      const std::optional<std::string> &tag,
      const std::vector<std::pair<std::string, std::optional<ExpressionPtr>>>
          &enumerators)
      : tag(tag), enumerators(enumerators) {}
};

// Union Declaration
struct UnionDeclaration : public Declaration {
  std::optional<std::string> tag;
  // Each union member is a variable declaration (without initializer
  // restrictions)
  std::vector<std::shared_ptr<VariableDeclaration>> members;
  UnionDeclaration(
      const std::optional<std::string> &tag,
      const std::vector<std::shared_ptr<VariableDeclaration>> &members)
      : tag(tag), members(members) {}
};

// ----- Statements -----

struct Statement {
  virtual ~Statement() = default;
};

struct CompoundStatement : public Statement {
  std::vector<StatementPtr> statements;
  void addStatement(const StatementPtr &stmt) { statements.push_back(stmt); }
};

struct ExpressionStatement : public Statement {
  ExpressionPtr expression;
  ExpressionStatement(ExpressionPtr expr) : expression(expr) {}
};

struct VariableDeclarationStatement : public Statement {
  std::string type;
  std::string name;
  std::optional<ExpressionPtr> initializer;
  VariableDeclarationStatement(const std::string &type, const std::string &name,
                               std::optional<ExpressionPtr> initializer)
      : type(type), name(name), initializer(initializer) {}
};

struct MultiVariableDeclarationStatement : public Statement {
  std::vector<std::shared_ptr<VariableDeclarationStatement>> declarations;
  MultiVariableDeclarationStatement(
      const std::vector<std::shared_ptr<VariableDeclarationStatement>> &decls)
      : declarations(decls) {}
};

struct IfStatement : public Statement {
  ExpressionPtr condition;
  StatementPtr thenBranch;
  std::optional<StatementPtr> elseBranch;
  IfStatement(ExpressionPtr condition, StatementPtr thenBranch,
              std::optional<StatementPtr> elseBranch)
      : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}
};

struct WhileStatement : public Statement {
  ExpressionPtr condition;
  StatementPtr body;
  WhileStatement(ExpressionPtr condition, StatementPtr body)
      : condition(condition), body(body) {}
};

struct ForStatement : public Statement {
  StatementPtr initializer;
  ExpressionPtr condition;
  ExpressionPtr increment;
  StatementPtr body;
  ForStatement(StatementPtr initializer, ExpressionPtr condition,
               ExpressionPtr increment, StatementPtr body)
      : initializer(initializer), condition(condition), increment(increment),
        body(body) {}
};

struct SwitchStatement : public Statement {
  ExpressionPtr expression;
  // Each case is a pair: (optional case expression, associated statement)
  std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>> cases;
  std::optional<StatementPtr> defaultCase;
  SwitchStatement(
      ExpressionPtr expr,
      const std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>>
          &cases,
      std::optional<StatementPtr> defaultCase)
      : expression(expr), cases(cases), defaultCase(defaultCase) {}
};

struct ReturnStatement : public Statement {
  ExpressionPtr expression;
  ReturnStatement(ExpressionPtr expr) : expression(expr) {}
};

// ----- Expressions -----

struct Expression {
  virtual ~Expression() = default;
};

struct BinaryExpression : public Expression {
  std::string op;
  ExpressionPtr left;
  ExpressionPtr right;
  BinaryExpression(const std::string &op, ExpressionPtr left,
                   ExpressionPtr right)
      : op(op), left(left), right(right) {}
};

struct UnaryExpression : public Expression {
  std::string op;
  ExpressionPtr operand;
  UnaryExpression(const std::string &op, ExpressionPtr operand)
      : op(op), operand(operand) {}
};

struct PostfixExpression : public Expression {
  ExpressionPtr operand;
  std::string op;
  PostfixExpression(ExpressionPtr operand, const std::string &op)
      : operand(operand), op(op) {}
};

struct CastExpression : public Expression {
  std::string castType;
  ExpressionPtr operand;
  CastExpression(const std::string &castType, ExpressionPtr operand)
      : castType(castType), operand(operand) {}
};

struct Literal : public Expression {
  std::variant<int, float, double, char, bool> value;
  Literal(int v) : value(v) {}
  Literal(float v) : value(v) {}
  Literal(double v) : value(v) {}
  Literal(char v) : value(v) {}
  Literal(bool v) : value(v) {}
};

struct Identifier : public Expression {
  std::string name;
  Identifier(const std::string &name) : name(name) {}
};

// Updated Assignment: lhs is now any assignable expression.
struct Assignment : public Expression {
  ExpressionPtr lhs;
  ExpressionPtr rhs;
  Assignment(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
};

struct FunctionCall : public Expression {
  std::string functionName;
  std::vector<ExpressionPtr> arguments;
  FunctionCall(const std::string &functionName,
               const std::vector<ExpressionPtr> &arguments)
      : functionName(functionName), arguments(arguments) {}
};

// NEW: Member Access Expression (for accessing union (or struct) members)
struct MemberAccess : public Expression {
  ExpressionPtr base;
  std::string member;
  MemberAccess(ExpressionPtr base, const std::string &member)
      : base(base), member(member) {}
};

#endif // AST_HPP
