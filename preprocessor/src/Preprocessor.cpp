#include "Preprocessor.hpp"
#include "ConditionalProcessor.hpp"
#include "IncludeProcessor.hpp"
#include "MacroExpander.hpp"
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <vector>

// Instead of calling llvm::sys::getResourceDir() (which no longer exists),
// we use the compile-time macro LLVM_RESOURCE_DIR (if defined) to obtain the
// LLVM built‑in headers resource directory.
#include <llvm/Support/Path.h>

namespace fs = std::filesystem;

// Helper function: Remove line continuations (backslash-newline sequences)
// as required by the C preprocessor standard.
static std::string removeLineContinuations(const std::string &source) {
  std::string result;
  result.reserve(source.size());
  for (size_t i = 0; i < source.size(); ++i) {
    // If a backslash is immediately followed by a newline (or "\r\n"), skip
    // both.
    if (source[i] == '\\' && i + 1 < source.size() && source[i + 1] == '\n') {
      i++; // Skip the newline
      continue;
    }
    // Handle Windows-style "\r\n"
    if (source[i] == '\\' && i + 2 < source.size() && source[i + 1] == '\r' &&
        source[i + 2] == '\n') {
      i += 2;
      continue;
    }
    result.push_back(source[i]);
  }
  return result;
}

/// New helper function: Runs an external preprocessor (Clang) on the given
/// header file. This is used for system headers.
static std::string runExternalPreprocessor(const std::string &headerPath) {
  // Construct the command to invoke Clang's preprocessor.
  // -E: preprocess only, -P: omit line markers, -x c-header: treat input as a C
  // header.
  std::string command = "clang -E -P -x c-header " + headerPath;
  FILE *pipe = popen(command.c_str(), "r");
  if (!pipe) {
    throw std::runtime_error("Failed to run external preprocessor on " +
                             headerPath);
  }
  char buffer[128];
  std::string result;
  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    result += buffer;
  }
  int rc = pclose(pipe);
  if (rc != 0) {
    throw std::runtime_error("External preprocessor returned error for " +
                             headerPath);
  }
  return result;
}

Preprocessor::Preprocessor(const std::vector<std::string> &sysPaths,
                           const std::vector<std::string> &userPaths)
    : systemIncludePaths(sysPaths), userIncludePaths(userPaths),
      includeProcessor(sysPaths, userPaths), topLevelDir("") // Initially empty.
{}

std::string Preprocessor::readFile(const std::string &path) {
  std::ifstream in(path);
  if (!in.is_open())
    throw std::runtime_error("Preprocessor Error: Unable to open file: " +
                             path);
  std::stringstream buffer;
  buffer << in.rdbuf();
  // Remove any line continuations (backslash-newline) before further
  // processing.
  std::string rawSource = buffer.str();
  return removeLineContinuations(rawSource);
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

      // Build the search directories.
      std::vector<std::string> searchDirs;
      if (isSystem) {
        searchDirs = systemIncludePaths;
      } else {
        // For quoted includes, first add the directory of the current file.
        fs::path currentDir = fs::path(currentFile).parent_path();
        if (!currentDir.empty())
          searchDirs.push_back(currentDir.string());
        // Then add all user-specified directories.
        for (const auto &dir : userIncludePaths)
          searchDirs.push_back(dir);
      }
      // Also add the top-level directory (if set) as a fallback.
      if (!topLevelDir.empty())
        searchDirs.push_back(topLevelDir);
      // Finally, add the current working directory.
      std::string cwd = fs::current_path().string();
      searchDirs.push_back(cwd);

      // Add LLVM's resource directory if LLVM_RESOURCE_DIR is defined.
#ifdef LLVM_RESOURCE_DIR
      std::string resourceDir = LLVM_RESOURCE_DIR;
#else
      std::string resourceDir = "";
#endif
      if (!resourceDir.empty())
        searchDirs.push_back(resourceDir);

      // Look for the header in the search directories.
      std::optional<std::string> headerPath;
      for (const auto &dir : searchDirs) {
        fs::path trial = fs::path(dir) / headerName;
        if (fs::exists(trial) && fs::is_regular_file(trial)) {
          headerPath = fs::absolute(trial).string();
          break;
        }
      }
      if (!headerPath.has_value()) {
        std::clog << "[WARNING] Preprocessor Warning: Cannot locate header: "
                  << headerName << ". Skipping include.\n";
        oss << "// Skipped missing include: " << headerName << "\n";
        continue;
      }

      // For system headers, run the external (Clang) preprocessor.
      if (isSystem) {
        std::string headerContents =
            runExternalPreprocessor(headerPath.value());
        oss << headerContents << "\n";
      } else {
        // For user headers, process them using our own preprocessor.
        std::string headerContents = processFile(headerPath.value());
        oss << headerContents << "\n";
      }
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
  return expander.expand(withoutDirectives.str());
}

std::string Preprocessor::processFile(const std::string &path) {
  // Check cache first.
  if (fileCache.find(path) != fileCache.end())
    return fileCache[path];

  std::string source = readFile(path);
  // Process includes, then conditionals, then macros.
  std::string included = processIncludes(source, path);
  std::string conditioned = processConditionals(included);
  std::string expanded = processMacros(conditioned);

  fileCache[path] = expanded;
  return expanded;
}

std::string Preprocessor::preprocess(const std::string &topLevelPath) {
  // Set the top-level directory from the top-level source file.
  fs::path topDir = fs::path(topLevelPath).parent_path();
  if (!topDir.empty())
    topLevelDir = topDir.string();
  else
    topLevelDir = "";
  return processFile(topLevelPath);
}
