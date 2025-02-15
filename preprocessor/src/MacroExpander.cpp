#include "MacroExpander.hpp"
#include "Lexer.hpp"
#include "Token.hpp"

#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

// Helper: join a vector of tokens into a string (tokens separated by a space).
static std::string tokensToString(const std::vector<Token> &tokens) {
  std::ostringstream oss;
  for (const auto &tok : tokens) {
    oss << tok.lexeme << " ";
  }
  return oss.str();
}

MacroExpander::MacroExpander() : currentFile("<unknown>") {
  // Empty constructor.
}

void MacroExpander::setCurrentFile(const std::string &fileName) {
  currentFile = fileName;
}

//
// processDirective:
//   Parses a directive line and adds or removes macro definitions.
//   This version manually scans the line to extract the macro name and,
//   if the next non‐whitespace character is '(', parses the parameter list.
//   Supports object-like, function-like, and variadic macros.
//
void MacroExpander::processDirective(const std::string &line) {
  size_t pos = line.find("#define");
  if (pos != std::string::npos) {
    pos += 7; // Skip "#define"
    // Skip whitespace.
    while (pos < line.size() && isspace(line[pos]))
      pos++;
    // Read the macro name (identifier).
    size_t start = pos;
    while (pos < line.size() && (isalnum(line[pos]) || line[pos] == '_'))
      pos++;
    std::string name = line.substr(start, pos - start);

    Macro macro;
    macro.isFunctionLike = false;
    macro.isVariadic = false;
    // If the next character is '(' (with no intervening whitespace), then it's
    // function-like.
    if (pos < line.size() && line[pos] == '(') {
      macro.isFunctionLike = true;
      pos++; // skip '('
      // Read parameter list until ')'
      std::string params;
      while (pos < line.size() && line[pos] != ')') {
        params.push_back(line[pos]);
        pos++;
      }
      if (pos == line.size()) {
        throw std::runtime_error("Missing ')' in macro definition: " + line);
      }
      pos++; // skip ')'
      // Tokenize parameters separated by commas.
      std::istringstream pss(params);
      std::string param;
      while (std::getline(pss, param, ',')) {
        // Trim whitespace.
        size_t s = param.find_first_not_of(" \t");
        size_t e = param.find_last_not_of(" \t");
        if (s != std::string::npos && e != std::string::npos) {
          std::string token = param.substr(s, e - s + 1);
          if (token == "...") {
            macro.isVariadic = true;
            macro.parameters.push_back("__VA_ARGS__");
          } else {
            macro.parameters.push_back(token);
          }
        }
      }
    }
    // Skip any whitespace before the replacement.
    while (pos < line.size() && isspace(line[pos]))
      pos++;
    std::string replacement;
    if (pos < line.size())
      replacement = line.substr(pos);
    macro.replacement = replacement;
    macros[name] = macro;
    std::cerr << "[DEBUG] Defined macro: " << name;
    if (macro.isFunctionLike) {
      std::cerr << " (function-like, params: ";
      for (const auto &p : macro.parameters)
        std::cerr << p << " ";
      std::cerr << ")";
    }
    std::cerr << " => '" << macro.replacement << "'\n";
  } else {
    pos = line.find("#undef");
    if (pos != std::string::npos) {
      pos += 6; // Skip "#undef"
      while (pos < line.size() && isspace(line[pos]))
        pos++;
      size_t start = pos;
      while (pos < line.size() && (isalnum(line[pos]) || line[pos] == '_'))
        pos++;
      std::string name = line.substr(start, pos - start);
      macros.erase(name);
      std::cerr << "[DEBUG] Undefining macro: " << name << "\n";
    }
  }
}

