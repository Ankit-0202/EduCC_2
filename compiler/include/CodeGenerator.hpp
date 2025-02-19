#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include "AST.hpp"
#include "SymbolTable.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class CodeGenerator {
public:
  CodeGenerator();

  // Generate LLVM IR for the given AST.
  std::unique_ptr<llvm::Module>
  generateCode(const std::shared_ptr<Program> &program);

  // Expression code generation.
  llvm::Value *generateExpression(const ExpressionPtr &expr);
  llvm::Value *generateLValue(const ExpressionPtr &expr);

  // Statement code generation.
  bool generateStatement(const StatementPtr &stmt);

  // Helper: generate IR for a local variable declaration.
  void generateVariableDeclaration(
      const std::shared_ptr<VariableDeclaration> &varDecl);

  // Get the LLVM type corresponding to a C type string.
  llvm::Type *getLLVMType(const std::string &type);

  // Generate IR for a function.
  llvm::Function *
  generateFunction(const std::shared_ptr<FunctionDeclaration> &funcDecl);

  // Get or create a function in the module.
  llvm::Function *
  getOrCreateFunctionInModule(const std::string &name, llvm::Type *returnType,
                              const std::vector<llvm::Type *> &paramTypes,
                              bool isDefinition);

  // Local scope management.
  void pushLocalScope();
  void popLocalScope();
  llvm::Value *lookupLocalVar(const std::string &name);

  // Members used for code generation.
  llvm::LLVMContext context;
  llvm::IRBuilder<> builder;
  std::unique_ptr<llvm::Module> module;

  // Local variable management.
  std::vector<std::unordered_map<std::string, llvm::Value *>> localVarStack;
  std::vector<std::unordered_set<std::string>> declaredVarStack;
  std::unordered_map<std::string, llvm::Type *> declaredTypes;
  std::unordered_map<std::string, std::string> declaredTypeStrings;

  // For function parameters allocation.
  std::unordered_map<std::string, llvm::Value *> localVariables;
};

#endif // CODEGENERATOR_HPP
