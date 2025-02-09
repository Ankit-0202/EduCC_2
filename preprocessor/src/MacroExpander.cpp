#include "MacroExpander.hpp"
#include "Lexer.hpp"
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

// Helper: join a vector of tokens into a string (tokens separated by a space),
// but skip tokens with type EOF_TOKEN.
static std::string tokensToString(const std::vector<Token>& tokens) {
    std::ostringstream oss;
    for (const auto &tok : tokens) {
        if (tok.type == TokenType::EOF_TOKEN)
            continue;
        oss << tok.lexeme << " ";
    }
    return oss.str();
}

MacroExpander::MacroExpander() {
    // Initially empty.
}

void MacroExpander::processDirective(const std::string &line) {
    std::string trimmed = trim(line);
    if (trimmed.compare(0, 7, "#define") == 0) {
        std::string rest = trim(trimmed.substr(7));
        // Extract macro name.
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
            // Split parameters by commas.
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
}

//
// expandTokens: Token–based recursive macro expansion.
//
std::string MacroExpander::expandTokens(const std::string &source) {
    Lexer lexer(source);
    std::vector<Token> tokens = lexer.tokenize();
    // Remove the EOF token.
    if (!tokens.empty() && tokens.back().type == TokenType::EOF_TOKEN)
        tokens.pop_back();
    std::vector<Token> output;

    for (size_t i = 0; i < tokens.size(); ++i) {
        Token token = tokens[i];
        if (token.type == TokenType::IDENTIFIER && macros.find(token.lexeme) != macros.end()) {
            const Macro &macro = macros[token.lexeme];
            if (macro.isFunctionLike) {
                // Function-like macro must be followed by '('.
                if (i + 1 < tokens.size() && tokens[i+1].type == TokenType::DELIM_LPAREN) {
                    size_t j = i + 1; // j points to '('
                    int parenLevel = 0;
                    std::vector<std::vector<Token>> argsTokens;
                    std::vector<Token> currentArg;
                    bool finished = false;
                    for (; j < tokens.size(); ++j) {
                        if (tokens[j].type == TokenType::DELIM_LPAREN) {
                            parenLevel++;
                            // Do not add the very first '(' to arguments.
                            if (parenLevel > 1)
                                currentArg.push_back(tokens[j]);
                        } else if (tokens[j].type == TokenType::DELIM_RPAREN) {
                            parenLevel--;
                            if (parenLevel == 0) {
                                if (!currentArg.empty())
                                    argsTokens.push_back(currentArg);
                                finished = true;
                                break;
                            } else {
                                currentArg.push_back(tokens[j]);
                            }
                        } else if (tokens[j].type == TokenType::DELIM_COMMA && parenLevel == 1) {
                            argsTokens.push_back(currentArg);
                            currentArg.clear();
                        } else {
                            currentArg.push_back(tokens[j]);
                        }
                    }
                    if (!finished)
                        throw std::runtime_error("Unmatched '(' in macro invocation for macro " + token.lexeme);
                    if (argsTokens.size() != macro.parameters.size())
                        throw std::runtime_error("Macro " + token.lexeme + " expects " +
                            std::to_string(macro.parameters.size()) + " arguments, but got " +
                            std::to_string(argsTokens.size()));
                    // Convert each argument token vector to a string.
                    std::vector<std::string> argStrings;
                    for (const auto &argVec : argsTokens)
                        argStrings.push_back(tokensToString(argVec));
                    // Perform parameter substitution.
                    std::string expansion = macro.replacement;
                    for (size_t k = 0; k < macro.parameters.size(); ++k) {
                        std::regex paramRe("\\b" + macro.parameters[k] + "\\b", std::regex_constants::ECMAScript);
                        expansion = std::regex_replace(expansion, paramRe, argStrings[k]);
                    }
                    // Recursively expand the result.
                    std::string expandedText = expandTokens(expansion);
                    // Tokenize the expanded text and append its tokens.
                    Lexer newLexer(expandedText);
                    std::vector<Token> newTokens = newLexer.tokenize();
                    if (!newTokens.empty() && newTokens.back().type == TokenType::EOF_TOKEN)
                        newTokens.pop_back();
                    output.insert(output.end(), newTokens.begin(), newTokens.end());
                    i = j; // Skip over macro invocation tokens.
                    continue;
                } else {
                    // If not followed by '(', leave token unchanged.
                    output.push_back(token);
                }
            } else {
                // Object-like macro: expand replacement text recursively.
                std::string expansion = macro.replacement;
                std::string expandedText = expandTokens(expansion);
                Lexer newLexer(expandedText);
                std::vector<Token> newTokens = newLexer.tokenize();
                if (!newTokens.empty() && newTokens.back().type == TokenType::EOF_TOKEN)
                    newTokens.pop_back();
                output.insert(output.end(), newTokens.begin(), newTokens.end());
            }
        } else {
            // Not a macro invocation; copy token.
            output.push_back(token);
        }
    }
    return tokensToString(output);
}

std::string MacroExpander::expand(const std::string &source) {
    return expandTokens(source);
}