//
// expandTokens:
//   Recursively expands macros in the given source string.
//   The 'disabled' map holds macro names that should not be expanded in this
//   context. Also performs built-in macro substitution for __FILE__ and
//   __LINE__.
//
std::string MacroExpander::expandTokens(
    const std::string &source,
    const std::unordered_map<std::string, bool> &disabled) {
  Lexer lexer(source);
  std::vector<Token> tokens = lexer.tokenize();
  if (!tokens.empty() && tokens.back().type == TokenType::EOF_TOKEN) {
    tokens.pop_back();
  }
  std::vector<Token> output;
  for (size_t i = 0; i < tokens.size(); ++i) {
    Token token = tokens[i];
    // Built-in macros.
    if (token.type == TokenType::IDENTIFIER) {
      if (token.lexeme == "__FILE__") {
        Token newToken;
        newToken.type =
            TokenType::LITERAL_CHAR; // Using LITERAL_CHAR as placeholder for
                                     // string literal.
        newToken.lexeme = "\"" + currentFile + "\"";
        newToken.line = token.line;
        newToken.column = token.column;
        output.push_back(newToken);
        continue;
      } else if (token.lexeme == "__LINE__") {
        Token newToken;
        newToken.type = TokenType::LITERAL_INT;
        newToken.lexeme = std::to_string(token.line);
        newToken.line = token.line;
        newToken.column = token.column;
        output.push_back(newToken);
        continue;
      }
    }
    // Check for macro expansion.
    if (token.type == TokenType::IDENTIFIER) {
      std::string name = token.lexeme;
      if (macros.find(name) != macros.end() &&
          disabled.find(name) == disabled.end()) {
        Macro macro = macros[name];
        std::unordered_map<std::string, bool> newDisabled = disabled;
        newDisabled[name] = true;
        if (macro.isFunctionLike) {
          if (i + 1 < tokens.size() &&
              tokens[i + 1].type == TokenType::DELIM_LPAREN) {
            size_t j = i + 1;
            int parenLevel = 0;
            std::vector<std::vector<Token>> args;
            std::vector<Token> currentArg;
            bool finished = false;
            for (; j < tokens.size(); ++j) {
              Token t = tokens[j];
              if (t.type == TokenType::DELIM_LPAREN) {
                parenLevel++;
                if (parenLevel > 1)
                  currentArg.push_back(t);
              } else if (t.type == TokenType::DELIM_RPAREN) {
                parenLevel--;
                if (parenLevel == 0) {
                  args.push_back(currentArg);
                  finished = true;
                  break;
                } else {
                  currentArg.push_back(t);
                }
              } else if (t.type == TokenType::DELIM_COMMA && parenLevel == 1) {
                args.push_back(currentArg);
                currentArg.clear();
              } else {
                currentArg.push_back(t);
              }
            }
            if (!finished) {
              throw std::runtime_error(
                  "Unmatched '(' in macro invocation for macro " + name);
            }
            std::string expansion =
                expandFunctionMacro(macro, args, newDisabled);
            std::string recursiveExpansion =
                expandTokens(expansion, newDisabled);
            Lexer newLexer(recursiveExpansion);
            std::vector<Token> newTokens = newLexer.tokenize();
            if (!newTokens.empty() &&
                newTokens.back().type == TokenType::EOF_TOKEN)
              newTokens.pop_back();
            output.insert(output.end(), newTokens.begin(), newTokens.end());
            i = j; // skip tokens consumed in macro invocation
            continue;
          } else {
            output.push_back(token);
          }
        } else {
          std::string expansion = macro.replacement;
          std::string recursiveExpansion = expandTokens(expansion, newDisabled);
          Lexer newLexer(recursiveExpansion);
          std::vector<Token> newTokens = newLexer.tokenize();
          if (!newTokens.empty() &&
              newTokens.back().type == TokenType::EOF_TOKEN)
            newTokens.pop_back();
          output.insert(output.end(), newTokens.begin(), newTokens.end());
          continue;
        }
      } else {
        output.push_back(token);
      }
    } else {
      output.push_back(token);
    }
  }
  // After processing tokens, perform token pasting.
  std::vector<Token> pasted;
  for (size_t i = 0; i < output.size(); ++i) {
    if (i + 1 < output.size() && output[i + 1].lexeme == "##") {
      if (i + 2 < output.size()) {
        std::string merged =
            pasteTokens(output[i].lexeme, output[i + 2].lexeme);
        Token mergedToken;
        mergedToken.type = TokenType::IDENTIFIER; // Fallback type.
        mergedToken.lexeme = merged;
        mergedToken.line = output[i].line;
        mergedToken.column = output[i].column;
        pasted.push_back(mergedToken);
        i += 2; // Skip the next two tokens.
      } else {
        throw std::runtime_error(
            "Token pasting operator '##' has no right-hand operand.");
      }
    } else {
      pasted.push_back(output[i]);
    }
  }
  return tokensToString(pasted);
}

