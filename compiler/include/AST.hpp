#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <optional>
#include <string>
#include <vector>

// Forward declarations
struct Expression;
using ExpressionPtr = std::shared_ptr<Expression>;

struct Statement;
using StatementPtr = std::shared_ptr<Statement>;

struct Declaration;
using DeclarationPtr = std::shared_ptr<Declaration>;

struct Program;

// Base Expression class
struct Expression {
  virtual ~Expression() = default;
};

// Literal expression
struct Literal : public Expression {
  enum class LiteralType { Int, Float, Double, Char, Bool };
  LiteralType type;
  int intValue;
  float floatValue;
  double doubleValue;
  char charValue;
  bool boolValue;
  Literal(int v) : type(LiteralType::Int), intValue(v) {}
  Literal(float v) : type(LiteralType::Float), floatValue(v) {}
  Literal(double v) : type(LiteralType::Double), doubleValue(v) {}
  Literal(char v) : type(LiteralType::Char), charValue(v) {}
  Literal(bool v) : type(LiteralType::Bool), boolValue(v) {}
};

// Identifier expression
struct Identifier : public Expression {
  std::string name;
  Identifier(const std::string &n) : name(n) {}
};

// Binary expression
struct BinaryExpression : public Expression {
  std::string op;
  ExpressionPtr left;
  ExpressionPtr right;
  BinaryExpression(const std::string &o, ExpressionPtr l, ExpressionPtr r)
      : op(o), left(l), right(r) {}
};

// Unary expression
struct UnaryExpression : public Expression {
  std::string op;
  ExpressionPtr operand;
  UnaryExpression(const std::string &o, ExpressionPtr expr)
      : op(o), operand(expr) {}
};

// Cast expression
struct CastExpression : public Expression {
  std::string castType;
  ExpressionPtr operand;
  CastExpression(const std::string &ct, ExpressionPtr expr)
      : castType(ct), operand(expr) {}
};

// Postfix expression (e.g., i++, i--)
struct PostfixExpression : public Expression {
  ExpressionPtr operand;
  std::string op; // "++" or "--"
  PostfixExpression(ExpressionPtr expr, const std::string &o)
      : operand(expr), op(o) {}
};

// NEW: Assignment expression (e.g., a = b)
struct Assignment : public Expression {
  ExpressionPtr lhs;
  ExpressionPtr rhs;
  Assignment(ExpressionPtr l, ExpressionPtr r) : lhs(l), rhs(r) {}
};

// Member access (e.g., a.b)
struct MemberAccess : public Expression {
  ExpressionPtr base;
  std::string member;
  MemberAccess(ExpressionPtr b, const std::string &m) : base(b), member(m) {}
};

// Array access (e.g., a[i])
struct ArrayAccess : public Expression {
  ExpressionPtr base;
  ExpressionPtr index;
  ArrayAccess(ExpressionPtr b, ExpressionPtr i) : base(b), index(i) {}
};

// Function call (e.g., foo(a, b))
struct FunctionCall : public Expression {
  std::string functionName;
  std::vector<ExpressionPtr> arguments;
  FunctionCall(const std::string &name, const std::vector<ExpressionPtr> &args)
      : functionName(name), arguments(args) {}
};

// Initializer list expression (for array or struct initializers)
struct InitializerList : public Expression {
  std::vector<ExpressionPtr> elements;
  InitializerList(const std::vector<ExpressionPtr> &elems) : elements(elems) {}
};

// Base Statement class
struct Statement {
  virtual ~Statement() = default;
};

// Expression statement
struct ExpressionStatement : public Statement {
  ExpressionPtr expression;
  ExpressionStatement(ExpressionPtr expr) : expression(expr) {}
};

// Compound statement (block)
struct CompoundStatement : public Statement {
  std::vector<StatementPtr> statements;
  void addStatement(const StatementPtr &stmt) { statements.push_back(stmt); }
};

// If statement
struct IfStatement : public Statement {
  ExpressionPtr condition;
  StatementPtr thenBranch;
  std::optional<StatementPtr> elseBranch;
  IfStatement(ExpressionPtr cond, StatementPtr thenBr,
              std::optional<StatementPtr> elseBr)
      : condition(cond), thenBranch(thenBr), elseBranch(elseBr) {}
};

// While statement
struct WhileStatement : public Statement {
  ExpressionPtr condition;
  StatementPtr body;
  WhileStatement(ExpressionPtr cond, StatementPtr b)
      : condition(cond), body(b) {}
};

// For statement
struct ForStatement : public Statement {
  StatementPtr initializer;
  ExpressionPtr condition;
  ExpressionPtr increment;
  StatementPtr body;
  ForStatement(StatementPtr init, ExpressionPtr cond, ExpressionPtr incr,
               StatementPtr b)
      : initializer(init), condition(cond), increment(incr), body(b) {}
};

