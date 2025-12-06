# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

EduCC is a teaching-oriented C compiler that emits LLVM IR and uses the host toolchain to produce native executables. The compiler is built in C++ and consists of three main libraries: common utilities, preprocessor, and compiler core.

## Build Commands

```bash
# Build the compiler
make

# Clean build artifacts
make clean

# Format code with clang-format
make lint
```

## Testing Commands

```bash
# Run full test suite
make test

# Run only linker integration tests
make test-linker

# Run tests with verbose output
make test-log

# Run specific test pattern using pytest
pytest -k <pattern>

# Run a single test file
pytest tests_py/test_frontend.py::test_frontend_behaviour[<test-case-path>]
```

## Running the Compiler

```bash
# Basic compilation
build/educc <source.c> [output.ll] [options]

# Common options
build/educc hello.c                       # Generates output.ll and a.out
build/educc hello.c --exe myprogram      # Custom executable name
build/educc hello.c --no-link            # Generate LLVM IR only
build/educc --link-from-ir foo.ll --exe foo  # Link existing LLVM IR

# Linker options
--lib <name>              # Add library (e.g., --lib m for libm)
--lib-path <dir>          # Add library search path
--linker-arg <arg>        # Forward argument to linker
--no-default-libs         # Don't include default libraries
--link-verbose            # Show linker command
```

## Architecture

The compiler is organized into three static libraries plus the main executable:

1. **libcommon.a** (`common/`): Shared utilities and base classes
2. **libpreprocessor.a** (`preprocessor/`): C preprocessor implementation
3. **libcompiler.a** (`compiler/`): Core compiler components
   - Lexer: Tokenization
   - Parser: Generates AST
   - SemanticAnalyzer: Type checking and semantic validation
   - CodeGenerator: LLVM IR generation
   - Linker: Integration with system toolchain

The main entry point (`main.cpp`) orchestrates the compilation pipeline: preprocessing → lexing → parsing → semantic analysis → code generation → linking.

## Testing Infrastructure

Tests use pytest with custom fixtures defined in `tests_py/conftest.py`. The test harness:
- Compiles each test case with both EduCC and gcc
- Compares exit codes and stdout output
- Supports linker-specific tests marked with `@pytest.mark.linker`

Test cases are discovered from `tests/` directory and parameterized in `tests_py/cases.py`.

## Key Dependencies

- LLVM (for IR generation and toolchain integration)
- clang/llc (for linking and backend compilation)
- gcc (reference compiler for testing)
- Python 3 with pytest (for test suite)

## Preprocessor Fallback

When encountering complex system headers, EduCC automatically falls back to `clang -E` for preprocessing, ensuring compatibility with system headers without maintaining vendor-specific copies.