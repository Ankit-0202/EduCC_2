#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <optional>
#include <string>
#include <vector>

// Forward declarations for Expression and Statement nodes.
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

// Base class for AST nodes.
struct ASTNode {
  virtual ~ASTNode() = default;
};

//========================
// Expressions
//========================
struct Expression : public ASTNode {};

struct Identifier : public Expression {
  std::string name;
  Identifier(const std::string &name) : name(name) {}
};

struct Literal : public Expression {
  enum class LiteralType { Int, Float, Double, Char, Bool } type;
  int intValue;
  float floatValue;
  double doubleValue;
  char charValue;
  bool boolValue;

  // Constructors for each literal type:
  Literal(int value) : type(LiteralType::Int), intValue(value) {}
  Literal(float value) : type(LiteralType::Float), floatValue(value) {}
  Literal(double value) : type(LiteralType::Double), doubleValue(value) {}
  Literal(char value) : type(LiteralType::Char), charValue(value) {}
  Literal(bool value) : type(LiteralType::Bool), boolValue(value) {}
};

struct BinaryExpression : public Expression {
  std::string op;
  ExpressionPtr left;
  ExpressionPtr right;
  BinaryExpression(const std::string &op, const ExpressionPtr &left,
                   const ExpressionPtr &right)
      : op(op), left(left), right(right) {}
};

struct UnaryExpression : public Expression {
  std::string op;
  ExpressionPtr operand;
  UnaryExpression(const std::string &op, const ExpressionPtr &operand)
      : op(op), operand(operand) {}
};

struct PostfixExpression : public Expression {
  ExpressionPtr operand;
  std::string op;
  PostfixExpression(const ExpressionPtr &operand, const std::string &op)
      : operand(operand), op(op) {}
};

struct CastExpression : public Expression {
  std::string castType;
  ExpressionPtr operand;
  CastExpression(const std::string &castType, const ExpressionPtr &operand)
      : castType(castType), operand(operand) {}
};

// NEW: Assignment node for handling assignments.
struct Assignment : public Expression {
  ExpressionPtr lhs;
  ExpressionPtr rhs;
  Assignment(const ExpressionPtr &lhs, const ExpressionPtr &rhs)
      : lhs(lhs), rhs(rhs) {}
};

struct FunctionCall : public Expression {
  std::string functionName;
  std::vector<ExpressionPtr> arguments;
  FunctionCall(const std::string &functionName,
               const std::vector<ExpressionPtr> &arguments)
      : functionName(functionName), arguments(arguments) {}
};

struct MemberAccess : public Expression {
  ExpressionPtr base;
  std::string member;
  MemberAccess(const ExpressionPtr &base, const std::string &member)
      : base(base), member(member) {}
};

//========================
// Declarations
//========================
struct Declaration : public ASTNode {};

struct VariableDeclaration : public Declaration {
  std::string type;
  std::string name;
  std::optional<ExpressionPtr> initializer;
  VariableDeclaration(const std::string &type, const std::string &name,
                      const std::optional<ExpressionPtr> &initializer)
      : type(type), name(name), initializer(initializer) {}
};

struct MultiVariableDeclaration : public Declaration {
  std::vector<std::shared_ptr<VariableDeclaration>> declarations;
  MultiVariableDeclaration(
      const std::vector<std::shared_ptr<VariableDeclaration>> &declarations)
      : declarations(declarations) {}
};

struct FunctionDeclaration : public Declaration {
  std::string returnType;
  std::string name;
  std::vector<std::pair<std::string, std::string>> parameters; // <type, name>
  StatementPtr body; // May be nullptr for prototypes.
  FunctionDeclaration(
      const std::string &returnType, const std::string &name,
      const std::vector<std::pair<std::string, std::string>> &parameters,
      const StatementPtr &body)
      : returnType(returnType), name(name), parameters(parameters), body(body) {
  }
};

