#pragma once
#include "AST.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

struct MemberInfo {
  std::string name;
  std::string type;
  size_t bitWidth{0};
  bool isUnsigned{false};
  size_t index;
  size_t offset;
  size_t size;
  bool isUnionMemberAlias{false};
  std::string unionTag;
  size_t unionFieldIndex{0};
};

struct AggregateTypeInfo {
  std::string tag;
  std::vector<MemberInfo> members;
  size_t totalSize;
  bool isUnion;
};

extern std::unordered_map<std::string, std::shared_ptr<UnionDeclaration>>
    unionRegistry;
extern std::unordered_map<std::string, std::shared_ptr<StructDeclaration>>
    structRegistry;
extern std::unordered_map<std::string, int> enumRegistry;
struct TypedefInfo {
  std::string underlyingType;
  std::vector<ExpressionPtr> dimensions;
  bool isFunctionPointer{false};
  std::vector<std::string> functionParamTypes;
};

extern std::unordered_map<std::string, TypedefInfo> typedefRegistry;

extern std::unordered_map<std::string, AggregateTypeInfo> aggregateTypeRegistry;

// Helper functions
std::string normalizeTag(const std::string &tag);
AggregateTypeInfo *getAggregateTypeInfo(const std::string &tag);
MemberInfo *getMemberInfo(const std::string &tag,
                          const std::string &memberName);

bool isTypedefName(const std::string &name);
const TypedefInfo *getTypedefInfo(const std::string &name);
TypedefInfo resolveTypedef(const std::string &name);
std::string makeFunctionPointerType(const std::string &returnType,
                                    const std::vector<std::string> &paramTypes);
bool parseFunctionPointerType(const std::string &type, std::string &returnType,
                              std::vector<std::string> &paramTypes);
