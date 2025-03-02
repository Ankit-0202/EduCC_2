#include "CodeGenerator/Helpers.hpp"
#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "TypeRegistry.hpp"
#include <algorithm>
#include <cctype>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using std::runtime_error;
using std::string;
using std::vector;

//
// normalizeTag: Remove trailing dot information (if any) from a tag.
//
std::string normalizeTag(const string &tag) {
  size_t pos = tag.find('.');
  if (pos != string::npos)
    return tag.substr(0, pos);
  return tag;
}

/// getEffectiveType: Infer the declared type (as a string) of an expression.
/// This implementation handles:
/// 1. Identifiers (by looking them up in the CodeGenerator's
/// declaredTypeStrings)
/// 2. MemberAccess expressions (for structs and unions)
/// 3. UnaryExpression with operator "*" (pointer dereference) – it removes one
/// trailing '*'
///    from the operand's effective type.
/// For other expression types, it throws an error.
string getEffectiveType(CodeGenerator &CG, const ExpressionPtr &expr) {
  // Case 1: Identifier.
  if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    auto it = CG.declaredTypeStrings.find(id->name);
    if (it == CG.declaredTypeStrings.end())
      throw runtime_error("CodeGenerator Error: Declared type for variable '" +
                          id->name + "' not found.");
    return it->second;
  }
  // Case 2: Member access (e.g. o.in.a).
  if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    string baseType = getEffectiveType(CG, mem->base);
    // If the base is a union.
    if (baseType.rfind("union ", 0) == 0) {
      string tag = baseType.substr(6);
      tag = normalizeTag(tag);
      auto uit = unionRegistry.find(tag);
      if (uit == unionRegistry.end())
        throw runtime_error("CodeGenerator Error: Unknown union type '" +
                            baseType + "'.");
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
        throw runtime_error("CodeGenerator Error: Unknown struct type '" +
                            baseType + "'.");
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
  // NEW: Handle pointer dereference.
  if (auto un = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
    if (un->op == "*") {
      // Get the effective type of the operand and remove one trailing '*' (if
      // present).
      string operandType = getEffectiveType(CG, un->operand);
      if (!operandType.empty() && operandType.back() == '*')
        operandType.pop_back();
      else
        throw runtime_error(
            "CodeGenerator Error: Cannot dereference non-pointer type '" +
            operandType + "'.");
      return operandType;
    }
  }
  // For other expression types, we throw an error.
  throw runtime_error("CodeGenerator Error: Unable to determine effective type "
                      "for expression.");
}

/// getLLVMType: Convert a string type (which may contain pointer stars)
/// into an LLVM type. Supports signed/unsigned, long/short modifiers, as well
/// as basic types, enums, unions, and structs.
llvm::Type *CodeGenerator::getLLVMType(const string &type) {
  // Count the number of '*' characters.
  int pointerCount = 0;
  size_t pos = type.find('*');
  if (pos != string::npos) {
    for (char c : type) {
      if (c == '*')
        pointerCount++;
    }
  }
  // Remove all '*' and trim whitespace.
  string baseType = type;
  baseType.erase(std::remove(baseType.begin(), baseType.end(), '*'),
                 baseType.end());
  while (!baseType.empty() && isspace(baseType.front()))
    baseType.erase(baseType.begin());
  while (!baseType.empty() && isspace(baseType.back()))
    baseType.pop_back();

  llvm::Type *ty = nullptr;
  // Support for signed/unsigned and long/short types.
  if (baseType == "int" || baseType == "signed int")
    ty = llvm::Type::getInt32Ty(context);
  else if (baseType == "unsigned int")
    ty = llvm::Type::getInt32Ty(context);
  else if (baseType == "long int" || baseType == "signed long int" ||
           baseType == "long")
    ty = llvm::Type::getInt64Ty(context);
  else if (baseType == "unsigned long int" || baseType == "unsigned long")
    ty = llvm::Type::getInt64Ty(context);
  else if (baseType == "short int" || baseType == "signed short int" ||
           baseType == "short")
    ty = llvm::Type::getInt16Ty(context);
  else if (baseType == "unsigned short int" || baseType == "unsigned short")
    ty = llvm::Type::getInt16Ty(context);
  else if (baseType == "float")
    ty = llvm::Type::getFloatTy(context);
  else if (baseType == "char" || baseType == "signed char")
    ty = llvm::Type::getInt8Ty(context);
  else if (baseType == "unsigned char")
    ty = llvm::Type::getInt8Ty(context);
  else if (baseType == "double")
    ty = llvm::Type::getDoubleTy(context);
  else if (baseType == "bool")
    ty = llvm::Type::getInt1Ty(context);
  else if (baseType == "void")
    ty = llvm::Type::getVoidTy(context);
  else if (baseType.rfind("enum ", 0) == 0)
    ty = llvm::Type::getInt32Ty(context);
  else if (baseType.rfind("union ", 0) == 0) {
    string tag = baseType.substr(6);
    auto it = unionRegistry.find(tag);
    if (it == unionRegistry.end())
      throw runtime_error("CodeGenerator Error: Unknown union type '" + type +
                          "'.");
    int maxSize = 0;
    llvm::DataLayout dl(module.get());
    for (auto &member : it->second->members) {
      int memberSize = 0;
      if (member->type == "int" || member->type == "signed int" ||
          member->type == "unsigned int" || member->type == "float")
        memberSize = 4;
      else if (member->type == "char" || member->type == "signed char" ||
               member->type == "unsigned char" || member->type == "bool")
        memberSize = 1;
      else if (member->type == "double")
        memberSize = 8;
      else if (member->type.rfind("enum ", 0) == 0)
        memberSize = 4;
      else if (member->type.rfind("union ", 0) == 0)
        throw runtime_error("Nested unions not supported.");
      else if (member->type.rfind("struct ", 0) == 0) {
        llvm::Type *structTy = getLLVMType(member->type);
        uint64_t size = dl.getTypeAllocSize(structTy);
        memberSize = static_cast<int>(size);
      } else {
        throw runtime_error("Unsupported union member type '" + member->type +
                            "'.");
      }
      if (memberSize > maxSize)
        maxSize = memberSize;
    }
    if (maxSize <= 0)
      maxSize = 1;
    ty = llvm::ArrayType::get(llvm::Type::getInt8Ty(context), maxSize);
  } else if (baseType.rfind("struct ", 0) == 0) {
    string tag = baseType.substr(7);
    auto it = structRegistry.find(tag);
    if (it == structRegistry.end())
      throw runtime_error("CodeGenerator Error: Unknown struct type '" + type +
                          "'.");
    vector<llvm::Type *> memberTypes;
    for (auto &m : it->second->members) {
      memberTypes.push_back(getLLVMType(m->type));
    }
    ty = llvm::StructType::create(context, memberTypes, tag, false);
  } else {
    throw runtime_error("CodeGenerator Error: Unsupported type '" + type +
                        "'.");
  }
  // Wrap the base type in pointer types as needed.
  for (int i = 0; i < pointerCount; i++) {
    ty = llvm::PointerType::getUnqual(ty);
  }
  return ty;
}
