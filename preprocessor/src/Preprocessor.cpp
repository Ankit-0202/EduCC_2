#include "Preprocessor.hpp"
#include "IncludeProcessor.hpp"
#include "MacroExpander.hpp"
#include "ConditionalProcessor.hpp"
#include <stdexcept>
#include <sstream>
#include <unordered_map>
#include <filesystem>
#include <fstream>  // Added to provide std::ifstream

namespace fs = std::filesystem;

Preprocessor::Preprocessor(const std::vector<std::string>& sysPaths,
                           const std::vector<std::string>& userPaths)
    : systemIncludePaths(sysPaths), userIncludePaths(userPaths) {
    // (You might store these for use in IncludeProcessor in a more advanced design.)
}

std::string Preprocessor::readFile(const std::string &path) {
    std::ifstream in(path);
    if (!in.is_open())
        throw std::runtime_error("Preprocessor Error: Unable to open file: " + path);
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

std::string Preprocessor::processIncludes(const std::string &source, const std::string &currentFile) {
    // Very basic implementation: scan each line; if it starts with "#include",
    // locate the header and recursively process it.
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
            if (start == std::string::npos || end == std::string::npos || end <= start)
                throw std::runtime_error("Preprocessor Error: Malformed #include directive: " + line);
            std::string headerName = trimmed.substr(start + 1, end - start - 1);
            bool isSystem = (trimmed[start] == '<');
            // Use the IncludeProcessor to locate and read the header.
            auto headerPathOpt = includeProcessor.locateHeader(headerName, isSystem);
            if (!headerPathOpt.has_value())
                throw std::runtime_error("Preprocessor Error: Cannot locate header: " + headerName);
            std::string headerContents = processFile(headerPathOpt.value());
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
    // First, run through the source to let the expander process all macro directives.
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
