#include "TypeRegistry.hpp"
#include <unordered_set>

// Global registries for unions, structs and enums.
std::unordered_map<std::string, std::shared_ptr<UnionDeclaration>>
    unionRegistry;
std::unordered_map<std::string, std::shared_ptr<StructDeclaration>>
    structRegistry;
std::unordered_map<std::string, int> enumRegistry;
std::unordered_map<std::string, TypedefInfo> typedefRegistry;

// Enhanced type registry for better struct/union handling
std::unordered_map<std::string, AggregateTypeInfo> aggregateTypeRegistry;

std::string normalizeTag(const std::string &tag) {
  size_t pos = tag.find('.');
  if (pos != std::string::npos)
    return tag.substr(0, pos);
  return tag;
}

AggregateTypeInfo *getAggregateTypeInfo(const std::string &tag) {
  auto it = aggregateTypeRegistry.find(tag);
  if (it != aggregateTypeRegistry.end()) {
    return &it->second;
  }
  return nullptr;
}

MemberInfo *getMemberInfo(const std::string &tag,
                          const std::string &memberName) {
  AggregateTypeInfo *typeInfo = getAggregateTypeInfo(tag);
  if (!typeInfo) {
    return nullptr;
  }

  for (auto &member : typeInfo->members) {
    if (member.name == memberName) {
      return &member;
    }
  }
  return nullptr;
}

bool isTypedefName(const std::string &name) {
  return typedefRegistry.find(name) != typedefRegistry.end();
}

const TypedefInfo *getTypedefInfo(const std::string &name) {
  auto it = typedefRegistry.find(name);
  if (it == typedefRegistry.end())
    return nullptr;
  return &it->second;
}

TypedefInfo resolveTypedef(const std::string &name) {
  TypedefInfo info{};
  auto it = typedefRegistry.find(name);
  if (it == typedefRegistry.end())
    return info;

  info = it->second;
  std::unordered_set<std::string> seen;
  seen.insert(name);
  while (isTypedefName(info.underlyingType) &&
         seen.find(info.underlyingType) == seen.end()) {
    seen.insert(info.underlyingType);
    const TypedefInfo &base = typedefRegistry[info.underlyingType];
    info.underlyingType = base.underlyingType;
    info.isFunctionPointer = base.isFunctionPointer;
    info.functionParamTypes = base.functionParamTypes;
    info.dimensions.insert(info.dimensions.end(), base.dimensions.begin(),
                           base.dimensions.end());
  }
  return info;
}

std::string
makeFunctionPointerType(const std::string &returnType,
                        const std::vector<std::string> &paramTypes) {
  std::string type = "fnptr:" + returnType + "(";
  for (size_t i = 0; i < paramTypes.size(); ++i) {
    if (i > 0)
      type += ",";
    type += paramTypes[i];
  }
  type += ")";
  return type;
}

static std::string trim(const std::string &s) {
  size_t start = s.find_first_not_of(" \t\n\r");
  if (start == std::string::npos)
    return "";
  size_t end = s.find_last_not_of(" \t\n\r");
  return s.substr(start, end - start + 1);
}

bool parseFunctionPointerType(const std::string &type, std::string &returnType,
                              std::vector<std::string> &paramTypes) {
  if (type.rfind("fnptr:", 0) != 0)
    return false;
  size_t lparen = type.find('(');
  size_t rparen = type.rfind(')');
  if (lparen == std::string::npos || rparen == std::string::npos ||
      rparen < lparen)
    return false;
  returnType = trim(type.substr(6, lparen - 6));
  std::string params = type.substr(lparen + 1, rparen - lparen - 1);
  paramTypes.clear();
  if (params.empty())
    return true;

  size_t start = 0;
  while (start < params.size()) {
    size_t comma = params.find(',', start);
    if (comma == std::string::npos)
      comma = params.size();
    std::string param = trim(params.substr(start, comma - start));
    if (!param.empty())
      paramTypes.push_back(param);
    start = comma + 1;
  }
  return true;
}
