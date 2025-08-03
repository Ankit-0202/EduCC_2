# EduCC Compiler Test Suite

This directory contains a comprehensive, well-organized test suite for the EduCC C compiler. The tests are structured hierarchically for easy navigation and maintenance.

## Directory Structure

```
tests/
├── basic/                    # Basic language features
│   ├── arithmetic/          # Basic arithmetic operations
│   ├── expressions/         # Expressions, operators, precedence
│   ├── control/            # Control structures (if, loops, switch)
│   ├── functions/          # Function definitions and calls
│   ├── arrays/             # Array operations and access
│   ├── pointers/           # Basic pointer operations
│   ├── variables/          # Variable declarations and scope
│   └── strings/            # String literals and operations
├── data_types/             # Complex data types
│   ├── structs/            # Structure definitions and usage
│   ├── unions/             # Union types and memory sharing
│   ├── enums/              # Enumeration types
│   ├── bitfields/          # Bit-field structures
│   └── typedefs/           # Type definitions and aliases
├── advanced/               # Advanced language features
│   ├── pointers/           # Advanced pointer operations
│   ├── control_flow/       # Advanced control flow (goto, etc.)
│   ├── expressions/        # Advanced expressions (comma, sizeof, etc.)
│   ├── functions/          # Advanced function features
│   └── preprocessor/       # Advanced preprocessor features
├── storage_classes/         # Storage class specifiers
│   ├── auto/              # Auto storage class
│   ├── register/           # Register storage class
│   ├── static/             # Static variables and functions
│   ├── extern/             # External linkage
│   ├── const/              # Const qualifier
│   └── volatile/           # Volatile qualifier
├── scope/                  # Variable scope and visibility
│   ├── block/              # Block scope
│   ├── file/               # File scope
│   └── shadowing/          # Variable shadowing
├── optimization/           # Compiler optimization tests
│   ├── constant_propagation/
│   ├── loop_unrolling/
│   ├── strength_reduction/
│   └── dead_code/
├── performance/            # Performance-critical code
│   ├── loops/              # Large loop operations
│   ├── memory/             # Memory-intensive operations
│   └── algorithms/         # Algorithm implementations
├── security/               # Security-related patterns
│   ├── buffer_overflow/    # Buffer overflow tests
│   ├── format_strings/     # Format string vulnerabilities
│   └── race_conditions/    # Race condition patterns
├── edge_cases/             # Edge cases and undefined behavior
│   ├── undefined_behavior/ # Undefined behavior tests
│   ├── overflow/           # Integer overflow
│   ├── zero_division/      # Division by zero
│   └── null_pointers/      # Null pointer dereference
├── features/               # Advanced C features
│   ├── recursion/          # Recursive functions
│   ├── variadic/           # Variadic functions
│   ├── inline/             # Inline functions
│   ├── void/               # Void functions and pointers
│   ├── function_pointers/  # Function pointers
│   ├── complex/            # Complex numbers
│   ├── designated/         # Designated initializers
│   ├── compound_literals/  # Compound literals
│   ├── restrict/           # Restrict qualifier
│   └── flexible/           # Flexible array members
└── run_tests.sh            # Test runner script
```

## Test Categories

### Basic Language Features (`basic/`)
Tests for fundamental C language constructs that every compiler should handle correctly.

### Data Types (`data_types/`)
Tests for complex data type definitions and usage patterns.

### Advanced Features (`advanced/`)
Tests for more sophisticated language features that demonstrate compiler maturity.

### Storage Classes (`storage_classes/`)
Tests for different variable storage and linkage specifications.

### Scope Management (`scope/`)
Tests for variable scope, visibility, and shadowing behavior.

### Optimization (`optimization/`)
Tests that should trigger specific compiler optimizations.

### Performance (`performance/`)
Tests for performance-critical code patterns and large-scale operations.

### Security (`security/`)
Tests for common security vulnerabilities and safe coding practices.

### Edge Cases (`edge_cases/`)
Tests for undefined behavior and boundary conditions.

### Advanced Features (`features/`)
Tests for modern C language features and extensions.

## Running Tests

```bash
# Run all tests
./tests/run_tests.sh

# Run tests for a specific category
./tests/run_tests.sh basic/arithmetic

# Run tests for a specific subcategory
./tests/run_tests.sh optimization/constant_propagation
```

## Test Structure

Each test file:
- Returns `0` on success, non-zero on failure
- Tests one specific language feature
- Uses deterministic values for comparison
- Is self-contained (no external dependencies)
- Includes comments explaining expected behavior

## Adding New Tests

1. **Choose the appropriate directory** based on the feature being tested
2. **Create a descriptive filename** that indicates what is being tested
3. **Follow the pattern**: return 0 for success, non-zero for failure
4. **Include comments** explaining the expected behavior
5. **Test one feature per file** for clarity

## Test Complexity Levels

### Beginner Level
- `basic/` - Fundamental language constructs
- `data_types/` - Basic type definitions

### Intermediate Level
- `advanced/` - Sophisticated language features
- `storage_classes/` - Variable storage specifications
- `scope/` - Variable visibility and scope

### Advanced Level
- `optimization/` - Compiler optimization patterns
- `performance/` - Large-scale operations
- `security/` - Vulnerability testing
- `edge_cases/` - Boundary condition testing
- `features/` - Modern C language features

## Expected Behavior

All tests should:
- Compile successfully with both GCC and your compiler
- Produce identical return values when run
- Handle edge cases gracefully
- Not crash on undefined behavior (though behavior may be undefined)

## Notes

- **Undefined Behavior Tests**: Some tests intentionally trigger undefined behavior to test compiler robustness
- **Performance Tests**: May take longer to execute due to large loops or memory operations
- **Security Tests**: Demonstrate potential vulnerabilities but don't exploit them
- **Edge Case Tests**: Help identify compiler limitations and boundary handling

## Maintenance

- Keep test names descriptive and consistent
- Group related tests in appropriate subdirectories
- Update the test runner script when adding new categories
- Document any special requirements or dependencies 