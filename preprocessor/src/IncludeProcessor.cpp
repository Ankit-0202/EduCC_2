#include "IncludeProcessor.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace fs = std::filesystem;

IncludeProcessor::IncludeProcessor(const std::vector<std::string> &systemPaths,
                                   const std::vector<std::string> &userPaths)
    : m_systemPaths(systemPaths), m_userPaths(userPaths) {
  // If an LLVM resource directory is defined, add it to system paths.
  if (const char *resDir = std::getenv("LLVM_RESOURCE_DIR"))
    m_systemPaths.push_back(resDir);
}

std::optional<std::string>
IncludeProcessor::locateHeader(const std::string &filename, bool isSystem) {
  std::vector<std::string> searchDirs;
  if (isSystem) {
    searchDirs = m_systemPaths;
  } else {
    searchDirs = m_userPaths;
  }
  for (const auto &dir : searchDirs) {
    fs::path trial = fs::path(dir) / filename;
    if (fs::exists(trial) && fs::is_regular_file(trial)) {
      return fs::absolute(trial).string();
    }
  }
  return std::nullopt;
}

std::string IncludeProcessor::readFile(const std::string &path) {
  std::ifstream in(path);
  if (!in.is_open()) {
    throw std::runtime_error("IncludeProcessor Error: Unable to open file: " +
                             path);
  }
  std::stringstream buffer;
  buffer << in.rdbuf();
  return buffer.str();
}
