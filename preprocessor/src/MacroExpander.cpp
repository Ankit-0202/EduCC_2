#include "MacroExpander.hpp"
#include <sstream>
#include <regex>
#include <stdexcept>
#include <cctype>

// Helper: trim whitespace from both ends.
static std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

MacroExpander::MacroExpander() {
    // Initially empty.
}

void MacroExpander::processDirective(const std::string &line) {
    std::string trimmed = trim(line);
    if (trimmed.compare(0, 7, "#define") == 0) {
        std::string rest = trim(trimmed.substr(7));
        // Extract the macro name.
        size_t nameEnd = rest.find_first_of(" \t(");
        if (nameEnd == std::string::npos)
            throw std::runtime_error("Invalid macro definition: " + line);
        std::string macroName = rest.substr(0, nameEnd);
        rest = trim(rest.substr(nameEnd));

        Macro macro;
        if (!rest.empty() && rest[0] == '(') {
            // Function-like macro.
            macro.isFunctionLike = true;
            size_t closingParen = rest.find(')');
            if (closingParen == std::string::npos)
                throw std::runtime_error("Missing ')' in macro definition: " + line);
            std::string paramsStr = rest.substr(1, closingParen - 1);
            // Split parameters by comma.
            std::istringstream iss(paramsStr);
            std::string param;
            while (std::getline(iss, param, ',')) {
                macro.parameters.push_back(trim(param));
            }
            rest = trim(rest.substr(closingParen + 1));
        } else {
            macro.isFunctionLike = false;
        }
        macro.replacement = rest;
        macros[macroName] = macro;
    } else if (trimmed.compare(0, 6, "#undef") == 0) {
        std::string macroName = trim(trimmed.substr(6));
        macros.erase(macroName);
    }
    // (Additional directives such as #ifdef/#if etc. could be handled here.)
}

std::vector<std::string> MacroExpander::splitArguments(const std::string &argString) {
    // Very naive splitting on commas; a full solution would need to handle nested parentheses.
    std::vector<std::string> args;
    std::istringstream iss(argString);
    std::string arg;
    while (std::getline(iss, arg, ',')) {
        args.push_back(trim(arg));
    }
    return args;
}

std::string MacroExpander::expandLine(const std::string &line) {
    std::string result = line;
    // First, replace object-like macros.
    for (const auto &kv : macros) {
        const std::string &name = kv.first;
        const Macro &macro = kv.second;
        if (!macro.isFunctionLike) {
            // Use word boundaries.
            std::regex word("\\b" + name + "\\b");
            result = std::regex_replace(result, word, macro.replacement);
        }
    }
    // Now, handle function-like macros.
    // (This implementation is naïve and does not handle nested calls or complex argument parsing.)
    for (const auto &kv : macros) {
        const std::string &name = kv.first;
        const Macro &macro = kv.second;
        if (macro.isFunctionLike) {
            std::regex funcRegex("\\b" + name + "\\s*\\(([^)]*)\\)");
            std::smatch match;
            while (std::regex_search(result, match, funcRegex)) {
                std::string argsStr = match[1].str();
                std::vector<std::string> args = splitArguments(argsStr);
                if (args.size() != macro.parameters.size()) {
                    throw std::runtime_error("Macro " + name + " expects " +
                                             std::to_string(macro.parameters.size()) +
                                             " arguments, but got " +
                                             std::to_string(args.size()));
                }
                std::string expanded = macro.replacement;
                // For each parameter, substitute its occurrence.
                for (size_t i = 0; i < macro.parameters.size(); ++i) {
                    std::regex paramRegex("\\b" + macro.parameters[i] + "\\b");
                    expanded = std::regex_replace(expanded, paramRegex, args[i]);
                }
                result.replace(match.position(0), match.length(0), expanded);
            }
        }
    }
    return result;
}

std::string MacroExpander::expand(const std::string &source) {
    std::istringstream iss(source);
    std::ostringstream oss;
    std::string line;
    while (std::getline(iss, line)) {
        // For now, assume that any macro directives (e.g. "#define") have been processed
        oss << expandLine(line) << "\n";
    }
    return oss.str();
}
