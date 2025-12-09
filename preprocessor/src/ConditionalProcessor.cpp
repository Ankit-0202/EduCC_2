#include "ConditionalProcessor.hpp"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

namespace {

std::string trim(const std::string &input) {
  size_t start = input.find_first_not_of(" \t");
  if (start == std::string::npos)
    return "";
  size_t end = input.find_last_not_of(" \t");
  return input.substr(start, end - start + 1);
}

bool isIdentifierStart(char c) {
  return std::isalpha(static_cast<unsigned char>(c)) || c == '_';
}

bool isIdentifierChar(char c) {
  return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
}

class ExpressionParser {
public:
  ExpressionParser(const std::string &expr,
                   const std::unordered_map<std::string, std::string> &macros,
                   int depth = 0)
      : text(expr), macros(macros), pos(0), depth(depth) {}

  long long parse() {
    long long value = parseConditional();
    skipWhitespace();
    if (pos < text.size()) {
      throw std::runtime_error("Unexpected tokens in conditional expression: " +
                               text.substr(pos));
    }
    return value;
  }
  long long parseConditional() {
    long long condition = parseLogicalOr();
    skipWhitespace();
    if (!consume("?"))
      return condition;

    long long trueValue = parseConditional();
    expect(":");
    long long falseValue = parseConditional();
    return condition != 0 ? trueValue : falseValue;
  }

private:
  static constexpr int kMaxDepth = 64;
  const std::string &text;
  const std::unordered_map<std::string, std::string> &macros;
  size_t pos;
  int depth;

  void skipWhitespace() {
    while (pos < text.size() &&
           std::isspace(static_cast<unsigned char>(text[pos]))) {
      ++pos;
    }
  }

  bool consume(const std::string &token) {
    skipWhitespace();
    if (text.compare(pos, token.size(), token) == 0) {
      pos += token.size();
      return true;
    }
    return false;
  }

  bool consumeBitwiseAndOperator() {
    skipWhitespace();
    if (pos < text.size() && text[pos] == '&') {
      if (pos + 1 < text.size() && text[pos + 1] == '&')
        return false;
      ++pos;
      return true;
    }
    return false;
  }

  bool consumeBitwiseOrOperator() {
    skipWhitespace();
    if (pos < text.size() && text[pos] == '|') {
      if (pos + 1 < text.size() && text[pos + 1] == '|')
        return false;
      ++pos;
      return true;
    }
    return false;
  }

  void expect(const std::string &token) {
    if (!consume(token)) {
      throw std::runtime_error("Expected '" + token +
                               "' in conditional expression.");
    }
  }

  std::string parseIdentifier() {
    skipWhitespace();
    if (pos >= text.size() || !isIdentifierStart(text[pos])) {
      throw std::runtime_error(
          "Expected identifier in conditional expression.");
    }
    size_t start = pos++;
    while (pos < text.size() && isIdentifierChar(text[pos])) {
      ++pos;
    }
    return text.substr(start, pos - start);
  }

  long long parseNumber() {
    skipWhitespace();
    size_t start = pos;
    if (pos < text.size() && text[pos] == '0' && pos + 1 < text.size() &&
        (text[pos + 1] == 'x' || text[pos + 1] == 'X')) {
      pos += 2;
      size_t digitsStart = pos;
      while (pos < text.size() &&
             std::isxdigit(static_cast<unsigned char>(text[pos]))) {
        ++pos;
      }
      if (digitsStart == pos)
        throw std::runtime_error("Invalid hexadecimal literal in conditional.");
    } else if (pos < text.size() && text[pos] == '0' && pos + 1 < text.size() &&
               (text[pos + 1] == 'b' || text[pos + 1] == 'B')) {
      pos += 2;
      size_t digitsStart = pos;
      while (pos < text.size() && (text[pos] == '0' || text[pos] == '1')) {
        ++pos;
      }
      if (digitsStart == pos)
        throw std::runtime_error("Invalid binary literal in conditional.");
      std::string digits = text.substr(digitsStart, pos - digitsStart);
      long long value = 0;
      for (char c : digits) {
        value = (value << 1) | (c - '0');
      }
      while (pos < text.size() && (text[pos] == 'u' || text[pos] == 'U' ||
                                   text[pos] == 'l' || text[pos] == 'L')) {
        ++pos;
      }
      return value;
    } else {
      size_t digitsStart = pos;
      while (pos < text.size() &&
             std::isdigit(static_cast<unsigned char>(text[pos]))) {
        ++pos;
      }
      if (digitsStart == pos)
        throw std::runtime_error("Invalid integer literal in conditional.");
    }
    size_t endDigits = pos;
    while (pos < text.size() && (text[pos] == 'u' || text[pos] == 'U' ||
                                 text[pos] == 'l' || text[pos] == 'L')) {
      ++pos;
    }
    std::string literal = text.substr(start, endDigits - start);
    int base = 10;
    if (literal.size() > 2 && literal[0] == '0' &&
        (literal[1] == 'x' || literal[1] == 'X')) {
      base = 16;
    } else if (literal.size() > 1 && literal[0] == '0') {
      base = 8;
    }
    try {
      return std::stoll(literal, nullptr, base);
    } catch (...) {
      throw std::runtime_error("Invalid numeric literal in conditional.");
    }
  }

