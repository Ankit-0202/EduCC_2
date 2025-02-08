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

/*
 * Structure to represent a symbol (variable or function).
 * 
 * Fields:
 *  - name
 *  - type: e.g. "int", "float", etc. (for variables/functions)
 *  - isFunction: true if this symbol is a function
 *  - parameterTypes: if isFunction == true, the list of parameter types
 *  - isDefined: if isFunction == true, indicates whether the function already has a body
 */
struct Symbol {
    std::string name;
    std::string type; 
    bool isFunction;
    std::vector<std::string> parameterTypes; 
    bool isDefined; // <== NEW: only relevant if isFunction == true

    // Constructors
    // For a variable:
    Symbol(const std::string& nm, const std::string& ty)
        : name(nm), type(ty), isFunction(false), isDefined(false) {}
    
    // For a function:
    Symbol(const std::string& nm, const std::string& ty,
           bool func, const std::vector<std::string>& params,
           bool defined)
        : name(nm), type(ty), isFunction(func),
          parameterTypes(params), isDefined(defined) {}
};

// SymbolTable class that manages scopes and symbols
class SymbolTable {
public:
    SymbolTable();

    // Enter a new scope
    void enterScope();

    // Exit the current scope
    void exitScope();

    // Declare a new symbol in the current scope.
    // Returns false if a symbol with the same name already exists in this scope.
    bool declare(const Symbol& symbol);

    // Lookup a symbol starting from the current scope up to global
    std::optional<Symbol> lookup(const std::string& name) const;

    // Check if a symbol exists (search all scopes)
    bool contains(const std::string& name) const;

    // Get or set the LLVM Value associated with a symbol
    llvm::Value* get(const std::string& name) const;
    void add(const std::string& name, llvm::Value* value);

private:
    // Each scope is a map from symbol name -> Symbol
    std::vector<std::unordered_map<std::string, Symbol>> scopes;

    // Map to hold LLVM Values for variables
    std::unordered_map<std::string, llvm::Value*> namedValues;
};

#endif // SYMBOL_TABLE_HPP
