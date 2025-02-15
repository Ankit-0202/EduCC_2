#include "ConditionalProcessor.hpp"
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

ConditionalProcessor::ConditionalProcessor() {
  // Start with a default active state.
  stateStack.push({true, false});
}

bool ConditionalProcessor::isConditionalDirective(const std::string &line) {
  std::string trimmed = line;
  trimmed.erase(0, trimmed.find_first_not_of(" \t"));
  return trimmed.compare(0, 1, "#") == 0;
}

//
// recordMacro:
//   Records a simple macro definition for use in conditional expressions.
//   (Only handles object-like macros. Function-like macros are not used in
//   conditionals.)
//
void ConditionalProcessor::recordMacro(const std::string &line) {
  std::string trimmed = line;
  trimmed.erase(0, trimmed.find_first_not_of(" \t"));
  if (trimmed.compare(0, 7, "#define") == 0) {
    std::string rest = trimmed.substr(7);
    rest = rest.substr(rest.find_first_not_of(" \t"));
    size_t nameEnd = rest.find_first_of(" \t(");
    std::string macroName;
    std::string replacement;
    if (nameEnd == std::string::npos) {
      macroName = rest;
      replacement = "";
    } else {
      macroName = rest.substr(0, nameEnd);
      replacement = rest.substr(nameEnd);
      replacement = replacement.substr(replacement.find_first_not_of(" \t"));
    }
    macroDefinitions[macroName] = replacement;
  } else if (trimmed.compare(0, 6, "#undef") == 0) {
    std::string rest = trimmed.substr(6);
    rest = rest.substr(rest.find_first_not_of(" \t"));
    macroDefinitions.erase(rest);
  }
}

//
// processNonConditionalDirective:
//   Processes non-conditional directives (like #define and #undef) by recording
//   the macro and then returning the line (so it can be passed to the macro
//   expander later).
//
std::string
ConditionalProcessor::processNonConditionalDirective(const std::string &line) {
  std::string trimmed = line;
  trimmed.erase(0, trimmed.find_first_not_of(" \t"));
  if (trimmed.compare(0, 7, "#define") == 0 ||
      trimmed.compare(0, 6, "#undef") == 0) {
    recordMacro(line);
    return line;
  }
  return "";
}

//
// evaluateExpression:
//   Evaluates a very simplified constant expression for conditionals.
//   It supports integer literals and the defined operator in the forms:
//       defined MACRO
//       defined(MACRO)
//   If the expression is not an integer literal, it attempts to substitute
//   a recorded macro definition and convert it to an integer.
//
int ConditionalProcessor::evaluateExpression(const std::string &expr) {
  std::string trimmed = expr;
  trimmed.erase(0, trimmed.find_first_not_of(" \t"));
  // Support "defined" operator.
  if (trimmed.compare(0, 7, "defined") == 0) {
    size_t pos = 7;
    while (pos < trimmed.size() && isspace(trimmed[pos]))
      pos++;
    std::string macroName;
    if (pos < trimmed.size() && trimmed[pos] == '(') {
      pos++; // skip '('
      size_t endPos = trimmed.find(')', pos);
      if (endPos == std::string::npos)
        throw std::runtime_error("Missing ')' in defined operator: " + expr);
      macroName = trimmed.substr(pos, endPos - pos);
    } else {
      size_t endPos = trimmed.find_first_of(" \t", pos);
      if (endPos == std::string::npos)
        macroName = trimmed.substr(pos);
      else
        macroName = trimmed.substr(pos, endPos - pos);
    }
    // Trim macroName.
    size_t s = macroName.find_first_not_of(" \t");
    size_t e = macroName.find_last_not_of(" \t");
    if (s != std::string::npos && e != std::string::npos)
      macroName = macroName.substr(s, e - s + 1);
    return (macroDefinitions.find(macroName) != macroDefinitions.end()) ? 1 : 0;
  }
  // Otherwise, try to convert the expression to an integer.
  try {
    return std::stoi(trimmed);
  } catch (...) {
    if (macroDefinitions.find(trimmed) != macroDefinitions.end()) {
      std::string replacement = macroDefinitions[trimmed];
      replacement.erase(0, replacement.find_first_not_of(" \t"));
      try {
        return std::stoi(replacement);
      } catch (...) {
        throw std::runtime_error(
            "Invalid expression after macro substitution: " + replacement);
      }
    }
    throw std::runtime_error("Invalid expression in conditional: " + expr);
  }
}

//
// processLine:
//   Processes a single line. For macro directives (#define, #undef), it records
//   them and preserves the line; for conditional directives (#if, #else, etc.),
//   it uses the evaluator.
//
std::string ConditionalProcessor::processLine(const std::string &line) {
  std::string trimmed = line;
  trimmed.erase(0, trimmed.find_first_not_of(" \t"));
  if (trimmed.empty())
    return line; // blank line

  // If the line doesn't start with '#', output it if we're active.
  if (trimmed[0] != '#') {
    return stateStack.top().active ? line : "";
  }

  // It is a directive.
  std::istringstream iss(trimmed);
  std::string directive;
  iss >> directive;

  // --- Preserve and record macro directives ---
  if (directive == "#define" || directive == "#undef") {
    recordMacro(line);
    return line; // Preserve for macro expansion.
  }

  // Now handle conditional directives.
  if (directive == "#if") {
    std::string expr;
    std::getline(iss, expr);
    expr = expr.substr(expr.find_first_not_of(" \t"));
    int result = evaluateExpression(expr);
    bool active = (result != 0) && stateStack.top().active;
    stateStack.push({active, active});
    return "";
  } else if (directive == "#ifdef") {
    // For simplicity, assume undefined.
    bool active = false;
    stateStack.push({active && stateStack.top().active, active});
    return "";
  } else if (directive == "#ifndef") {
    // For simplicity, assume always true.
    bool active = true;
    stateStack.push({active && stateStack.top().active, active});
    return "";
  } else if (directive == "#elif") {
    if (stateStack.empty())
      throw std::runtime_error("#elif without matching #if");
    auto prev = stateStack.top();
    stateStack.pop();
    std::string expr;
    std::getline(iss, expr);
    expr = expr.substr(expr.find_first_not_of(" \t"));
    int result = evaluateExpression(expr);
    bool active = (!prev.taken) && (result != 0) && stateStack.top().active;
    bool taken = prev.taken || active;
    stateStack.push({active, taken});
    return "";
  } else if (directive == "#else") {
    if (stateStack.empty())
      throw std::runtime_error("#else without matching #if");
    auto prev = stateStack.top();
    stateStack.pop();
    bool active = (!prev.taken) && stateStack.top().active;
    stateStack.push({active, prev.taken || active});
    return "";
  } else if (directive == "#endif") {
    if (stateStack.empty())
      throw std::runtime_error("#endif without matching #if");
    stateStack.pop();
    return "";
  } else {
    // For any other directives, just remove them.
    return "";
  }
}

void ConditionalProcessor::verifyBalanced() const {
  if (stateStack.size() != 1)
    throw std::runtime_error("Unterminated conditional directives detected.");
}
