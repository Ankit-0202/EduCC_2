#include "Linker.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_set>

#include <llvm/ADT/SmallString.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/Process.h>
#include <llvm/Support/Program.h>

namespace {

bool pathExists(const std::string &path) {
  return llvm::sys::fs::exists(path);
}

std::string normalizeLibraryName(const std::string &lib) {
  if (lib.rfind("-l", 0) == 0) {
    return lib.substr(2);
  }
  return lib;
}

bool isClangLikeExecutable(llvm::StringRef path) {
  llvm::StringRef filename = llvm::sys::path::filename(path);
  return filename.starts_with_insensitive("clang");
}

void appendLibraryPathsFromEnv(std::vector<std::string> &paths,
                               const char *envVar) {
  if (!envVar)
    return;
  const char *raw = std::getenv(envVar);
  if (!raw || !*raw)
    return;

#ifdef _WIN32
  const char separator = ';';
#else
  const char separator = ':';
#endif

  std::stringstream ss(raw);
  std::string item;
  while (std::getline(ss, item, separator)) {
    if (!item.empty())
      paths.emplace_back(item);
  }
}

std::string emitObjectWithClang(const std::string &clangPath,
                                const std::string &irPath, bool verbose) {
  llvm::SmallString<128> tempObjPath;
  if (auto ec = llvm::sys::fs::createTemporaryFile("educ_ir", ".o", tempObjPath)) {
    throw std::runtime_error(
        "Linker Error: Unable to create temporary object file: " +
        ec.message());
  }
  std::string objPath = tempObjPath.str().str();

  std::vector<std::string> ownedArgs;
  ownedArgs.push_back(clangPath);
  ownedArgs.emplace_back("-Wno-override-module");
  ownedArgs.emplace_back("-x");
  ownedArgs.emplace_back("ir");
  ownedArgs.emplace_back("-c");
  ownedArgs.push_back(irPath);
  ownedArgs.emplace_back("-o");
  ownedArgs.push_back(objPath);

  llvm::SmallVector<llvm::StringRef, 12> args;
  args.reserve(ownedArgs.size());
  for (const auto &arg : ownedArgs) {
    args.push_back(arg);
  }

  if (verbose) {
    std::cerr << "[LINK] Lowering IR to object via clang:";
    for (const auto &arg : ownedArgs) {
      std::cerr << ' ' << arg;
    }
    std::cerr << std::endl;
  }

  int result = llvm::sys::ExecuteAndWait(clangPath, args);
  if (result != 0) {
    std::ostringstream cmd;
    for (const auto &arg : ownedArgs) {
      cmd << arg << ' ';
    }
    llvm::sys::fs::remove(objPath);
    throw std::runtime_error(
        "Linker Error: clang failed to produce object file (exit code " +
        std::to_string(result) + "). Command: " + cmd.str());
  }

  return objPath;
}

} // namespace

Linker::Linker() : options() {}

Linker::Linker(Options options) : options(std::move(options)) {}

