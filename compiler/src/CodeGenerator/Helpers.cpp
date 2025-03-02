#include "CodeGenerator/Helpers.hpp"
#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "TypeRegistry.hpp"
#include <memory>
#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;

std::string normalizeTag(const string &tag) {
  size_t pos = tag.find('.');
  if (pos != string::npos)
    return tag.substr(0, pos);
  return tag;
}

std::string getEffectiveType(CodeGenerator &CG, const ExpressionPtr &expr) {
  // Case 1: Identifier
  if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    auto it = CG.declaredTypeStrings.find(id->name);
    if (it == CG.declaredTypeStrings.end())
      throw runtime_error("CodeGenerator Error: Declared type for variable '" +
                          id->name + "' not found.");
    return it->second;
  }
  // Case 2: Member Access: base.member
  if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    string baseType = getEffectiveType(CG, mem->base);
    // If the base is a union.
    if (baseType.rfind("union ", 0) == 0) {
      string tag = baseType.substr(6);
      tag = normalizeTag(tag);
      auto uit = unionRegistry.find(tag);
      if (uit == unionRegistry.end())
        throw runtime_error("CodeGenerator Error: Unknown union type '" + tag +
                            "'.");
      for (auto &member : uit->second->members) {
        if (member->name == mem->member)
          return member->type;
      }
      throw runtime_error("CodeGenerator Error: Union type '" + baseType +
                          "' does not contain member '" + mem->member + "'.");
    }
    // If the base is a struct.
    else if (baseType.rfind("struct ", 0) == 0) {
      string tag = baseType.substr(7);
      tag = normalizeTag(tag);
      auto sit = structRegistry.find(tag);
      if (sit == structRegistry.end())
        throw runtime_error("CodeGenerator Error: Unknown struct type '" + tag +
                            "'.");
      for (auto &member : sit->second->members) {
        if (member->name == mem->member)
          return member->type;
      }
      throw runtime_error("CodeGenerator Error: Struct type '" + baseType +
                          "' does not contain member '" + mem->member + "'.");
    } else {
      throw runtime_error("CodeGenerator Error: Base expression type '" +
                          baseType + "' is not an aggregate type.");
    }
  }

  // Case 3: Unary Expression (handle & and * operators)
  if (auto un = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
    string operandType = getEffectiveType(CG, un->operand);
    if (un->op == "*") {
      if (operandType.empty() || operandType.back() != '*')
        throw runtime_error(
            "CodeGenerator Error: Attempt to deref non-pointer type '" +
            operandType + "'.");
      operandType.pop_back(); // Remove one '*'
      return operandType;
    } else if (un->op == "&") {
      operandType += "*";
      return operandType;
    } else {
      // For other unary operators, assume type is unchanged.
      return operandType;
    }
  }

  // Case 4: Binary Expression (handle pointer arithmetic)
  if (auto bin = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
    if (bin->op == "+" || bin->op == "-") {
      string leftType = getEffectiveType(CG, bin->left);
      string rightType = getEffectiveType(CG, bin->right);
      // If one operand is a pointer and the other is int, the result is the
      // pointer type.
      if (!leftType.empty() && leftType.back() == '*' && rightType == "int")
        return leftType;
      if (bin->op == "+" && !rightType.empty() && rightType.back() == '*' &&
          leftType == "int")
        return rightType;
      // For subtraction between two pointers, result is an int.
      if (bin->op == "-" && !leftType.empty() && leftType.back() == '*' &&
          !rightType.empty() && rightType.back() == '*')
        return "int";
    }
    // Fallback: return the effective type of the left operand.
    return getEffectiveType(CG, bin->left);
  }

  // (No branch is provided for function calls, since they are not used in
  // lvalue contexts.)

  throw runtime_error("CodeGenerator Error: Unable to determine effective type "
                      "for expression.");
}