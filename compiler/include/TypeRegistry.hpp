#pragma once
#include "AST.hpp"
#include <memory>
#include <string>
#include <unordered_map>

extern std::unordered_map<std::string, std::shared_ptr<UnionDeclaration>>
    unionRegistry;
extern std::unordered_map<std::string, std::shared_ptr<StructDeclaration>>
    structRegistry;
extern std::unordered_map<std::string, int> enumRegistry;
