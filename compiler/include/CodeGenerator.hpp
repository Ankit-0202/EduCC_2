#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include "AST.hpp"
#include "SymbolTable.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class CodeGenerator {
public:
  llvm::LLVMContext context;
  llvm::IRBuilder<> builder;
  std::unique_ptr<llvm::Module> module;

  // Maps for variable lookups and type tracking.
  std::unordered_map<std::string, llvm::Value *> localVariables;
  std::unordered_map<std::string, llvm::Type *> declaredTypes;
  std::unordered_map<std::string, std::string> declaredTypeStrings;

  // Local scope management stacks.
  // localVarStack: maps variable names to their alloca pointers.
  std::vector<std::unordered_map<std::string, llvm::Value *>> localVarStack;
  // declaredVarStack: tracks variable names declared in each scope.
  std::vector<std::unordered_set<std::string>> declaredVarStack;

  CodeGenerator();

  // Generates an LLVM module from the AST.
  std::unique_ptr<llvm::Module>
  generateCode(const std::shared_ptr<Program> &program);

  // Returns the LLVM type corresponding to a source-level type string.
  llvm::Type *getLLVMType(const std::string &type);

  // Gets or creates an LLVM function in the module.
  llvm::Function *
  getOrCreateFunctionInModule(const std::string &name, llvm::Type *returnType,
                              const std::vector<llvm::Type *> &paramTypes,
                              bool isDefinition);

  // Generates code for a function declaration.
  llvm::Function *
  generateFunction(const std::shared_ptr<FunctionDeclaration> &funcDecl);

  // Code generation for statements and expressions.
  bool generateStatement(const StatementPtr &stmt);
  llvm::Value *generateExpression(const ExpressionPtr &expr);
  llvm::Value *generateLValue(const ExpressionPtr &expr);
  void generateVariableDeclarationStatement(
      const std::shared_ptr<VariableDeclarationStatement> &varDeclStmt);

  // Local scope management.
  void pushLocalScope();
  void popLocalScope();
  llvm::Value *lookupLocalVar(const std::string &name);
};

#endif // CODEGENERATOR_HPP
