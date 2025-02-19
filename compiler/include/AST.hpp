#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

// Forward declarations
class Expression;
class Statement;
class Declaration;

using ExpressionPtr = std::shared_ptr<Expression>;
using StatementPtr = std::shared_ptr<Statement>;
using DeclarationPtr = std::shared_ptr<Declaration>;

//////////////////////
// Program (AST Root)
//////////////////////
class Program {
public:
  std::vector<DeclarationPtr> declarations;
  void addDeclaration(const DeclarationPtr &decl) {
    declarations.push_back(decl);
  }
};

//////////////////////
// Expression Classes
//////////////////////

class Expression {
public:
  virtual ~Expression() = default;
};

class Literal : public Expression {
public:
  enum class LiteralType { Int, Float, Double, Char, Bool };
  LiteralType type;
  int intValue;
  float floatValue;
  double doubleValue;
  char charValue;
  bool boolValue;
  // Constructors for each literal type
  Literal(int value) : type(LiteralType::Int), intValue(value) {}
  Literal(float value) : type(LiteralType::Float), floatValue(value) {}
  Literal(double value) : type(LiteralType::Double), doubleValue(value) {}
  Literal(char value) : type(LiteralType::Char), charValue(value) {}
  Literal(bool value) : type(LiteralType::Bool), boolValue(value) {}
};

class Identifier : public Expression {
public:
  std::string name;
  Identifier(const std::string &n) : name(n) {}
};

