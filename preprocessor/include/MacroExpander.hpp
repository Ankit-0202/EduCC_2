#ifndef MACRO_EXPANDER_HPP
#define MACRO_EXPANDER_HPP

#include <string>
#include <unordered_map>
#include <vector>

// Structure to hold a macro’s information.
struct Macro {
    bool isFunctionLike;
    std::vector<std::string> parameters;
    std::string replacement;
};

class MacroExpander {
public:
    MacroExpander();

    // Process a preprocessor directive (e.g. "#define SQUARE(x) ((x)*(x))" or "#undef ...")
    void processDirective(const std::string &line);

    // Expand macros in the given source text.
    std::string expand(const std::string &source);

private:
    // Token–based helper: recursively expand macros in source text.
    std::string expandTokens(const std::string &source);

    std::unordered_map<std::string, Macro> macros;
};

#endif // MACRO_EXPANDER_HPP
