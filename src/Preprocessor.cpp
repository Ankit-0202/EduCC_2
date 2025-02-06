#include "Preprocessor.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

//--------------------------//
//  IncludeGuardManager    //
//--------------------------//

void IncludeGuardManager::onIfndef(const std::string& macro) {
    // Start tracking that we encountered #ifndef SOME_MACRO
    pendingIfndefMacro = macro;
    haveMatchedDefine = false;
}

void IncludeGuardManager::onDefine(const std::string& macro) {
    // If the macro matches the pending #ifndef, we consider it matched.
    if (pendingIfndefMacro.has_value() && pendingIfndefMacro.value() == macro) {
        haveMatchedDefine = true;
    }
}

void IncludeGuardManager::onEndif() {
    // If we had #ifndef X and #define X properly matched, we consider the file guarded.
    // We'll let the Preprocessor mark that at the end of processing the file.
}

void IncludeGuardManager::onPragmaOnce(const std::string& filename) {
    onceFiles.insert(filename);
}

bool IncludeGuardManager::isCurrentFileGuarded(const std::string& filename) {
    // If #pragma once was used for the file, it's definitely guarded:
    if (onceFiles.find(filename) != onceFiles.end()) {
        return true;
    }
    // If there's a pending #ifndef that was matched with #define, that suggests a valid guard.
    if (pendingIfndefMacro.has_value() && haveMatchedDefine) {
        return true;
    }
    return false;
}

bool IncludeGuardManager::isInsideActiveGuardBlock() const {
    // True if #ifndef and #define have matched so far (i.e. the file is effectively ignoring re-includes).
    return (pendingIfndefMacro.has_value() && haveMatchedDefine);
}

void IncludeGuardManager::reset() {
    pendingIfndefMacro.reset();
    haveMatchedDefine = false;
    // We do not clear onceFiles globally here because #pragma once is typically tied to each file’s manager usage.
    // In this simplified approach, we re-create the guard manager for each file pass if desired.
}

//--------------------------//
//      Preprocessor        //
//--------------------------//

Preprocessor::Preprocessor(const std::vector<std::string>& systemIncludePaths,
                           const std::vector<std::string>& userIncludePaths)
    : systemIncludePaths(systemIncludePaths),
      userIncludePaths(userIncludePaths)
{
}

std::string Preprocessor::preprocess(const std::string& topLevelPath) {
    fileCache.clear();
    fullyGuardedFiles.clear();

    // Expand the top-level file, which triggers recursion for all includes.
    std::string result = expandFile(topLevelPath);

    // Return the final, expanded code.
    return result;
}

std::optional<std::string> Preprocessor::locateHeader(const std::string& filename, bool isSystem) {
    // If isSystem is true, we search systemIncludePaths first; otherwise userIncludePaths first.
    // (We do the "fallback" logic separately in handleIncludeDirective so we can handle local dirs properly.)
    const auto& searchDirs = (isSystem ? systemIncludePaths : userIncludePaths);

    for (const auto& dir : searchDirs) {
        fs::path trial = fs::path(dir) / filename;
        if (fs::exists(trial) && fs::is_regular_file(trial)) {
            // Return absolute path
            return fs::absolute(trial).string();
        }
    }
    return std::nullopt;
}

std::string Preprocessor::expandFile(const std::string& path) {
    // Convert path to absolute form
    std::string absPath = fs::absolute(path).string();

    // If we've already expanded this file, return from cache.
    auto it = fileCache.find(absPath);
    if (it != fileCache.end()) {
        return it->second;
    }

    // Check for circular includes (if already on our includeStack).
    {
        std::stack<std::string> tempStack = includeStack;
        while (!tempStack.empty()) {
            if (tempStack.top() == absPath) {
                throw std::runtime_error("Preprocessor Error: Circular include detected for file: " + absPath);
            }
            tempStack.pop();
        }
    }

    // Check if we've previously concluded that file is fully guarded (already included once).
    if (fullyGuardedFiles.find(absPath) != fullyGuardedFiles.end()) {
        // This file is effectively a no-op on subsequent includes.
        fileCache[absPath] = "";
        return "";
    }

    // Mark that we are now expanding this file
    includeStack.push(absPath);

    // Reset guard manager for this file
    guardManager.reset();

    // Read raw content
    std::string content = readFile(absPath);

    // Process the file lines
    std::string expanded = processFileContent(absPath, content);

    // Check if file turned out to be fully guarded
    if (guardManager.isCurrentFileGuarded(absPath)) {
        fullyGuardedFiles.insert(absPath);
    }

    // Cache the result
    fileCache[absPath] = expanded;

    // Done expanding
    includeStack.pop();

    return expanded;
}

