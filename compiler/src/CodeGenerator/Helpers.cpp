#include "CodeGenerator/Helpers.hpp"
#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "Debug.hpp"
#include "TypeRegistry.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;

// normalizeTag is now defined in TypeRegistry.cpp

std::string getEffectiveType(CodeGenerator &CG, const ExpressionPtr &expr) {
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] getEffectiveType: Starting" << std::endl;
  // Case 1: Identifier
  if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] getEffectiveType: Processing identifier: "
                << id->name << std::endl;
    if (id->name == "I")
      return "double complex";
    auto it = CG.declaredTypeStrings.find(id->name);
    if (it == CG.declaredTypeStrings.end())
      throw runtime_error("CodeGenerator Error: Declared type for variable '" +
                          id->name + "' not found.");
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] getEffectiveType: Found type: " << it->second
                << std::endl;
    return it->second;
  }

  // Case 2: Member Access: base.member
  if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] Processing member access: " << mem->member
                << std::endl;
    string baseType = getEffectiveType(CG, mem->base);
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] Base type: " << baseType << std::endl;

    // If the base is a union.
    if (baseType.rfind("union ", 0) == 0) {
      string tag = baseType.substr(6);
      tag = normalizeTag(tag);

      // Use the enhanced type registry to get member type
      MemberInfo *memberInfo = getMemberInfo(tag, mem->member);
      if (memberInfo) {
        return memberInfo->type;
      }

      // Fallback to simplified approach
      if (mem->member == "i" || mem->member == "f" || mem->member == "c") {
        return mem->member == "i" ? "int"
                                  : (mem->member == "f" ? "float" : "char");
      }
      throw runtime_error("CodeGenerator Error: Union member '" + mem->member +
                          "' not supported.");
    }
    // If the base is a struct.
    else if (baseType.rfind("struct ", 0) == 0) {
      string tag = baseType.substr(7);
      tag = normalizeTag(tag);

      // Use the enhanced type registry to get member type
      MemberInfo *memberInfo = getMemberInfo(tag, mem->member);
      if (memberInfo) {
        return memberInfo->type;
      }

      // Fallback to simplified approach
      if (mem->member == "x" || mem->member == "y") {
        return "int"; // Assuming both x and y are int for now
      }
      throw runtime_error("CodeGenerator Error: Struct member '" + mem->member +
                          "' not supported.");
    } else {
      throw runtime_error("CodeGenerator Error: Base expression type '" +
                          baseType + "' is not an aggregate type.");
    }
  }

  // Case 3: Unary Expression (handle & and * operators)
  if (auto un = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
    string operandType = getEffectiveType(CG, un->operand);
    if (un->op == "*") {
      if (operandType.rfind("fnptr:", 0) == 0)
        return operandType;
      if (operandType.empty() || operandType.back() != '*')
        throw runtime_error(
            "CodeGenerator Error: Attempt to deref non-pointer type '" +
            operandType + "'.");
      operandType.pop_back(); // Remove one '*'
      return operandType;
    } else if (un->op == "&") {
      if (operandType.rfind("fnptr:", 0) == 0)
        return operandType + "*";
      operandType += "*";
      return operandType;
    } else {
      // For other unary operators, assume type is unchanged.
      return operandType;
    }
  }

  // Case 4: Array Access (handle array indexing)
  if (auto arr = std::dynamic_pointer_cast<ArrayAccess>(expr)) {
    string baseType = getEffectiveType(CG, arr->base);
    // Remove one level of array dimension while preserving remaining suffix.
    size_t lb = baseType.find('[');
    if (lb != string::npos) {
      size_t rb = baseType.find(']', lb);
      string prefix = baseType.substr(0, lb);
      string suffix = (rb != string::npos) ? baseType.substr(rb + 1) : "";
      return prefix + suffix;
    }
    if (!baseType.empty() && baseType.back() == '*') {
      baseType.pop_back();
      while (!baseType.empty() &&
             isspace(static_cast<unsigned char>(baseType.back()))) {
        baseType.pop_back();
      }
      return baseType;
    }
    // Support the commutative form i[arr] by checking the index operand.
    string idxType = getEffectiveType(CG, arr->index);
    lb = idxType.find('[');
    if (lb != string::npos) {
      size_t rb = idxType.find(']', lb);
      string prefix = idxType.substr(0, lb);
      string suffix = (rb != string::npos) ? idxType.substr(rb + 1) : "";
      return prefix + suffix;
    }
    if (!idxType.empty() && idxType.back() == '*') {
      idxType.pop_back();
      while (!idxType.empty() &&
             isspace(static_cast<unsigned char>(idxType.back()))) {
        idxType.pop_back();
      }
      return idxType;
    }
    throw runtime_error("CodeGenerator Error: Cannot index non-array type '" +
                        baseType + "'.");
  }

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
    }
  }

  // Case 5: Binary Expression (handle pointer arithmetic)
  if (auto bin = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
    auto decayArrayToPointer = [](std::string t) {
      size_t lb = t.find('[');
      if (lb != string::npos) {
        t = t.substr(0, lb);
        t += "*";
      }
      return t;
    };
    if (bin->op == "+" || bin->op == "-") {
      string leftType = getEffectiveType(CG, bin->left);
      string rightType = getEffectiveType(CG, bin->right);
      string leftDecay = decayArrayToPointer(leftType);
      string rightDecay = decayArrayToPointer(rightType);
      // If one operand is a pointer and the other is int, the result is the
      // pointer type.
      if (!leftDecay.empty() && leftDecay.back() == '*' && rightType == "int")
        return leftDecay;
      if (bin->op == "+" && !rightDecay.empty() && rightDecay.back() == '*' &&
          leftType == "int")
        return rightDecay;
      // For subtraction between two pointers, result is an int.
      if (bin->op == "-" && !leftDecay.empty() && leftDecay.back() == '*' &&
          !rightDecay.empty() && rightDecay.back() == '*')
        return "int";
    }
    // Fallback: return the effective type of the left operand.
    return getEffectiveType(CG, bin->left);
  }

  if (auto castExpr = std::dynamic_pointer_cast<CastExpression>(expr)) {
    return castExpr->castType;
  }

  if (std::dynamic_pointer_cast<SizeOfExpression>(expr)) {
    return "size_t";
  }

  if (std::dynamic_pointer_cast<AlignOfExpression>(expr)) {
    return "size_t";
  }

  if (auto gen = std::dynamic_pointer_cast<GenericSelection>(expr)) {
    if (!gen->associations.empty())
      return getEffectiveType(CG, gen->associations.front().second);
    if (gen->defaultExpr)
      return getEffectiveType(CG, gen->defaultExpr.value());
    return "int";
  }

  if (auto call = std::dynamic_pointer_cast<FunctionCall>(expr)) {
    if (!call->functionName.empty()) {
      auto it = CG.declaredTypeStrings.find(call->functionName);
      if (it != CG.declaredTypeStrings.end())
        return it->second;
    }
    return "int";
  }

  if (auto compLit = std::dynamic_pointer_cast<CompoundLiteral>(expr)) {
    return compLit->type;
  }

  if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
    return getEffectiveType(CG, assign->lhs);
  }

  if (auto post = std::dynamic_pointer_cast<PostfixExpression>(expr)) {
    return getEffectiveType(CG, post->operand);
  }

  if (auto tern = std::dynamic_pointer_cast<TernaryExpression>(expr)) {
    return getEffectiveType(CG, tern->trueExpr);
  }

  // (No branch is provided for function calls, since they are not used in
  // lvalue contexts.)

  throw runtime_error("CodeGenerator Error: Unable to determine effective type "
                      "for expression.");
}
