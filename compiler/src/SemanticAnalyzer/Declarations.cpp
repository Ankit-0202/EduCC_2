#include "AST.hpp"
#include "Debug.hpp"
#include "SemanticAnalyzer.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>

using std::runtime_error;
using std::string;
using std::vector;

static string normalizeBaseType(string type) {
  auto stripPrefix = [](string &s, const string &prefix) {
    if (s.rfind(prefix, 0) == 0) {
      s = s.substr(prefix.size());
      while (!s.empty() && s.front() == ' ')
        s.erase(s.begin());
    }
  };
  stripPrefix(type, "const ");
  stripPrefix(type, "volatile ");
  stripPrefix(type, "static ");
  stripPrefix(type, "const ");
  stripPrefix(type, "volatile ");
  stripPrefix(type, "_Atomic ");
  stripPrefix(type, "_Atomic");
  stripPrefix(type, "_Thread_local ");
  stripPrefix(type, "_Thread_local");
  if (type.rfind("unsigned ", 0) == 0)
    stripPrefix(type, "unsigned ");
  else if (type.rfind("signed ", 0) == 0)
    stripPrefix(type, "signed ");
  auto bracket = type.find('[');
  if (bracket != string::npos)
    type = type.substr(0, bracket);
  return type;
}

static std::optional<long long> getTypeSize(const std::string &rawType) {
  std::string type = rawType;
  if (type.find('*') != std::string::npos)
    return 8;
  size_t lb = type.find('[');
  if (lb != std::string::npos) {
    std::string base = type.substr(0, lb);
    auto baseSize = getTypeSize(base);
    if (!baseSize.has_value())
      return std::nullopt;
    size_t rb = type.find(']', lb);
    long long len = 1;
    if (rb != std::string::npos && rb > lb + 1) {
      try {
        len = std::stoll(type.substr(lb + 1, rb - lb - 1));
      } catch (...) {
        len = 1;
      }
    }
    return baseSize.value() * len;
  }

  std::string base = normalizeBaseType(type);
  if (base == "char" || base == "bool")
    return 1;
  if (base == "short")
    return 2;
  if (base == "int")
    return 4;
  if (base == "long" || base == "long long")
    return 8;
  if (base == "float")
    return 4;
  if (base == "double")
    return 8;
  if (base == "size_t" || base == "uintptr_t" || base == "intptr_t" ||
      base == "ptrdiff_t" || base == "ssize_t" || base == "max_align_t" ||
      base == "uint64_t" || base == "int64_t")
    return 8;
  if (base == "uint32_t" || base == "int32_t")
    return 4;
  if (base == "uint16_t" || base == "int16_t")
    return 2;
  if (base == "uint8_t" || base == "int8_t")
    return 1;
  if (base.rfind("struct ", 0) == 0 || base.rfind("union ", 0) == 0) {
    std::string tag = normalizeTag(base.substr(base.find(' ') + 1));
    if (auto *info = getAggregateTypeInfo(tag)) {
      if (info->totalSize > 0)
        return static_cast<long long>(info->totalSize);
    }
  }
  return std::nullopt;
}

