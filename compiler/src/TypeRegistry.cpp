#include "TypeRegistry.hpp"

std::unordered_map<std::string, std::shared_ptr<UnionDeclaration>> unionRegistry;
std::unordered_map<std::string, std::shared_ptr<StructDeclaration>> structRegistry;
