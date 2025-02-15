#include "MacroExpander.hpp"
#include "Lexer.hpp"
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <iostream>  // For debug logging

// Helper: trim whitespace from both ends.
static std::string trim(const std::string &s) {
  size_t start = s.find_first_not_of(" \t");
  size_t end = s.find_last_not_of(" \t");
  return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

// Helper: join a vector of tokens into a string (tokens separated by a space),
// but skip tokens with type EOF_TOKEN.
static std::string tokensToString(const std::vector<Token> &tokens) {
  std::ostringstream oss;
  for (const auto &tok : tokens) {
    if (tok.type == TokenType::EOF_TOKEN)
      continue;
    oss << tok.lexeme << " ";
  }
  return oss.str();
}

// Helper: replace all occurrences of 'param' in 'input' with 'arg'
// but only when 'param' appears as a separate token.
static std::string replaceParameter(const std::string &input,
                                    const std::string &param,
                                    const std::string &arg) {
  std::string output;
  size_t pos = 0;
  while (true) {
    size_t found = input.find(param, pos);
    if (found == std::string::npos) {
      output.append(input, pos, std::string::npos);
      break;
    }
    // Check left boundary.
    bool leftOk = (found == 0) ||
                  (!std::isalnum(input[found - 1]) && input[found - 1] != '_');
    // Check right boundary.
    bool rightOk = (found + param.size() >= input.size()) ||
                   (!std::isalnum(input[found + param.size()]) &&
                    input[found + param.size()] != '_');
    if (leftOk && rightOk) {
      output.append(input, pos, found - pos);
      output.append(arg);
      pos = found + param.size();
    } else {
      output.append(input, pos, found - pos + 1);
      pos = found + 1;
    }
  }
  return output;
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
    std::string macroName;
    if (nameEnd == std::string::npos) {
      // No whitespace or '(' found after the name:
      // treat the entire rest as the macro name and use an empty replacement.
      macroName = rest;
      rest = "";
    } else {
      macroName = rest.substr(0, nameEnd);
      rest = trim(rest.substr(nameEnd));
    }
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
    // Debug log
    std::cerr << "[DEBUG] Defined macro: " << macroName;
    if (macro.isFunctionLike) {
      std::cerr << " (function-like, params: ";
      for (const auto &p : macro.parameters)
        std::cerr << p << " ";
      std::cerr << ")";
    }
    std::cerr << " => '" << macro.replacement << "'\n";
  } else if (trimmed.compare(0, 6, "#undef") == 0) {
    std::string macroName = trim(trimmed.substr(6));
    macros.erase(macroName);
    std::cerr << "[DEBUG] Undefining macro: " << macroName << "\n";
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
    // If token is an identifier and matches a defined macro…
    if (token.type == TokenType::IDENTIFIER && macros.find(token.lexeme) != macros.end()) {
      const Macro &macro = macros[token.lexeme];
      // For function-like macros, relax the requirement:
      // Look ahead for a '(' token even if not immediately adjacent.
      size_t lookahead = i + 1;
      while (lookahead < tokens.size() && tokens[lookahead].type == TokenType::UNKNOWN)
        ++lookahead;
      if (macro.isFunctionLike && lookahead < tokens.size() &&
          tokens[lookahead].type == TokenType::DELIM_LPAREN) {
        std::cerr << "[DEBUG] Expanding function-like macro: " << token.lexeme
                  << " at line " << token.line << "\n";
        size_t j = lookahead; // j points to '('
        int parenLevel = 0;
        std::vector<std::vector<Token>> argsTokens;
        std::vector<Token> currentArg;
        bool finished = false;
        for (; j < tokens.size(); ++j) {
          if (tokens[j].type == TokenType::DELIM_LPAREN) {
            parenLevel++;
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
          throw std::runtime_error(
              "Unmatched '(' in macro invocation for macro " + token.lexeme);
        if (argsTokens.size() != macro.parameters.size())
          throw std::runtime_error("Macro " + token.lexeme + " expects " +
                                   std::to_string(macro.parameters.size()) +
                                   " arguments, but got " +
                                   std::to_string(argsTokens.size()));
        // Convert each argument token vector to a string.
        std::vector<std::string> argStrings;
        for (const auto &argVec : argsTokens)
          argStrings.push_back(tokensToString(argVec));
        // Perform parameter substitution.
        std::string expansion = macro.replacement;
        for (size_t k = 0; k < macro.parameters.size(); ++k) {
          expansion = replaceParameter(expansion, macro.parameters[k],
                                       argStrings[k]);
        }
        // Recursively expand the result.
        std::string expandedText = expandTokens(expansion);
        // Tokenize the expanded text and append its tokens.
        Lexer newLexer(expandedText);
        std::vector<Token> newTokens = newLexer.tokenize();
        if (!newTokens.empty() &&
            newTokens.back().type == TokenType::EOF_TOKEN)
          newTokens.pop_back();
        output.insert(output.end(), newTokens.begin(), newTokens.end());
        i = j; // Skip over macro invocation tokens.
        continue;
      }
      // For object-like macros.
      else if (!macro.isFunctionLike) {
        std::cerr << "[DEBUG] Expanding object-like macro: " << token.lexeme
                  << " at line " << token.line << "\n";
        std::string expansion = macro.replacement;
        std::string expandedText = expandTokens(expansion);
        Lexer newLexer(expandedText);
        std::vector<Token> newTokens = newLexer.tokenize();
        if (!newTokens.empty() && newTokens.back().type == TokenType::EOF_TOKEN)
          newTokens.pop_back();
        output.insert(output.end(), newTokens.begin(), newTokens.end());
        continue;
      }
      // If function-like but no '(' follows, treat it as a normal identifier.
      else {
        output.push_back(token);
      }
    } else {
      // Not a macro invocation; copy token.
      output.push_back(token);
    }
  }
  return tokensToString(output);
}

//
// Modified expand: repeatedly apply expandTokens until no further changes occur.
//
std::string MacroExpander::expand(const std::string &source) {
  std::string prev;
  std::string curr = source;
  do {
    prev = curr;
    curr = expandTokens(prev);
  } while (curr != prev);
  return curr;
}
