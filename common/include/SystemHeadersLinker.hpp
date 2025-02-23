#ifndef SYSTEM_HEADERS_LINKER_HPP
#define SYSTEM_HEADERS_LINKER_HPP

#include <llvm/IR/Module.h>
#include <memory>
#include <string>

// Links a precompiled system headers module (bitcode file) into the given main
// module. Returns the updated module (or nullptr on error).
std::unique_ptr<llvm::Module>
linkSystemHeaders(std::unique_ptr<llvm::Module> mainModule,
                  const std::string &bitcodePath);

#endif // SYSTEM_HEADERS_LINKER_HPP
