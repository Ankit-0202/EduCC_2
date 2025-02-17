#include "AST.hpp"
#include "SemanticAnalyzer.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
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
      // Regardless of whether the function has a body, predeclare it as not
      // defined.
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
  Symbol symbol(varDecl->name, varDecl->type);
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
    // This case should not occur because of the pre-declaration pass.
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
      // Update the existing function symbol to mark it as defined.
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
  }
}

void SemanticAnalyzer::analyzeUnionDeclaration(
    const std::shared_ptr<UnionDeclaration> &unionDecl) {
  for (auto &member : unionDecl->members) {
    analyzeVariableDeclaration(member);
  }
  if (unionDecl->tag.has_value()) {
    unionRegistry[unionDecl->tag.value()] = unionDecl;
  }
}

void SemanticAnalyzer::analyzeStructDeclaration(
    const std::shared_ptr<StructDeclaration> &structDecl) {
  for (auto &member : structDecl->members) {
    analyzeVariableDeclaration(member);
  }
  if (structDecl->tag.has_value()) {
    structRegistry[structDecl->tag.value()] = structDecl;
  }
}

vector<std::string> SemanticAnalyzer::getParameterTypes(
    const std::vector<std::pair<std::string, std::string>> &parameters) {
  vector<std::string> types;
  for (const auto &param : parameters) {
    types.push_back(param.first);
  }
  return types;
}

bool SemanticAnalyzer::isFunctionSignatureCompatible(
    const Symbol &existing, const std::string &returnType,
    const std::vector<std::string> &paramTypes) const {
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
