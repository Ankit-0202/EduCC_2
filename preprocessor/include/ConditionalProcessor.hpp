#ifndef CONDITIONAL_PROCESSOR_HPP
#define CONDITIONAL_PROCESSOR_HPP

#include <stack>
#include <string>
#include <unordered_map>

class ConditionalProcessor {
public:
  ConditionalProcessor();

  // Process a line that starts with a conditional directive.
  // Returns an empty string if the line should be omitted,
  // or the line (or modified line) if it should be kept.
  // This function should update the internal conditional state.
  std::string processLine(const std::string &line);

  // After processing the entire file, check that all conditionals are closed.
  void verifyBalanced() const;

private:
  // A simple state stack for conditionals.
  struct ConditionalState {
    bool active; // Is the current block active (i.e. being included)?
    bool taken;  // Has a true branch been taken?
  };

  std::stack<ConditionalState> stateStack;

  // Evaluate a constant expression (a very naive implementation that supports
  // only integer literals and basic operators).
  int evaluateExpression(const std::string &expr);

  // Helper to check if a line is a conditional directive.
  bool isConditionalDirective(const std::string &line);

  // Process a directive that is not conditional.
  std::string processNonConditionalDirective(const std::string &line);
};

#endif // CONDITIONAL_PROCESSOR_HPP
