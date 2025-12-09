#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "Debug.hpp"
#include "Lexer.hpp"
#include "Linker.hpp"
#include "Parser.hpp"
#include "Preprocessor.hpp"
#include "SemanticAnalyzer.hpp"

#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <llvm/Config/llvm-config.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/TargetParser/Triple.h>
#include <sstream>
#include <string>
#include <system_error>
#include <vector>

static void appendIncludePathIfExists(std::vector<std::string> &paths,
                                      const std::string &candidate) {
  if (candidate.empty())
    return;
  namespace fs = std::filesystem;
  std::error_code ec;
  if (fs::exists(candidate, ec) && fs::is_directory(candidate, ec) &&
      std::find(paths.begin(), paths.end(), candidate) == paths.end()) {
    paths.push_back(candidate);
  }
}

static void appendIncludePathsFromEnv(std::vector<std::string> &paths,
                                      const char *envVar) {
  if (!envVar)
    return;
  const char *raw = std::getenv(envVar);
  if (!raw || !*raw)
    return;
  std::string value(raw);
  std::stringstream ss(value);
  std::string item;
  while (std::getline(ss, item, ':')) {
    appendIncludePathIfExists(paths, item);
  }
}

static std::vector<std::string> defaultSystemIncludePaths() {
  std::vector<std::string> paths;
  appendIncludePathIfExists(paths, "/usr/include");
  appendIncludePathIfExists(paths, "/usr/local/include");

  appendIncludePathsFromEnv(paths, "CPATH");
  appendIncludePathsFromEnv(paths, "C_INCLUDE_PATH");
  appendIncludePathsFromEnv(paths, "CPLUS_INCLUDE_PATH");

#ifdef __APPLE__
  const char *sdkRoot = std::getenv("SDKROOT");
  if (sdkRoot && *sdkRoot) {
    appendIncludePathIfExists(paths, std::string(sdkRoot) + "/usr/include");
  }

  const char *developerDir = std::getenv("DEVELOPER_DIR");
  if (developerDir && *developerDir) {
    appendIncludePathIfExists(
        paths,
        std::string(developerDir) +
            "/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include");
    appendIncludePathIfExists(paths,
                              std::string(developerDir) + "/usr/include");
  }

  const std::vector<std::string> appleCandidates = {
      "/Library/Developer/CommandLineTools/usr/include",
      "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include",
      "/Applications/Xcode.app/Contents/Developer/Toolchains/"
      "XcodeDefault.xctoolchain/usr/include",
      "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/"
      "Developer/SDKs/MacOSX.sdk/usr/include"};
  for (const auto &candidate : appleCandidates) {
    appendIncludePathIfExists(paths, candidate);
  }
#endif

#if defined(__linux__)
  const std::vector<std::string> linuxCandidates = {
      "/usr/include/x86_64-linux-gnu", "/usr/include/aarch64-linux-gnu",
      "/usr/local/include/x86_64-linux-gnu",
      "/usr/local/include/aarch64-linux-gnu"};
  for (const auto &candidate : linuxCandidates) {
    appendIncludePathIfExists(paths, candidate);
  }
#endif

  return paths;
}

struct DriverConfig {
  std::string sourcePath;
  std::string irOutputPath = "output.ll";
  std::string executablePath;
  bool link = true;
  bool linkOnly = false;
  std::string linkInputPath;
  std::vector<std::string> additionalLibraries;
  std::vector<std::string> additionalLibraryPaths;
  Linker::Options linkerOptions;
};

static void printUsage(const char *progName) {
  std::cerr
      << "Usage: " << progName << " <source_file> [llvm_output.ll] [options]\n"
      << "Options:\n"
      << "  --exe <path>           Set output executable path "
         "(default derived from source name)\n"
      << "  --no-link              Skip linking (emit LLVM IR only)\n"
      << "  --linker <path>        Override linker executable "
         "(default: clang)\n"
      << "  --lib <name>           Link against additional library "
         "(repeatable)\n"
      << "  --lib-path <path>      Add library search path (repeatable)\n"
      << "  --linker-arg <arg>     Forward an extra argument to the linker "
         "(repeatable)\n"
      << "  --link-from-ir <path>  Link an existing LLVM IR file using the "
         "configured linker options\n"
      << "  --no-default-libs      Do not link default system libraries\n"
      << "  --link-verbose         Print the linker command before running\n"
      << "  -h, --help             Show this message\n";
}

