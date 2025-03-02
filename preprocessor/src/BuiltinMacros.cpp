#include "BuiltinMacros.hpp"
#include <string>
#include <unordered_set>
#include <vector>

// In a production system these sets would be generated from target‐info.
// For now we list a representative set of items.

static const std::unordered_set<std::string> supportedAttributes = {
    "cold", "noreturn", "unused", "deprecated", "format", "always_inline"};

static const std::unordered_set<std::string> supportedExtensions = {
    // This set includes any __has_extension() items that LLVM normally
    // supports.
    "attribute_deprecated_with_message"};

static const std::unordered_set<std::string> supportedBuiltins = {
    "__builtin_va_start", "__builtin_va_end", "__builtin_expect"};

static const std::unordered_set<std::string> supportedFeatures = {
    "c_generic_selections", "c_static_assert"};

int evaluateBuiltinMacro(const std::string &macroName,
                         const std::vector<std::string> &args) {
  if (macroName == "__has_attribute") {
    if (args.size() != 1)
      return 0;
    return supportedAttributes.count(args[0]) ? 1 : 0;
  } else if (macroName == "__has_extension") {
    if (args.size() != 1)
      return 0;
    return supportedExtensions.count(args[0]) ? 1 : 0;
  } else if (macroName == "__has_builtin") {
    if (args.size() != 1)
      return 0;
    return supportedBuiltins.count(args[0]) ? 1 : 0;
  } else if (macroName == "__has_feature") {
    if (args.size() != 1)
      return 0;
    return supportedFeatures.count(args[0]) ? 1 : 0;
  }
  // Support __is_target_os: assume target is macos.
  else if (macroName == "__is_target_os") {
    if (args.size() != 1)
      return 0;
    if (args[0] == "macos")
      return 1;
    else
      return 0;
  }
  // NEW: Support __has_safe_buffers.
  else if (macroName == "__has_safe_buffers") {
    if (args.size() != 0 && !(args.size() == 1 && args[0].empty()))
      return 0;
    // For now, assume safe buffers are not supported.
    return 0;
  }
  // NEW: Support __has_ptrcheck.
  else if (macroName == "__has_ptrcheck") {
    if (args.size() != 0 && !(args.size() == 1 && args[0].empty()))
      return 0;
    // For now, assume ptrcheck is not supported.
    return 0;
  }
  return 0;
}