static std::optional<long long> evaluateConstant(const ExpressionPtr &expr,
                                                 SemanticAnalyzer &analyzer) {
  if (!expr)
    return std::nullopt;
  if (auto lit = std::dynamic_pointer_cast<Literal>(expr)) {
    switch (lit->type) {
    case Literal::LiteralType::Int:
      return static_cast<long long>(lit->intValue);
    case Literal::LiteralType::Bool:
      return lit->boolValue ? 1 : 0;
    case Literal::LiteralType::Char:
      return static_cast<unsigned char>(lit->charValue);
    case Literal::LiteralType::Float:
    case Literal::LiteralType::Double:
      return static_cast<long long>(lit->doubleValue);
    case Literal::LiteralType::String:
      return std::nullopt;
    }
  }
  if (auto sizeofExpr = std::dynamic_pointer_cast<SizeOfExpression>(expr)) {
    std::string typeName;
    if (sizeofExpr->isType) {
      typeName = sizeofExpr->typeName;
    } else if (auto id =
                   std::dynamic_pointer_cast<Identifier>(sizeofExpr->operand)) {
      auto sym = analyzer.getSymbolTable().lookup(id->name);
      if (sym.has_value())
        typeName = sym->type;
    }
    auto size = getTypeSize(typeName);
    if (size.has_value())
      return size;
  }
  if (auto alignExpr = std::dynamic_pointer_cast<AlignOfExpression>(expr)) {
    if (alignExpr->isType) {
      auto alignSize = getTypeSize(alignExpr->typeName);
      if (alignSize.has_value())
        return alignSize;
    }
  }
  if (auto un = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
    auto val = evaluateConstant(un->operand, analyzer);
    if (!val.has_value())
      return std::nullopt;
    if (un->op == "+")
      return val;
    if (un->op == "-")
      return -val.value();
    if (un->op == "!")
      return val.value() == 0 ? 1 : 0;
    if (un->op == "~")
      return ~val.value();
    return std::nullopt;
  }
  if (auto bin = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
    auto lhs = evaluateConstant(bin->left, analyzer);
    auto rhs = evaluateConstant(bin->right, analyzer);
    if (!lhs.has_value() || !rhs.has_value())
      return std::nullopt;
    long long l = lhs.value();
    long long r = rhs.value();
    if (bin->op == "+")
      return l + r;
    if (bin->op == "-")
      return l - r;
    if (bin->op == "*")
      return l * r;
    if (bin->op == "/")
      return r != 0 ? std::optional<long long>(l / r) : std::nullopt;
    if (bin->op == "%")
      return r != 0 ? std::optional<long long>(l % r) : std::nullopt;
    if (bin->op == "<<")
      return l << r;
    if (bin->op == ">>")
      return l >> r;
    if (bin->op == "&")
      return l & r;
    if (bin->op == "|")
      return l | r;
    if (bin->op == "^")
      return l ^ r;
    if (bin->op == "==")
      return l == r;
    if (bin->op == "!=")
      return l != r;
    if (bin->op == "<")
      return l < r;
    if (bin->op == "<=")
      return l <= r;
    if (bin->op == ">")
      return l > r;
    if (bin->op == ">=")
      return l >= r;
    if (bin->op == "&&")
      return (l != 0 && r != 0) ? 1 : 0;
    if (bin->op == "||")
      return (l != 0 || r != 0) ? 1 : 0;
    return std::nullopt;
  }
  if (auto ternary = std::dynamic_pointer_cast<TernaryExpression>(expr)) {
    auto condVal = evaluateConstant(ternary->condition, analyzer);
    if (!condVal.has_value())
      return std::nullopt;
    if (condVal.value() != 0)
      return evaluateConstant(ternary->trueExpr, analyzer);
    return evaluateConstant(ternary->falseExpr, analyzer);
  }
  if (auto castExpr = std::dynamic_pointer_cast<CastExpression>(expr)) {
    return evaluateConstant(castExpr->operand, analyzer);
  }
  return std::nullopt;
}

SemanticAnalyzer::SemanticAnalyzer() {
  // Create the global scope.
  symbolTable.enterScope();
  auto addBuiltinFunc = [this](const std::string &name, const std::string &ret,
                               const std::vector<std::string> &params) {
    Symbol sym(name, ret, true, params, false);
    symbolTable.declare(sym);
  };
  addBuiltinFunc("isinf", "int", {"double"});
  addBuiltinFunc("signbit", "int", {"double"});
  addBuiltinFunc("atomic_compare_exchange_strong", "int",
                 {"int*", "int*", "int"});
  addBuiltinFunc("atomic_compare_exchange_weak", "int",
                 {"int*", "int*", "int"});
  addBuiltinFunc("atomic_fetch_add", "int", {"int*", "int"});
  addBuiltinFunc("atomic_load", "int", {"int*"});
}

