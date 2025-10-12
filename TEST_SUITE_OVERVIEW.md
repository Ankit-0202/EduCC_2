# EduCC Comprehensive Test Suite

## Overview
This document describes the comprehensive test suite created for the EduCC C compiler. The tests are designed to validate compiler functionality by comparing output with LLVM's reference implementation.

## Test Categories

### 1. Basic Functionality Tests (`tests/basic/`)

#### Variables (`tests/basic/variables/`)
- `global_variables.c` - Global variable declarations and initialization
- `local_variables.c` - Local variables and scope shadowing

#### Arithmetic (`tests/basic/arithmetic/`)
- `basic_arithmetic.c` - Basic arithmetic operations (+, -, *, /, %)
- `floating_point.c` - Floating point arithmetic

#### Expressions (`tests/basic/expressions/`)
- `complex_expressions.c` - Complex expression evaluation
- `ternary_operator.c` - Ternary operator functionality
- `logical_operators.c` - Logical operators (&&, ||, !)
- `bitwise_operators.c` - Bitwise operations (&, |, ^, <<, >>)

#### Control Flow (`tests/basic/control/`)
- `if_else_nested.c` - Nested if-else statements
- `while_loop.c` - While loop functionality
- `for_loop.c` - For loop functionality
- `do_while_loop.c` - Do-while loop functionality
- `switch_statement.c` - Switch statement with cases
- `break_continue.c` - Break and continue statements

#### Functions (`tests/basic/functions/`)
- `function_calls.c` - Function calls and parameters
- `recursive_factorial.c` - Recursive factorial function
- `recursive_fibonacci.c` - Recursive fibonacci function
- `function_pointers.c` - Function pointer usage

#### Pointers (`tests/basic/pointers/`)
- `pointer_arithmetic.c` - Pointer arithmetic operations
- `pointer_to_pointer.c` - Pointer to pointer functionality

#### Arrays (`tests/basic/arrays/`)
- `array_initialization.c` - Array initialization and access
- `multidimensional_array.c` - 2D array operations

#### Strings (`tests/basic/strings/`)
- `string_operations.c` - String length calculation
- `string_comparison.c` - String character comparison

#### Structs (`tests/basic/structs/`)
- `basic_struct.c` - Basic struct definition and access
- `struct_pointer.c` - Struct with pointer members

#### Unions (`tests/basic/unions/`)
- `basic_union.c` - Basic union functionality

### 2. Advanced Tests (`tests/advanced/`)

#### Expressions (`tests/advanced/expressions/`)
- `complex_ternary.c` - Complex nested ternary expressions
- `operator_precedence.c` - Operator precedence testing

#### Control Flow (`tests/advanced/control/`)
- `nested_loops.c` - Nested loop structures

#### Functions (`tests/advanced/functions/`)
- `mutual_recursion.c` - Mutual recursion between functions

#### Pointers (`tests/advanced/pointers/`)
- `pointer_arrays.c` - Array of pointers

#### Structs (`tests/advanced/structs/`)
- `struct_arrays.c` - Array of structs

### 3. Edge Case Tests (`tests/edge_cases/`)

#### Overflow (`tests/edge_cases/overflow/`)
- `integer_overflow.c` - Integer overflow behavior

#### Division (`tests/edge_cases/division/`)
- `division_by_zero.c` - Division by zero handling

#### Null Pointers (`tests/edge_cases/null_pointers/`)
- `null_pointer_deref.c` - Null pointer dereference

#### Array Bounds (`tests/edge_cases/array_bounds/`)
- `array_bounds_check.c` - Array bounds checking

### 4. Performance Tests (`tests/performance/`)

#### Loops (`tests/performance/loops/`)
- `loop_optimization.c` - Loop optimization opportunities

#### Algorithms (`tests/performance/algorithms/`)
- `sorting.c` - Bubble sort algorithm implementation

#### Memory (`tests/performance/memory/`)
- `memory_intensive.c` - Memory-intensive operations

### 5. Feature Tests (`tests/features/`)

#### Preprocessor (`tests/features/preprocessor/`)
- `macro_expansion.c` - Macro definition and expansion
- `conditional_compilation.c` - Conditional compilation directives
- `stringification.c` - Stringification and token pasting

### 6. Integration Tests (`tests/integration/`)
- `calculator.c` - Comprehensive calculator with multiple functions
- `data_structures.c` - Linked list data structure
- `matrix_operations.c` - Matrix transpose operation

## Test Execution

### Manual Testing
Run individual tests:
```bash
./build/educc tests/basic/arithmetic/basic_arithmetic.c test_output.ll
```

### Comprehensive Testing
Run all tests with the provided script:
```bash
./run_comprehensive_tests.sh
```

### Test Comparison
The test suite compares EduCC output with LLVM reference output to ensure correctness.

## Test Design Principles

1. **Comprehensive Coverage**: Tests cover all major C language features
2. **Incremental Complexity**: Tests progress from basic to advanced concepts
3. **Edge Case Testing**: Includes boundary conditions and error cases
4. **Performance Awareness**: Tests include performance-critical scenarios
5. **Integration Focus**: Tests validate complete program functionality

## Expected Outcomes

- **Basic Tests**: Should all pass, validating core compiler functionality
- **Advanced Tests**: May reveal areas needing improvement
- **Edge Cases**: Help identify robustness issues
- **Performance Tests**: Validate optimization capabilities
- **Integration Tests**: Ensure end-to-end functionality

## Maintenance

- Add new tests as compiler features are implemented
- Update tests when fixing bugs or adding features
- Regular execution ensures regression prevention
- Compare results with LLVM reference implementation

This comprehensive test suite provides thorough validation of the EduCC compiler's capabilities and helps ensure reliable, correct compilation of C programs.
