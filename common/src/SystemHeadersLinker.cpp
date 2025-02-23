#include "SystemHeadersLinker.hpp"
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Linker/Linker.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>
#include <memory>

std::unique_ptr<llvm::Module>
linkSystemHeaders(std::unique_ptr<llvm::Module> mainModule,
                  const std::string &bitcodePath) {
  llvm::LLVMContext &context = mainModule->getContext();
  // Read the bitcode file into a memory buffer.
  auto bufferOrError = llvm::MemoryBuffer::getFile(bitcodePath);
  if (!bufferOrError) {
    llvm::errs() << "Error reading bitcode file: " << bitcodePath << "\n";
    return nullptr;
  }
  auto buffer = std::move(*bufferOrError);
  // Parse the bitcode into an LLVM module.
  llvm::Expected<std::unique_ptr<llvm::Module>> moduleOrErr =
      llvm::parseBitcodeFile(buffer->getMemBufferRef(), context);
  if (!moduleOrErr) {
    llvm::errs() << "Error parsing bitcode file: " << bitcodePath << "\n";
    return nullptr;
  }
  std::unique_ptr<llvm::Module> systemModule = std::move(*moduleOrErr);
  // Use LLVM's Linker to merge the system module into the main module.
  if (llvm::Linker::linkModules(*mainModule, std::move(systemModule))) {
    llvm::errs() << "Error linking system headers module.\n";
    return nullptr;
  }
  return mainModule;
}
