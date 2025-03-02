#include "ConditionalProcessor.hpp"
#include "BuiltinMacros.hpp"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

// The ConditionalProcessor uses a stack of states to track whether
// the current block is active.
ConditionalProcessor::ConditionalProcessor() {
  stateStack.push({true, false});
  // Predefine built‑in macros required by many system header conditionals.
  macroDefinitions["__STDC_WANT_LIB_EXT1__"] = "0";
  macroDefinitions["__STRICT_ANSI__"] = "0";
  // Remove the trailing L so that numeric conversion succeeds.
  macroDefinitions["__DARWIN_C_LEVEL"] = "200809";
  macroDefinitions["__DARWIN_C_FULL"] = "900000";
}

namespace {

// Forward declarations for our recursive‑descent parser functions.
int parseExpression(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions);
int parseLogicalOr(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions);
int parseLogicalAnd(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions);
int parseEquality(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions);
int parseRelational(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions);
int parseAdditive(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions);
int parseMultiplicative(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions);
int parseUnary(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions);
int parsePrimary(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions);
int parseBuiltinMacro(const std::string &s, size_t &pos);

void skipSpaces(const std::string &s, size_t &pos) {
  while (pos < s.size() && std::isspace(s[pos]))
    pos++;
}

int parseUnary(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions) {
  skipSpaces(s, pos);
  if (pos < s.size()) {
    if (s[pos] == '!') {
      pos++;
      int value = parseUnary(s, pos, macroDefinitions);
      return !value;
    } else if (s[pos] == '-') {
      pos++;
      int value = parseUnary(s, pos, macroDefinitions);
      return -value;
    } else if (s[pos] == '+') {
      pos++;
      return parseUnary(s, pos, macroDefinitions);
    }
  }
  return parsePrimary(s, pos, macroDefinitions);
}

int parseAdditive(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions) {
  int lhs = parseUnary(s, pos, macroDefinitions);
  skipSpaces(s, pos);
  while (pos < s.size() && (s[pos] == '+' || s[pos] == '-')) {
    char op = s[pos];
    pos++;
    int rhs = parseUnary(s, pos, macroDefinitions);
    lhs = (op == '+') ? (lhs + rhs) : (lhs - rhs);
    skipSpaces(s, pos);
  }
  return lhs;
}

int parseRelational(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions) {
  int lhs = parseAdditive(s, pos, macroDefinitions);
  skipSpaces(s, pos);
  while (true) {
    if (s.compare(pos, 2, ">=") == 0) {
      pos += 2;
      int rhs = parseAdditive(s, pos, macroDefinitions);
      lhs = (lhs >= rhs) ? 1 : 0;
    } else if (s.compare(pos, 2, "<=") == 0) {
      pos += 2;
      int rhs = parseAdditive(s, pos, macroDefinitions);
      lhs = (lhs <= rhs) ? 1 : 0;
    } else if (pos < s.size() && s[pos] == '>') {
      pos++;
      int rhs = parseAdditive(s, pos, macroDefinitions);
      lhs = (lhs > rhs) ? 1 : 0;
    } else if (pos < s.size() && s[pos] == '<') {
      pos++;
      int rhs = parseAdditive(s, pos, macroDefinitions);
      lhs = (lhs < rhs) ? 1 : 0;
    } else {
      break;
    }
    skipSpaces(s, pos);
  }
  return lhs;
}

int parseEquality(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions) {
  int lhs = parseRelational(s, pos, macroDefinitions);
  skipSpaces(s, pos);
  while (true) {
    if (s.compare(pos, 2, "==") == 0) {
      pos += 2;
      int rhs = parseRelational(s, pos, macroDefinitions);
      lhs = (lhs == rhs) ? 1 : 0;
    } else if (s.compare(pos, 2, "!=") == 0) {
      pos += 2;
      int rhs = parseRelational(s, pos, macroDefinitions);
      lhs = (lhs != rhs) ? 1 : 0;
    } else {
      break;
    }
    skipSpaces(s, pos);
  }
  return lhs;
}

int parseLogicalAnd(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions) {
  int lhs = parseEquality(s, pos, macroDefinitions);
  skipSpaces(s, pos);
  while (s.compare(pos, 2, "&&") == 0) {
    pos += 2;
    int rhs = parseEquality(s, pos, macroDefinitions);
    lhs = (lhs && rhs) ? 1 : 0;
    skipSpaces(s, pos);
  }
  return lhs;
}

int parseLogicalOr(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions) {
  int lhs = parseLogicalAnd(s, pos, macroDefinitions);
  skipSpaces(s, pos);
  while (s.compare(pos, 2, "||") == 0) {
    pos += 2;
    int rhs = parseLogicalAnd(s, pos, macroDefinitions);
    lhs = (lhs || rhs) ? 1 : 0;
    skipSpaces(s, pos);
  }
  return lhs;
}

int parseExpression(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions) {
  return parseLogicalOr(s, pos, macroDefinitions);
}

int parseBuiltinMacro(const std::string &s, size_t &pos) {
  size_t start = pos;
  while (pos < s.size() && (std::isalnum(s[pos]) || s[pos] == '_'))
    pos++;
  std::string macroName = s.substr(start, pos - start);
  skipSpaces(s, pos);
  // Special cases: allow __has_safe_buffers and __has_ptrcheck without
  // parentheses.
  if ((macroName == "__has_safe_buffers" || macroName == "__has_ptrcheck") &&
      (pos >= s.size() || s[pos] != '('))
    return evaluateBuiltinMacro(macroName, {});
  if (pos >= s.size() || s[pos] != '(')
    throw std::runtime_error("Expected '(' after builtin macro " + macroName);
  pos++; // skip '('
  skipSpaces(s, pos);
  std::string arg;
  while (pos < s.size() && s[pos] != ')') {
    arg.push_back(s[pos]);
    pos++;
  }
  if (pos >= s.size() || s[pos] != ')')
    throw std::runtime_error("Missing ')' in builtin macro " + macroName);
  pos++; // skip ')'
  skipSpaces(s, pos);
  size_t argStart = arg.find_first_not_of(" \t");
  size_t argEnd = arg.find_last_not_of(" \t");
  if (argStart != std::string::npos && argEnd != std::string::npos)
    arg = arg.substr(argStart, argEnd - argStart + 1);
  if (!arg.empty() && arg.front() == '"' && arg.back() == '"')
    arg = arg.substr(1, arg.size() - 2);
  return evaluateBuiltinMacro(macroName, {arg});
}

int parsePrimary(
    const std::string &s, size_t &pos,
    const std::unordered_map<std::string, std::string> &macroDefinitions) {
  skipSpaces(s, pos);
  if (pos >= s.size())
    throw std::runtime_error("Unexpected end of expression");

  // Handle builtin macros starting with __has_ or __is_target_os.
  if (s.compare(pos, 6, "__has_") == 0 ||
      s.compare(pos, 14, "__is_target_os") == 0)
    return parseBuiltinMacro(s, pos);

  // Handle parenthesized expressions.
  if (s[pos] == '(') {
    pos++;
    int value = parseExpression(s, pos, macroDefinitions);
    skipSpaces(s, pos);
    if (pos >= s.size() || s[pos] != ')')
      throw std::runtime_error("Missing ')' in expression");
    pos++;
    return value;
  }

  // Handle defined operator.
  if (s.compare(pos, 7, "defined") == 0) {
    pos += 7;
    skipSpaces(s, pos);
    std::string macroName;
    if (pos < s.size() && s[pos] == '(') {
      pos++;
      skipSpaces(s, pos);
      while (pos < s.size() && (std::isalnum(s[pos]) || s[pos] == '_')) {
        macroName.push_back(s[pos]);
        pos++;
      }
      skipSpaces(s, pos);
      if (pos >= s.size() || s[pos] != ')')
        throw std::runtime_error("Missing ')' in defined operator");
      pos++;
    } else {
      while (pos < s.size() && (std::isalnum(s[pos]) || s[pos] == '_')) {
        macroName.push_back(s[pos]);
        pos++;
      }
    }
    return (macroDefinitions.find(macroName) != macroDefinitions.end()) ? 1 : 0;
  }

  // Handle numeric literals.
  if (std::isdigit(s[pos])) {
    std::string number;
    while (pos < s.size() && std::isdigit(s[pos])) {
      number.push_back(s[pos]);
      pos++;
    }
    // Skip any trailing alphabetic characters.
    while (pos < s.size() && std::isalpha(s[pos]))
      pos++;
    try {
      return std::stoi(number);
    } catch (...) {
      throw std::runtime_error("Invalid integer literal: " + number);
    }
  }

  // Handle an identifier: if defined, substitute; otherwise, default to 0.
  std::string token;
  while (pos < s.size() && (std::isalnum(s[pos]) || s[pos] == '_')) {
    token.push_back(s[pos]);
    pos++;
  }
  if (token.empty())
    throw std::runtime_error("Expected token in expression");
  if (macroDefinitions.find(token) != macroDefinitions.end()) {
    std::string val = macroDefinitions.at(token);
    // Remove a trailing 'L' or 'l' if present.
    if (!val.empty() && (val.back() == 'L' || val.back() == 'l'))
      val.pop_back();
    // If the macro expansion isn’t a valid numeric constant, return 0.
    if (val.empty() ||
        (!(std::isdigit(val[0]) || val[0] == '-' || val[0] == '+')))
      return 0;
    try {
      return std::stoi(val);
    } catch (...) {
      return 0;
    }
  }
  return 0;
}

} // end anonymous namespace