  long long evaluateMacro(const std::string &name) {
    auto it = macros.find(name);
    if (it == macros.end())
      return 0;
    if (depth >= kMaxDepth) {
      throw std::runtime_error(
          "Macro expansion depth exceeded in conditional expression.");
    }
    std::string replacement = trim(it->second);
    if (replacement.empty())
      return 0;
    ExpressionParser nested(replacement, macros, depth + 1);
    return nested.parse();
  }

  long long parsePrimary() {
    skipWhitespace();
    if (consume("(")) {
      long long value = parseLogicalOr();
      expect(")");
      return value;
    }
    if (consume("defined")) {
      bool hasParen = consume("(");
      std::string name = parseIdentifier();
      if (hasParen)
        expect(")");
      return macros.find(name) != macros.end() ? 1 : 0;
    }
    if (pos < text.size() &&
        std::isdigit(static_cast<unsigned char>(text[pos]))) {
      return parseNumber();
    }
    if (pos < text.size() && isIdentifierStart(text[pos])) {
      std::string name = parseIdentifier();
      return evaluateMacro(name);
    }
    throw std::runtime_error("Unexpected token in conditional expression: " +
                             text.substr(pos));
  }

  long long parseUnary() {
    if (consume("!"))
      return parseUnary() == 0 ? 1 : 0;
    if (consume("~"))
      return ~parseUnary();
    if (consume("+"))
      return parseUnary();
    if (consume("-"))
      return -parseUnary();
    return parsePrimary();
  }

  long long parseMultiplicative() {
    long long value = parseUnary();
    while (true) {
      if (consume("*")) {
        value *= parseUnary();
      } else if (consume("/")) {
        long long rhs = parseUnary();
        if (rhs == 0)
          throw std::runtime_error(
              "Division by zero in conditional expression.");
        value /= rhs;
      } else if (consume("%")) {
        long long rhs = parseUnary();
        if (rhs == 0)
          throw std::runtime_error("Modulo by zero in conditional expression.");
        value %= rhs;
      } else {
        break;
      }
    }
    return value;
  }

  long long parseAdditive() {
    long long value = parseMultiplicative();
    while (true) {
      if (consume("+")) {
        value += parseMultiplicative();
      } else if (consume("-")) {
        value -= parseMultiplicative();
      } else {
        break;
      }
    }
    return value;
  }

  long long parseShift() {
    long long value = parseAdditive();
    while (true) {
      if (consume("<<")) {
        value <<= parseAdditive();
      } else if (consume(">>")) {
        value >>= parseAdditive();
      } else {
        break;
      }
    }
    return value;
  }

  long long parseRelational() {
    long long value = parseShift();
    while (true) {
      if (consume("<=")) {
        value = (value <= parseShift()) ? 1 : 0;
      } else if (consume(">=")) {
        value = (value >= parseShift()) ? 1 : 0;
      } else if (consume("<")) {
        value = (value < parseShift()) ? 1 : 0;
      } else if (consume(">")) {
        value = (value > parseShift()) ? 1 : 0;
      } else {
        break;
      }
    }
    return value;
  }

  long long parseEquality() {
    long long value = parseRelational();
    while (true) {
      if (consume("==")) {
        value = (value == parseRelational()) ? 1 : 0;
      } else if (consume("!=")) {
        value = (value != parseRelational()) ? 1 : 0;
      } else {
        break;
      }
    }
    return value;
  }

  long long parseBitwiseAnd() {
    long long value = parseEquality();
    while (consumeBitwiseAndOperator()) {
      value &= parseEquality();
    }
    return value;
  }

  long long parseBitwiseXor() {
    long long value = parseBitwiseAnd();
    while (consume("^")) {
      value ^= parseBitwiseAnd();
    }
    return value;
  }

  long long parseBitwiseOr() {
    long long value = parseBitwiseXor();
    while (consumeBitwiseOrOperator()) {
      value |= parseBitwiseXor();
    }
    return value;
  }

  long long parseLogicalAnd() {
    long long value = parseBitwiseOr();
    while (consume("&&")) {
      value = (value != 0 && parseBitwiseOr() != 0) ? 1 : 0;
    }
    return value;
  }

