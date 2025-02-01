#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP

#include "AST.hpp"
#include "SymbolTable.hpp"
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

class CodeGenerator {
public:
    CodeGenerator();
    std::unique_ptr<llvm::Module> generateCode(const std::shared_ptr<Program>& program);
private:
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    std::unique_ptr<llvm::Module> module;
    std::unordered_map<std::string, llvm::Value*> localVariables;
    llvm::Type* getLLVMType(const std::string& type);
    bool generateStatement(const StatementPtr& stmt);
    llvm::Value* generateExpression(const std::shared_ptr<Expression>& expr);
    void generateFunction(const std::shared_ptr<FunctionDeclaration>& funcDecl);
    void generateVariableDeclarationStatement(const std::shared_ptr<VariableDeclarationStatement>& varDeclStmt);
};

#endif // CODE_GENERATOR_HPP
