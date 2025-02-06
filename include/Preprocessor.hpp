#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <optional>

/*
 * IncludeGuardManager tracks header guards:
 *  - #ifndef X / #define X / #endif
 *  - #pragma once
 * 
 * This helps detect when a file is "guarded" so that repeated includes
 * can be skipped. It also helps detect circular includes that lack guards.
 */
class IncludeGuardManager {
public:
    // Called when we parse a line with "#ifndef GUARD_MACRO"
    void onIfndef(const std::string& macro);

    // Called when we parse a line with "#define GUARD_MACRO"
    void onDefine(const std::string& macro);

    // Called when we parse a line with "#endif"
    void onEndif();

    // Called when we parse a line with "#pragma once"
    void onPragmaOnce(const std::string& filename);

    // Checks if the current file is definitely guarded (i.e. #ifndef / #define / #endif or #pragma once).
    bool isCurrentFileGuarded(const std::string& filename);

    // Returns whether we have encountered a #define that matches the #ifndef
    // from earlier in the file. If so, we treat the file as guarded.
    bool isInsideActiveGuardBlock() const;

    // Clear all internal state (used when we finish processing one file).
    void reset();

private:
    // For #ifndef / #define tracking
    // We track macros that appear in #ifndef lines, and see if they've also been #define’d.
    std::optional<std::string> pendingIfndefMacro;
    bool haveMatchedDefine = false;

    // For #pragma once tracking
    std::unordered_set<std::string> onceFiles;
};

/*
 * Preprocessor class:
 *  - Takes an entrypoint .c file (or a header).
 *  - Scans line by line looking for #include, #ifndef, #define, #endif, #pragma once, etc.
 *  - Recursively processes included headers.
 *  - Uses search paths: system (for #include <...>) and user (for #include "...")
 *  - Tracks visited files to detect circular includes.
 *  - Uses IncludeGuardManager to detect & skip repeated includes of guarded files.
 *  - Finally, produces a single combined source (as a string) that can be fed to the Lexer.
 */
class Preprocessor {
public:
    // Provide lists of system include directories, plus (optionally) a directory for the "local" file context.
    // e.g. systemIncludePaths = { "/usr/include", "/usr/local/include", ... };
    // userIncludePaths   = { "." } (the directory of the main .c file, or any project-specific includes).
    Preprocessor(const std::vector<std::string>& systemIncludePaths,
                 const std::vector<std::string>& userIncludePaths);

    // Preprocess the file at topLevelPath, returning the final combined source code.
    // Throws std::runtime_error if there's an error (missing file, circular include, etc.).
    std::string preprocess(const std::string& topLevelPath);

private:
    // The content of system include directories vs user include directories.
    std::vector<std::string> systemIncludePaths;
    std::vector<std::string> userIncludePaths;

    // A stack to track which files we are *currently* expanding (to detect circular includes).
    std::stack<std::string> includeStack;

    // A map from absolute-file-path -> the already expanded text of that file (cached).
    // Once we expand a file fully, we store it here so we don't do the same work again.
    std::unordered_map<std::string, std::string> fileCache;

    // Keep track of files that are known to be "guarded" by #ifndef / #define or #pragma once
    // so we can skip re-including them. This is separate from the final expansions in fileCache,
    // because a file might not be fully processed if we detect it’s guarded early.
    std::unordered_set<std::string> fullyGuardedFiles;

    // Utility to locate a header file, given name and angle-bracket vs. quote style
    std::optional<std::string> locateHeader(const std::string& filename, bool isSystem);

    // Actually do the expansion of an individual file, returning the expanded text.
    // If already in cache, returns from fileCache.
    // If encountering circular dependency, throws std::runtime_error.
    std::string expandFile(const std::string& path);

    // Parse lines from the raw file content; handle #include, #ifndef, #define, #endif, #pragma once, etc.
    // Return combined text with includes replaced recursively by expanded content.
    std::string processFileContent(const std::string& path, const std::string& content);

    // Read the entire file from disk into a string. Throws on error.
    std::string readFile(const std::string& path);

    // Called whenever we see a #include line. We recursively expand that header.
    // Returns the expanded content of that included file (or empty string if it’s guarded and already included).
    std::string handleIncludeDirective(const std::string& directiveLine, const std::string& currentFile);

    // We maintain a separate IncludeGuardManager for each file as we parse it from top to bottom.
    // Once we're done with that file, we see if it was fully guarded. If yes, we record that in fullyGuardedFiles.
    IncludeGuardManager guardManager;
};

#endif // PREPROCESSOR_HPP
