#ifndef MACRO_EXPANDER_HPP
#define MACRO_EXPANDER_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "Token.hpp"  // Assumes Token.hpp defines Token and TokenType

// Structure representing a macro definition.
struct Macro {
    bool isFunctionLike;               // true if the macro is function-like
    bool isVariadic;                   // true if the macro is variadic (has "..." in parameters)
    std::vector<std::string> parameters; // List of parameter names (for variadic macros, the last is "__VA_ARGS__")
    std::string replacement;           // The replacement text (as written in the macro definition)
};

class MacroExpander {
public:
    MacroExpander();

    // Process a macro directive line (e.g. "#define ..." or "#undef ...").
    void processDirective(const std::string &line);

    // Fully expand macros in the given source text.
    std::string expand(const std::string &source);

    // Set the current file name for built-in macro expansion (__FILE__).
    void setCurrentFile(const std::string &fileName);

private:
    // Recursively expand macros in the source text.
    // 'disabled' holds macro names that are currently disabled (to prevent recursive re-expansion).
    std::string expandTokens(const std::string &source, const std::unordered_map<std::string, bool>& disabled);

    // Expand a function-like macro using its arguments.
    std::string expandFunctionMacro(const Macro &macro,
                                    const std::vector<std::vector<Token>> &args,
                                    const std::unordered_map<std::string, bool>& disabled);

    // Convert a sequence of tokens into a string literal (for stringification).
    std::string stringifyArgument(const std::vector<Token>& tokens);

    // Concatenate (paste) two token lexemes.
    std::string pasteTokens(const std::string &left, const std::string &right);

    // The macro table.
    std::unordered_map<std::string, Macro> macros;

    // Built-in macro state.
    std::string currentFile; // For __FILE__ replacement.
};

#endif // MACRO_EXPANDER_HPP