// Switch statement
struct SwitchStatement : public Statement {
  ExpressionPtr expression;
  std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>> cases;
  std::optional<StatementPtr> defaultCase;
  SwitchStatement(
      ExpressionPtr expr,
      const std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>>
          &cs,
      std::optional<StatementPtr> defCase)
      : expression(expr), cases(cs), defaultCase(defCase) {}
};

// Return statement
struct ReturnStatement : public Statement {
  ExpressionPtr expression;
  ReturnStatement(ExpressionPtr expr) : expression(expr) {}
};

// Declaration statement (for declarations within statements)
struct DeclarationStatement : public Statement {
  DeclarationPtr declaration;
  DeclarationStatement(DeclarationPtr decl) : declaration(decl) {}
};

// Local variable declaration statement
struct VariableDeclarationStatement : public Statement {
  std::string type;
  std::string name;
  std::optional<ExpressionPtr> initializer;
  std::vector<ExpressionPtr> dimensions;
  VariableDeclarationStatement(const std::string &t, const std::string &n,
                               std::optional<ExpressionPtr> init,
                               const std::vector<ExpressionPtr> &dims)
      : type(t), name(n), initializer(init), dimensions(dims) {}
};

// Multi-variable declaration statement (for local declarations, e.g. int a, b,
// c;)
struct MultiVariableDeclarationStatement : public Statement {
  std::vector<std::shared_ptr<VariableDeclarationStatement>> declarations;
  MultiVariableDeclarationStatement(
      const std::vector<std::shared_ptr<VariableDeclarationStatement>> &decls)
      : declarations(decls) {}
};

// Declarations

// Base Declaration class
struct Declaration {
  virtual ~Declaration() = default;
};

// Global variable declaration
struct VariableDeclaration : public Declaration {
  std::string type;
  std::string name;
  std::optional<ExpressionPtr> initializer;
  std::vector<ExpressionPtr> dimensions;
  VariableDeclaration(const std::string &t, const std::string &n,
                      std::optional<ExpressionPtr> init,
                      const std::vector<ExpressionPtr> &dims)
      : type(t), name(n), initializer(init), dimensions(dims) {}
  // NEW: Overload for declarations without explicit dimensions.
  VariableDeclaration(const std::string &t, const std::string &n,
                      std::optional<ExpressionPtr> init)
      : type(t), name(n), initializer(init), dimensions() {}
};

// NEW: Global multi-variable declaration (for declarations with multiple
// variables)
struct MultiVariableDeclaration : public Declaration {
  std::vector<std::shared_ptr<VariableDeclaration>> declarations;
  MultiVariableDeclaration(
      const std::vector<std::shared_ptr<VariableDeclaration>> &decls)
      : declarations(decls) {}
};

// Function declaration
struct FunctionDeclaration : public Declaration {
  std::string returnType;
  std::string name;
  std::vector<std::pair<std::string, std::string>> parameters; // type, name
  StatementPtr body; // nullptr for prototypes
  FunctionDeclaration(
      const std::string &ret, const std::string &n,
      const std::vector<std::pair<std::string, std::string>> &params,
      StatementPtr b)
      : returnType(ret), name(n), parameters(params), body(b) {}
};

// Enum declaration
struct EnumDeclaration : public Declaration {
  std::optional<std::string> tag;
  std::vector<std::pair<std::string, std::optional<ExpressionPtr>>> enumerators;
  std::vector<int> enumeratorValues;
  EnumDeclaration(
      std::optional<std::string> t,
      const std::vector<std::pair<std::string, std::optional<ExpressionPtr>>>
          &enums)
      : tag(t), enumerators(enums) {}
};

// Struct declaration
struct StructDeclaration : public Declaration {
  std::optional<std::string> tag;
  std::vector<std::shared_ptr<VariableDeclaration>> members;
  StructDeclaration(std::optional<std::string> t,
                    const std::vector<std::shared_ptr<VariableDeclaration>> &m)
      : tag(t), members(m) {}
};

// Union declaration
struct UnionDeclaration : public Declaration {
  std::optional<std::string> tag;
  std::vector<std::shared_ptr<VariableDeclaration>> members;
  UnionDeclaration(std::optional<std::string> t,
                   const std::vector<std::shared_ptr<VariableDeclaration>> &m)
      : tag(t), members(m) {}
};

// Program node
struct Program {
  std::vector<DeclarationPtr> declarations;
  void addDeclaration(DeclarationPtr decl) { declarations.push_back(decl); }
};

#endif // AST_HPP
