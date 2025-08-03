#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

// Forward declarations
class Expression;
class Statement;
class Declaration;

using ExpressionPtr = std::shared_ptr<Expression>;
using StatementPtr = std::shared_ptr<Statement>;
using DeclarationPtr = std::shared_ptr<Declaration>;

//--------------------//
//    Program Class   //
//--------------------//

class Program {
public:
  std::vector<DeclarationPtr> declarations;
  void addDeclaration(const DeclarationPtr &decl) {
    declarations.push_back(decl);
  }
};

//--------------------//
//   Expression Base  //
//--------------------//

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

class Assignment : public Expression {
public:
  ExpressionPtr lhs;
  ExpressionPtr rhs;
  Assignment(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
};

class ArrayAccess : public Expression {
public:
  ExpressionPtr base;
  ExpressionPtr index;
  ArrayAccess(ExpressionPtr base, ExpressionPtr index)
      : base(base), index(index) {}
};

class MemberAccess : public Expression {
public:
  ExpressionPtr base;
  std::string member;
  MemberAccess(ExpressionPtr base, const std::string &member)
      : base(base), member(member) {}
};

class FunctionCall : public Expression {
public:
  std::string functionName;
  std::vector<ExpressionPtr> arguments;
  FunctionCall(const std::string &name, const std::vector<ExpressionPtr> &args)
      : functionName(name), arguments(args) {}
};

class CastExpression : public Expression {
public:
  std::string castType;
  ExpressionPtr operand;
  CastExpression(const std::string &castType, ExpressionPtr operand)
      : castType(castType), operand(operand) {}
};

class PostfixExpression : public Expression {
public:
  ExpressionPtr operand;
  std::string op; // "++" or "--"
  PostfixExpression(ExpressionPtr operand, const std::string &op)
      : operand(operand), op(op) {}
};

class TernaryExpression : public Expression {
public:
  ExpressionPtr condition;
  ExpressionPtr trueExpr;
  ExpressionPtr falseExpr;
  TernaryExpression(ExpressionPtr condition, ExpressionPtr trueExpr, ExpressionPtr falseExpr)
      : condition(condition), trueExpr(trueExpr), falseExpr(falseExpr) {}
};

class InitializerList : public Expression {
public:
  std::vector<ExpressionPtr> elements;
  InitializerList(const std::vector<ExpressionPtr> &elems) : elements(elems) {}
};

//--------------------//
//   Statement Base   //
//--------------------//

class Statement {
public:
  virtual ~Statement() = default;
};

class ExpressionStatement : public Statement {
public:
  ExpressionPtr expression;
  ExpressionStatement(ExpressionPtr expr) : expression(expr) {}
};

class DeclarationStatement : public Statement {
public:
  DeclarationPtr declaration;
  DeclarationStatement(DeclarationPtr decl) : declaration(decl) {}
};

class CompoundStatement : public Statement {
public:
  std::vector<StatementPtr> statements;
  void addStatement(StatementPtr stmt) { statements.push_back(stmt); }
};

class IfStatement : public Statement {
public:
  ExpressionPtr condition;
  StatementPtr thenBranch;
  std::optional<StatementPtr> elseBranch;
  IfStatement(ExpressionPtr condition, StatementPtr thenBranch,
              std::optional<StatementPtr> elseBranch)
      : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}
};

class WhileStatement : public Statement {
public:
  ExpressionPtr condition;
  StatementPtr body;
  WhileStatement(ExpressionPtr condition, StatementPtr body)
      : condition(condition), body(body) {}
};

class ForStatement : public Statement {
public:
  StatementPtr initializer;
  ExpressionPtr condition;
  ExpressionPtr increment;
  StatementPtr body;
  ForStatement(StatementPtr initializer, ExpressionPtr condition,
               ExpressionPtr increment, StatementPtr body)
      : initializer(initializer), condition(condition), increment(increment),
        body(body) {}
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

class ReturnStatement : public Statement {
public:
  ExpressionPtr expression;
  ReturnStatement(ExpressionPtr expr) : expression(expr) {}
};

class BreakStatement : public Statement {
public:
  BreakStatement() = default;
};

class ContinueStatement : public Statement {
public:
  ContinueStatement() = default;
};

// For local variable declarations (statements)
class VariableDeclarationStatement : public Statement {
public:
  std::string type;
  std::string name;
  std::optional<ExpressionPtr> initializer;
  std::vector<ExpressionPtr> dimensions;
  VariableDeclarationStatement(const std::string &type, const std::string &name,
                               std::optional<ExpressionPtr> initializer,
                               const std::vector<ExpressionPtr> &dimensions)
      : type(type), name(name), initializer(initializer),
        dimensions(dimensions) {}
};

class MultiVariableDeclarationStatement : public Statement {
public:
  std::vector<std::shared_ptr<VariableDeclarationStatement>> declarations;
  MultiVariableDeclarationStatement(
      const std::vector<std::shared_ptr<VariableDeclarationStatement>> &decls)
      : declarations(decls) {}
};

//--------------------//
//  Declaration Base  //
//--------------------//

class Declaration {
public:
  virtual ~Declaration() = default;
};

class VariableDeclaration : public Declaration {
public:
  std::string type;
  std::string name;
  std::optional<ExpressionPtr> initializer;
  std::vector<ExpressionPtr> dimensions;
  VariableDeclaration(const std::string &type, const std::string &name,
                      std::optional<ExpressionPtr> initializer = std::nullopt,
                      const std::vector<ExpressionPtr> &dimensions = {})
      : type(type), name(name), initializer(initializer),
        dimensions(dimensions) {}
};

// NEW: Multiple variable declarations in a single declaration.
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
  // Each parameter: pair of (type, name)
  std::vector<std::pair<std::string, std::string>> parameters;
  StatementPtr body; // if nullptr, it's a forward declaration
  FunctionDeclaration(
      const std::string &retType, const std::string &name,
      const std::vector<std::pair<std::string, std::string>> &params,
      StatementPtr body)
      : returnType(retType), name(name), parameters(params), body(body) {}
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

class UnionDeclaration : public Declaration {
public:
  std::optional<std::string> tag;
  std::vector<std::shared_ptr<VariableDeclaration>> members;
  UnionDeclaration(
      std::optional<std::string> tag,
      const std::vector<std::shared_ptr<VariableDeclaration>> &members)
      : tag(tag), members(members) {}
};

class EnumDeclaration : public Declaration {
public:
  std::optional<std::string> tag;
  std::vector<std::pair<std::string, std::optional<ExpressionPtr>>> enumerators;
  std::vector<int> enumeratorValues;
  EnumDeclaration(
      std::optional<std::string> tag,
      const std::vector<std::pair<std::string, std::optional<ExpressionPtr>>>
          &enumerators)
      : tag(tag), enumerators(enumerators) {}
};

#endif // AST_HPP
