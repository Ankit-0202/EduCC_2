#ifndef BUILTIN_MACROS_HPP
#define BUILTIN_MACROS_HPP

#include <string>
#include <vector>

// Evaluate a built-in macro that takes one argument. For example,
// __has_attribute("cold"). Returns 1 if the requested
// attribute/extension/builtin/feature is supported, or 0 otherwise.
int evaluateBuiltinMacro(const std::string &macroName,
                         const std::vector<std::string> &args);

#endif // BUILTIN_MACROS_HPP
