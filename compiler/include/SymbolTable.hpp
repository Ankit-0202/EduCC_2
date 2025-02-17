#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <llvm/IR/Value.h>

#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

/*
 * Structure to represent a symbol (variable or function).
 *
 * Fields:
 *  - name
 *  - type: e.g. "int", "float", etc. (for variables/functions)
 *  - isFunction: true if this symbol is a function
 *  - parameterTypes: if isFunction == true, the list of parameter types
 *  - isDefined: if isFunction == true, indicates whether the function already
 * has a body
 */
struct Symbol {
  std::string name;
  std::string type;
  bool isFunction;
  std::vector<std::string> parameterTypes;
  bool isDefined; // <== NEW: only relevant if isFunction == true

  // Constructors
  // For a variable:
  Symbol(const std::string &nm, const std::string &ty)
      : name(nm), type(ty), isFunction(false), isDefined(false) {}

  // For a function:
  Symbol(const std::string &nm, const std::string &ty, bool func,
         const std::vector<std::string> &params, bool defined)
      : name(nm), type(ty), isFunction(func), parameterTypes(params),
        isDefined(defined) {}
};

// SymbolTable class that manages scopes and symbols
class SymbolTable {
public:
  SymbolTable();

  // Scope management.
  void enterScope();
  void exitScope();

  // Declare a new symbol in the current (innermost) scope.
  bool declare(const Symbol &symbol);

  // Look up a symbol by name from innermost to outermost scope.
  std::optional<Symbol> lookup(const std::string &name) const;

  // Check if a symbol exists (in any scope).
  bool contains(const std::string &name) const;

  // Get the LLVM Value associated with a symbol.
  llvm::Value *get(const std::string &name) const;

  // Add an LLVM Value to the symbol table.
  void add(const std::string &name, llvm::Value *value);

  // Remove a symbol from the innermost scope that contains it.
  void remove(const std::string &name);

private:
  // Each scope is a mapping from symbol name to Symbol.
  std::vector<std::unordered_map<std::string, Symbol>> scopes;

  // Mapping for LLVM Values associated with symbols.
  std::unordered_map<std::string, llvm::Value *> namedValues;
};

#endif // SYMBOL_TABLE_HPP
