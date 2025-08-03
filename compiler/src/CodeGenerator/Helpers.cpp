#include "CodeGenerator/Helpers.hpp"
#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "TypeRegistry.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;

// normalizeTag is now defined in TypeRegistry.cpp

std::string getEffectiveType(CodeGenerator &CG, const ExpressionPtr &expr) {
  std::cerr << "[DEBUG] getEffectiveType: Starting" << std::endl;
  // Case 1: Identifier
  if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    std::cerr << "[DEBUG] getEffectiveType: Processing identifier: " << id->name
              << std::endl;
    auto it = CG.declaredTypeStrings.find(id->name);
    if (it == CG.declaredTypeStrings.end())
      throw runtime_error("CodeGenerator Error: Declared type for variable '" +
                          id->name + "' not found.");
    std::cerr << "[DEBUG] getEffectiveType: Found type: " << it->second
              << std::endl;
    return it->second;
  }

  // Case 2: Member Access: base.member
  if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    std::cerr << "[DEBUG] Processing member access: " << mem->member
              << std::endl;
    string baseType = getEffectiveType(CG, mem->base);
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

  // Case 4: Array Access (handle array indexing)
  if (auto arr = std::dynamic_pointer_cast<ArrayAccess>(expr)) {
    string baseType = getEffectiveType(CG, arr->base);
    // Remove one level of array dimension
    size_t pos = baseType.find('[');
    if (pos != string::npos) {
      return baseType.substr(0, pos);
    }
    throw runtime_error("CodeGenerator Error: Cannot index non-array type '" +
                        baseType + "'.");
  }

  // Case 5: Binary Expression (handle pointer arithmetic)
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
