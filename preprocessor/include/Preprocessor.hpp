#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include "IncludeProcessor.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class Preprocessor {
public:
  Preprocessor(const std::vector<std::string> &sysPaths,
               const std::vector<std::string> &userPaths);

  // Preprocess the file at topLevelPath and return the fully expanded source.
  std::string preprocess(const std::string &topLevelPath);

private:
  std::vector<std::string> systemIncludePaths;
  std::vector<std::string> userIncludePaths;

  // Caches to avoid reprocessing files.
  std::unordered_map<std::string, std::string> fileCache;

  // Process a file: handle includes, then pass through conditional and macro
  // expansion.
  std::string processFile(const std::string &path);

  // Process include directives.
  std::string processIncludes(const std::string &source,
                              const std::string &currentFile);

  // Process conditionals.
  std::string processConditionals(const std::string &source);

  // Process macros.
  std::string processMacros(const std::string &source);

  // Helper: read file from disk.
  std::string readFile(const std::string &path);

  // A configurable IncludeProcessor.
  IncludeProcessor includeProcessor;
};

#endif // PREPROCESSOR_HPP
