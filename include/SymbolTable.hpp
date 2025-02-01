#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

// IMPORTANT: Ensure your compile flags include the correct LLVM include path,
// for example: -I/opt/homebrew/opt/llvm/include
#include <llvm/IR/Value.h>

#include <unordered_map>
#include <vector>
#include <string>
#include <optional>
#include <stdexcept>

// Structure to represent a symbol (variable or function)
struct Symbol {
    std::string name;
    std::string type; // e.g., "int", "float"
    bool isFunction;
    std::vector<std::string> parameterTypes; // Only used for functions

    // Constructor
    Symbol(const std::string& nm, const std::string& ty, bool func = false, const std::vector<std::string>& params = {})
        : name(nm), type(ty), isFunction(func), parameterTypes(params) {}
};

// SymbolTable class that manages scopes and symbols
class SymbolTable {
public:
    SymbolTable();

    // Enter a new scope
    void enterScope();

    // Exit the current scope
    void exitScope();

    // Declare a new symbol in the current scope
    bool declare(const Symbol& symbol);

    // Lookup a symbol starting from the current scope up to global
    std::optional<Symbol> lookup(const std::string& name) const;

    // Check if a symbol exists (search all scopes)
    bool contains(const std::string& name) const;

    // Get the LLVM Value associated with a symbol
    llvm::Value* get(const std::string& name) const;

    // Add an LLVM Value to the symbol table
    void add(const std::string& name, llvm::Value* value);

private:
    // Each scope is a map from symbol name to Symbol
    std::vector<std::unordered_map<std::string, Symbol>> scopes;

    // Map to hold LLVM Values for variables
    std::unordered_map<std::string, llvm::Value*> namedValues;
};

#endif // SYMBOL_TABLE_HPP
