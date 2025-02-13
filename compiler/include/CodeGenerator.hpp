#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include "AST.hpp"
#include "SymbolTable.hpp"
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

/*
 * CodeGenerator class:
 *   - Converts the AST (Program) into an LLVM Module.
 *   - Merges repeated prototypes for the same function.
 *   - Generates an IR "declare" for prototypes and a "define" for the actual body.
 */
class CodeGenerator {
public:
    CodeGenerator();
    // Main entry: generate IR module from a top-level AST Program
    std::unique_ptr<llvm::Module> generateCode(const std::shared_ptr<Program>& program);

private:
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    std::unique_ptr<llvm::Module> module;

    // Map for local variables.
    std::unordered_map<std::string, llvm::Value*> localVariables;

    // Create or fetch a function in the module, ensuring
    // a single IR function matches the signature. 
    // 'isDefinition = false' => we produce (or unify) a 'declare'
    // 'isDefinition = true'  => we produce (or unify) a 'define'
    llvm::Function* getOrCreateFunctionInModule(
        const std::string& name, 
        llvm::Type* returnType,                     
        const std::vector<llvm::Type*>& paramTypes,
        bool isDefinition
    );

    // Convert a string type ("int", "float", etc.) to an LLVM Type*
    llvm::Type* getLLVMType(const std::string& type);

    // Generate code for a top-level function (prototype or definition)
    void generateFunction(const std::shared_ptr<FunctionDeclaration>& funcDecl);

    // Generate code for statements
    bool generateStatement(const std::shared_ptr<Statement>& stmt);

    // Generate code for expressions
    llvm::Value* generateExpression(const std::shared_ptr<Expression>& expr);

    // For local variable declarations (e.g. "int x = 5;" inside a function)
    void generateVariableDeclarationStatement(
        const std::shared_ptr<VariableDeclarationStatement>& varDeclStmt
    );

    llvm::Value* generateLValue(const std::shared_ptr<Expression>& expr);
};

#endif // CODEGENERATOR_HPP
