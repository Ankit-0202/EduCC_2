#ifndef TARGETINFO_HPP
#define TARGETINFO_HPP

#include <string>
#include <unordered_set>

class TargetInfo {
public:
  TargetInfo();

  /// Return true if the target supports the given attribute.
  bool hasAttribute(const std::string &attr) const;

  /// Return true if the target supports the given extension.
  bool hasExtension(const std::string &ext) const;

  /// Return true if the target supports the given builtin.
  bool hasBuiltin(const std::string &builtin) const;

  /// Return true if the target supports the given language feature.
  bool hasFeature(const std::string &feature) const;

  /// Return true if the target's OS matches the given name (e.g. "macos",
  /// "linux", "windows").
  bool isTargetOS(const std::string &os) const;

  // (Future extensions: add CPU, vector width, etc.)

private:
  std::unordered_set<std::string> supportedAttributes;
  std::unordered_set<std::string> supportedExtensions;
  std::unordered_set<std::string> supportedBuiltins;
  std::unordered_set<std::string> supportedFeatures;
  std::string targetOS;
};

#endif // TARGETINFO_HPP