void SemanticAnalyzer::analyze(const std::shared_ptr<Program> &program) {
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] semantic: analyze start, decl count="
              << program->declarations.size() << std::endl;
  // Pre-declare all function prototypes in the global scope.
  for (const auto &decl : program->declarations) {
    if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclaration>(decl)) {
      const string &fnName = funcDecl->name;
      const string &retType = funcDecl->returnType;
      bool predeclDefined = false;
      vector<string> paramTypes = getParameterTypes(funcDecl->parameters);
      auto existingOpt = symbolTable.lookup(fnName);
      if (!existingOpt.has_value()) {
        Symbol newFunc(fnName, retType, true, paramTypes, predeclDefined,
                       funcDecl->isVarArgs);
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
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] semantic: analyzing declaration" << std::endl;
    analyzeDeclaration(decl);
  }
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] semantic: analyze done" << std::endl;
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
  } else if (auto typedefDecl =
                 std::dynamic_pointer_cast<TypedefDeclaration>(decl)) {
    analyzeTypedefDeclaration(typedefDecl);
  } else if (auto staticAssert =
                 std::dynamic_pointer_cast<StaticAssertDeclaration>(decl)) {
    auto val = evaluateConstant(staticAssert->condition, *this);
    if (val.has_value() && val.value() == 0)
      throw runtime_error("Semantic Analysis Error: _Static_assert failed: " +
                          staticAssert->message);
  } else {
    throw runtime_error(
        "Semantic Analysis Error: Unknown declaration type encountered.");
  }
}

