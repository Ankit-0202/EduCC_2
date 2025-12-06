# CODEX.md

This file guides Codex when working in this repository.

## Project Overview

EduCC is a teaching-oriented C compiler that emits LLVM IR and shells out to the host toolchain to produce executables. The codebase is C++17 and split into shared utilities, a preprocessor, and the compiler core.

## Build Commands

```bash
make          # Build static libs and build/educc
make clean    # Remove build artifacts and temporary outputs
make lint     # clang-format across C/C++ sources
```

## Testing Commands

```bash
make test            # Full pytest suite (frontend + linker)
make test-linker     # Only linker-marked tests
make test-log        # Verbose pytest (-vv)
pytest -k <pattern>  # Ad hoc selection
```

## Running the Compiler

```bash
build/educc <source.c> [output.ll] [options]
make run path/to/file.c                     # Shortcut wrapper
build/educc --link-from-ir foo.ll --exe out # Link existing LLVM IR
build/educc --link-verbose                  # Print constructed linker command
```

## Architecture

- `common/` (libcommon): shared lexer/token utilities.
- `preprocessor/` (libpreprocessor): preprocessor pipeline.
- `compiler/` (libcompiler): Parser, SemanticAnalyzer, CodeGenerator, Linker.
- `main.cpp`: orchestrates preprocessing → lexing → parsing → semantics → IR generation → linking.
Headers live under each module's `include/`; implementations are under `src/`.

## Testing Infrastructure

- Tests are `.c` fixtures under `tests/`; pytest parametrizes each file via `tests_py/`.
- The harness builds `build/educc`, generates IR/object files, and compares exit code and stdout against `gcc`. Linker tests use `--link-from-ir`.
- Toolchain requirements: `clang`, `llc`, and `gcc` must be on PATH. Failures include captured stdout/stderr for debugging.

## Key Dependencies

- LLVM toolchain (e.g., Homebrew LLVM 21.x) providing `llvm-config`, `clang`, and `llc`.
- Host C toolchain (`gcc` by default) for comparison.
- Python 3 with pytest. Configure `PYTEST_ARGS`/`PYTEST_TARGETS` via `make` if needed.
- Environment variables `CPATH`, `C_INCLUDE_PATH`, `CPLUS_INCLUDE_PATH`, and `LIBRARY_PATH` are honored during header/library resolution.

## Preprocessor & Linking Notes

- EduCC falls back to `clang -E` when in-tree preprocessing cannot handle system headers.
- Default linking injects system libs (`-lc`, `-lm`) unless suppressed with `--no-default-libs`.
- Use `--lib`/`--lib-path` to add libraries, and `--link-verbose` to debug linker arguments.

## VS Code Setup

- `.vscode/tasks.json` exposes make targets for build, clean, lint, and tests; invoke via the command palette or default build/test shortcuts.
- `.vscode/launch.json` adds LLDB and GDB launchers for `build/educc`, pre-building with `make` and passing the active file as the source argument.
- `.vscode/c_cpp_properties.json` wires IntelliSense to project headers and clang++ with C++17; adjust `compilerPath` or include paths if your toolchain differs.
- Recommended extensions sit in `.vscode/extensions.json` (C/C++, CodeLLDB, Makefile Tools, Python/Pylance for pytest support).
