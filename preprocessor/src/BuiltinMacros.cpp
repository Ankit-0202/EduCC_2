#include "BuiltinMacros.hpp"
#include "TargetInfo.hpp"
#include <string>
#include <vector>

// Create a global TargetInfo instance.
static TargetInfo targetInfo;

int evaluateBuiltinMacro(const std::string &macroName,
                         const std::vector<std::string> &args) {
  if (macroName == "__has_attribute") {
    if (args.size() != 1)
      return 0;
    return targetInfo.hasAttribute(args[0]) ? 1 : 0;
  } else if (macroName == "__has_extension") {
    if (args.size() != 1)
      return 0;
    return targetInfo.hasExtension(args[0]) ? 1 : 0;
  } else if (macroName == "__has_builtin") {
    if (args.size() != 1)
      return 0;
    return targetInfo.hasBuiltin(args[0]) ? 1 : 0;
  } else if (macroName == "__has_feature") {
    if (args.size() != 1)
      return 0;
    return targetInfo.hasFeature(args[0]) ? 1 : 0;
  }
  // Support a built-in macro __is_target_os that returns 1 if the current
  // target OS matches the argument (e.g. __is_target_os("macos"))
  else if (macroName == "__is_target_os") {
    if (args.size() != 1)
      return 0;
    return targetInfo.isTargetOS(args[0]) ? 1 : 0;
  }
  return 0;
}
