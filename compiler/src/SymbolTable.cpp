#include "SymbolTable.hpp"

// Constructor: Initialize with a global scope.
SymbolTable::SymbolTable() { enterScope(); }

// Enter a new scope by pushing a new map.
void SymbolTable::enterScope() { scopes.emplace_back(); }

// Exit the current scope by popping the last map.
void SymbolTable::exitScope() {
  if (!scopes.empty()) {
    scopes.pop_back();
  } else {
    throw std::runtime_error("SymbolTable Error: No scope to exit.");
  }
}

// Declare a new symbol in the current (innermost) scope.
bool SymbolTable::declare(const Symbol &symbol) {
  if (scopes.empty()) {
    throw std::runtime_error(
        "SymbolTable Error: No active scope to declare symbol.");
  }
  auto &currentScope = scopes.back();

  // Attempt to insert symbol
  auto result = currentScope.emplace(symbol.name, symbol);
  return result
      .second; // true if inserted, false if already exists in this scope
}

std::optional<Symbol> SymbolTable::lookup(const std::string &name) const {
  // Search from innermost scope outward
  for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
    const auto &scope = *it;
    auto found = scope.find(name);
    if (found != scope.end()) {
      return found->second;
    }
  }
  return std::nullopt;
}

// Check if a symbol exists (in any scope).
bool SymbolTable::contains(const std::string &name) const {
  return lookup(name).has_value();
}

// Get the LLVM Value associated with a symbol.
llvm::Value *SymbolTable::get(const std::string &name) const {
  auto it = namedValues.find(name);
  if (it != namedValues.end()) {
    return it->second;
  }
  throw std::runtime_error("SymbolTable Error: LLVM Value for symbol '" + name +
                           "' not found.");
}

// Add an LLVM Value to the symbol table.
void SymbolTable::add(const std::string &name, llvm::Value *value) {
  namedValues[name] = value;
}

// New method: remove a symbol from the innermost scope that contains it.
void SymbolTable::remove(const std::string &name) {
  for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
    if (it->erase(name) > 0) {
      return;
    }
  }
}
