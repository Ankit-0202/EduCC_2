#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "CodeGenerator/Helpers.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"

#include <algorithm>
#include <cctype>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/Casting.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

using namespace llvm;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;

//===----------------------------------------------------------------------===//
// Array Access Helper
//===----------------------------------------------------------------------===//

llvm::Value *
CodeGenerator::generateArrayElementPointer(const shared_ptr<ArrayAccess> &arr) {
  // We require that the base of the array access is an identifier.
  if (auto baseId = std::dynamic_pointer_cast<Identifier>(arr->base)) {
    auto it = declaredTypes.find(baseId->name);
    if (it == declaredTypes.end())
      throw runtime_error("Declared type for array variable not found: " +
                          baseId->name);
    llvm::Type *arrayTy = it->second;
    if (!arrayTy->isArrayTy())
      throw runtime_error("Expected array type for variable: " + baseId->name);

    // Evaluate the index expression.
    llvm::Value *indexVal = generateExpression(arr->index);
    if (!indexVal->getType()->isIntegerTy(32))
      indexVal = builder.CreateIntCast(indexVal, Type::getInt32Ty(context),
                                       true, "arrayidxcast");

    vector<llvm::Value *> indices;
    // First index: 0 (for the pointer to the array itself)
    indices.push_back(ConstantInt::get(Type::getInt32Ty(context), 0));
    // Second index: the array index
    indices.push_back(indexVal);

    llvm::Value *baseLVal = generateLValue(arr->base);
    llvm::Value *gep =
        builder.CreateGEP(arrayTy, baseLVal, indices, "arraygep");
    return gep;
  } else {
    throw runtime_error("Array access on non-identifier base not supported.");
  }
}
