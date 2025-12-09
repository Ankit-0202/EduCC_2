#include "AST.hpp"
#include "Debug.hpp"
#include "SemanticAnalyzer.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <iostream>
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
      return !lit->literalType.empty() ? lit->literalType : "int";
    case Literal::LiteralType::Float:
      return "float";
    case Literal::LiteralType::Double:
      return "double";
    case Literal::LiteralType::Char:
      return "char";
    case Literal::LiteralType::Bool:
      return "bool";
    case Literal::LiteralType::String:
      return "char*";
    default:
      throw runtime_error("Cannot infer type for literal");
    }
  }
  if (auto align = std::dynamic_pointer_cast<AlignOfExpression>(expr)) {
    return "int";
  }
  if (auto gen = std::dynamic_pointer_cast<GenericSelection>(expr)) {
    auto normalize = [](std::string t) {
      auto strip = [](std::string &s, const std::string &p) {
        if (s.rfind(p, 0) == 0) {
          s = s.substr(p.size());
          while (!s.empty() && s.front() == ' ')
            s.erase(s.begin());
        }
      };
      strip(t, "const ");
      strip(t, "volatile ");
      strip(t, "static ");
      strip(t, "_Atomic ");
      return t;
    };
    std::string selectorType =
        normalize(inferExpressionType(gen->selector, analyzer));
    if (auto litSel = std::dynamic_pointer_cast<Literal>(gen->selector)) {
      if (litSel->type == Literal::LiteralType::String)
        selectorType = "char[]";
    }
    for (auto &assoc : gen->associations) {
      if (normalize(assoc.first) == selectorType)
        return inferExpressionType(assoc.second, analyzer);
    }
    if (gen->defaultExpr)
      return inferExpressionType(gen->defaultExpr.value(), analyzer);
    if (!gen->associations.empty())
      return inferExpressionType(gen->associations.front().second, analyzer);
    return "int";
  }
  if (auto comp = std::dynamic_pointer_cast<CompoundLiteral>(expr)) {
    if (!comp->dimensions.empty())
      return comp->type + "*";
    return comp->type;
  }
  // For an identifier, look it up using the public getter.
  if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    if (id->name == "I")
      return "double complex";
    auto symOpt = analyzer.getSymbolTable().lookup(id->name);
    if (!symOpt.has_value())
      throw runtime_error("Semantic Analysis Error: Undefined variable '" +
                          id->name + "'.");
    return symOpt.value().type;
  }
  // For a member access, first infer the type of the base.
  if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    string baseType = inferExpressionType(mem->base, analyzer);
    auto normalizeAggregate = [](std::string t) {
      auto strip = [](std::string &s, const std::string &p) {
        if (s.rfind(p, 0) == 0) {
          s = s.substr(p.size());
          while (!s.empty() && s.front() == ' ')
            s.erase(s.begin());
          return true;
        }
        return false;
      };
      bool changed = true;
      while (changed) {
        changed = strip(t, "const ") || strip(t, "volatile ") ||
                  strip(t, "static ") || strip(t, "_Atomic ");
      }
      return t;
    };
    std::string normalized = normalizeAggregate(baseType);
    // If the base is a union.
    if (normalized.rfind("union ", 0) == 0) {
      string tag = normalized.substr(6);
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
    else if (normalized.rfind("struct ", 0) == 0) {
      string tag = normalized.substr(7);
      if (auto *memberInfo = getMemberInfo(tag, mem->member))
        return memberInfo->type;
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
    if (funcCall->hasCalleeExpr()) {
      std::string calleeType =
          inferExpressionType(funcCall->calleeExpr, analyzer);
      std::string retType;
      std::vector<std::string> paramTypes;
      if (!parseFunctionPointerType(calleeType, retType, paramTypes)) {
        if (!calleeType.empty() && calleeType.back() == '*') {
          std::string stripped = calleeType.substr(0, calleeType.size() - 1);
          parseFunctionPointerType(stripped, retType, paramTypes);
        }
      }
      if (retType.empty())
        throw runtime_error(
            "Semantic Analysis Error: Expression is not callable.");
      return retType;
    }
    auto symOpt = analyzer.getSymbolTable().lookup(funcCall->functionName);
    if (!symOpt.has_value())
      throw runtime_error("Semantic Analysis Error: Undefined function '" +
                          funcCall->functionName + "'.");
    if (symOpt->isFunction)
      return symOpt.value().type;
    std::string retType;
    std::vector<std::string> paramTypes;
    if (parseFunctionPointerType(symOpt->type, retType, paramTypes))
      return retType;
    throw runtime_error("Semantic Analysis Error: '" + funcCall->functionName +
                        "' is not callable.");
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
      if (operandType.rfind("fnptr:", 0) == 0)
        return operandType;
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
      size_t close = baseType.find(']', pos);
      string remaining = (close != string::npos && close + 1 < baseType.size())
                             ? baseType.substr(close + 1)
                             : "";
      return baseType.substr(0, pos) + remaining;
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
    auto normalizeAggregate = [](std::string t) {
      auto strip = [](std::string &s, const std::string &p) {
        if (s.rfind(p, 0) == 0) {
          s = s.substr(p.size());
          while (!s.empty() && s.front() == ' ')
            s.erase(s.begin());
          return true;
        }
        return false;
      };
      bool changed = true;
      while (changed) {
        changed = strip(t, "const ") || strip(t, "volatile ") ||
                  strip(t, "static ") || strip(t, "_Atomic ");
      }
      return t;
    };
    std::string normalized = normalizeAggregate(baseType);
    if (normalized.rfind("union ", 0) == 0) {
      string tag = normalized.substr(6);
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
    } else if (normalized.rfind("struct ", 0) == 0) {
      string tag = normalized.substr(7);
      if (!getAggregateTypeInfo(tag))
        throw runtime_error("Semantic Analysis Error: Unknown struct type '" +
                            baseType + "'.");
      if (!getMemberInfo(tag, mem->member))
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
    if (id->name == "I") {
      return;
    }
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
    if (funcCall->functionName == "__builtin_va_arg") {
      if (!funcCall->arguments.empty())
        analyzeExpression(funcCall->arguments[0]);
      return;
    }
    if (funcCall->hasCalleeExpr()) {
      analyzeExpression(funcCall->calleeExpr);
      std::string calleeType = inferExpressionType(funcCall->calleeExpr, *this);
      std::string retType;
      std::vector<std::string> paramTypes;
      bool parsed = parseFunctionPointerType(calleeType, retType, paramTypes);
      if (!parsed && !calleeType.empty() && calleeType.back() == '*') {
        std::string stripped = calleeType.substr(0, calleeType.size() - 1);
        parsed = parseFunctionPointerType(stripped, retType, paramTypes);
      }
      if (!parsed) {
        throw runtime_error(
            "Semantic Analysis Error: Expression is not callable.");
      }
      if (!paramTypes.empty() && !funcCall->arguments.empty() &&
          paramTypes.size() != funcCall->arguments.size()) {
        throw runtime_error(
            "Semantic Analysis Error: Function called with an incorrect "
            "number of arguments.");
      }
      for (const auto &arg : funcCall->arguments) {
        analyzeExpression(arg);
      }
      return;
    }
    auto sym = symbolTable.lookup(funcCall->functionName);
    std::vector<std::string> fpParamTypes;
    bool callableViaPointer = false;
    if (!sym.has_value()) {
      Symbol implicit(funcCall->functionName, "int", true, {}, false, false);
      symbolTable.declare(implicit);
      sym = implicit;
    } else if (!sym->isFunction) {
      std::string retType;
      if (parseFunctionPointerType(sym->type, retType, fpParamTypes)) {
        callableViaPointer = true;
      } else {
        throw runtime_error("Semantic Analysis Error: '" +
                            funcCall->functionName +
                            "' is not a function or function pointer.");
      }
    }
    if (sym->isFunction) {
      if (!sym->parameterTypes.empty() && !sym->isVarArgs &&
          sym->parameterTypes.size() != funcCall->arguments.size()) {
        if (educcDebugEnabled()) {
          std::cerr << "[DEBUG] Function call '" << funcCall->functionName
                    << "' expected " << sym->parameterTypes.size()
                    << " args but got " << funcCall->arguments.size() << "\n";
        }
        throw runtime_error("Semantic Analysis Error: Function '" +
                            funcCall->functionName +
                            "' called with an incorrect number of arguments.");
      }
    } else if (callableViaPointer) {
      if (!fpParamTypes.empty() &&
          fpParamTypes.size() != funcCall->arguments.size()) {
        throw runtime_error("Semantic Analysis Error: Function pointer '" +
                            funcCall->functionName +
                            "' called with an incorrect number of arguments.");
      }
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
  } else if (auto alignExpr =
                 std::dynamic_pointer_cast<AlignOfExpression>(expr)) {
    if (!alignExpr->isType)
      analyzeExpression(alignExpr->operand);
  } else if (auto gen = std::dynamic_pointer_cast<GenericSelection>(expr)) {
    analyzeExpression(gen->selector);
    for (auto &assoc : gen->associations)
      analyzeExpression(assoc.second);
    if (gen->defaultExpr)
      analyzeExpression(gen->defaultExpr.value());
  } else if (std::dynamic_pointer_cast<CompoundLiteral>(expr)) {
    // Elements will be analyzed via initializer parsing if needed.
  } else {
    throw runtime_error(
        "Semantic Analysis Error: Unsupported expression type encountered.");
  }
}