class BinaryExpression : public Expression {
public:
  std::string op;
  ExpressionPtr left;
  ExpressionPtr right;
  BinaryExpression(const std::string &op, ExpressionPtr left,
                   ExpressionPtr right)
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
  std::string op; // "++" or "--"
  PostfixExpression(ExpressionPtr operand, const std::string &op)
      : operand(operand), op(op) {}
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

// NEW: Assignment node to represent assignments (e.g. a = b)
class Assignment : public Expression {
public:
  ExpressionPtr lhs;
  ExpressionPtr rhs;
  Assignment(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
};

// NEW: Member access node for structure/union members (e.g. a.member)
class MemberAccess : public Expression {
public:
  ExpressionPtr base;
  std::string member;
  MemberAccess(ExpressionPtr base, const std::string &member)
      : base(base), member(member) {}
};

// Array access node for indexing (e.g. a[5])
class ArrayAccess : public Expression {
public:
  ExpressionPtr base;
  ExpressionPtr index;
  ArrayAccess(ExpressionPtr base, ExpressionPtr index)
      : base(base), index(index) {}
};

//////////////////////
// Statement Classes
//////////////////////

class Statement {
public:
  virtual ~Statement() = default;
};

class CompoundStatement : public Statement {
public:
  std::vector<StatementPtr> statements;
  void addStatement(StatementPtr stmt) { statements.push_back(stmt); }
};

class ExpressionStatement : public Statement {
public:
  ExpressionPtr expression;
  ExpressionStatement(ExpressionPtr expr) : expression(expr) {}
};

class ReturnStatement : public Statement {
public:
  ExpressionPtr expression;
  ReturnStatement(ExpressionPtr expr) : expression(expr) {}
};

class IfStatement : public Statement {
public:
  ExpressionPtr condition;
  StatementPtr thenBranch;
  std::optional<StatementPtr> elseBranch;
  IfStatement(ExpressionPtr cond, StatementPtr thenBranch,
              std::optional<StatementPtr> elseBranch)
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
  ForStatement(StatementPtr init, ExpressionPtr cond, ExpressionPtr incr,
               StatementPtr body)
      : initializer(init), condition(cond), increment(incr), body(body) {}
};

class SwitchStatement : public Statement {
public:
  ExpressionPtr expression;
  std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>> cases;
  std::optional<StatementPtr> defaultCase;
  SwitchStatement(
      ExpressionPtr expr,
      const std::vector<std::pair<std::optional<ExpressionPtr>, StatementPtr>>
          &cases,
      std::optional<StatementPtr> defaultCase)
      : expression(expr), cases(cases), defaultCase(defaultCase) {}
};

// A statement that wraps a declaration
class DeclarationStatement : public Statement {
public:
  DeclarationPtr declaration;
  DeclarationStatement(DeclarationPtr decl) : declaration(decl) {}
};

//////////////////////
// Declaration Classes
//////////////////////

class Declaration {
public:
  virtual ~Declaration() = default;
};

class VariableDeclaration : public Declaration {
public:
  std::string type;
  std::string name;
  std::optional<ExpressionPtr> initializer;
  // For arrays, a list of dimension expressions (empty if not an array)
  std::vector<ExpressionPtr> dimensions;
  VariableDeclaration(const std::string &type, const std::string &name,
                      std::optional<ExpressionPtr> initializer = std::nullopt,
                      const std::vector<ExpressionPtr> &dims = {})
      : type(type), name(name), initializer(initializer), dimensions(dims) {}
};

class MultiVariableDeclaration : public Declaration {
public:
  std::vector<std::shared_ptr<VariableDeclaration>> declarations;
  MultiVariableDeclaration(
      const std::vector<std::shared_ptr<VariableDeclaration>> &decls)
      : declarations(decls) {}
};

class FunctionDeclaration : public Declaration {
public:
  std::string returnType;
  std::string name;
  std::vector<std::pair<std::string, std::string>>
      parameters;    // pair: type and name
  StatementPtr body; // if null, then only a declaration
  FunctionDeclaration(
      const std::string &retType, const std::string &name,
      const std::vector<std::pair<std::string, std::string>> &params,
      StatementPtr body)
      : returnType(retType), name(name), parameters(params), body(body) {}
};

class EnumDeclaration : public Declaration {
public:
  std::optional<std::string> tag;
  std::vector<std::pair<std::string, std::optional<ExpressionPtr>>> enumerators;
  std::vector<int> enumeratorValues; // filled during semantic analysis
  EnumDeclaration(
      std::optional<std::string> tag,
      const std::vector<std::pair<std::string, std::optional<ExpressionPtr>>>
          &enumerators)
      : tag(tag), enumerators(enumerators) {}
};

class UnionDeclaration : public Declaration {
public:
  std::optional<std::string> tag;
  std::vector<std::shared_ptr<VariableDeclaration>> members;
  UnionDeclaration(
      std::optional<std::string> tag,
      const std::vector<std::shared_ptr<VariableDeclaration>> &members)
      : tag(tag), members(members) {}
};

class StructDeclaration : public Declaration {
public:
  std::optional<std::string> tag;
  std::vector<std::shared_ptr<VariableDeclaration>> members;
  StructDeclaration(
      std::optional<std::string> tag,
      const std::vector<std::shared_ptr<VariableDeclaration>> &members)
      : tag(tag), members(members) {}
};

// A variable declaration statement that directly takes a type, name,
// initializer, and dimensions.
class VariableDeclarationStatement : public DeclarationStatement {
public:
  std::shared_ptr<VariableDeclaration> varDecl;
  VariableDeclarationStatement(const std::string &type, const std::string &name,
                               const std::optional<ExpressionPtr> &initializer,
                               const std::vector<ExpressionPtr> &dimensions)
      : DeclarationStatement(std::make_shared<VariableDeclaration>(
            type, name, initializer, dimensions)) {
    varDecl = std::dynamic_pointer_cast<VariableDeclaration>(declaration);
  }
};

// A multi-variable declaration statement that aggregates several
// variable declaration statements.
class MultiVariableDeclarationStatement : public Statement {
public:
  std::vector<std::shared_ptr<VariableDeclaration>> declarations;
  MultiVariableDeclarationStatement(
      const std::vector<std::shared_ptr<VariableDeclarationStatement>> &decls) {
    for (auto &d : decls) {
      auto varDecl =
          std::dynamic_pointer_cast<VariableDeclaration>(d->declaration);
      if (varDecl)
        declarations.push_back(varDecl);
      else
        throw std::runtime_error(
            "MultiVariableDeclarationStatement constructor: underlying "
            "declaration is not VariableDeclaration");
    }
  }
};

#endif // AST_HPP
