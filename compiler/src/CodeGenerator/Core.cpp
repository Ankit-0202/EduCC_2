// compiler/src/CodeGenerator/Core.cpp

#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <stdexcept>
#include <unordered_map>
#include <vector>

using namespace llvm;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;

CodeGenerator::CodeGenerator()
    : builder(context),
      module(std::make_unique<Module>("main_module", context)) {
  // Set a default data layout for the module.
  module->setDataLayout("e-m:o-i64:64-f80:128-n8:16:32:64-S128");
  // NOTE: Opaque pointers are enabled by default in LLVM 15+.
  // To call getElementType(), your LLVM must disable opaque pointers.
}

std::unique_ptr<Module>
CodeGenerator::generateCode(const shared_ptr<Program> &program) {
  // Process global declarations first.
  for (const auto &decl : program->declarations) {
    if (auto varDecl = std::dynamic_pointer_cast<VariableDeclaration>(decl)) {
      // e.g. int x;   or   int array[10];
      llvm::Type *varType = getLLVMType(varDecl->type);
      // If there are array dimensions, wrap them in an ArrayType
      if (!varDecl->dimensions.empty()) {
        for (auto it = varDecl->dimensions.rbegin();
             it != varDecl->dimensions.rend(); ++it) {
          llvm::Value *dimVal = generateExpression(*it);
          ConstantInt *constDim = dyn_cast<ConstantInt>(dimVal);
          if (!constDim)
            throw runtime_error("CodeGenerator Error: Array dimension must be "
                                "a constant integer.");
          uint64_t arraySize = constDim->getZExtValue();
          varType = ArrayType::get(varType, arraySize);
        }
      }
      // Create the global
      GlobalVariable *gVar = new GlobalVariable(
          *module, varType, /*isConstant=*/false, GlobalValue::ExternalLinkage,
          nullptr, varDecl->name);

      // If it has an initializer
      if (varDecl->initializer) {
        if (auto initList = std::dynamic_pointer_cast<InitializerList>(
                varDecl->initializer.value())) {
          // array initializer
          auto arrayTy = dyn_cast<ArrayType>(varType);
          if (!arrayTy)
            throw runtime_error("CodeGenerator Error: Initializer list used "
                                "for non-array variable.");
          uint64_t arraySize = arrayTy->getNumElements();
          vector<Constant *> elems;
          for (uint64_t i = 0; i < arraySize; i++) {
            Constant *elemConst = nullptr;
            if (i < initList->elements.size()) {
              auto lit =
                  std::dynamic_pointer_cast<Literal>(initList->elements[i]);
              if (!lit)
                throw runtime_error("CodeGenerator Error: Global initializer "
                                    "list must contain literals.");
              if (lit->type == Literal::LiteralType::Int)
                elemConst =
                    ConstantInt::get(Type::getInt32Ty(context), lit->intValue);
              else if (lit->type == Literal::LiteralType::Float)
                elemConst =
                    ConstantFP::get(Type::getFloatTy(context), lit->floatValue);
              else if (lit->type == Literal::LiteralType::Double)
                elemConst = ConstantFP::get(Type::getDoubleTy(context),
                                            lit->doubleValue);
              else if (lit->type == Literal::LiteralType::Char)
                elemConst =
                    ConstantInt::get(Type::getInt8Ty(context), lit->charValue);
              else if (lit->type == Literal::LiteralType::Bool)
                elemConst =
                    ConstantInt::get(Type::getInt1Ty(context), lit->boolValue);
              else
                throw runtime_error("CodeGenerator Error: Unsupported literal "
                                    "in global initializer.");
            } else {
              elemConst = Constant::getNullValue(arrayTy->getElementType());
            }
            elems.push_back(elemConst);
          }
          Constant *arrayInit = ConstantArray::get(arrayTy, elems);
          gVar->setInitializer(arrayInit);
        } else if (auto lit = std::dynamic_pointer_cast<Literal>(
                       varDecl->initializer.value())) {
          // single literal init
          Constant *initVal = nullptr;
          if (lit->type == Literal::LiteralType::Int)
            initVal =
                ConstantInt::get(Type::getInt32Ty(context), lit->intValue);
          else if (lit->type == Literal::LiteralType::Float)
            initVal =
                ConstantFP::get(Type::getFloatTy(context), lit->floatValue);
          else if (lit->type == Literal::LiteralType::Double)
            initVal =
                ConstantFP::get(Type::getDoubleTy(context), lit->doubleValue);
          else if (lit->type == Literal::LiteralType::Char)
            initVal =
                ConstantInt::get(Type::getInt8Ty(context), lit->charValue);
          else if (lit->type == Literal::LiteralType::Bool)
            initVal =
                ConstantInt::get(Type::getInt1Ty(context), lit->boolValue);
          else
            throw runtime_error("CodeGenerator Error: Unsupported literal type "
                                "in global init.");
          // possibly convert float -> double or double -> float
          if (initVal->getType() != varType) {
            if (initVal->getType()->isFloatingPointTy() &&
                varType->isFloatingPointTy()) {
              // cast from float->double or double->float
              auto litVal = (lit->type == Literal::LiteralType::Double)
                                ? (float)lit->doubleValue
                                : (double)lit->floatValue;
              initVal = ConstantFP::get(varType, litVal);
            } else {
              throw runtime_error(
                  "CodeGenerator Error: Incompatible initializer type in "
                  "global var declaration.");
            }
          }
          gVar->setInitializer(initVal);
        } else {
          throw runtime_error("CodeGenerator Error: Global initializer must be "
                              "literal or list.");
        }
      } else {
        // no initializer => zero init
        Constant *defaultVal = nullptr;
        if (varDecl->type == "int")
          defaultVal = ConstantInt::get(Type::getInt32Ty(context), 0);
        else if (varDecl->type == "float")
          defaultVal = ConstantFP::get(Type::getFloatTy(context), 0.0f);
        else if (varDecl->type == "char")
          defaultVal = ConstantInt::get(Type::getInt8Ty(context), 0);
        else if (varDecl->type == "double")
          defaultVal = ConstantFP::get(Type::getDoubleTy(context), 0.0);
        else if (varDecl->type == "bool")
          defaultVal = ConstantInt::get(Type::getInt1Ty(context), 0);
        else
          throw runtime_error("CodeGenerator Error: Unsupported type in global "
                              "var declaration.");
        gVar->setInitializer(defaultVal);
      }
    }

    else if (auto multiDecl =
                 std::dynamic_pointer_cast<MultiVariableDeclaration>(decl)) {
      // e.g. int x=1, y=2, z[10];
      for (const auto &singleDecl : multiDecl->declarations) {
        llvm::Type *varType = getLLVMType(singleDecl->type);
        if (!singleDecl->dimensions.empty()) {
          for (auto it = singleDecl->dimensions.rbegin();
               it != singleDecl->dimensions.rend(); ++it) {
            llvm::Value *dimVal = generateExpression(*it);
            ConstantInt *constDim = dyn_cast<ConstantInt>(dimVal);
            if (!constDim)
              throw runtime_error("CodeGenerator Error: Array dimension must "
                                  "be a constant integer.");
            uint64_t arraySize = constDim->getZExtValue();
            varType = ArrayType::get(varType, arraySize);
          }
        }
        GlobalVariable *gVar = new GlobalVariable(*module, varType, false,
                                                  GlobalValue::ExternalLinkage,
                                                  nullptr, singleDecl->name);

        if (singleDecl->initializer) {
          if (auto initList = std::dynamic_pointer_cast<InitializerList>(
                  singleDecl->initializer.value())) {
            auto arrayTy = dyn_cast<ArrayType>(varType);
            if (!arrayTy)
              throw runtime_error(
                  "CodeGenerator Error: Init list used for non-array.");
            uint64_t arraySize = arrayTy->getNumElements();
            vector<Constant *> elems;
            for (uint64_t i = 0; i < arraySize; i++) {
              Constant *elemConst = nullptr;
              if (i < initList->elements.size()) {
                auto lit =
                    std::dynamic_pointer_cast<Literal>(initList->elements[i]);
                if (!lit)
                  throw runtime_error(
                      "Global init list must contain literals only.");
                if (lit->type == Literal::LiteralType::Int)
                  elemConst = ConstantInt::get(Type::getInt32Ty(context),
                                               lit->intValue);
                else if (lit->type == Literal::LiteralType::Float)
                  elemConst = ConstantFP::get(Type::getFloatTy(context),
                                              lit->floatValue);
                else if (lit->type == Literal::LiteralType::Double)
                  elemConst = ConstantFP::get(Type::getDoubleTy(context),
                                              lit->doubleValue);
                else if (lit->type == Literal::LiteralType::Char)
                  elemConst = ConstantInt::get(Type::getInt8Ty(context),
                                               lit->charValue);
                else if (lit->type == Literal::LiteralType::Bool)
                  elemConst = ConstantInt::get(Type::getInt1Ty(context),
                                               lit->boolValue);
                else
                  throw runtime_error(
                      "Unsupported literal in global initializer.");
              } else {
                elemConst = Constant::getNullValue(arrayTy->getElementType());
              }
              elems.push_back(elemConst);
            }
            Constant *arrayInit = ConstantArray::get(arrayTy, elems);
            gVar->setInitializer(arrayInit);
          } else if (auto lit = std::dynamic_pointer_cast<Literal>(
                         singleDecl->initializer.value())) {
            Constant *initVal = nullptr;
            if (lit->type == Literal::LiteralType::Int)
              initVal =
                  ConstantInt::get(Type::getInt32Ty(context), lit->intValue);
            else if (lit->type == Literal::LiteralType::Float)
              initVal =
                  ConstantFP::get(Type::getFloatTy(context), lit->floatValue);
            else if (lit->type == Literal::LiteralType::Double)
              initVal =
                  ConstantFP::get(Type::getDoubleTy(context), lit->doubleValue);
            else if (lit->type == Literal::LiteralType::Char)
              initVal =
                  ConstantInt::get(Type::getInt8Ty(context), lit->charValue);
            else if (lit->type == Literal::LiteralType::Bool)
              initVal =
                  ConstantInt::get(Type::getInt1Ty(context), lit->boolValue);
            else
              throw runtime_error(
                  "CodeGenerator Error: Unsupported literal in global init.");
            // possibly float <-> double
            if (initVal->getType() != varType) {
              if (initVal->getType()->isFloatingPointTy() &&
                  varType->isFloatingPointTy()) {
                auto litVal = (lit->type == Literal::LiteralType::Double)
                                  ? (float)lit->doubleValue
                                  : (double)lit->floatValue;
                initVal = ConstantFP::get(varType, litVal);
              } else {
                throw runtime_error(
                    "CodeGenerator Error: Incompatible initializer type in "
                    "global var declaration.");
              }
            }
            gVar->setInitializer(initVal);
          } else {
            throw runtime_error("CodeGenerator Error: Global var init must be "
                                "literal or init list.");
          }
        } else {
          // no initializer => zero
          Constant *defaultVal = nullptr;
          if (singleDecl->type == "int")
            defaultVal = ConstantInt::get(Type::getInt32Ty(context), 0);
          else if (singleDecl->type == "float")
            defaultVal = ConstantFP::get(Type::getFloatTy(context), 0.0f);
          else if (singleDecl->type == "char")
            defaultVal = ConstantInt::get(Type::getInt8Ty(context), 0);
          else if (singleDecl->type == "double")
            defaultVal = ConstantFP::get(Type::getDoubleTy(context), 0.0);
          else if (singleDecl->type == "bool")
            defaultVal = ConstantInt::get(Type::getInt1Ty(context), 0);
          else
            throw runtime_error(
                "CodeGenerator Error: Unsupported type in global var decl.");
          gVar->setInitializer(defaultVal);
        }
      }
    }

    else if (auto enumDecl = std::dynamic_pointer_cast<EnumDeclaration>(decl)) {
      for (size_t i = 0; i < enumDecl->enumerators.size(); ++i) {
        string enumName = enumDecl->enumerators[i].first;
        int value = enumDecl->enumeratorValues[i];
        Constant *initVal = ConstantInt::get(Type::getInt32Ty(context), value);
        GlobalVariable *gEnum =
            new GlobalVariable(*module, Type::getInt32Ty(context), true,
                               GlobalValue::ExternalLinkage, initVal, enumName);
      }
    }
  }

  // 2) Then handle function declarations
  for (const auto &decl : program->declarations) {
    if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclaration>(decl)) {
      generateFunction(funcDecl);
    }
  }

  // verify
  if (verifyModule(*module, &errs()))
    throw runtime_error("CodeGenerator Error: Module verification failed.");
  return std::move(module);
}

