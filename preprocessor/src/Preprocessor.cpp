#include "Preprocessor.hpp"
#include "ConditionalProcessor.hpp"
#include "IncludeProcessor.hpp"
#include "MacroExpander.hpp"
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream> // Added to provide std::ifstream
#include <iostream>
#include <llvm/ADT/SmallVector.h>
#include <llvm/Support/Program.h>
#include <optional>
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
      size_t start = trimmed.find_first_of("\"<");
      size_t end = trimmed.find_last_of("\">");
      if (start == std::string::npos || end == std::string::npos ||
          end <= start)
        throw std::runtime_error(
            "Preprocessor Error: Malformed #include directive: " + line);
      std::string headerName = trimmed.substr(start + 1, end - start - 1);
      bool isSystem = (trimmed[start] == '<');

      // For system headers, skip expansion to avoid pulling in complex
      // platform headers that the teaching parser cannot handle. External
      // calls will be resolved at link time.
      if (isSystem) {
        oss << "/* skipped system header: " << headerName << " */\n";
        continue;
      }

      std::vector<std::string> searchDirs;
      auto addSearchDir = [&searchDirs](const std::string &dir) {
        if (dir.empty())
          return;
        if (std::find(searchDirs.begin(), searchDirs.end(), dir) ==
            searchDirs.end()) {
          searchDirs.push_back(dir);
        }
      };

      fs::path currentDir = fs::path(currentFile).parent_path();
      if (!currentDir.empty())
        addSearchDir(currentDir.string());

      for (const auto &dir : userIncludePaths)
        addSearchDir(dir);

      for (const auto &dir : systemIncludePaths)
        addSearchDir(dir);

      addSearchDir(".");

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
  try {
    expander = MacroExpander();
    fileCache.clear();
    return processFile(topLevelPath);
  } catch (const std::exception &ex) {
    std::cerr << "[INFO] Preprocessor fallback to system clang: " << ex.what()
              << "\n";
    return preprocessWithSystemClang(topLevelPath);
  }
}

std::string
Preprocessor::preprocessWithSystemClang(const std::string &topLevelPath) const {
  auto clangPathOrErr = llvm::sys::findProgramByName("clang");
  if (!clangPathOrErr) {
    throw std::runtime_error(
        "Preprocessor Error: Unable to locate system 'clang' executable.");
  }
  std::string clangPath = *clangPathOrErr;

  auto timestamp = std::chrono::steady_clock::now().time_since_epoch().count();
  fs::path outputPath =
      fs::temp_directory_path() /
      ("educc-preprocessed-" + std::to_string(timestamp) + ".i");

  std::vector<std::string> args;
  args.push_back(clangPath);
  args.push_back("-E");
  args.push_back("-P");
  args.push_back("-x");
  args.push_back("c");

  for (const auto &userDir : userIncludePaths) {
    if (!userDir.empty())
      args.push_back("-I" + userDir);
  }
  for (const auto &sysDir : systemIncludePaths) {
    if (!sysDir.empty())
      args.push_back("-isystem" + sysDir);
  }

  args.push_back(topLevelPath);
  args.push_back("-o");
  args.push_back(outputPath.string());

  llvm::SmallVector<llvm::StringRef, 16> llvmArgs;
  llvmArgs.reserve(args.size());
  for (const auto &arg : args) {
    llvmArgs.push_back(arg);
  }

  int result = llvm::sys::ExecuteAndWait(clangPath, llvmArgs);
  if (result != 0) {
    throw std::runtime_error(
        "Preprocessor Error: 'clang -E' failed with exit code " +
        std::to_string(result));
  }

  std::ifstream in(outputPath);
  if (!in.is_open()) {
    throw std::runtime_error("Preprocessor Error: Unable to read system "
                             "preprocessor output at " +
                             outputPath.string());
  }
  std::stringstream buffer;
  buffer << in.rdbuf();
  in.close();

  std::error_code ec;
  fs::remove(outputPath, ec);

  return buffer.str();
}
