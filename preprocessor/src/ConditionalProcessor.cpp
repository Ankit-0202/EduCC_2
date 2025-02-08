#include "ConditionalProcessor.hpp"
#include <sstream>
#include <stdexcept>
#include <regex>
#include <cctype>

ConditionalProcessor::ConditionalProcessor() {
    // Start with a default active state.
    stateStack.push({true, false});
}

bool ConditionalProcessor::isConditionalDirective(const std::string &line) {
    std::string trimmed = line;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    return trimmed.compare(0, 1, "#") == 0;
}

int ConditionalProcessor::evaluateExpression(const std::string &expr) {
    // VERY simplified: assume the expression is a single integer literal.
    // A full implementation would parse and evaluate a complete constant expression.
    return std::stoi(expr);
}

std::string ConditionalProcessor::processNonConditionalDirective(const std::string &line) {
    // For now, simply return an empty string (we remove these lines).
    return "";
}

std::string ConditionalProcessor::processLine(const std::string &line) {
    std::string trimmed = line;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    if (trimmed.empty()) return line; // blank line
    
    if (trimmed[0] != '#') {
        // Not a directive: include the line only if the current state is active.
        return stateStack.top().active ? line : "";
    }
    
    // It is a directive.
    std::istringstream iss(trimmed);
    std::string directive;
    iss >> directive;
    
    if (directive == "#if") {
        std::string expr;
        std::getline(iss, expr);
        expr = expr.substr(expr.find_first_not_of(" \t"));
        int result = evaluateExpression(expr);
        bool active = (result != 0) && stateStack.top().active;
        stateStack.push({active, active});
        return "";
    } else if (directive == "#ifdef") {
        // For simplicity, we do not support macro evaluation here.
        // Assume undefined.
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
        ConditionalState prev = stateStack.top();
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
        ConditionalState prev = stateStack.top();
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
        // Other directives (such as #include, #define, etc.) are handled elsewhere.
        return processNonConditionalDirective(line);
    }
}

void ConditionalProcessor::verifyBalanced() const {
    if (stateStack.size() != 1)
        throw std::runtime_error("Unterminated conditional directives detected.");
}
