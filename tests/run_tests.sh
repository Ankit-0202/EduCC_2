#!/bin/bash

# Test runner script for EduCC compiler
# Compares output with GCC

COMPILER="./compiler"  # Path to your compiler
GCC="gcc"
CC="gcc -std=c99"  # Use C99 standard for compatibility

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Statistics
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Function to run a single test
run_test() {
    local test_file="$1"
    local test_name=$(basename "$test_file" .c)
    
    echo -n "Testing $test_name... "
    
    # Compile with GCC
    $CC -o "${test_name}_gcc" "$test_file" 2>/dev/null
    if [ $? -ne 0 ]; then
        echo -e "${YELLOW}GCC compilation failed${NC}"
        return 1
    fi
    
    # Run with GCC
    ./"${test_name}_gcc" >/dev/null 2>&1
    local gcc_result=$?
    
    # Compile with your compiler
    $COMPILER "$test_file" -o "${test_name}_edu" 2>/dev/null
    if [ $? -ne 0 ]; then
        echo -e "${RED}Compiler failed${NC}"
        rm -f "${test_name}_gcc"
        return 1
    fi
    
    # Run with your compiler
    ./"${test_name}_edu" >/dev/null 2>&1
    local edu_result=$?
    
    # Compare results
    if [ $gcc_result -eq $edu_result ]; then
        echo -e "${GREEN}PASS${NC}"
        ((PASSED_TESTS++))
    else
        echo -e "${RED}FAIL (GCC: $gcc_result, EduCC: $edu_result)${NC}"
        ((FAILED_TESTS++))
    fi
    
    # Cleanup
    rm -f "${test_name}_gcc" "${test_name}_edu"
    ((TOTAL_TESTS++))
}

# Function to run tests in a directory
run_directory_tests() {
    local dir="$1"
    if [ -d "$dir" ]; then
        echo "=== Testing $dir ==="
        for test_file in "$dir"/*.c; do
            if [ -f "$test_file" ]; then
                run_test "$test_file"
            fi
        done
        echo
    fi
}

# Main execution
echo "EduCC Compiler Test Suite"
echo "========================="
echo

# Test categories
test_dirs=(
    "basic/arithmetic"
    "basic/expressions"
    "basic/control"
    "basic/functions"
    "basic/arrays"
    "basic/pointers"
    "basic/variables"
    "basic/strings"
    "data_types/structs"
    "data_types/unions"
    "data_types/enums"
    "data_types/bitfields"
    "data_types/typedefs"
    "advanced/pointers"
    "advanced/control_flow"
    "advanced/expressions"
    "advanced/functions"
    "advanced/preprocessor"
    "storage_classes/auto"
    "storage_classes/register"
    "storage_classes/static"
    "storage_classes/extern"
    "storage_classes/const"
    "storage_classes/volatile"
    "scope/block"
    "scope/file"
    "scope/shadowing"
    "optimization/constant_propagation"
    "optimization/loop_unrolling"
    "optimization/strength_reduction"
    "optimization/dead_code"
    "performance/loops"
    "performance/memory"
    "performance/algorithms"
    "security/buffer_overflow"
    "security/format_strings"
    "security/race_conditions"
    "edge_cases/undefined_behavior"
    "edge_cases/overflow"
    "edge_cases/zero_division"
    "edge_cases/null_pointers"
    "features/recursion"
    "features/variadic"
    "features/inline"
    "features/void"
    "features/function_pointers"
    "features/complex"
    "features/designated"
    "features/compound_literals"
    "features/restrict"
    "features/flexible"
)

# Run tests for each category
for dir in "${test_dirs[@]}"; do
    run_directory_tests "tests/$dir"
done

# Print summary
echo "========================="
echo "Test Summary:"
echo "Total tests: $TOTAL_TESTS"
echo -e "Passed: ${GREEN}$PASSED_TESTS${NC}"
echo -e "Failed: ${RED}$FAILED_TESTS${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed.${NC}"
    exit 1
fi 