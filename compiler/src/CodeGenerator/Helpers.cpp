#include "CodeGenerator/Helpers.hpp"
#include "TypeRegistry.hpp" // for unionRegistry and structRegistry
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
  // For an identifier, look up its declared type.
  if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    auto it = CG.declaredTypeStrings.find(id->name);
    if (it == CG.declaredTypeStrings.end())
      throw runtime_error("CodeGenerator Error: Declared type for variable '" +
                          id->name + "' not found.");
    return it->second;
  }
  // For a member access, recursively determine the type.
  if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    string baseType = getEffectiveType(CG, mem->base);
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
      throw runtime_error("CodeGenerator Error: Union type '" + tag +
                          "' does not contain member '" + mem->member + "'.");
    } else if (baseType.rfind("struct ", 0) == 0) {
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
      throw runtime_error("CodeGenerator Error: Struct type '" + tag +
                          "' does not contain member '" + mem->member + "'.");
    } else {
      throw runtime_error("CodeGenerator Error: Base expression type '" +
                          baseType + "' is not an aggregate type.");
    }
  }
  throw runtime_error("CodeGenerator Error: Unable to determine effective type "
                      "for expression.");
}