static std::string deriveDefaultExecutableName(const std::string &sourcePath) {
  namespace fs = std::filesystem;
  fs::path input(sourcePath);
  fs::path filename = input.filename();
  if (filename.empty()) {
    filename = "a.out";
  }
  filename.replace_extension("");
  if (filename.empty()) {
    filename = "a.out";
  }
#ifdef _WIN32
  filename += ".exe";
#endif
  return filename.string();
}

int main(int argc, char *argv[]) {
  DriverConfig config;
  std::vector<std::string> positionalArgs;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-h" || arg == "--help") {
      printUsage(argv[0]);
      return 0;
    } else if (arg == "--no-link" || arg == "--emit-llvm-only") {
      config.link = false;
    } else if (arg == "--exe") {
      if (i + 1 >= argc) {
        std::cerr << "Error: --exe requires a path argument.\n";
        return 1;
      }
      config.executablePath = argv[++i];
    } else if (arg == "--linker") {
      if (i + 1 >= argc) {
        std::cerr << "Error: --linker requires a path argument.\n";
        return 1;
      }
      config.linkerOptions.linkerExecutable = argv[++i];
    } else if (arg == "--lib") {
      if (i + 1 >= argc) {
        std::cerr << "Error: --lib requires a library name.\n";
        return 1;
      }
      config.additionalLibraries.emplace_back(argv[++i]);
    } else if (arg == "--lib-path") {
      if (i + 1 >= argc) {
        std::cerr << "Error: --lib-path requires a directory path.\n";
        return 1;
      }
      config.additionalLibraryPaths.emplace_back(argv[++i]);
    } else if (arg == "--linker-arg") {
      if (i + 1 >= argc) {
        std::cerr << "Error: --linker-arg requires a value.\n";
        return 1;
      }
      config.linkerOptions.extraArgs.emplace_back(argv[++i]);
    } else if (arg == "--no-default-libs") {
      config.linkerOptions.useDefaultLibraries = false;
      config.linkerOptions.forcedLibraries.clear();
    } else if (arg == "--link-verbose") {
      config.linkerOptions.verbose = true;
    } else if (arg == "--link-from-ir") {
      if (config.linkOnly) {
        std::cerr << "Error: --link-from-ir specified multiple times.\n";
        return 1;
      }
      if (i + 1 >= argc) {
        std::cerr << "Error: --link-from-ir requires an IR file path.\n";
        return 1;
      }
      config.linkOnly = true;
      config.linkInputPath = argv[++i];
    } else if (!arg.empty() && arg[0] == '-') {
      std::cerr << "Error: Unknown option '" << arg << "'.\n";
      printUsage(argv[0]);
      return 1;
    } else {
      positionalArgs.emplace_back(std::move(arg));
    }
  }

  if (!config.linkOnly && positionalArgs.empty()) {
    printUsage(argv[0]);
    return 1;
  }

  if (!config.linkOnly) {
    config.sourcePath = positionalArgs[0];
    if (positionalArgs.size() >= 2) {
      config.irOutputPath = positionalArgs[1];
    }

    if (config.link && config.executablePath.empty()) {
      config.executablePath = deriveDefaultExecutableName(config.sourcePath);
    }

    if (config.irOutputPath.empty()) {
      config.irOutputPath = "output.ll";
    }
  } else {
    if (config.linkInputPath.empty()) {
      std::cerr << "Error: --link-from-ir specified without a valid path.\n";
      return 1;
    }
    if (config.executablePath.empty()) {
      config.executablePath = deriveDefaultExecutableName(config.linkInputPath);
    }
    Linker linker(config.linkerOptions);
    try {
      linker.linkIRToExecutable(config.linkInputPath, config.executablePath,
                                config.additionalLibraries,
                                config.additionalLibraryPaths);
      std::cout << "Executable linked at '" << config.executablePath << "'.\n";
      return 0;
    } catch (const std::exception &linkError) {
      std::cerr << linkError.what() << "\n";
      return 1;
    }
  }

  if (llvm::InitializeNativeTarget()) {
    std::cerr << "Error: Failed to initialize native target.\n";
    return 1;
  }
  if (llvm::InitializeNativeTargetAsmPrinter()) {
    std::cerr << "Error: Failed to initialize native asm printer.\n";
    return 1;
  }
  if (llvm::InitializeNativeTargetAsmParser()) {
    std::cerr << "Error: Failed to initialize native asm parser.\n";
    return 1;
  }

  // --- Step 0: Read and dump the original source ---
  std::ifstream srcFile(config.sourcePath);
  if (!srcFile.is_open()) {
    std::cerr << "Error: Could not open source file '" << config.sourcePath
              << "'.\n";
    return 1;
  }
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] main: Source file opened successfully" << std::endl;
  std::stringstream srcBuffer;
  srcBuffer << srcFile.rdbuf();
  std::string originalSource = srcBuffer.str();
  if (educcDebugEnabled())
    std::cerr << "[DEBUG] main: Source file read successfully" << std::endl;
  std::cout << "===== Original Source =====\n";
  std::cout << originalSource << "\n";
  std::cout << "===========================\n\n";

  /*
   * Step 1: Preprocessing
   */
  std::vector<std::string> systemPaths = defaultSystemIncludePaths();
  std::vector<std::string> userPaths = {"."};

  Preprocessor preprocessor(systemPaths, userPaths);
  std::string preprocessedSource;
  try {
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] main: About to call preprocessor.preprocess"
                << std::endl;
    preprocessedSource = preprocessor.preprocess(config.sourcePath);
    if (educcDebugEnabled())
      std::cerr
          << "[DEBUG] main: preprocessor.preprocess completed successfully"
          << std::endl;
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
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] main: About to call lexer.tokenize" << std::endl;
    tokens = lexer.tokenize();
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] main: lexer.tokenize completed successfully"
                << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Lexer Error: " << e.what() << "\n";
    return 1;
  }

  /*
   * Step 3: Parsing
   */
  Parser parser(tokens);
  std::shared_ptr<Program> ast;
  try {
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] main: About to call parser.parse" << std::endl;
    ast = parser.parse();
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] main: parser.parse completed successfully"
                << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Parser Error: " << e.what() << "\n";
    return 1;
  }

  /*
   * Step 4: Semantic Analysis
   */
  SemanticAnalyzer semanticAnalyzer;
  try {
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] main: About to call semanticAnalyzer.analyze"
                << std::endl;
    semanticAnalyzer.analyze(ast);
    if (educcDebugEnabled())
      std::cerr
          << "[DEBUG] main: semanticAnalyzer.analyze completed successfully"
          << std::endl;
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
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] main: About to call generateCode" << std::endl;
    std::unique_ptr<llvm::Module> module = codeGen.generateCode(ast);
    if (educcDebugEnabled())
      std::cerr << "[DEBUG] main: generateCode completed successfully"
                << std::endl;
    std::error_code EC;
    llvm::raw_fd_ostream dest(config.irOutputPath, EC,
                              static_cast<llvm::sys::fs::OpenFlags>(0));
    if (EC) {
      std::cerr << "Could not open output file: " << EC.message() << "\n";
      return 1;
    }
    module->print(dest, nullptr);
    dest.flush();
    std::cout << "LLVM IR generated and written to '" << config.irOutputPath
              << "'.\n";

    if (config.link) {
#if LLVM_VERSION_MAJOR >= 20
      const std::string moduleTripleStr = module->getTargetTriple().str();
#else
      const std::string moduleTripleStr = module->getTargetTriple();
#endif
      if (!moduleTripleStr.empty()) {
        config.linkerOptions.targetTriple = moduleTripleStr;
      }
      Linker linker(config.linkerOptions);
      try {
        linker.linkIRToExecutable(config.irOutputPath, config.executablePath,
                                  config.additionalLibraries,
                                  config.additionalLibraryPaths);
        std::cout << "Executable linked at '" << config.executablePath
                  << "'.\n";
      } catch (const std::exception &linkError) {
        std::cerr << linkError.what() << "\n";
        return 1;
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "Code Generation Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