llvm::Type *CodeGenerator::getLLVMType(const string &type) {
  // handle pointer syntax "int**"
  if (type.find("*") != string::npos) {
    // remove trailing '*'
    string baseType = type;
    while (!baseType.empty() &&
           (baseType.back() == ' ' || baseType.back() == '*'))
      baseType.pop_back();
    while (!baseType.empty() && baseType.front() == ' ')
      baseType.erase(baseType.begin());
    llvm::Type *baseLLVM = getLLVMType(baseType);
    return PointerType::getUnqual(baseLLVM);
  }

  if (type == "int")
    return Type::getInt32Ty(context);
  else if (type == "float")
    return Type::getFloatTy(context);
  else if (type == "char")
    return Type::getInt8Ty(context);
  else if (type == "double")
    return Type::getDoubleTy(context);
  else if (type == "bool")
    return Type::getInt1Ty(context);
  else if (type == "void")
    return Type::getVoidTy(context);
  else if (type.rfind("enum ", 0) == 0)
    return Type::getInt32Ty(context);
  else if (type.rfind("union ", 0) == 0) {
    // union
    string tag = type.substr(6);
    auto it = unionRegistry.find(tag);
    if (it == unionRegistry.end())
      throw runtime_error("CodeGenerator Error: Unknown union type '" + type +
                          "'.");
    int maxSize = 0;
    DataLayout dl(module.get());
    for (auto &member : it->second->members) {
      int memberSize = 0;
      if (member->type == "int" || member->type == "float")
        memberSize = 4;
      else if (member->type == "char" || member->type == "bool")
        memberSize = 1;
      else if (member->type == "double")
        memberSize = 8;
      else if (member->type.rfind("enum ", 0) == 0)
        memberSize = 4;
      else if (member->type.rfind("union ", 0) == 0)
        throw runtime_error("Nested unions not supported.");
      else if (member->type.rfind("struct ", 0) == 0) {
        llvm::Type *structTy = getLLVMType(member->type);
        uint64_t size = dl.getTypeAllocSize(structTy);
        memberSize = (int)size;
      } else {
        throw runtime_error("Unsupported union member type '" + member->type +
                            "'.");
      }
      if (memberSize > maxSize)
        maxSize = memberSize;
    }
    if (maxSize <= 0)
      maxSize = 1;
    return ArrayType::get(Type::getInt8Ty(context), maxSize);
  } else if (type.rfind("struct ", 0) == 0) {
    // struct
    string tag = type.substr(7);
    auto it = structRegistry.find(tag);
    if (it == structRegistry.end())
      throw runtime_error("CodeGenerator Error: Unknown struct type '" + type +
                          "'.");
    vector<Type *> memberTypes;
    for (auto &m : it->second->members) {
      memberTypes.push_back(getLLVMType(m->type));
    }
    StructType *structType =
        StructType::create(context, memberTypes, tag, /*packed=*/false);
    return structType;
  }
  throw runtime_error("CodeGenerator Error: Unsupported type '" + type + "'.");
}