std::string Preprocessor::processFileContent(const std::string& path, const std::string& content) {
    std::stringstream in(content);
    std::stringstream out;

    std::string line;
    while (std::getline(in, line)) {
        // Trim leading whitespace
        auto firstNonSpace = std::find_if_not(line.begin(), line.end(), ::isspace);
        if (firstNonSpace == line.end()) {
            // It's an empty/whitespace-only line
            out << line << "\n";
            continue;
        }

        // If line starts with '#', we might have directives
        if (*firstNonSpace == '#') {
            std::string directive = line.substr(std::distance(line.begin(), firstNonSpace));

            // #include
            if (directive.rfind("#include", 0) == 0) {
                out << handleIncludeDirective(directive, path);
                continue;
            }
            // #ifndef
            else if (directive.rfind("#ifndef", 0) == 0) {
                std::string macro = directive.substr(7); // skip "#ifndef"
                // remove leading/trailing spaces
                while (!macro.empty() && isspace((unsigned char)macro.front())) macro.erase(macro.begin());
                while (!macro.empty() && isspace((unsigned char)macro.back())) macro.pop_back();
                guardManager.onIfndef(macro);
                // We don't copy the directive text into final expansion.
                continue;
            }
            // #define
            else if (directive.rfind("#define", 0) == 0) {
                std::string macro = directive.substr(7); // skip "#define"
                while (!macro.empty() && isspace((unsigned char)macro.front())) macro.erase(macro.begin());
                while (!macro.empty() && isspace((unsigned char)macro.back())) macro.pop_back();
                guardManager.onDefine(macro);
                continue;
            }
            // #endif
            else if (directive.rfind("#endif", 0) == 0) {
                guardManager.onEndif();
                continue;
            }
            // #pragma once
            else if (directive.rfind("#pragma once", 0) == 0) {
                guardManager.onPragmaOnce(path);
                continue;
            }
            else {
                // Some other directive (e.g. #undef, #if, #else, etc.).
                // We'll just pass it along unmodified:
                out << line << "\n";
                continue;
            }
        } else {
            // Normal code line
            out << line << "\n";
        }
    }

    return out.str();
}

std::string Preprocessor::readFile(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        throw std::runtime_error("Preprocessor Error: Unable to open file: " + path);
    }
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

std::string Preprocessor::handleIncludeDirective(const std::string& directiveLine, const std::string& currentFile) {
    // Remove "#include"
    std::string afterInclude = directiveLine.substr(8);
    while (!afterInclude.empty() && isspace((unsigned char)afterInclude.front())) {
        afterInclude.erase(afterInclude.begin());
    }

    // Distinguish between <...> (system) and "..." (local)
    if (!afterInclude.empty() && afterInclude.front() == '<') {
        // System include
        auto endPos = afterInclude.find('>');
        if (endPos == std::string::npos) {
            throw std::runtime_error("Preprocessor Error: Malformed #include (missing '>'): " + directiveLine);
        }
        std::string headerName = afterInclude.substr(1, endPos - 1);
        // Trim spaces
        while (!headerName.empty() && isspace((unsigned char)headerName.front())) headerName.erase(headerName.begin());
        while (!headerName.empty() && isspace((unsigned char)headerName.back())) headerName.pop_back();

        // 1) Search system include paths
        auto pathOpt = locateHeader(headerName, true);
        if (!pathOpt.has_value()) {
            // 2) Fallback to user include paths
            pathOpt = locateHeader(headerName, false);
            if (!pathOpt.has_value()) {
                throw std::runtime_error("Preprocessor Error: Cannot find system header '" + headerName + "'");
            }
        }
        return expandFile(pathOpt.value());
    }
    else if (!afterInclude.empty() && afterInclude.front() == '"') {
        // User/local include
        auto endPos = afterInclude.find('"', 1);
        if (endPos == std::string::npos) {
            throw std::runtime_error("Preprocessor Error: Malformed #include (missing closing quote): " + directiveLine);
        }
        std::string headerName = afterInclude.substr(1, endPos - 1);

        // ---- Replicate typical GCC logic for #include "file.h" ----
        // 1) Search the directory of the file that issued this include.
        fs::path includingPath = fs::absolute(currentFile);
        fs::path includingDir  = includingPath.parent_path();
        fs::path trialLocal    = includingDir / headerName;
        if (fs::exists(trialLocal) && fs::is_regular_file(trialLocal)) {
            return expandFile(fs::absolute(trialLocal).string());
        }

        // 2) Next, search userIncludePaths
        auto pathOpt = locateHeader(headerName, false);
        if (!pathOpt.has_value()) {
            // 3) Finally, fallback to system paths
            pathOpt = locateHeader(headerName, true);
            if (!pathOpt.has_value()) {
                throw std::runtime_error("Preprocessor Error: Cannot find header '" + headerName + "'");
            }
        }
        return expandFile(pathOpt.value());
    }
    else {
        throw std::runtime_error("Preprocessor Error: Malformed #include directive: " + directiveLine);
    }
}