void SemanticAnalyzer::analyzeVariableDeclaration(
    const std::shared_ptr<VariableDeclaration> &varDecl) {
  if (varDecl->inlineStructDecl) {
    analyzeStructDeclaration(varDecl->inlineStructDecl);
  }
  if (varDecl->inlineUnionDecl) {
    analyzeUnionDeclaration(varDecl->inlineUnionDecl);
  }

  // Build the type string including array dimensions
  string typeWithDimensions = varDecl->type;
  for (auto &dimExpr : varDecl->dimensions) {
    analyzeExpression(dimExpr);
    auto constDim = evaluateConstant(dimExpr, *this);
    if (constDim.has_value())
      typeWithDimensions += "[" + std::to_string(constDim.value()) + "]";
    else
      typeWithDimensions += "[]";
  }
  if (varDecl->hasEmptyArrayDimension) {
    size_t inferredSize = 0;
    if (varDecl->initializer) {
      if (auto initList = std::dynamic_pointer_cast<InitializerList>(
              varDecl->initializer.value())) {
        inferredSize = initList->elements.empty() ? static_cast<size_t>(1)
                                                  : initList->elements.size();
      } else if (auto lit = std::dynamic_pointer_cast<Literal>(
                     varDecl->initializer.value())) {
        if (lit->type == Literal::LiteralType::String)
          inferredSize = lit->stringValue.size() + 1;
      }
    }
    if (inferredSize > 0)
      typeWithDimensions += "[" + std::to_string(inferredSize) + "]";
    else
      typeWithDimensions += "[]";
  }

  if (educcDebugEnabled()) {
    std::cerr << "[DEBUG] semantic: declaring variable '" << varDecl->name
              << "' type '" << typeWithDimensions
              << "' dims=" << varDecl->dimensions.size() << " emptyDim="
              << (varDecl->hasEmptyArrayDimension ? "true" : "false")
              << std::endl;
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
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] semantic: function '" << fnName
              << "' varargs=" << (funcDecl->isVarArgs ? "true" : "false")
              << std::endl;
  bool hasBody = (funcDecl->body != nullptr);
  vector<string> paramTypes = getParameterTypes(funcDecl->parameters);

  auto existingOpt = symbolTable.lookup(fnName);
  if (!existingOpt.has_value()) {
    Symbol newFunc(fnName, retType, true, paramTypes, hasBody,
                   funcDecl->isVarArgs);
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
    if (!isFunctionSignatureCompatible(existingSym, retType, paramTypes,
                                       funcDecl->isVarArgs)) {
      symbolTable.remove(fnName);
      Symbol newSym(fnName, retType, true, paramTypes, hasBody,
                    funcDecl->isVarArgs);
      symbolTable.declare(newSym);
      existingSym = newSym;
    } else if (existingSym.isDefined && hasBody) {
      throw runtime_error("Semantic Analysis Error: Function '" + fnName +
                          "' is already defined.");
    } else if (!existingSym.isDefined && hasBody) {
      // Update the function definition.
      symbolTable.remove(fnName);
      Symbol newSym(fnName, retType, true, paramTypes, true,
                    funcDecl->isVarArgs);
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
      auto constVal = evaluateConstant(enumerator.second.value(), *this);
      if (!constVal.has_value()) {
        if (educcDebugEnabled()) {
          std::cerr << "[DEBUG] Enum initializer for '" << enumerator.first
                    << "' expr type="
                    << typeid(*(enumerator.second.value())).name() << std::endl;
        }
        throw runtime_error("Semantic Analysis Error: Enum initializer for '" +
                            enumerator.first + "' is not a literal.");
      }
      value = static_cast<int>(constVal.value());
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
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] analyzeUnionDeclaration: Processing union declaration"
              << std::endl;

  // Create aggregate type info for the union
  AggregateTypeInfo unionInfo;
  unionInfo.tag = unionDecl->tag.value_or("anonymous_union");
  unionInfo.isUnion = true;
  unionInfo.totalSize = 0;

  auto computeMemberSize =
      [&](const std::shared_ptr<VariableDeclaration> &member) -> size_t {
    // Flexible array members do not contribute to the containing struct size.
    if (member->hasEmptyArrayDimension)
      return 0;
    string baseType = normalizeBaseType(member->type);
    size_t baseSize = 0;
    if (baseType == "int" || baseType == "float")
      baseSize = 4;
    else if (baseType == "char" || baseType == "bool")
      baseSize = 1;
    else if (baseType == "double")
      baseSize = 8;
    else if (baseType == "long long")
      baseSize = 8;
    else if (baseType == "short")
      baseSize = 2;
    else if (baseType == "long")
      baseSize = 8;
    else if (baseType.rfind("enum ", 0) == 0)
      baseSize = 4;
    else if (baseType.rfind("struct ", 0) == 0) {
      std::string structTag = baseType.substr(7);
      auto *info = getAggregateTypeInfo(structTag);
      baseSize = info ? info->totalSize : 4;
    } else if (baseType.rfind("union ", 0) == 0) {
      std::string nestedTag = baseType.substr(6);
      auto *info = getAggregateTypeInfo(nestedTag);
      baseSize = info ? info->totalSize : 4;
    } else {
      baseSize = 4;
    }
    size_t multiplier = 1;
    for (const auto &dim : member->dimensions) {
      analyzeExpression(dim);
      if (auto lit = std::dynamic_pointer_cast<Literal>(dim)) {
        multiplier *= static_cast<size_t>(lit->intValue);
      }
    }
    return baseSize * multiplier;
  };

  symbolTable.enterScope();
  size_t memberIndex = 0;
  for (auto &member : unionDecl->members) {
    size_t memberSize = computeMemberSize(member);

    MemberInfo memberInfo;
    memberInfo.name = member->name;

    // Construct the full type including array dimensions
    string fullType = member->type;
    for (const auto &dim : member->dimensions) {
      if (auto lit = std::dynamic_pointer_cast<Literal>(dim)) {
        fullType += "[" + std::to_string(lit->intValue) + "]";
      }
    }
    memberInfo.type = fullType;
    memberInfo.index = 0;
    memberInfo.offset = 0; // All union members start at offset 0
    memberInfo.size = memberSize;
    unionInfo.members.push_back(memberInfo);

    if (memberSize > unionInfo.totalSize) {
      unionInfo.totalSize = memberSize;
    }

    memberIndex++;
  }
  symbolTable.exitScope();

  if (unionDecl->tag.has_value()) {
    if (educcDebugEnabled())
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

  for (const auto &nestedUnion : structDecl->nestedUnions) {
    analyzeUnionDeclaration(nestedUnion);
  }
  for (const auto &nestedStruct : structDecl->nestedStructs) {
    analyzeStructDeclaration(nestedStruct);
  }

  auto computeMemberSize =
      [&](const std::shared_ptr<VariableDeclaration> &member) -> size_t {
    string baseType = normalizeBaseType(member->type);
    size_t baseSize = 0;
    if (baseType == "int" || baseType == "float")
      baseSize = 4;
    else if (baseType == "char" || baseType == "bool")
      baseSize = 1;
    else if (baseType == "double")
      baseSize = 8;
    else if (baseType == "long long")
      baseSize = 8;
    else if (baseType == "short")
      baseSize = 2;
    else if (baseType == "long")
      baseSize = 8;
    else if (baseType.rfind("enum ", 0) == 0)
      baseSize = 4;
    else if (baseType.rfind("struct ", 0) == 0) {
      std::string structTag = baseType.substr(7);
      auto *info = getAggregateTypeInfo(structTag);
      baseSize = info ? info->totalSize : 4;
    } else if (baseType.rfind("union ", 0) == 0) {
      std::string unionTag = baseType.substr(6);
      auto *info = getAggregateTypeInfo(unionTag);
      baseSize = info ? info->totalSize : 4;
    } else {
      baseSize = 4;
    }
    size_t multiplier = 1;
    for (const auto &dim : member->dimensions) {
      analyzeExpression(dim);
      if (auto lit = std::dynamic_pointer_cast<Literal>(dim)) {
        multiplier *= static_cast<size_t>(lit->intValue);
      }
    }
    return baseSize * multiplier;
  };

  symbolTable.enterScope();
  for (auto &member : structDecl->members) {
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] semantic: struct member '" << member->name << "'"
                << (member->bitWidth ? " (bitfield)" : "") << std::endl;

    string baseType = normalizeBaseType(member->type);
    size_t memberSize = computeMemberSize(member);

    MemberInfo memberInfo;
    memberInfo.name = member->name;
    memberInfo.type = member->type;
    for (const auto &dimExpr : member->dimensions) {
      if (auto lit = std::dynamic_pointer_cast<Literal>(dimExpr)) {
        memberInfo.type += "[" + std::to_string(lit->intValue) + "]";
      } else {
        memberInfo.type += "[]";
      }
    }
    if (member->hasEmptyArrayDimension) {
      memberInfo.type += "[]";
    }
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

    if (baseType.rfind("union ", 0) == 0 && member->isAnonymousUnionField) {
      string unionTag = baseType.substr(6);
      unionTag = normalizeTag(unionTag);
      if (auto *unionInfo = getAggregateTypeInfo(unionTag)) {
        for (const auto &uMember : unionInfo->members) {
          MemberInfo alias = uMember;
          alias.index = memberIndex;
          alias.offset = currentOffset;
          alias.isUnionMemberAlias = true;
          alias.unionTag = unionTag;
          alias.unionFieldIndex = memberIndex;
          structInfo.members.push_back(alias);
        }
      }
    } else if (baseType.rfind("struct ", 0) == 0 &&
               member->isAnonymousStructField) {
      string structTag = baseType.substr(7);
      structTag = normalizeTag(structTag);
      if (auto *nestedInfo = getAggregateTypeInfo(structTag)) {
        for (const auto &sMember : nestedInfo->members) {
          MemberInfo alias = sMember;
          alias.index = memberIndex;
          alias.offset = currentOffset + sMember.offset;
          structInfo.members.push_back(alias);
        }
      }
    }

    currentOffset += memberSize;
    memberIndex++;
  }
  symbolTable.exitScope();

  structInfo.totalSize = currentOffset;

  if (structDecl->tag.has_value()) {
    structRegistry[structDecl->tag.value()] = structDecl;
    aggregateTypeRegistry[structDecl->tag.value()] = structInfo;
  }
}

void SemanticAnalyzer::analyzeTypedefDeclaration(
    const std::shared_ptr<TypedefDeclaration> &typedefDecl) {
  TypedefInfo info{typedefDecl->underlyingType, typedefDecl->dimensions,
                   typedefDecl->isFunctionPointer,
                   typedefDecl->functionParamTypes};
  typedefRegistry[typedefDecl->alias] = info;

  if (typedefDecl->structDecl) {
    analyzeStructDeclaration(typedefDecl->structDecl);
  } else if (typedefDecl->unionDecl) {
    analyzeUnionDeclaration(typedefDecl->unionDecl);
  } else if (typedefDecl->enumDecl) {
    analyzeEnumDeclaration(typedefDecl->enumDecl);
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
    const vector<string> &paramTypes, bool isVarArgs) const {
  if (existing.type != returnType) {
    return false;
  }
  if (!existing.isVarArgs && !isVarArgs &&
      existing.parameterTypes.size() != paramTypes.size()) {
    return false;
  }
  if (existing.isVarArgs != isVarArgs) {
    return false;
  }
  if (existing.parameterTypes.empty())
    return true;
  size_t limit = std::min(existing.parameterTypes.size(), paramTypes.size());
  for (size_t i = 0; i < limit; ++i) {
    if (existing.parameterTypes[i] != paramTypes[i]) {
      return false;
    }
  }
  return true;
}