int ConditionalProcessor::evaluateExpression(const std::string &expr) {
  std::string trimmed = expr;
  trimmed.erase(0, trimmed.find_first_not_of(" \t"));
  size_t pos = 0;
  try {
    int result = parseExpression(trimmed, pos, macroDefinitions);
    skipSpaces(trimmed, pos);
    if (pos < trimmed.size() && !std::all_of(
                                    trimmed.begin() + pos, trimmed.end(),
                                    [](char c) { return std::isspace(c); }))
      throw std::runtime_error("Unexpected characters at end of expression");
    return result;
  } catch (const std::exception &e) {
    throw std::runtime_error("Invalid expression in conditional: " + expr +
                             "\nReason: " + e.what());
  }
}

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

std::string ConditionalProcessor::processLine(const std::string &line) {
  std::string trimmed = line;
  trimmed.erase(0, trimmed.find_first_not_of(" \t"));
  if (trimmed.empty())
    return line; // blank line

  if (trimmed[0] != '#')
    return stateStack.top().active ? line : "";

  std::istringstream iss(trimmed);
  std::string directive;
  iss >> directive;

  if (directive == "#define" || directive == "#undef") {
    recordMacro(line);
    return line;
  }

  if (directive == "#if") {
    std::string expr;
    std::getline(iss, expr);
    expr = expr.substr(expr.find_first_not_of(" \t"));
    int result = evaluateExpression(expr);
    bool active = (result != 0) && stateStack.top().active;
    stateStack.push({active, active});
    return "";
  } else if (directive == "#ifdef") {
    stateStack.push({false, false});
    return "";
  } else if (directive == "#ifndef") {
    stateStack.push({false, false});
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
    return "";
  }
}

void ConditionalProcessor::verifyBalanced() const {
  if (stateStack.size() != 1)
    throw std::runtime_error("Unterminated conditional directives detected.");
}
