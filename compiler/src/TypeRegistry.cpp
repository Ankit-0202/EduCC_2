#include "TypeRegistry.hpp"

// Global registries for unions, structs, and enums.
std::unordered_map<std::string, std::shared_ptr<UnionDeclaration>>
    unionRegistry;
std::unordered_map<std::string, std::shared_ptr<StructDeclaration>>
    structRegistry;
std::unordered_map<std::string, int> enumRegistry;
