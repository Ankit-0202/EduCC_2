#ifndef TYPE_REGISTRY_HPP
#define TYPE_REGISTRY_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include "AST.hpp"

extern std::unordered_map<std::string, std::shared_ptr<UnionDeclaration>> unionRegistry;
extern std::unordered_map<std::string, std::shared_ptr<StructDeclaration>> structRegistry;

#endif // TYPE_REGISTRY_HPP
