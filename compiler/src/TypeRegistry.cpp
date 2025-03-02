#include "TypeRegistry.hpp"

// Global registries for unions, structs, and enums.
std::unordered_map<std::string, std::shared_ptr<UnionDeclaration>>
    unionRegistry;
std::unordered_map<std::string, std::shared_ptr<StructDeclaration>>
    structRegistry;
std::unordered_map<std::string, int> enumRegistry;

// *** NEW: Global typedef registry ***
// This single instance is now shared across all translation units.
std::unordered_map<std::string, std::string> typedefRegistry;
