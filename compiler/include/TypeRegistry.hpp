#ifndef TYPE_REGISTRY_HPP
#define TYPE_REGISTRY_HPP

#include "AST.hpp"
#include <memory>
#include <string>
#include <unordered_map>

extern std::unordered_map<std::string, std::shared_ptr<UnionDeclaration>>
    unionRegistry;

#endif // TYPE_REGISTRY_HPP
