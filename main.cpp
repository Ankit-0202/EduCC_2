#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Preprocessor.hpp"
#include "SemanticAnalyzer.hpp"
#include "TokenUtils.hpp"

#include <fstream>
#include <iostream>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <sstream>
#include <string>
#include <system_error>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: C99Compiler <source_file.c> [optional output.ll]\n";
    return 1;
  }

  std::string sourcePath = argv[1];
  std::string outFile = "output.ll";
  if (argc >= 3) {
    outFile = argv[2];
  }

  // --- Step 0: Read and dump the original source ---
  std::ifstream srcFile(sourcePath);
  if (!srcFile.is_open()) {
    std::cerr << "Error: Could not open source file: " << sourcePath << "\n";
    return 1;
  }
  std::stringstream srcBuffer;
  srcBuffer << srcFile.rdbuf();
  std::string originalSource = srcBuffer.str();
  std::cout << "===== Original Source =====\n";
  std::cout << originalSource << "\n";
  std::cout << "===========================\n\n";

  /*
   * Step 1: Preprocessing
   */
  // Update systemPaths to include the Xcode SDK header path.
  std::vector<std::string> systemPaths = {
      "/usr/include", "/usr/local/include",
      "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/"
      "Developer/SDKs/MacOSX.sdk/usr/include" // <- using Xcode SDK path
  };
  std::vector<std::string> userPaths = {"."};

  Preprocessor preprocessor(systemPaths, userPaths);
  std::string preprocessedSource;
  try {
    preprocessedSource = preprocessor.preprocess(sourcePath);
  } catch (const std::exception &e) {
    std::cerr << "Preprocessing Error: " << e.what() << "\n";
    return 1;
  }

  std::cout << "===== Preprocessed Source =====\n";
  std::cout << preprocessedSource << "\n";
  std::cout << "================================\n\n";

  /*
   * Step 2: Lexing
   */
  Lexer lexer(preprocessedSource);
  std::vector<Token> tokens;
  try {
    tokens = lexer.tokenize();
  } catch (const std::exception &e) {
    std::cerr << "Lexer Error: " << e.what() << "\n";
    return 1;
  }

  std::cout << "===== Token Stream =====\n";
  for (const auto &token : tokens) {
    std::cout << "Type: " << tokenTypeToString(token.type) << ", Lexeme: '"
              << token.lexeme << "', Line: " << token.line
              << ", Column: " << token.column << "\n";
  }
  std::cout << "========================\n\n";

  /*
   * Step 3: Parsing
   */
  Parser parser(tokens);
  std::shared_ptr<Program> ast;
  try {
    ast = parser.parse();
  } catch (const std::exception &e) {
    std::cerr << "Parser Error: " << e.what() << "\n";
    return 1;
  }

  // (Optional: If you have a function to dump the AST, print it here.)
  // std::cout << "===== AST Dump =====\n";
  // ast->print(std::cout);
  // std::cout << "====================\n\n";

  /*
   * Step 4: Semantic Analysis
   */
  SemanticAnalyzer semanticAnalyzer;
  try {
    semanticAnalyzer.analyze(ast);
    std::cout << "Semantic analysis completed successfully.\n";
  } catch (const std::exception &e) {
    std::cerr << "Semantic Analysis Error: " << e.what() << "\n";
    return 1;
  }

  /*
   * Step 5: Code Generation (LLVM IR)
   */
  CodeGenerator codeGen;
  try {
    std::unique_ptr<llvm::Module> module = codeGen.generateCode(ast);
    std::error_code EC;
    llvm::raw_fd_ostream dest(outFile, EC,
                              static_cast<llvm::sys::fs::OpenFlags>(0));
    if (EC) {
      std::cerr << "Could not open output file: " << EC.message() << "\n";
      return 1;
    }
    module->print(dest, nullptr);
    dest.flush();
    std::cout << "LLVM IR generated and written to '" << outFile << "'.\n";
  } catch (const std::exception &e) {
    std::cerr << "Code Generation Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
