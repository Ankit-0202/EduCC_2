#include "AST.hpp"
#include "SemanticAnalyzer.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <stdexcept>
#include <string>
#include <vector>

using std::runtime_error;
using std::string;
using std::vector;

// Free helper function to infer the type (as a string) of an expression.
// It uses the analyzer's symbol table via its public interface, and the global
// unionRegistry and structRegistry.
namespace {
std::string inferExpressionType(const std::shared_ptr<Expression> &expr,
                                SemanticAnalyzer &analyzer) {
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
      throw std::runtime_error("Cannot infer type for literal");
    }
  }
  // NEW: Handle string literal.
  if (auto strLit = std::dynamic_pointer_cast<llvm::StringLiteral>(expr)) {
    // We choose to treat string literals as "char*".
    return "char*";
  }
  // For an identifier, look it up.
  if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    auto symOpt = analyzer.getSymbolTable().lookup(id->name);
    if (!symOpt.has_value())
      throw std::runtime_error("Semantic Analysis Error: Undefined variable '" +
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
    // If the function is not found, allow external functions such as printf.
    if (!symOpt.has_value() || !symOpt.value().isFunction) {
      if (funcCall->functionName == "printf") {
        // Declare an external function for printf with return type "int".
        // (Note: printf is variadic, so we bypass the parameter count check
        // below.)
        Symbol externalFunc("printf", "int", true, vector<string>(), true);
        analyzer.getSymbolTable().declare(externalFunc);
        // Retrieve the newly declared symbol.
        symOpt = analyzer.getSymbolTable().lookup("printf");
      } else {
        throw runtime_error("Semantic Analysis Error: Undefined function '" +
                            funcCall->functionName + "'.");
      }
    }
    // For printf, skip parameter count check (since it is variadic).
    if (funcCall->functionName != "printf" &&
        symOpt.value().parameterTypes.size() != funcCall->arguments.size()) {
      throw runtime_error("Semantic Analysis Error: Function '" +
                          funcCall->functionName +
                          "' called with an incorrect number of arguments.");
    }
    for (const auto &arg : funcCall->arguments) {
      analyzer.analyzeExpression(arg);
    }
    return symOpt.value().type;
  }
  throw runtime_error(
      "Semantic Analysis Error: Cannot infer type for expression.");
}
} // namespace

void SemanticAnalyzer::analyzeExpression(const ExpressionPtr &expr) {
  if (!expr)
    return;

  // NEW: Handle initializer lists.
  if (auto initList = std::dynamic_pointer_cast<InitializerList>(expr)) {
    for (const auto &elem : initList->elements) {
      analyzeExpression(elem);
    }
    return;
  }

  // NEW: Handle string literal expressions.
  if (auto strLit = std::dynamic_pointer_cast<llvm::StringLiteral>(expr)) {
    // No further analysis required.
    return;
  }

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
  }
  // NEW: Handle array access expressions.
  else if (auto arrAccess = std::dynamic_pointer_cast<ArrayAccess>(expr)) {
    analyzeExpression(arrAccess->base);
    analyzeExpression(arrAccess->index);
  } else if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
    // No analysis needed for numeric or char literals.
  } else if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    if (!getSymbolTable().lookup(id->name).has_value()) {
      throw std::runtime_error(
          "Semantic Analysis Error: Undefined variable or function '" +
          id->name + "'.");
    }
  } else if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
    if (auto mem = std::dynamic_pointer_cast<MemberAccess>(assign->lhs)) {
      inferExpressionType(assign->lhs, *this);
    }
    analyzeExpression(assign->rhs);
  } else if (auto funcCall = std::dynamic_pointer_cast<FunctionCall>(expr)) {
    (void)inferExpressionType(expr, *this); // triggers function lookup, etc.
  } else {
    throw std::runtime_error(
        "Semantic Analysis Error: Unsupported expression type encountered.");
  }
}
