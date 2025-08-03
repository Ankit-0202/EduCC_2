#include "AST.hpp"
#include "SemanticAnalyzer.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;

namespace {
// Helper function to infer the type (as a string) of an expression.
// It uses the analyzer's symbol table via the public getter and the global
// unionRegistry and structRegistry.
string inferExpressionType(const std::shared_ptr<Expression> &expr,
                           const SemanticAnalyzer &analyzer) {
  // NEW: Handle binary expressions for pointer arithmetic.
  if (auto binExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
    if (binExpr->op == "+" || binExpr->op == "-") {
      string leftType = inferExpressionType(binExpr->left, analyzer);
      string rightType = inferExpressionType(binExpr->right, analyzer);
      // If one operand is a pointer (ends with '*') and the other is int.
      if (!leftType.empty() && leftType.back() == '*' && rightType == "int")
        return leftType;
      if (binExpr->op == "+" && !rightType.empty() && rightType.back() == '*' &&
          leftType == "int")
        return rightType;
      // Pointer subtraction: both pointers yields an int (ptrdiff_t)
      if (!leftType.empty() && leftType.back() == '*' && !rightType.empty() &&
          rightType.back() == '*' && binExpr->op == "-")
        return "int";
    }
    // For other binary expressions, assume type is that of the left operand.
    return inferExpressionType(binExpr->left, analyzer);
  }

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
  // For sizeof expressions, return "int" (sizeof returns size_t which is
  // typically int)
  if (auto sizeofExpr = std::dynamic_pointer_cast<SizeOfExpression>(expr)) {
    return "int";
  }
  // For a postfix expression, return the type of the operand.
  if (auto postExpr = std::dynamic_pointer_cast<PostfixExpression>(expr)) {
    return inferExpressionType(postExpr->operand, analyzer);
  }
  // For a unary expression, infer type based on the operator.
  if (auto unExpr = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
    string operandType = inferExpressionType(unExpr->operand, analyzer);
    if (unExpr->op == "*") {
      // Dereference: remove one level of pointer
      if (!operandType.empty() && operandType.back() == '*')
        return operandType.substr(0, operandType.size() - 1);
      throw runtime_error("Cannot dereference non-pointer type: " +
                          operandType);
    } else if (unExpr->op == "&") {
      // Address-of: add one level of pointer
      return operandType + "*";
    } else if (unExpr->op == "+" || unExpr->op == "-" || unExpr->op == "~" ||
               unExpr->op == "!") {
      return operandType;
    }
    throw runtime_error("Unknown unary operator: " + unExpr->op);
  }
  // For an assignment, return the type of the left-hand side.
  if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
    return inferExpressionType(assign->lhs, analyzer);
  }
  // For an array access, return the element type of the array or pointer.
  if (auto arrAccess = std::dynamic_pointer_cast<ArrayAccess>(expr)) {
    string baseType = inferExpressionType(arrAccess->base, analyzer);
    // Remove one level of pointer
    if (!baseType.empty() && baseType.back() == '*') {
      return baseType.substr(0, baseType.size() - 1);
    }
    // Remove '[N]' for array types (if present)
    size_t pos = baseType.find('[');
    if (pos != string::npos) {
      return baseType.substr(0, pos);
    }
    throw runtime_error("Cannot index non-array/non-pointer type: " + baseType);
  }
  // For other expressions, we can't infer the type.
  throw runtime_error("Cannot infer type for expression");
}
} // namespace

void SemanticAnalyzer::analyzeExpression(
    const std::shared_ptr<Expression> &expr) {
  if (!expr)
    return;

  // NEW: If the expression is an initializer list (used for array
  // initializers), analyze each element.
  if (auto initList = std::dynamic_pointer_cast<InitializerList>(expr)) {
    for (const auto &elem : initList->elements) {
      analyzeExpression(elem);
    }
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
  } else if (auto ternary =
                 std::dynamic_pointer_cast<TernaryExpression>(expr)) {
    analyzeExpression(ternary->condition);
    analyzeExpression(ternary->trueExpr);
    analyzeExpression(ternary->falseExpr);
  } else if (auto sizeofExpr =
                 std::dynamic_pointer_cast<SizeOfExpression>(expr)) {
    if (sizeofExpr->isType) {
      // sizeof(type) - no expression to analyze
    } else {
      // sizeof(expression) - analyze the operand
      analyzeExpression(sizeofExpr->operand);
    }
  } else {
    throw runtime_error(
        "Semantic Analysis Error: Unsupported expression type encountered.");
  }
}
