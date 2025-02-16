#include "AST.hpp"
#include "SemanticAnalyzer.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;

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
    if (auto baseId = std::dynamic_pointer_cast<Identifier>(mem->base)) {
      auto symbolOpt = symbolTable.lookup(baseId->name);
      if (!symbolOpt.has_value()) {
        throw runtime_error("Semantic Analysis Error: Undefined variable '" +
                            baseId->name + "' used in member access.");
      }
      string type = symbolOpt.value().type;
      if (type.rfind("union ", 0) != 0) {
        throw runtime_error("Semantic Analysis Error: Variable '" +
                            baseId->name + "' is not of a union type.");
      }
      string tag = type.substr(6);
      auto unionIt = unionRegistry.find(tag);
      if (unionIt == unionRegistry.end()) {
        throw runtime_error("Semantic Analysis Error: Unknown union type '" +
                            type + "'.");
      }
      bool found = false;
      for (auto &member : unionIt->second->members) {
        if (member->name == mem->member) {
          found = true;
          break;
        }
      }
      if (!found) {
        throw runtime_error("Semantic Analysis Error: Union type '" + type +
                            "' does not contain a member named '" +
                            mem->member + "'.");
      }
    } else {
      throw runtime_error("Semantic Analysis Error: Unsupported base "
                          "expression in member access.");
    }
  } else if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
    // No analysis needed for literals.
  } else if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    if (!symbolTable.lookup(id->name).has_value()) {
      throw runtime_error(
          "Semantic Analysis Error: Undefined variable or function '" +
          id->name + "'.");
    }
  } else if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
    if (auto id = std::dynamic_pointer_cast<Identifier>(assign->lhs)) {
      if (!symbolTable.lookup(id->name).has_value()) {
        throw runtime_error("Semantic Analysis Error: Undefined variable '" +
                            id->name + "' used as assignment target.");
      }
    } else if (auto mem =
                   std::dynamic_pointer_cast<MemberAccess>(assign->lhs)) {
      if (auto baseId = std::dynamic_pointer_cast<Identifier>(mem->base)) {
        if (!symbolTable.lookup(baseId->name).has_value()) {
          throw runtime_error("Semantic Analysis Error: Undefined variable '" +
                              baseId->name +
                              "' used in member access for assignment.");
        }
      } else {
        throw runtime_error("Semantic Analysis Error: Invalid assignment "
                            "target in member access.");
      }
    } else {
      throw runtime_error(
          "Semantic Analysis Error: Invalid assignment target.");
    }
    analyzeExpression(assign->rhs);
  } else if (auto funcCall = std::dynamic_pointer_cast<FunctionCall>(expr)) {
    auto sym = symbolTable.lookup(funcCall->functionName);
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
