#ifndef MACRO_EXPANDER_HPP
#define MACRO_EXPANDER_HPP

#include <string>
#include <unordered_map>
#include <vector>

// Represents a macro definition.
struct Macro {
    bool isFunctionLike;
    std::vector<std::string> parameters; // Only used if function-like.
    std::string replacement;
};

class MacroExpander {
public:
    MacroExpander();

    // Process a directive line (e.g. "#define ..." or "#undef ...")
    void processDirective(const std::string &line);

    // Expand macros in the given source text.
    std::string expand(const std::string &source);

private:
    std::unordered_map<std::string, Macro> macros;

    // Expand macros in a single line.
    std::string expandLine(const std::string &line);

    // Helper functions for function‐like macro expansion.
    std::vector<std::string> splitArguments(const std::string &argString);
};

#endif // MACRO_EXPANDER_HPP
