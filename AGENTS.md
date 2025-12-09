# Repository Guidelines

## Project Structure & Module Organization

- Source lives in `common/` (shared token/lexer utilities), `preprocessor/`, `compiler/` (Parser, SemanticAnalyzer, CodeGenerator, Linker) plus `main.cpp` orchestrating the pipeline.
- Public headers sit in each module's `include/`; implementations are under `src/`. Build artefacts land in `build/`.
- C fixtures live under `tests/`; pytest harness lives in `tests_py/`. `Makefile` drives builds, tests, and linting.

## Build, Test, and Development Commands

- `make` builds static libs and `build/educc`; `make clean` removes `build/` artifacts.
- `build/educc <file.c> [output.ll] [options]` runs the compiler; `make run path/to/file.c` is a shortcut. Use `--link-from-ir` for existing LLVM IR; `--link-verbose` prints the linker call.
- `make test` runs the full pytest suite, comparing EduCC output to `gcc`; `make test-linker` or `pytest -m linker` scopes to linker cases; `make test-log` adds `-vv`. `pytest -k <pattern>` filters ad hoc.
- Format with `make lint` (clang-format). Ensure `llvm-config`, `clang`, `llc`, and `gcc` are on PATH before running tests.

## Coding Style & Naming Conventions

- Code targets C++17; use 2-space indentation, same-line braces, and group includes with project headers before LLVM/system headers.
- Prefer PascalCase for types, camelCase for functions/variables, SCREAMING_SNAKE for enums/constants, and traditional include guards (`FOO_HPP`) on headers.
- Keep new APIs under the relevant module `include/` dir to preserve encapsulation; avoid exposing internal headers from other modules.

## Testing Guidelines

- Each `.c` file in `tests/` becomes a parametrized pytest case identified by its relative path; names should reflect behaviour (e.g., `types/implicit_conversion_float_int.c`).
- Tests require `clang`, `llc`, and `gcc`; subprocess failures include captured stdout/stderr for gcc diffs.
- When adding coverage, supply runtime args or env overrides via `CompilerTestCase` overrides if needed, and keep expected output aligned with gcc's behaviour.

## Commit & Pull Request Guidelines

- Follow the existing short, imperative commit style (e.g., "Add claude files", "Use pytest for testing"); keep subjects under ~72 characters.
- PRs should describe behaviour changes, affected CLI flags, and toolchain assumptions; link issues when relevant.
- Include the commands you ran (e.g., `make test`, targeted `pytest -k ...`) and any noteworthy linker/LLVM diagnostics. Update README/CLAUDE/AGENTS when flags, dependencies, or workflows change.

## Toolchain & Configuration Tips

- Ensure LLVM-provided `llvm-config`, `clang`, and `llc` match your host libc; set `CPATH`/`C_INCLUDE_PATH`/`CPLUS_INCLUDE_PATH` and `LIBRARY_PATH` so system headers/libs resolve.
- EduCC falls back to `clang -E` on tricky headers; combine `--link-verbose` with `--lib`/`--lib-path` to debug linkage.
