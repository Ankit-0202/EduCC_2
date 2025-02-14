#include "SemanticAnalyzer.hpp"
#include "AST.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <iostream>
#include <stdexcept>

SemanticAnalyzer::SemanticAnalyzer() { symbolTable.enterScope(); }

void SemanticAnalyzer::analyze(const std::shared_ptr<Program> &program) {
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
  } else {
    throw std::runtime_error(
        "Semantic Analysis Error: Unknown declaration type encountered.");
  }
}

void SemanticAnalyzer::analyzeVariableDeclaration(
    const std::shared_ptr<VariableDeclaration> &varDecl) {
  // A variable is simpler: just ensure no conflicting declaration in the
  // current scope.
  Symbol symbol(varDecl->name, varDecl->type);
  if (!symbolTable.declare(symbol)) {
    throw std::runtime_error("Semantic Analysis Error: Variable '" +
                             varDecl->name +
                             "' is already declared in this scope.");
  }
  // If there is an initializer, analyze it.
  if (varDecl->initializer) {
    analyzeExpression(varDecl->initializer.value());
  }
}

void SemanticAnalyzer::analyzeFunctionDeclaration(
    const std::shared_ptr<FunctionDeclaration> &funcDecl) {
  const std::string &fnName = funcDecl->name;
  const std::string &retType = funcDecl->returnType;
  bool hasBody = (funcDecl->body != nullptr);
  std::vector<std::string> paramTypes = getParameterTypes(funcDecl->parameters);

  // See if it's already declared.
  auto existingOpt = symbolTable.lookup(fnName);
  if (!existingOpt.has_value()) {
    Symbol newFunc(fnName, retType, true, paramTypes, hasBody);
    if (!symbolTable.declare(newFunc)) {
      throw std::runtime_error(
          "Semantic Analysis Error: Could not declare function '" + fnName +
          "'.");
    }
  } else {
    Symbol existingSym = existingOpt.value();
    if (!existingSym.isFunction) {
      throw std::runtime_error("Semantic Analysis Error: '" + fnName +
                               "' is already declared as a variable.");
    }
    // Check signature match.
    if (!isFunctionSignatureCompatible(existingSym, retType, paramTypes)) {
      throw std::runtime_error(
          "Semantic Analysis Error: Conflicting declaration for function '" +
          fnName +
          "'. The parameter list or return type does not match the previous "
          "declaration.");
    }
    if (existingSym.isDefined && hasBody) {
      throw std::runtime_error("Semantic Analysis Error: Function '" + fnName +
                               "' is already defined.");
    } else if (!existingSym.isDefined && hasBody) {
      symbolTable.exitScope();
      symbolTable.enterScope();
      Symbol newSym(fnName, retType, true, paramTypes, true);
      if (!symbolTable.declare(newSym)) {
        throw std::runtime_error("Semantic Analysis Error: Could not update "
                                 "the definition of function '" +
                                 fnName + "'.");
      }
    }
  }

  // If there is a body, analyze it in a new scope (for parameters).
  if (hasBody) {
    symbolTable.enterScope();
    for (const auto &param : funcDecl->parameters) {
      Symbol paramSymbol(param.second, param.first);
      if (!symbolTable.declare(paramSymbol)) {
        throw std::runtime_error("Semantic Analysis Error: Parameter '" +
                                 param.second +
                                 "' is declared more than once.");
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
  // For an enum, we compute integer values for each enumerator.
  int currentValue = 0;
  enumDecl->enumeratorValues.clear();
  for (const auto &enumerator : enumDecl->enumerators) {
    int value = 0;
    if (enumerator.second.has_value()) {
      // For simplicity, assume the initializer is a literal int.
      auto lit = std::dynamic_pointer_cast<Literal>(enumerator.second.value());
      if (!lit) {
        throw std::runtime_error(
            "Semantic Analysis Error: Enum initializer for '" +
            enumerator.first + "' is not a literal.");
      }
      if (!std::holds_alternative<int>(lit->value)) {
        throw std::runtime_error(
            "Semantic Analysis Error: Enum initializer for '" +
            enumerator.first + "' must be an integer literal.");
      }
      value = std::get<int>(lit->value);
      currentValue = value + 1;
    } else {
      value = currentValue;
      currentValue++;
    }
    enumDecl->enumeratorValues.push_back(value);
    Symbol enumSymbol(enumerator.first, "int");
    if (!symbolTable.declare(enumSymbol)) {
      throw std::runtime_error("Semantic Analysis Error: Enumerator '" +
                               enumerator.first +
                               "' has already been declared.");
    }
  }
}

void SemanticAnalyzer::analyzeUnionDeclaration(
    const std::shared_ptr<UnionDeclaration> &unionDecl) {
  // Analyze each member.
  for (auto &member : unionDecl->members) {
    analyzeVariableDeclaration(member);
  }
  // Register the union declaration in the global union registry if it has a
  // tag.
  if (unionDecl->tag.has_value()) {
    unionRegistry[unionDecl->tag.value()] = unionDecl;
  }
}

std::vector<std::string> SemanticAnalyzer::getParameterTypes(
    const std::vector<std::pair<std::string, std::string>> &parameters) {
  std::vector<std::string> types;
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

//------------------------------------------//
//         Statement / Expression           //
//------------------------------------------//

void SemanticAnalyzer::analyzeStatement(const StatementPtr &stmt) {
  if (auto compound = std::dynamic_pointer_cast<CompoundStatement>(stmt)) {
    symbolTable.enterScope();
    for (const auto &s : compound->statements) {
      analyzeStatement(s);
    }
    symbolTable.exitScope();
  } else if (auto exprStmt =
                 std::dynamic_pointer_cast<ExpressionStatement>(stmt)) {
    analyzeExpression(exprStmt->expression);
  } else if (auto retStmt = std::dynamic_pointer_cast<ReturnStatement>(stmt)) {
    analyzeExpression(retStmt->expression);
  } else if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(stmt)) {
    analyzeExpression(ifStmt->condition);
    analyzeStatement(ifStmt->thenBranch);
    if (ifStmt->elseBranch)
      analyzeStatement(ifStmt->elseBranch.value());
  } else if (auto whileStmt = std::dynamic_pointer_cast<WhileStatement>(stmt)) {
    analyzeExpression(whileStmt->condition);
    analyzeStatement(whileStmt->body);
  } else if (auto forStmt = std::dynamic_pointer_cast<ForStatement>(stmt)) {
    if (forStmt->initializer)
      analyzeStatement(forStmt->initializer);
    if (forStmt->condition)
      analyzeExpression(forStmt->condition);
    if (forStmt->increment)
      analyzeExpression(forStmt->increment);
    analyzeStatement(forStmt->body);
  } else if (auto switchStmt =
                 std::dynamic_pointer_cast<SwitchStatement>(stmt)) {
    analyzeExpression(switchStmt->expression);
    for (const auto &caseClause : switchStmt->cases) {
      if (caseClause.first.has_value()) {
        analyzeExpression(caseClause.first.value());
      }
      analyzeStatement(caseClause.second);
    }
    if (switchStmt->defaultCase.has_value()) {
      analyzeStatement(switchStmt->defaultCase.value());
    }
  } else if (auto varDeclStmt =
                 std::dynamic_pointer_cast<VariableDeclarationStatement>(
                     stmt)) {
    auto tempVarDecl = std::make_shared<VariableDeclaration>(
        varDeclStmt->type, varDeclStmt->name, varDeclStmt->initializer);
    analyzeVariableDeclaration(tempVarDecl);
  } else if (auto multiVarDeclStmt =
                 std::dynamic_pointer_cast<MultiVariableDeclarationStatement>(
                     stmt)) {
    for (const auto &singleDeclStmt : multiVarDeclStmt->declarations) {
      auto tempVarDecl = std::make_shared<VariableDeclaration>(
          singleDeclStmt->type, singleDeclStmt->name,
          singleDeclStmt->initializer);
      analyzeVariableDeclaration(tempVarDecl);
    }
  } else {
    throw std::runtime_error(
        "Semantic Analysis Error: Unsupported statement type encountered.");
  }
}

void SemanticAnalyzer::analyzeExpression(const ExpressionPtr &expr) {
  if (!expr)
    return;
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
  }
  // NEW: Handle member access.
  else if (auto mem = std::dynamic_pointer_cast<MemberAccess>(expr)) {
    // Analyze the base expression first.
    analyzeExpression(mem->base);
    // Expect the base to be an identifier.
    if (auto baseId = std::dynamic_pointer_cast<Identifier>(mem->base)) {
      auto symbolOpt = symbolTable.lookup(baseId->name);
      if (!symbolOpt.has_value()) {
        throw std::runtime_error(
            "Semantic Analysis Error: Undefined variable '" + baseId->name +
            "' used in member access.");
      }
      std::string type = symbolOpt.value().type;
      // The type should start with "union "
      if (type.rfind("union ", 0) != 0) {
        throw std::runtime_error("Semantic Analysis Error: Variable '" +
                                 baseId->name + "' is not of a union type.");
      }
      std::string tag = type.substr(6);
      auto unionIt = unionRegistry.find(tag);
      if (unionIt == unionRegistry.end()) {
        throw std::runtime_error(
            "Semantic Analysis Error: Unknown union type '" + type + "'.");
      }
      bool found = false;
      for (auto &member : unionIt->second->members) {
        if (member->name == mem->member) {
          found = true;
          break;
        }
      }
      if (!found) {
        throw std::runtime_error("Semantic Analysis Error: Union type '" +
                                 type + "' does not contain a member named '" +
                                 mem->member + "'.");
      }
    } else {
      throw std::runtime_error("Semantic Analysis Error: Unsupported base "
                               "expression in member access.");
    }
  } else if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
    // No analysis needed for literals.
  } else if (auto id = std::dynamic_pointer_cast<Identifier>(expr)) {
    if (!symbolTable.lookup(id->name).has_value()) {
      throw std::runtime_error(
          "Semantic Analysis Error: Undefined variable or function '" +
          id->name + "'.");
    }
  } else if (auto assign = std::dynamic_pointer_cast<Assignment>(expr)) {
    // For assignments, check the left-hand side.
    // (Our code generator will later obtain the lvalue pointer from the lhs.)
    if (auto id = std::dynamic_pointer_cast<Identifier>(assign->lhs)) {
      if (!symbolTable.lookup(id->name).has_value()) {
        throw std::runtime_error(
            "Semantic Analysis Error: Undefined variable '" + id->name +
            "' used as assignment target.");
      }
    } else if (auto mem =
                   std::dynamic_pointer_cast<MemberAccess>(assign->lhs)) {
      if (auto baseId = std::dynamic_pointer_cast<Identifier>(mem->base)) {
        if (!symbolTable.lookup(baseId->name).has_value()) {
          throw std::runtime_error(
              "Semantic Analysis Error: Undefined variable '" + baseId->name +
              "' used in member access for assignment.");
        }
      } else {
        throw std::runtime_error("Semantic Analysis Error: Invalid assignment "
                                 "target in member access.");
      }
    } else {
      throw std::runtime_error(
          "Semantic Analysis Error: Invalid assignment target.");
    }
    analyzeExpression(assign->rhs);
  } else if (auto funcCall = std::dynamic_pointer_cast<FunctionCall>(expr)) {
    auto sym = symbolTable.lookup(funcCall->functionName);
    if (!sym.has_value() || !sym->isFunction) {
      throw std::runtime_error("Semantic Analysis Error: Undefined function '" +
                               funcCall->functionName + "'.");
    }
    if (sym->parameterTypes.size() != funcCall->arguments.size()) {
      throw std::runtime_error(
          "Semantic Analysis Error: Function '" + funcCall->functionName +
          "' called with an incorrect number of arguments.");
    }
    for (const auto &arg : funcCall->arguments) {
      analyzeExpression(arg);
    }
  } else {
    throw std::runtime_error(
        "Semantic Analysis Error: Unsupported expression type encountered.");
  }
}
