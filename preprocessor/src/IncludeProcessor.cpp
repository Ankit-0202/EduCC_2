#include "IncludeProcessor.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;

std::optional<std::string> IncludeProcessor::locateHeader(const std::string &filename, bool isSystem) {
    // For simplicity, we search in a fixed set of directories.
    // In a full implementation, these would be configurable.
    std::vector<std::string> searchDirs;
    if (isSystem) {
        searchDirs = {"/usr/include", "/usr/local/include"};
    } else {
        searchDirs = {"."};
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
        throw std::runtime_error("IncludeProcessor Error: Unable to open file: " + path);
    }
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}
