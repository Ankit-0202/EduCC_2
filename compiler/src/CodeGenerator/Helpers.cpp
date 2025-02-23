#include "CodeGenerator/Helpers.hpp"
#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "TypeRegistry.hpp" // for unionRegistry and structRegistry
#include <memory>
#include <stdexcept>
#include <string>

using std::runtime_error;
using std::shared_ptr;
using std::string;

std::string normalizeTag(const string &tag) {
  size_t pos = tag.find('.');
  if (pos != string::npos)
    return tag.substr(0, pos);
  return tag;
}

std::string getEffectiveType(CodeGenerator &CG, const ExpressionPtr &expr) {
  // 1) IDENTIFIER
  if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    auto it = CG.declaredTypeStrings.find(id->name);
    if (it == CG.declaredTypeStrings.end()) {
      throw runtime_error("CodeGenerator Error: Declared type for variable '" +
                          id->name + "' not found.");
    }
    return it->second;
  }

  // 2) MEMBER ACCESS: base.member
  if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    // Recursively get the base type
    string baseType = getEffectiveType(CG, mem->base);
    // If the base is a union
    if (baseType.rfind("union ", 0) == 0) {
      string tag = baseType.substr(6);
      tag = normalizeTag(tag);
      auto uit = unionRegistry.find(tag);
      if (uit == unionRegistry.end()) {
        throw runtime_error("CodeGenerator Error: Unknown union type '" + tag +
                            "'.");
      }
      // find the matching member
      for (auto &member : uit->second->members) {
        if (member->name == mem->member) {
          return member->type;
        }
      }
      throw runtime_error("CodeGenerator Error: Union type '" + tag +
                          "' does not contain member '" + mem->member + "'.");
    }
    // If the base is a struct
    else if (baseType.rfind("struct ", 0) == 0) {
      string tag = baseType.substr(7);
      tag = normalizeTag(tag);
      auto sit = structRegistry.find(tag);
      if (sit == structRegistry.end()) {
        throw runtime_error("CodeGenerator Error: Unknown struct type '" + tag +
                            "'.");
      }
      // find the matching member
      for (auto &member : sit->second->members) {
        if (member->name == mem->member) {
          return member->type;
        }
      }
      throw runtime_error("CodeGenerator Error: Struct type '" + tag +
                          "' does not contain member '" + mem->member + "'.");
    } else {
      throw runtime_error("CodeGenerator Error: Base expression type '" +
                          baseType + "' is not an aggregate type.");
    }
  }

  // 3) NEW: UNARY EXPRESSION => handle & or *
  if (auto un = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
    // get the operand's type
    string operandType = getEffectiveType(CG, un->operand);
    if (un->op == "*") {
      // if operand type ends with '*', remove one
      // e.g. "int**" => "int*"
      if (operandType.empty() || operandType.back() != '*') {
        throw runtime_error(
            "CodeGenerator Error: Attempt to deref non-pointer type '" +
            operandType + "'.");
      }
      operandType.pop_back(); // remove one '*'
      return operandType;
    } else if (un->op == "&") {
      // e.g. "int" => "int*" or "int*" => "int**"
      operandType += "*";
      return operandType;
    } else {
      // +, - , ! => usually doesn't change the type
      // just pass it through
      return operandType;
    }
  }

  // If we got here with something else, we can't figure out the type in codegen
  throw runtime_error("CodeGenerator Error: Unable to determine effective type "
                      "for expression.");
}
