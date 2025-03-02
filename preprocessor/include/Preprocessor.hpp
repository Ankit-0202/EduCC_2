#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include "IncludeProcessor.hpp"
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

class Preprocessor {
public:
  Preprocessor(const std::vector<std::string> &systemPaths,
               const std::vector<std::string> &userPaths);

  // Preprocess a file given its path.
  std::string preprocess(const std::string &topLevelPath);

private:
  // Helper methods.
  std::string readFile(const std::string &path);
  std::string processIncludes(const std::string &source,
                              const std::string &currentFile);
  std::string processConditionals(const std::string &source);
  std::string processMacros(const std::string &source);
  std::string processFile(const std::string &path);

  // Include search paths.
  std::vector<std::string> systemIncludePaths;
  std::vector<std::string> userIncludePaths;

  // Cache for processed files.
  std::unordered_map<std::string, std::string> fileCache;

  // Our IncludeProcessor member.
  IncludeProcessor includeProcessor;

  // NEW: Directory of the top-level source file.
  std::string topLevelDir;
};

#endif // PREPROCESSOR_HPP
