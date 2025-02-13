#ifndef TYPE_REGISTRY_HPP
#define TYPE_REGISTRY_HPP

#include "AST.hpp"
#include <unordered_map>
#include <memory>
#include <string>

extern std::unordered_map<std::string, std::shared_ptr<UnionDeclaration>> unionRegistry;

#endif // TYPE_REGISTRY_HPP
