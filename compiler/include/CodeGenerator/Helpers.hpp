#ifndef CODEGENERATOR_HELPERS_HPP
#define CODEGENERATOR_HELPERS_HPP

#include "AST.hpp"
#include "CodeGenerator.hpp"
#include <string>

// Returns the effective type (as a string) of the given expression.
// For identifiers, this returns the declared type stored in
// CodeGenerator::declaredTypeStrings. For member accesses, it recursively
// computes the effective type of the base and then looks up the member's type
// from the union or struct registry.
std::string getEffectiveType(CodeGenerator &CG, const ExpressionPtr &expr);

// Normalizes a tag by stripping any trailing ".<number>".
std::string normalizeTag(const std::string &tag);

#endif // CODEGENERATOR_HELPERS_HPP
