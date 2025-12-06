#include "AST.hpp"
#include "SemanticAnalyzer.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::runtime_error;
using std::string;
using std::vector;

SemanticAnalyzer::SemanticAnalyzer() {
  // Create the global scope.
  symbolTable.enterScope();
}

void SemanticAnalyzer::analyze(const std::shared_ptr<Program> &program) {
  // Pre-declare all function prototypes in the global scope.
  for (const auto &decl : program->declarations) {
    if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclaration>(decl)) {
      const string &fnName = funcDecl->name;
      const string &retType = funcDecl->returnType;
      bool predeclDefined = false;
      vector<string> paramTypes = getParameterTypes(funcDecl->parameters);
      auto existingOpt = symbolTable.lookup(fnName);
      if (!existingOpt.has_value()) {
        Symbol newFunc(fnName, retType, true, paramTypes, predeclDefined);
        if (!symbolTable.declare(newFunc)) {
          throw runtime_error(
              "Semantic Analysis Error: Could not declare function '" + fnName +
              "'.");
        }
      }
    }
  }

  // Now analyze each declaration.
  for (const auto &decl : program->declarations) {
    analyzeDeclaration(decl);
  }
}

void SemanticAnalyzer::analyzeDeclaration(const DeclarationPtr &decl) {
  if (auto varDecl = std::dynamic_pointer_cast<VariableDeclaration>(decl)) {
    analyzeVariableDeclaration(varDecl);
  } else if (auto funcDecl =
                 std::dynamic_pointer_cast<FunctionDeclaration>(decl)) {
    analyzeFunctionDeclaration(funcDecl);
  } else if (auto multiVarDecl =
                 std::dynamic_pointer_cast<MultiVariableDeclaration>(decl)) {
    for (const auto &singleDecl : multiVarDecl->declarations) {
      analyzeVariableDeclaration(singleDecl);
    }
  } else if (auto enumDecl = std::dynamic_pointer_cast<EnumDeclaration>(decl)) {
    analyzeEnumDeclaration(enumDecl);
  } else if (auto unionDecl =
                 std::dynamic_pointer_cast<UnionDeclaration>(decl)) {
    analyzeUnionDeclaration(unionDecl);
  } else if (auto structDecl =
                 std::dynamic_pointer_cast<StructDeclaration>(decl)) {
    analyzeStructDeclaration(structDecl);
  } else {
    throw runtime_error(
        "Semantic Analysis Error: Unknown declaration type encountered.");
  }
}

void SemanticAnalyzer::analyzeVariableDeclaration(
    const std::shared_ptr<VariableDeclaration> &varDecl) {
  // Build the type string including array dimensions
  string typeWithDimensions = varDecl->type;
  for (auto &dimExpr : varDecl->dimensions) {
    analyzeExpression(dimExpr);
    if (auto lit = std::dynamic_pointer_cast<Literal>(dimExpr)) {
      if (lit->type != Literal::LiteralType::Int) {
        throw runtime_error("Semantic Analysis Error: Array dimension for '" +
                            varDecl->name + "' must be an integer literal.");
      }
      typeWithDimensions += "[" + std::to_string(lit->intValue) + "]";
    } else {
      throw runtime_error("Semantic Analysis Error: Array dimension for '" +
                          varDecl->name +
                          "' must be a constant integer literal.");
    }
  }

  Symbol symbol(varDecl->name, typeWithDimensions);
  if (!symbolTable.declare(symbol)) {
    throw runtime_error("Semantic Analysis Error: Variable '" + varDecl->name +
                        "' is already declared in this scope.");
  }

  if (varDecl->initializer) {
    analyzeExpression(varDecl->initializer.value());
  }
}

