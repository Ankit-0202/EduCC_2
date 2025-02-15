#include "ConditionalProcessor.hpp"
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

// Make sure ConditionalProcessor.hpp declares:
//   std::unordered_map<std::string, std::string> macroDefinitions;
// in its private section.

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
// Record simple macro definitions for conditionals (only handles simple cases)
//
void ConditionalProcessor::recordMacro(const std::string &line) {
  std::string trimmed = line;
  trimmed.erase(0, trimmed.find_first_not_of(" \t"));
  if (trimmed.compare(0, 7, "#define") == 0) {
    std::string rest = trimmed.substr(7);
    rest = rest.substr(rest.find_first_not_of(" \t"));
    size_t nameEnd = rest.find_first_of(" \t");
    std::string macroName;
    std::string replacement;
    if (nameEnd == std::string::npos) {
      // No replacement text; use empty string.
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
// Process non-conditional directives. For our purposes, process and record
// macro definitions, then remove them from the output.
//
std::string ConditionalProcessor::processNonConditionalDirective(const std::string &line) {
  std::string trimmed = line;
  trimmed.erase(0, trimmed.find_first_not_of(" \t"));
  if (trimmed.compare(0, 7, "#define") == 0 || trimmed.compare(0, 6, "#undef") == 0) {
    recordMacro(line);
    return "";
  }
  return "";
}

//
// Evaluate a conditional expression. Our implementation is very simplified.
// It first trims the expression, then attempts to convert it to an int.
// If conversion fails, it looks up the expression in our macroDefinitions
// (so that an expression like "FLAG" will be replaced with "1").
//
int ConditionalProcessor::evaluateExpression(const std::string &expr) {
  std::string trimmed = expr;
  trimmed.erase(0, trimmed.find_first_not_of(" \t"));
  try {
    return std::stoi(trimmed);
  } catch (...) {
    if (macroDefinitions.find(trimmed) != macroDefinitions.end()) {
      std::string replacement = macroDefinitions[trimmed];
      replacement.erase(0, replacement.find_first_not_of(" \t"));
      try {
        return std::stoi(replacement);
      } catch (...) {
        throw std::runtime_error("Invalid expression after macro substitution: " + replacement);
      }
    }
    throw std::runtime_error("Invalid expression in conditional: " + expr);
  }
}

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
    recordMacro(line);  // record the macro definition for conditionals
    return line;        // preserve the line for later macro expansion
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
