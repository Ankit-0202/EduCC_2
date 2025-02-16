#include "AST.hpp"
#include "SemanticAnalyzer.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;

// Free helper function to infer the type (as a string) of an expression.
// It uses the analyzer's symbol table via the public getter, and the global
// unionRegistry and structRegistry.
namespace {
string inferExpressionType(const ExpressionPtr &expr,
                           const SemanticAnalyzer &analyzer) {
  // For a literal, return its type.
  if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
    switch (lit->type) {
    case Literal::LiteralType::Int:
      return "int";
    case Literal::LiteralType::Float:
      return "float";
    case Literal::LiteralType::Double:
      return "double";
    case Literal::LiteralType::Char:
      return "char";
    case Literal::LiteralType::Bool:
      return "bool";
    default:
      throw runtime_error("Cannot infer type for literal");
    }
  }
  // For an identifier, look it up using the public getter.
  if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    auto symOpt = analyzer.getSymbolTable().lookup(id->name);
    if (!symOpt.has_value())
      throw runtime_error("Semantic Analysis Error: Undefined variable '" +
                          id->name + "'.");
    return symOpt.value().type;
  }
  // For a member access, first infer the type of the base.
  if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    string baseType = inferExpressionType(mem->base, analyzer);
    // If the base is a union.
    if (baseType.rfind("union ", 0) == 0) {
      string tag = baseType.substr(6);
      auto unionIt = unionRegistry.find(tag);
      if (unionIt == unionRegistry.end())
        throw runtime_error("Semantic Analysis Error: Unknown union type '" +
                            baseType + "'.");
      for (auto &member : unionIt->second->members) {
        if (member->name == mem->member)
          return member->type;
      }
      throw runtime_error("Semantic Analysis Error: Union type '" + baseType +
                          "' does not contain a member named '" + mem->member +
                          "'.");
    }
    // If the base is a struct.
    else if (baseType.rfind("struct ", 0) == 0) {
      string tag = baseType.substr(7);
      auto structIt = structRegistry.find(tag);
      if (structIt == structRegistry.end())
        throw runtime_error("Semantic Analysis Error: Unknown struct type '" +
                            baseType + "'.");
      for (auto &member : structIt->second->members) {
        if (member->name == mem->member)
          return member->type;
      }
      throw runtime_error("Semantic Analysis Error: Struct type '" + baseType +
                          "' does not contain a member named '" + mem->member +
                          "'.");
    } else {
      throw runtime_error("Semantic Analysis Error: Base expression type '" +
                          baseType + "' is not an aggregate type.");
    }
  }
  // For a function call, return the function's return type.
  if (auto funcCall = std::dynamic_pointer_cast<FunctionCall>(expr)) {
    auto symOpt = analyzer.getSymbolTable().lookup(funcCall->functionName);
    if (!symOpt.has_value())
      throw runtime_error("Semantic Analysis Error: Undefined function '" +
                          funcCall->functionName + "'.");
    return symOpt.value().type;
  }
  throw runtime_error(
      "Semantic Analysis Error: Cannot infer type for expression.");
}
} // namespace

void SemanticAnalyzer::analyzeExpression(const ExpressionPtr &expr) {
  if (!expr)
    return;
  if (auto binExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
    analyzeExpression(binExpr->left);
    analyzeExpression(binExpr->right);
  } else if (auto unExpr = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
    analyzeExpression(unExpr->operand);
  } else if (auto postExpr =
                 std::dynamic_pointer_cast<PostfixExpression>(expr)) {
    analyzeExpression(postExpr->operand);
  } else if (auto castExpr = std::dynamic_pointer_cast<CastExpression>(expr)) {
    analyzeExpression(castExpr->operand);
  } else if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    analyzeExpression(mem->base);
    string baseType = inferExpressionType(mem->base, *this);
    if (baseType.rfind("union ", 0) == 0) {
      string tag = baseType.substr(6);
      auto unionIt = unionRegistry.find(tag);
      if (unionIt == unionRegistry.end())
        throw runtime_error("Semantic Analysis Error: Unknown union type '" +
                            baseType + "'.");
      bool found = false;
      for (auto &member : unionIt->second->members) {
        if (member->name == mem->member) {
          found = true;
          break;
        }
      }
      if (!found)
        throw runtime_error("Semantic Analysis Error: Union type '" + baseType +
                            "' does not contain a member named '" +
                            mem->member + "'.");
    } else if (baseType.rfind("struct ", 0) == 0) {
      string tag = baseType.substr(7);
      auto structIt = structRegistry.find(tag);
      if (structIt == structRegistry.end())
        throw runtime_error("Semantic Analysis Error: Unknown struct type '" +
                            baseType + "'.");
      bool found = false;
      for (auto &member : structIt->second->members) {
        if (member->name == mem->member) {
          found = true;
          break;
        }
      }
      if (!found)
        throw runtime_error("Semantic Analysis Error: Struct type '" +
                            baseType + "' does not contain a member named '" +
                            mem->member + "'.");
    } else {
      throw runtime_error("Semantic Analysis Error: Base expression type '" +
                          baseType + "' is not an aggregate type.");
    }
  } else if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
    // No analysis needed for literals.
  } else if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    if (!getSymbolTable().lookup(id->name).has_value()) {
      throw runtime_error(
          "Semantic Analysis Error: Undefined variable or function '" +
          id->name + "'.");
    }
  } else if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
    // For assignments with member access targets, verify the left-hand side.
    if (auto mem = std::dynamic_pointer_cast<MemberAccess>(assign->lhs)) {
      // Calling inferExpressionType ensures the member access is valid.
      inferExpressionType(assign->lhs, *this);
    }
    analyzeExpression(assign->rhs);
  } else if (auto funcCall = std::dynamic_pointer_cast<FunctionCall>(expr)) {
    auto sym = getSymbolTable().lookup(funcCall->functionName);
    if (!sym.has_value() || !sym->isFunction) {
      throw runtime_error("Semantic Analysis Error: Undefined function '" +
                          funcCall->functionName + "'.");
    }
    if (sym->parameterTypes.size() != funcCall->arguments.size()) {
      throw runtime_error("Semantic Analysis Error: Function '" +
                          funcCall->functionName +
                          "' called with an incorrect number of arguments.");
    }
    for (const auto &arg : funcCall->arguments) {
      analyzeExpression(arg);
    }
  } else {
    throw runtime_error(
        "Semantic Analysis Error: Unsupported expression type encountered.");
  }
}
