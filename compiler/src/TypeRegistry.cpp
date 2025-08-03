#include "TypeRegistry.hpp"

// Global registries for unions, structs and enums.
std::unordered_map<std::string, std::shared_ptr<UnionDeclaration>>
    unionRegistry;
std::unordered_map<std::string, std::shared_ptr<StructDeclaration>>
    structRegistry;
std::unordered_map<std::string, int> enumRegistry;

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
