#include "Preprocessor.hpp"
#include "ConditionalProcessor.hpp"
#include "IncludeProcessor.hpp"
#include "MacroExpander.hpp"
#include <filesystem>
#include <fstream> // Added to provide std::ifstream
#include <sstream>
#include <stdexcept>
#include <unordered_map>

namespace fs = std::filesystem;

Preprocessor::Preprocessor(const std::vector<std::string> &sysPaths,
                           const std::vector<std::string> &userPaths)
    : systemIncludePaths(sysPaths), userIncludePaths(userPaths) {
  // (You might store these for use in IncludeProcessor in a more advanced
  // design.)
}

std::string Preprocessor::readFile(const std::string &path) {
  std::ifstream in(path);
  if (!in.is_open())
    throw std::runtime_error("Preprocessor Error: Unable to open file: " +
                             path);
  std::stringstream buffer;
  buffer << in.rdbuf();
  return buffer.str();
}

std::string Preprocessor::processIncludes(const std::string &source,
                                          const std::string &currentFile) {
  std::istringstream iss(source);
  std::ostringstream oss;
  std::string line;
  while (std::getline(iss, line)) {
    std::string trimmed = line;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    if (trimmed.compare(0, 8, "#include") == 0) {
      // Extract the header file name.
      size_t start = trimmed.find_first_of("\"<");
      size_t end = trimmed.find_last_of("\">");
      if (start == std::string::npos || end == std::string::npos ||
          end <= start)
        throw std::runtime_error(
            "Preprocessor Error: Malformed #include directive: " + line);
      std::string headerName = trimmed.substr(start + 1, end - start - 1);
      bool isSystem = (trimmed[start] == '<');

      // Build a list of directories to search.
      std::vector<std::string> searchDirs;
      if (isSystem) {
        searchDirs = {"/usr/include", "/usr/local/include"};
      } else {
        // For quoted includes, first search the directory of the current file…
        fs::path currentDir = fs::path(currentFile).parent_path();
        if (!currentDir.empty())
          searchDirs.push_back(currentDir.string());
        // …then fall back to the current working directory.
        searchDirs.push_back(".");
      }

      // Look for the header in the search directories.
      std::optional<std::string> headerPath;
      for (const auto &dir : searchDirs) {
        fs::path trial = fs::path(dir) / headerName;
        if (fs::exists(trial) && fs::is_regular_file(trial)) {
          headerPath = fs::absolute(trial).string();
          break;
        }
      }
      if (!headerPath.has_value())
        throw std::runtime_error("Preprocessor Error: Cannot locate header: " +
                                 headerName);

      std::string headerContents = processFile(headerPath.value());
      oss << headerContents << "\n";
    } else {
      oss << line << "\n";
    }
  }
  return oss.str();
}

std::string Preprocessor::processConditionals(const std::string &source) {
  ConditionalProcessor condProc;
  std::istringstream iss(source);
  std::ostringstream oss;
  std::string line;
  while (std::getline(iss, line)) {
    oss << condProc.processLine(line) << "\n";
  }
  condProc.verifyBalanced();
  return oss.str();
}

std::string Preprocessor::processMacros(const std::string &source) {
  MacroExpander expander;
  // First, run through the source to let the expander process all macro
  // directives.
  std::istringstream iss(source);
  std::ostringstream withoutDirectives;
  std::string line;
  while (std::getline(iss, line)) {
    std::string trimmed = line;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    if (trimmed.compare(0, 7, "#define") == 0 ||
        trimmed.compare(0, 6, "#undef") == 0) {
      expander.processDirective(line);
      continue; // Skip directive lines.
    }
    withoutDirectives << line << "\n";
  }
  // Now expand macros in the rest of the source.
  return expander.expand(withoutDirectives.str());
}

std::string Preprocessor::processFile(const std::string &path) {
  // Check cache first.
  if (fileCache.find(path) != fileCache.end())
    return fileCache[path];

  std::string source = readFile(path);
  // First, process includes.
  std::string included = processIncludes(source, path);
  // Then process conditionals.
  std::string conditioned = processConditionals(included);
  // Finally, process macros.
  std::string expanded = processMacros(conditioned);

  fileCache[path] = expanded;
  return expanded;
}

std::string Preprocessor::preprocess(const std::string &topLevelPath) {
  return processFile(topLevelPath);
}
