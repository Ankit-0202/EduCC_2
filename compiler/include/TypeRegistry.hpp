#ifndef TYPEREGISTRY_HPP
#define TYPEREGISTRY_HPP

#include <memory>
#include <string>
#include <unordered_map>

// Forward declarations for AST node types
class StructDeclaration;
class UnionDeclaration;
class EnumDeclaration;

// Global registries for unions, structs, and enums.
extern std::unordered_map<std::string, std::shared_ptr<UnionDeclaration>>
    unionRegistry;
extern std::unordered_map<std::string, std::shared_ptr<StructDeclaration>>
    structRegistry;
extern std::unordered_map<std::string, int> enumRegistry;

// *** NEW: Global typedef registry ***
// Maps a typedef alias (e.g. "myint") to its underlying type (e.g. "int").
extern std::unordered_map<std::string, std::string> typedefRegistry;

#endif // TYPEREGISTRY_HPP
