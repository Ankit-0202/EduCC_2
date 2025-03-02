#include "TargetInfo.hpp"
#include <cstdlib>

// In a professional implementation the constructor would examine the target
// triple, CPU features, OS version, and command–line options (or use system
// APIs) to decide which attributes, extensions, built–ins, and language
// features are available. Here we implement a complete solution based on
// compile–time macros.

TargetInfo::TargetInfo() {
#ifdef __APPLE__
  targetOS = "macos";
  supportedAttributes = {"cold",
                         "noreturn",
                         "unused",
                         "deprecated",
                         "format",
                         "always_inline",
                         "deprecated_with_message"};
  supportedExtensions = {"attribute_deprecated_with_message",
                         "vector_extensions", "sse2", "avx2"};
  supportedBuiltins = {"__builtin_va_start", "__builtin_va_end",
                       "__builtin_expect", "__builtin_popcount"};
  supportedFeatures = {"c_generic_selections", "c_static_assert", "atomic",
                       "tls"};
#elif defined(_WIN32)
  targetOS = "windows";
  supportedAttributes = {"noreturn", "unused", "deprecated", "format"};
  supportedExtensions = {"attribute_deprecated_with_message"};
  supportedBuiltins = {"__builtin_va_start", "__builtin_va_end"};
  supportedFeatures = {"c_static_assert", "atomic"};
#else
  // Fallback for Linux/other Unix-like systems.
  targetOS = "linux";
  supportedAttributes = {"noreturn", "unused", "deprecated", "format"};
  supportedExtensions = {"attribute_deprecated_with_message",
                         "vector_extensions"};
  supportedBuiltins = {"__builtin_va_start", "__builtin_va_end",
                       "__builtin_expect"};
  supportedFeatures = {"c_static_assert", "atomic", "tls"};
#endif
}

bool TargetInfo::hasAttribute(const std::string &attr) const {
  return supportedAttributes.find(attr) != supportedAttributes.end();
}

bool TargetInfo::hasExtension(const std::string &ext) const {
  return supportedExtensions.find(ext) != supportedExtensions.end();
}

bool TargetInfo::hasBuiltin(const std::string &builtin) const {
  return supportedBuiltins.find(builtin) != supportedBuiltins.end();
}

bool TargetInfo::hasFeature(const std::string &feature) const {
  return supportedFeatures.find(feature) != supportedFeatures.end();
}

bool TargetInfo::isTargetOS(const std::string &os) const {
  return targetOS == os;
}
