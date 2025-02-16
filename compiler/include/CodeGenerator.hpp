#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP

#include "AST.hpp"
#include "SymbolTable.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

/*
 * CodeGenerator class:
 *   - Converts the AST (Program) into an LLVM Module.
 *   - Merges repeated prototypes for the same function.
 *   - Generates an IR "declare" for prototypes and a "define" for the actual
 * body.
 */
class CodeGenerator {
public:
  CodeGenerator();

  // Generates LLVM IR from the AST.
  std::unique_ptr<llvm::Module>
  generateCode(const std::shared_ptr<Program> &program);

  // Returns the LLVM type for a given C type name.
  llvm::Type *getLLVMType(const std::string &type);

  // Expression generation routines.
  llvm::Value *generateExpression(const ExpressionPtr &expr);
  llvm::Value *generateLValue(const ExpressionPtr &expr);

  // Statement generation routine.
  bool generateStatement(const StatementPtr &stmt);

  // Generates a local variable declaration statement.
  void generateVariableDeclarationStatement(
      const std::shared_ptr<VariableDeclarationStatement> &varDeclStmt);

  // If a function is being defined, this routine either creates or returns an
  // existing function in the module.
  llvm::Function *
  getOrCreateFunctionInModule(const std::string &name, llvm::Type *returnType,
                              const std::vector<llvm::Type *> &paramTypes,
                              bool isDefinition);

  // NEW: Declaration for function generation.
  llvm::Function *
  generateFunction(const std::shared_ptr<FunctionDeclaration> &funcDecl);

  // Expose context and module for convenience.
  llvm::LLVMContext context;
  llvm::IRBuilder<> builder;
  std::unique_ptr<llvm::Module> module;

  // Map of local variable names to their alloca instructions.
  std::unordered_map<std::string, llvm::Value *> localVariables;
  std::unordered_map<std::string, llvm::Type *> declaredTypes;
  std::unordered_map<std::string, std::string> declaredTypeStrings;
};

#endif // CODE_GENERATOR_HPP