//
// expand:
//   Repeatedly applies macro expansion until a fixed point is reached.
//
std::string MacroExpander::expand(const std::string &source) {
  std::string prev;
  std::string curr = source;
  std::unordered_map<std::string, bool> disabled;
  do {
    prev = curr;
    curr = expandTokens(prev, disabled);
  } while (curr != prev);
  return curr;
}

//
// expandFunctionMacro:
//   Expands a function-like macro by substituting parameters with the argument
//   tokens. Handles stringification (the '#' operator), token pasting ('##'),
//   and variadic macros (using "__VA_ARGS__").
//   Returns the resulting replacement string (which will be recursively
//   expanded).
//
std::string MacroExpander::expandFunctionMacro(
    const Macro &macro, const std::vector<std::vector<Token>> &args,
    const std::unordered_map<std::string, bool> &disabled) {
  size_t paramCount = macro.parameters.size();
  bool variadic = macro.isVariadic;
  if (!variadic && args.size() != paramCount) {
    throw std::runtime_error("Macro expects " + std::to_string(paramCount) +
                             " arguments, but got " +
                             std::to_string(args.size()));
  }
  if (variadic && args.size() < paramCount - 1) {
    throw std::runtime_error(
        "Macro expects at least " + std::to_string(paramCount - 1) +
        " arguments, but got " + std::to_string(args.size()));
  }
  // Tokenize the replacement text.
  Lexer lexer(macro.replacement);
  std::vector<Token> repTokens = lexer.tokenize();
  if (!repTokens.empty() && repTokens.back().type == TokenType::EOF_TOKEN)
    repTokens.pop_back();

  // --- Merge adjacent '#' tokens into a single token "##" ---
  std::vector<Token> mergedTokens;
  for (size_t i = 0; i < repTokens.size(); ++i) {
    if (repTokens[i].lexeme == "#" &&
        (i + 1 < repTokens.size() && repTokens[i + 1].lexeme == "#")) {
      Token newToken;
      newToken.lexeme = "##";
      newToken.type = repTokens[i].type;
      newToken.line = repTokens[i].line;
      newToken.column = repTokens[i].column;
      mergedTokens.push_back(newToken);
      i++; // Skip next token.
    } else {
      mergedTokens.push_back(repTokens[i]);
    }
  }

  std::vector<Token> result;
  // Process the tokens in the replacement.
  for (size_t i = 0; i < mergedTokens.size(); ++i) {
    Token t = mergedTokens[i];
    if (t.lexeme == "#") {
      // Stringification: the next token must be an identifier (a parameter).
      if (i + 1 < mergedTokens.size() &&
          mergedTokens[i + 1].type == TokenType::IDENTIFIER) {
        std::string paramName = mergedTokens[i + 1].lexeme;
        int index = -1;
        for (size_t j = 0; j < macro.parameters.size(); ++j) {
          if (macro.parameters[j] == paramName) {
            index = j;
            break;
          }
        }
        if (index == -1) {
          throw std::runtime_error("Stringification error: parameter " +
                                   paramName + " not found in macro");
        }
        std::vector<Token> argTokens;
        if (variadic && paramName == "__VA_ARGS__") {
          for (size_t j = macro.parameters.size() - 1; j < args.size(); ++j) {
            argTokens.insert(argTokens.end(), args[j].begin(), args[j].end());
            if (j != args.size() - 1) {
              Token comma;
              comma.type = TokenType::DELIM_COMMA;
              comma.lexeme = ",";
              comma.line = t.line;
              comma.column = t.column;
              argTokens.push_back(comma);
            }
          }
        } else {
          if (index >= args.size())
            throw std::runtime_error(
                "Not enough arguments for macro expansion.");
          argTokens = args[index];
        }
        std::string strLit = stringifyArgument(argTokens);
        Token newToken;
        newToken.type =
            TokenType::LITERAL_INT; // Placeholder type for string literals.
        newToken.lexeme = strLit;
        newToken.line = t.line;
        newToken.column = t.column;
        result.push_back(newToken);
        i++; // Skip parameter token.
        continue;
      } else {
        throw std::runtime_error("Invalid use of '#' in macro replacement.");
      }
    } else if (t.lexeme == "##") {
      // Leave token pasting operators for later.
      result.push_back(t);
    } else if (t.type == TokenType::IDENTIFIER) {
      bool isParam = false;
      int index = -1;
      for (size_t j = 0; j < macro.parameters.size(); ++j) {
        if (macro.parameters[j] == t.lexeme) {
          isParam = true;
          index = j;
          break;
        }
      }
      if (isParam) {
        std::vector<Token> argTokens;
        if (variadic && t.lexeme == "__VA_ARGS__") {
          for (size_t j = macro.parameters.size() - 1; j < args.size(); ++j) {
            argTokens.insert(argTokens.end(), args[j].begin(), args[j].end());
            if (j != args.size() - 1) {
              Token comma;
              comma.type = TokenType::DELIM_COMMA;
              comma.lexeme = ",";
              comma.line = t.line;
              comma.column = t.column;
              argTokens.push_back(comma);
            }
          }
        } else {
          if (index >= args.size())
            throw std::runtime_error(
                "Not enough arguments for macro expansion.");
          argTokens = args[index];
        }
        std::string argStr = tokensToString(argTokens);
        std::string expandedArg = expandTokens(argStr, disabled);
        Lexer newLexer(expandedArg);
        std::vector<Token> newTokens = newLexer.tokenize();
        if (!newTokens.empty() && newTokens.back().type == TokenType::EOF_TOKEN)
          newTokens.pop_back();
        result.insert(result.end(), newTokens.begin(), newTokens.end());
        continue;
      } else {
        result.push_back(t);
      }
    } else {
      result.push_back(t);
    }
  }
  // Now perform token pasting.
  std::vector<Token> pasted;
  for (size_t i = 0; i < result.size(); ++i) {
    if (i + 1 < result.size() && result[i + 1].lexeme == "##") {
      if (i + 2 < result.size()) {
        std::string merged =
            pasteTokens(result[i].lexeme, result[i + 2].lexeme);
        Token mergedToken;
        mergedToken.type = TokenType::IDENTIFIER;
        mergedToken.lexeme = merged;
        mergedToken.line = result[i].line;
        mergedToken.column = result[i].column;
        pasted.push_back(mergedToken);
        i += 2;
      } else {
        throw std::runtime_error(
            "Token pasting operator '##' has no right-hand operand.");
      }
    } else {
      pasted.push_back(result[i]);
    }
  }
  return tokensToString(pasted);
}

//
// stringifyArgument:
//   Converts the list of tokens for an argument into a string literal.
//   Escapes backslashes and quotes as needed.
//
std::string MacroExpander::stringifyArgument(const std::vector<Token> &tokens) {
  std::ostringstream oss;
  oss << "\"";
  for (const auto &t : tokens) {
    for (char c : t.lexeme) {
      if (c == '\\' || c == '"') {
        oss << '\\';
      }
      oss << c;
    }
    oss << " ";
  }
  oss << "\"";
  return oss.str();
}

//
// pasteTokens:
//   Concatenates two token lexemes (the simplest form of token pasting).
//
std::string MacroExpander::pasteTokens(const std::string &left,
                                       const std::string &right) {
  return left + right;
}
