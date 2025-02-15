#ifndef CONDITIONAL_PROCESSOR_HPP
#define CONDITIONAL_PROCESSOR_HPP

#include <string>
#include <stack>
#include <unordered_map>

// Structure to hold the state for conditional directives.
struct ConditionalState {
  bool active;
  bool taken;
};

class ConditionalProcessor {
public:
  ConditionalProcessor();

  // Checks if a line is any preprocessor directive (starting with '#').
  bool isConditionalDirective(const std::string &line);

  // Process a given line (handles conditional directives and passes through non-conditionals).
  std::string processLine(const std::string &line);

  // Process non-conditional directives (e.g. #define, #undef).
  std::string processNonConditionalDirective(const std::string &line);

  // Verify that all conditionals have been closed.
  void verifyBalanced() const;

  // Evaluate a constant expression (very simplified).
  int evaluateExpression(const std::string &expr);

private:
  // Record simple macro definitions for conditionals.
  void recordMacro(const std::string &line);

  // Stack that holds the current conditional state.
  std::stack<ConditionalState> stateStack;

  // Map to hold macro definitions (for simple cases) used in conditionals.
  std::unordered_map<std::string, std::string> macroDefinitions;
};

#endif // CONDITIONAL_PROCESSOR_HPP
