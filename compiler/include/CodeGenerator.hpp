#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include "AST.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <memory>
#include <string>
#include <unordered_map>

/*
 * CodeGenerator class:
 *   - Converts the AST (Program) into an LLVM Module.
 *   - Merges repeated prototypes for the same function.
 *   - Generates an IR "declare" for prototypes and a "define" for the actual
 * body.
 */
class CodeGenerator {
public:
  llvm::LLVMContext context;
  llvm::IRBuilder<> builder;
  std::unique_ptr<llvm::Module> module;

  // Map of local variables (name -> alloca)
  std::unordered_map<std::string, llvm::Value*> localVariables;

  CodeGenerator();

  // Entry point
  std::unique_ptr<llvm::Module> generateCode(const std::shared_ptr<Program> &program);

  // Returns the LLVM type corresponding to the given string type.
  llvm::Type *getLLVMType(const std::string &type);

  // Returns a pointer to an lvalue for assignment.
  llvm::Value *generateLValue(const ExpressionPtr &expr);

  // Generates code for an expression.
  llvm::Value *generateExpression(const ExpressionPtr &expr);

  // Generates code for a statement; returns true if the statement terminates.
  bool generateStatement(const StatementPtr &stmt);

  // Generates code for a variable declaration statement.
  void generateVariableDeclarationStatement(const std::shared_ptr<VariableDeclarationStatement> &varDeclStmt);

  // Generates a function declaration/definition.
  void generateFunction(const std::shared_ptr<FunctionDeclaration> &funcDecl);

  // Helper: get or create a function in the module.
  llvm::Function *getOrCreateFunctionInModule(const std::string &name, llvm::Type *returnType,
                                                const std::vector<llvm::Type *> &paramTypes,
                                                bool isDefinition);
};

#endif // CODEGENERATOR_HPP