static bool functionSignaturesMatch(FunctionType *existing,
                                    FunctionType *candidate) {
  if (existing->getReturnType() != candidate->getReturnType())
    return false;
  if (existing->getNumParams() != candidate->getNumParams())
    return false;
  for (unsigned i = 0; i < existing->getNumParams(); ++i) {
    if (existing->getParamType(i) != candidate->getParamType(i))
      return false;
  }
  return true;
}

llvm::Function *CodeGenerator::getOrCreateFunctionInModule(
    const std::string &name, llvm::Type *returnType,
    const vector<Type *> &paramTypes, bool isDefinition) {
  FunctionType *fType = FunctionType::get(returnType, paramTypes, false);
  if (Function *existingFn = module->getFunction(name)) {
    FunctionType *existingType = existingFn->getFunctionType();
    if (!functionSignaturesMatch(existingType, fType))
      throw runtime_error("CodeGenerator Error: Conflicting signature for '" +
                          name + "'.");
    if (isDefinition && !existingFn->empty())
      throw runtime_error("CodeGenerator Error: Function '" + name +
                          "' is already defined.");
    return existingFn;
  }
  Function *newFn =
      Function::Create(fType, Function::ExternalLinkage, name, module.get());
  return newFn;
}

llvm::Function *CodeGenerator::generateFunction(
    const shared_ptr<FunctionDeclaration> &funcDecl) {
  // Convert return type to LLVM
  llvm::Type *retTy = getLLVMType(funcDecl->returnType);
  // Parameter types
  vector<Type *> paramTys;
  for (auto &param : funcDecl->parameters) {
    // param.first is e.g. "int*" or "float"
    llvm::Type *pty = getLLVMType(param.first);
    paramTys.push_back(pty);
  }
  bool hasBody = (funcDecl->body != nullptr);

  llvm::Function *function =
      getOrCreateFunctionInModule(funcDecl->name, retTy, paramTys, hasBody);
  if (!hasBody)
    return function; // forward declaration

  if (!function->empty()) {
    throw runtime_error("CodeGenerator Error: Unexpected redefinition for '" +
                        funcDecl->name + "'.");
  }

  // Create entry block
  BasicBlock *entryBB = BasicBlock::Create(context, "entry", function);
  builder.SetInsertPoint(entryBB);

  // Clear local state, push new local scope
  localVarStack.clear();
  pushLocalScope();

  // For each function parameter, allocate local space and store declared type
  // string
  size_t i = 0;
  for (auto &arg : function->args()) {
    const auto &paramName = funcDecl->parameters[i].second;      // e.g. "a"
    const auto &paramTypeString = funcDecl->parameters[i].first; // e.g. "int*"

    arg.setName(paramName);
    AllocaInst *alloc = builder.CreateAlloca(arg.getType(), nullptr, paramName);
    builder.CreateStore(&arg, alloc);

    // Add to local scope
    localVarStack.back()[paramName] = alloc;
    declaredTypes[paramName] = arg.getType();
    declaredTypeStrings[paramName] = paramTypeString; // <-- Important line

    i++;
  }

  // Generate function body
  auto compound = std::dynamic_pointer_cast<CompoundStatement>(funcDecl->body);
  if (!compound) {
    throw runtime_error(
        "CodeGenerator Error: Function body is not a CompoundStatement.");
  }
  generateStatement(compound);

  // If no terminator => add a default return
  if (!builder.GetInsertBlock()->getTerminator()) {
    // e.g. if return type is void => ret void
    if (funcDecl->returnType == "void")
      builder.CreateRetVoid();
    else if (funcDecl->returnType == "int")
      builder.CreateRet(ConstantInt::get(Type::getInt32Ty(context), 0));
    else if (funcDecl->returnType == "float")
      builder.CreateRet(ConstantFP::get(Type::getFloatTy(context), 0.0f));
    else if (funcDecl->returnType == "double")
      builder.CreateRet(ConstantFP::get(Type::getDoubleTy(context), 0.0));
    else if (funcDecl->returnType == "char")
      builder.CreateRet(ConstantInt::get(Type::getInt8Ty(context), 0));
    else if (funcDecl->returnType == "bool")
      builder.CreateRet(ConstantInt::get(Type::getInt1Ty(context), 0));
    else
      throw runtime_error("CodeGenerator Error: Unsupported return type '" +
                          funcDecl->returnType + "'.");
  }
  return function;
}