void Linker::linkIRToExecutable(
    const std::string &irPath, const std::string &outputPath,
    const std::vector<std::string> &additionalLibraries,
    const std::vector<std::string> &additionalLibraryPaths) const {
  if (!pathExists(irPath)) {
    throw std::runtime_error("Linker Error: LLVM IR file '" + irPath +
                             "' does not exist.");
  }

  llvm::SmallString<256> outputPathStorage(outputPath);
  llvm::StringRef outputDir = llvm::sys::path::parent_path(outputPathStorage);
  if (!outputDir.empty()) {
    if (auto ec = llvm::sys::fs::create_directories(outputDir)) {
      throw std::runtime_error("Linker Error: Unable to create output directory '" +
                               outputDir.str() + "': " + ec.message());
    }
  }

  auto linkerPathOrErr =
      llvm::sys::findProgramByName(options.linkerExecutable);
  if (!linkerPathOrErr) {
    throw std::runtime_error(
        "Linker Error: Could not locate linker executable '" +
        options.linkerExecutable + "'. Ensure it is installed and on PATH.");
  }
  std::string linkerPath = *linkerPathOrErr;

  bool useClangDriver = isClangLikeExecutable(linkerPath);
  std::string inputPath = irPath;
  std::string tempObjectPath;
  if (!useClangDriver) {
    auto clangPath = llvm::sys::findProgramByName("clang");
    if (!clangPath) {
      throw std::runtime_error(
          "Linker Error: Non-clang linker requested but system 'clang' "
          "executable was not found to lower LLVM IR to an object file.");
    }
    tempObjectPath =
        emitObjectWithClang(*clangPath, irPath, options.verbose);
    inputPath = tempObjectPath;
  }

  std::vector<std::string> ownedArgs;
  ownedArgs.reserve(12 + options.forcedLibraries.size() +
                    options.librarySearchPaths.size() +
                    additionalLibraries.size() +
                    additionalLibraryPaths.size());

  ownedArgs.push_back(linkerPath);
  if (useClangDriver) {
    ownedArgs.emplace_back("-Wno-override-module");
  }
  if (useClangDriver && inputPath == irPath) {
    ownedArgs.emplace_back("-x");
    ownedArgs.emplace_back("ir");
  }
  ownedArgs.push_back(inputPath);
  ownedArgs.push_back("-o");
  ownedArgs.push_back(outputPath);

  if (!options.useDefaultLibraries) {
    ownedArgs.emplace_back("-nodefaultlibs");
  }

  std::vector<std::string> envLibraryPaths;
  appendLibraryPathsFromEnv(envLibraryPaths, "LIBRARY_PATH");
#ifdef __APPLE__
  appendLibraryPathsFromEnv(envLibraryPaths, "DYLD_LIBRARY_PATH");
#else
  appendLibraryPathsFromEnv(envLibraryPaths, "LD_LIBRARY_PATH");
#endif

  std::vector<std::string> allLibraryPaths;
  allLibraryPaths.reserve(options.librarySearchPaths.size() +
                          envLibraryPaths.size() +
                          additionalLibraryPaths.size());

  std::unordered_set<std::string> seenPaths;
  auto appendLibraryPaths = [&](const std::vector<std::string> &paths) {
    for (const auto &path : paths) {
      if (!path.empty()) {
        if (!pathExists(path))
          continue;
        if (seenPaths.insert(path).second) {
          allLibraryPaths.push_back(path);
        }
      }
    }
  };

  appendLibraryPaths(options.librarySearchPaths);
  appendLibraryPaths(envLibraryPaths);
  appendLibraryPaths(additionalLibraryPaths);

  for (const auto &path : allLibraryPaths) {
    ownedArgs.push_back("-L" + path);
  }

  for (const auto &arg : options.extraArgs) {
    if (!arg.empty()) {
      ownedArgs.push_back(arg);
    }
  }

  std::unordered_set<std::string> seenLibs;
  auto appendLibraries = [&ownedArgs, &seenLibs](const std::vector<std::string> &libs) {
    for (const auto &lib : libs) {
      if (lib.empty())
        continue;

      // If the argument starts with '-' treat it as a fully formed linker
      // argument (e.g. -framework, -pthread).
      if (lib[0] == '-') {
        if (seenLibs.insert(lib).second) {
          ownedArgs.push_back(lib);
        }
        continue;
      }

      std::string normalized = normalizeLibraryName(lib);
      if (seenLibs.insert(normalized).second) {
        ownedArgs.push_back("-l" + normalized);
      }
    }
  };

  if (options.useDefaultLibraries) {
    appendLibraries(options.forcedLibraries);
  }
  appendLibraries(additionalLibraries);

  llvm::SmallVector<llvm::StringRef, 16> args;
  args.reserve(ownedArgs.size());
  for (const auto &arg : ownedArgs) {
    args.push_back(arg);
  }

  if (options.verbose) {
    std::cerr << "[LINK] Executing:";
    for (const auto &arg : ownedArgs) {
      std::cerr << ' ' << arg;
    }
    std::cerr << std::endl;
  }

  int result = llvm::sys::ExecuteAndWait(linkerPath, args);
  if (result != 0) {
    std::ostringstream cmd;
    for (const auto &arg : ownedArgs) {
      cmd << arg << ' ';
    }
    throw std::runtime_error(
        "Linker Error: '" + options.linkerExecutable +
        "' exited with code " + std::to_string(result) +
        ". Command: " + cmd.str());
  }

  if (!tempObjectPath.empty()) {
    llvm::sys::fs::remove(tempObjectPath);
  }
}
