#ifndef EDUCC_LINKER_HPP
#define EDUCC_LINKER_HPP

#include <string>
#include <vector>

/**
 * Linker encapsulates the final stage of the compiler pipeline.
 * It shells out to a system linker (clang by default) so that we can reuse
 * the platform's existing C runtime and system libraries instead of attempting
 * to build or ship our own copies.
 */
class Linker {
public:
  struct Options {
    std::string linkerExecutable = "clang";
    std::vector<std::string> librarySearchPaths{};
    std::vector<std::string> forcedLibraries{"c", "m"};
    std::vector<std::string> extraArgs{};
    std::string targetTriple;
    bool useDefaultLibraries = true;
    bool verbose = false;
  };

  Linker();
  explicit Linker(Options options);

  /**
   * Link the LLVM IR file at `irPath` into a native executable located at
   * `outputPath`. Additional libraries and library search paths can be
   * provided, and will be appended after the defaults to give callers a way to
   * extend the link without replacing the system defaults.
   *
   * Throws std::runtime_error if any step fails.
   */
  void linkIRToExecutable(
      const std::string &irPath, const std::string &outputPath,
      const std::vector<std::string> &additionalLibraries = {},
      const std::vector<std::string> &additionalLibraryPaths = {}) const;

private:
  Options options;
};

#endif // EDUCC_LINKER_HPP
