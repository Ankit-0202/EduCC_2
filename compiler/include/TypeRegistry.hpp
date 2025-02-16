#ifndef TYPE_REGISTRY_HPP
#define TYPE_REGISTRY_HPP

#include "AST.hpp"
#include <memory>
#include <string>
#include <unordered_map>

// Already existing union registry:
extern std::unordered_map<std::string, std::shared_ptr<UnionDeclaration>>
    unionRegistry;

// New: struct registry to keep track of defined struct types.
extern std::unordered_map<std::string, std::shared_ptr<StructDeclaration>>
    structRegistry;

#endif // TYPE_REGISTRY_HPP
