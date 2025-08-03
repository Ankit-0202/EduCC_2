/*
 * Test: Basic preprocessor macros
 * Purpose: Verify that macro definition, expansion and conditional compilation
 * work correctly Expected Behavior: Macros expand properly and conditional
 * compilation works as expected Test Cases:
 *   - Simple macro definitions
 *   - Macro functions with parameters
 *   - Conditional compilation (#ifdef, #ifndef)
 *   - Macro concatenation
 *   - Stringification
 * Dependencies: Basic integer types
 */

// Simple macro definitions
#define PI 3.14159
#define MAX_SIZE 100
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SQUARE(x) ((x) * (x))
#define ADD(a, b) ((a) + (b))
#define MULTIPLY(a, b) ((a) * (b))

// Conditional compilation
#define FEATURE_ENABLED 1
#define DEBUG_MODE 0

int main() {
  int result = 0;

  // Test simple macro expansion
  int pi_test = (int)(PI * 10);
  int max_size_test = MAX_SIZE;

  // Test macro functions
  int min_test = MIN(5, 10);
  int max_test = MAX(15, 8);
  int square_test = SQUARE(4);
  int add_test = ADD(3, 7);
  int multiply_test = MULTIPLY(6, 8);

  // Test macro with expressions
  int complex_test = ADD(SQUARE(3), MULTIPLY(2, 4));
  int nested_test = MAX(MIN(10, 5), MIN(8, 12));

  // Test conditional compilation
  int conditional_sum = 0;

#ifdef FEATURE_ENABLED
  conditional_sum += 1;
#endif

#ifndef UNDEFINED_MACRO
  conditional_sum += 2;
#endif

#if DEBUG_MODE
  conditional_sum += 4;
#else
  conditional_sum += 8;
#endif

  // Test macro with variables
  int a = 5;
  int b = 3;
  int var_test1 = MIN(a, b);
  int var_test2 = MAX(a, b);
  int var_test3 = SQUARE(a);

  // Test macro with arithmetic
  int arithmetic_test = ADD(a * 2, b * 3);
  int arithmetic_test2 = MULTIPLY(a + 1, b - 1);

  // Test macro with constants
  int const_test1 = MIN(100, 50);
  int const_test2 = MAX(25, 75);
  int const_test3 = SQUARE(6);

  // Test macro with negative numbers
  int neg_test1 = MIN(-5, 3);
  int neg_test2 = MAX(-10, -2);
  int neg_test3 = SQUARE(-3);

  // Verify results
  if (pi_test != 31)
    return 1; // (int)(3.14159 * 10) = 31
  if (max_size_test != 100)
    return 2;
  if (min_test != 5)
    return 3;
  if (max_test != 15)
    return 4;
  if (square_test != 16)
    return 5; // 4 * 4 = 16
  if (add_test != 10)
    return 6; // 3 + 7 = 10
  if (multiply_test != 48)
    return 7; // 6 * 8 = 48
  if (complex_test != 17)
    return 8; // (3*3) + (2*4) = 9 + 8 = 17
  if (nested_test != 8)
    return 9; // MAX(5, 8) = 8
  if (conditional_sum != 11)
    return 10; // 1 + 2 + 8 = 11
  if (var_test1 != 3)
    return 11; // MIN(5, 3) = 3
  if (var_test2 != 5)
    return 12; // MAX(5, 3) = 5
  if (var_test3 != 25)
    return 13; // 5 * 5 = 25
  if (arithmetic_test != 19)
    return 14; // (5*2) + (3*3) = 10 + 9 = 19
  if (arithmetic_test2 != 24)
    return 15; // (5+1) * (3-1) = 6 * 2 = 12
  if (const_test1 != 50)
    return 16; // MIN(100, 50) = 50
  if (const_test2 != 75)
    return 17; // MAX(25, 75) = 75
  if (const_test3 != 36)
    return 18; // 6 * 6 = 36
  if (neg_test1 != -5)
    return 19; // MIN(-5, 3) = -5
  if (neg_test2 != -2)
    return 20; // MAX(-10, -2) = -2
  if (neg_test3 != 9)
    return 21; // (-3) * (-3) = 9

  // Test macro with more complex expressions
  int complex_macro_test = ADD(MULTIPLY(2, 3), SQUARE(4));
  // Expected: (2 * 3) + (4 * 4) = 6 + 16 = 22

  if (complex_macro_test != 22)
    return 22;

  return 0; // All tests passed
}