void SemanticAnalyzer::analyzeFunctionDeclaration(
    const std::shared_ptr<FunctionDeclaration> &funcDecl) {
  const string &fnName = funcDecl->name;
  const string &retType = funcDecl->returnType;
  bool hasBody = (funcDecl->body != nullptr);
  vector<string> paramTypes = getParameterTypes(funcDecl->parameters);

  auto existingOpt = symbolTable.lookup(fnName);
  if (!existingOpt.has_value()) {
    Symbol newFunc(fnName, retType, true, paramTypes, hasBody);
    if (!symbolTable.declare(newFunc)) {
      throw runtime_error(
          "Semantic Analysis Error: Could not declare function '" + fnName +
          "'.");
    }
  } else {
    Symbol existingSym = existingOpt.value();
    if (!existingSym.isFunction) {
      throw runtime_error("Semantic Analysis Error: '" + fnName +
                          "' is already declared as a variable.");
    }
    if (!isFunctionSignatureCompatible(existingSym, retType, paramTypes)) {
      throw runtime_error(
          "Semantic Analysis Error: Conflicting declaration for function '" +
          fnName +
          "'. The parameter list or return type does not match the previous "
          "declaration.");
    }
    if (existingSym.isDefined && hasBody) {
      throw runtime_error("Semantic Analysis Error: Function '" + fnName +
                          "' is already defined.");
    } else if (!existingSym.isDefined && hasBody) {
      // Update the function definition.
      symbolTable.remove(fnName);
      Symbol newSym(fnName, retType, true, paramTypes, true);
      if (!symbolTable.declare(newSym)) {
        throw runtime_error("Semantic Analysis Error: Could not update the "
                            "definition of function '" +
                            fnName + "'.");
      }
    }
  }

  if (hasBody) {
    symbolTable.enterScope();
    for (const auto &param : funcDecl->parameters) {
      Symbol paramSymbol(param.second, param.first);
      if (!symbolTable.declare(paramSymbol)) {
        throw runtime_error("Semantic Analysis Error: Parameter '" +
                            param.second + "' is declared more than once.");
      }
    }
    if (auto compound =
            std::dynamic_pointer_cast<CompoundStatement>(funcDecl->body)) {
      for (const auto &stmt : compound->statements) {
        analyzeStatement(stmt);
      }
    }
    symbolTable.exitScope();
  }
}

void SemanticAnalyzer::analyzeEnumDeclaration(
    const std::shared_ptr<EnumDeclaration> &enumDecl) {
  int currentValue = 0;
  enumDecl->enumeratorValues.clear();
  for (const auto &enumerator : enumDecl->enumerators) {
    int value = 0;
    if (enumerator.second.has_value()) {
      auto lit = std::dynamic_pointer_cast<Literal>(enumerator.second.value());
      if (!lit) {
        throw runtime_error("Semantic Analysis Error: Enum initializer for '" +
                            enumerator.first + "' is not a literal.");
      }
      if (lit->type != Literal::LiteralType::Int) {
        throw runtime_error("Semantic Analysis Error: Enum initializer for '" +
                            enumerator.first + "' must be an integer literal.");
      }
      value = lit->intValue;
      currentValue = value + 1;
    } else {
      value = currentValue;
      currentValue++;
    }
    enumDecl->enumeratorValues.push_back(value);
    Symbol enumSymbol(enumerator.first, "int");
    if (!symbolTable.declare(enumSymbol)) {
      throw runtime_error("Semantic Analysis Error: Enumerator '" +
                          enumerator.first + "' has already been declared.");
    }
    // Also record the enumerator in the global enum registry so code generation
    // finds it.
    enumRegistry[enumerator.first] = value;
  }
}

void SemanticAnalyzer::analyzeUnionDeclaration(
    const std::shared_ptr<UnionDeclaration> &unionDecl) {
  std::cerr << "[DEBUG] analyzeUnionDeclaration: Processing union declaration"
            << std::endl;

  // Create aggregate type info for the union
  AggregateTypeInfo unionInfo;
  unionInfo.tag = unionDecl->tag.value_or("anonymous_union");
  unionInfo.isUnion = true;
  unionInfo.totalSize = 0;

  size_t memberIndex = 0;
  for (auto &member : unionDecl->members) {
    analyzeVariableDeclaration(member);

    // Calculate member size (simplified)
    size_t memberSize = 0;
    if (member->type == "int" || member->type == "float")
      memberSize = 4;
    else if (member->type == "char" || member->type == "bool")
      memberSize = 1;
    else if (member->type == "double")
      memberSize = 8;
    else if (member->type.rfind("enum ", 0) == 0)
      memberSize = 4;
    else if (member->type.rfind("struct ", 0) == 0) {
      std::string structTag = member->type.substr(7);
      auto structIt = structRegistry.find(structTag);
      if (structIt != structRegistry.end()) {
        // Calculate struct size based on members
        memberSize = 0;
        for (const auto &structMember : structIt->second->members) {
          size_t structMemberSize = 0;
          if (structMember->type == "int" || structMember->type == "float")
            structMemberSize = 4;
          else if (structMember->type == "char" || structMember->type == "bool")
            structMemberSize = 1;
          else if (structMember->type == "double")
            structMemberSize = 8;
          else
            structMemberSize = 4; // Default
          memberSize += structMemberSize;
        }
      } else {
        memberSize = 4; // Default size
      }
    } else {
      memberSize = 4; // Default size
    }

    // For unions, all members share the same memory location
    MemberInfo memberInfo;
    memberInfo.name = member->name;
    
    // Construct the full type including array dimensions
    string fullType = member->type;
    for (const auto& dim : member->dimensions) {
      if (auto lit = std::dynamic_pointer_cast<Literal>(dim)) {
        if (lit->type == Literal::LiteralType::Int) {
          fullType += "[" + std::to_string(lit->intValue) + "]";
        }
      }
    }
    memberInfo.type = fullType;
    memberInfo.index = memberIndex;
    memberInfo.offset = 0; // All union members start at offset 0
    memberInfo.size = memberSize;
    unionInfo.members.push_back(memberInfo);

    // Union size is the size of the largest member
    if (memberSize > unionInfo.totalSize) {
      unionInfo.totalSize = memberSize;
    }

    memberIndex++;
  }

  if (unionDecl->tag.has_value()) {
    std::cerr << "[DEBUG] analyzeUnionDeclaration: Registering union '"
              << unionDecl->tag.value() << "'" << std::endl;
    unionRegistry[unionDecl->tag.value()] = unionDecl;
    aggregateTypeRegistry[unionDecl->tag.value()] = unionInfo;
  }
}