struct EnumDeclaration : public Declaration {
  std::optional<std::string> tag;
  std::vector<std::pair<std::string, std::optional<ExpressionPtr>>> enumerators;
  std::vector<int> enumeratorValues; // Computed during semantic analysis.
  EnumDeclaration(
      const std::optional<std::string> &tag,
      const std::vector<std::pair<std::string, std::optional<ExpressionPtr>>>
          &enumerators)
      : tag(tag), enumerators(enumerators) {}
};

struct UnionDeclaration : public Declaration {
  std::optional<std::string> tag;
  std::vector<std::shared_ptr<VariableDeclaration>> members;
  UnionDeclaration(
      const std::optional<std::string> &tag,
      const std::vector<std::shared_ptr<VariableDeclaration>> &members)
      : tag(tag), members(members) {}
};

// New: StructDeclaration (for full C struct support)
struct StructDeclaration : public Declaration {
  std::optional<std::string> tag;
  std::vector<std::shared_ptr<VariableDeclaration>> members;
  StructDeclaration(
      const std::optional<std::string> &tag,
      const std::vector<std::shared_ptr<VariableDeclaration>> &members)
      : tag(tag), members(members) {}
};

//========================
// Statements
//========================
struct Statement : public ASTNode {};

struct ExpressionStatement : public Statement {
  ExpressionPtr expression;
  ExpressionStatement(const ExpressionPtr &expression)
      : expression(expression) {}
};

struct CompoundStatement : public Statement {
  std::vector<StatementPtr> statements;
  void addStatement(const StatementPtr &stmt) { statements.push_back(stmt); }
};

struct ReturnStatement : public Statement {
  ExpressionPtr expression;
  ReturnStatement(const ExpressionPtr &expression) : expression(expression) {}
};

struct IfStatement : public Statement {
  ExpressionPtr condition;
  StatementPtr thenBranch;
  std::optional<StatementPtr> elseBranch;
  IfStatement(const ExpressionPtr &condition, const StatementPtr &thenBranch,
              const std::optional<StatementPtr> &elseBranch)
      : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}
};

struct WhileStatement : public Statement {
  ExpressionPtr condition;
  StatementPtr body;
  WhileStatement(const ExpressionPtr &condition, const StatementPtr &body)
      : condition(condition), body(body) {}
};

struct ForStatement : public Statement {
  StatementPtr initializer;
  ExpressionPtr condition;
  ExpressionPtr increment;
  StatementPtr body;
  ForStatement(const StatementPtr &initializer, const ExpressionPtr &condition,
               const ExpressionPtr &increment, const StatementPtr &body)
      : initializer(initializer), condition(condition), increment(increment),
        body(body) {}
};

struct SwitchStatement : public Statement {
  ExpressionPtr expression;
  std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>> cases;
  std::optional<StatementPtr> defaultCase;
  SwitchStatement(
      const ExpressionPtr &expression,
      const std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>>
          &cases,
      const std::optional<StatementPtr> &defaultCase)
      : expression(expression), cases(cases), defaultCase(defaultCase) {}
};

class DeclarationStatement : public Statement {
public:
  DeclarationStatement(const DeclarationPtr &decl) : declaration(decl) {}
  DeclarationPtr declaration;
};

struct VariableDeclarationStatement : public Statement {
  std::string type;
  std::string name;
  std::optional<ExpressionPtr> initializer;
  VariableDeclarationStatement(const std::string &type, const std::string &name,
                               const std::optional<ExpressionPtr> &initializer)
      : type(type), name(name), initializer(initializer) {}
};

struct MultiVariableDeclarationStatement : public Statement {
  std::vector<std::shared_ptr<VariableDeclarationStatement>> declarations;
  MultiVariableDeclarationStatement(
      const std::vector<std::shared_ptr<VariableDeclarationStatement>>
          &declarations)
      : declarations(declarations) {}
};

#endif // AST_HPP