  long long parseLogicalOr() {
    long long value = parseLogicalAnd();
    while (consume("||")) {
      value = (value != 0 || parseLogicalAnd() != 0) ? 1 : 0;
    }
    return value;
  }
};

} // namespace

ConditionalProcessor::ConditionalProcessor() { stateStack.push({true, false}); }

bool ConditionalProcessor::isConditionalDirective(const std::string &line) {
  std::string trimmed = trim(line);
  return !trimmed.empty() && trimmed[0] == '#';
}

void ConditionalProcessor::recordMacro(const std::string &line) {
  std::string trimmed = trim(line);
  if (trimmed.rfind("#define", 0) == 0) {
    std::string remainder = trim(trimmed.substr(7));
    if (remainder.empty())
      return;
    std::istringstream iss(remainder);
    std::string name;
    iss >> name;
    size_t parenPos = name.find('(');
    if (parenPos != std::string::npos)
      name = name.substr(0, parenPos);
    if (name.empty())
      return;
    std::string replacement;
    std::getline(iss, replacement);
    macroDefinitions[name] = trim(replacement);
  } else if (trimmed.rfind("#undef", 0) == 0) {
    std::string name = trim(trimmed.substr(6));
    size_t parenPos = name.find('(');
    if (parenPos != std::string::npos)
      name = name.substr(0, parenPos);
    if (!name.empty())
      macroDefinitions.erase(name);
  }
}

std::string
ConditionalProcessor::processNonConditionalDirective(const std::string &line) {
  if (stateStack.empty() || !stateStack.top().active)
    return "";
  recordMacro(line);
  return line;
}

long long ConditionalProcessor::evaluateExpression(const std::string &expr) {
  ExpressionParser parser(expr, macroDefinitions);
  return parser.parse();
}

std::string ConditionalProcessor::processLine(const std::string &line) {
  std::string trimmed = trim(line);
  if (trimmed.empty())
    return stateStack.top().active ? line : "";
  if (trimmed[0] != '#')
    return stateStack.top().active ? line : "";

  std::istringstream iss(trimmed);
  std::string directive;
  iss >> directive;

  bool parentActive = stateStack.top().active;

  if (directive == "#define" || directive == "#undef") {
    if (parentActive)
      recordMacro(line);
    return parentActive ? line : "";
  }

  if (directive == "#if") {
    std::string expr;
    std::getline(iss, expr);
    long long result = evaluateExpression(expr);
    bool conditionTrue = (result != 0);
    bool branchActive = conditionTrue && parentActive;
    stateStack.push({branchActive, conditionTrue});
    return "";
  }

  if (directive == "#ifdef") {
    std::string name;
    iss >> name;
    name = trim(name);
    if (name.empty())
      throw std::runtime_error("#ifdef without macro name.");
    bool conditionTrue = macroDefinitions.find(name) != macroDefinitions.end();
    bool branchActive = conditionTrue && parentActive;
    stateStack.push({branchActive, conditionTrue});
    return "";
  }

  if (directive == "#ifndef") {
    std::string name;
    iss >> name;
    name = trim(name);
    if (name.empty())
      throw std::runtime_error("#ifndef without macro name.");
    bool conditionTrue = macroDefinitions.find(name) == macroDefinitions.end();
    bool branchActive = conditionTrue && parentActive;
    stateStack.push({branchActive, conditionTrue});
    return "";
  }

  if (directive == "#elif") {
    if (stateStack.size() <= 1)
      throw std::runtime_error("#elif without matching #if");
    ConditionalState prev = stateStack.top();
    stateStack.pop();
    std::string expr;
    std::getline(iss, expr);
    long long result = evaluateExpression(expr);
    bool conditionTrue = (result != 0);
    bool branchActive =
        (!prev.taken) && conditionTrue && stateStack.top().active;
    bool taken = prev.taken || conditionTrue;
    stateStack.push({branchActive, taken});
    return "";
  }

  if (directive == "#else") {
    if (stateStack.size() <= 1)
      throw std::runtime_error("#else without matching #if");
    ConditionalState prev = stateStack.top();
    stateStack.pop();
    bool branchActive = (!prev.taken) && stateStack.top().active;
    stateStack.push({branchActive, true});
    return "";
  }

  if (directive == "#endif") {
    if (stateStack.size() <= 1)
      throw std::runtime_error("#endif without matching #if");
    stateStack.pop();
    return "";
  }

  if (directive == "#line") {
    return parentActive ? line : "";
  }

  // Unknown directive – ignore.
  return "";
}

void ConditionalProcessor::verifyBalanced() const {
  if (stateStack.size() != 1) {
    throw std::runtime_error(
        "Preprocessor Error: Unmatched conditional directives.");
  }
}