void SemanticAnalyzer::analyzeStructDeclaration(
    const std::shared_ptr<StructDeclaration> &structDecl) {
  // Create aggregate type info for the struct
  AggregateTypeInfo structInfo;
  structInfo.tag = structDecl->tag.value_or("anonymous_struct");
  structInfo.isUnion = false;
  structInfo.totalSize = 0;

  size_t memberIndex = 0;
  size_t currentOffset = 0;

  for (auto &member : structDecl->members) {
    analyzeVariableDeclaration(member);

    // Calculate member size (simplified)
    size_t memberSize = 0;
    if (member->type == "int" || member->type == "float")
      memberSize = 4;
    else if (member->type == "char" || member->type == "bool")
      memberSize = 1;
    else if (member->type == "double")
      memberSize = 8;
    else if (member->type.rfind("enum ", 0) == 0)
      memberSize = 4;
    else if (member->type.rfind("struct ", 0) == 0) {
      std::string structTag = member->type.substr(7);
      auto structIt = structRegistry.find(structTag);
      if (structIt != structRegistry.end()) {
        // Calculate struct size based on members
        memberSize = 0;
        for (const auto &structMember : structIt->second->members) {
          size_t structMemberSize = 0;
          if (structMember->type == "int" || structMember->type == "float")
            structMemberSize = 4;
          else if (structMember->type == "char" || structMember->type == "bool")
            structMemberSize = 1;
          else if (structMember->type == "double")
            structMemberSize = 8;
          else
            structMemberSize = 4; // Default
          memberSize += structMemberSize;
        }
      } else {
        memberSize = 4; // Default size
      }
    } else {
      memberSize = 4; // Default size
    }

    // For structs, members are laid out sequentially
    MemberInfo memberInfo;
    memberInfo.name = member->name;
    memberInfo.type = member->type;
    memberInfo.bitWidth = member->bitWidth.has_value()
                              ? static_cast<size_t>(member->bitWidth.value())
                              : 0;
    memberInfo.isUnsigned =
        (member->type.rfind("unsigned", 0) == 0) ||
        (member->type.find(" unsigned") != std::string::npos);
    memberInfo.index = memberIndex;
    memberInfo.offset = currentOffset;
    memberInfo.size = memberSize;
    structInfo.members.push_back(memberInfo);

    currentOffset += memberSize;
    memberIndex++;
  }

  structInfo.totalSize = currentOffset;

  if (structDecl->tag.has_value()) {
    structRegistry[structDecl->tag.value()] = structDecl;
    aggregateTypeRegistry[structDecl->tag.value()] = structInfo;
  }
}

vector<string> SemanticAnalyzer::getParameterTypes(
    const std::vector<std::pair<string, string>> &parameters) {
  vector<string> types;
  for (const auto &param : parameters) {
    types.push_back(param.first);
  }
  return types;
}

bool SemanticAnalyzer::isFunctionSignatureCompatible(
    const Symbol &existing, const string &returnType,
    const vector<string> &paramTypes) const {
  if (existing.type != returnType) {
    return false;
  }
  if (existing.parameterTypes.size() != paramTypes.size()) {
    return false;
  }
  for (size_t i = 0; i < paramTypes.size(); ++i) {
    if (existing.parameterTypes[i] != paramTypes[i]) {
      return false;
    }
  }
  return true;
}
