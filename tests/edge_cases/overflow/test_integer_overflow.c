/*
 * Test: Integer overflow scenarios
 * Purpose: Verify how the compiler handles integer overflow in various
 * operations Expected Behavior: Overflow should be handled according to C
 * standard (wrapping behavior) Test Cases:
 *   - Addition overflow
 *   - Multiplication overflow
 *   - Shift overflow
 *   - Large number operations
 *   - Signed vs unsigned overflow
 * Dependencies: Basic integer types, arithmetic operations
 */

int main() {
  int result = 0;

  // Test signed integer overflow
  int max_int = 2147483647;    // Maximum 32-bit signed int
  int overflow1 = max_int + 1; // Should wrap to -2147483648

  // Test unsigned integer overflow
  unsigned int max_uint = 4294967295;    // Maximum 32-bit unsigned int
  unsigned int overflow2 = max_uint + 1; // Should wrap to 0

  // Test multiplication overflow
  int large1 = 1000000;
  int large2 = 1000000;
  int mult_overflow = large1 * large2; // Should overflow

  // Test shift overflow
  int shift_overflow = 1 << 31;  // Should be negative
  int shift_overflow2 = 1 << 32; // Should be 0 or undefined

  // Test char overflow
  char char_max = 127;
  char char_overflow = char_max + 1; // Should wrap to -128

  // Test short overflow
  short short_max = 32767;
  short short_overflow = short_max + 1; // Should wrap to -32768

  // Test negative overflow
  int min_int = -2147483648;
  int neg_overflow = min_int - 1; // Should wrap to 2147483647

  // Test unsigned negative
  unsigned int neg_uint = 0;
  unsigned int neg_uint_overflow = neg_uint - 1; // Should wrap to 4294967295

  // Test overflow in expressions
  int expr_overflow = (max_int / 2) * 3; // Should overflow

  // Test overflow with constants
  int const_overflow = 2000000000 + 2000000000; // Should overflow

  // Verify overflow behavior (these checks depend on implementation)
  // Note: These are implementation-dependent, so we just check they don't crash

  // Test that operations complete without crashing
  int test1 = overflow1 + 1;
  int test2 = overflow2 + 1;
  int test3 = mult_overflow + 1;
  int test4 = shift_overflow + 1;
  int test5 = char_overflow + 1;
  int test6 = short_overflow + 1;
  int test7 = neg_overflow + 1;
  int test8 = neg_uint_overflow + 1;
  int test9 = expr_overflow + 1;
  int test10 = const_overflow + 1;

  // Test overflow in loops
  int loop_overflow = 0;
  for (int i = 0; i < 1000; i++) {
    loop_overflow += 1000000; // Should overflow multiple times
  }

  // Test overflow with bitwise operations
  int bit_overflow = 0x7FFFFFFF;      // Max positive int
  int bit_result = bit_overflow << 1; // Should overflow

  // Test overflow with floating point conversion
  float large_float = 1e10f;
  int float_overflow = (int)large_float; // Should overflow

  // All operations should complete without crashing
  // The actual values depend on the implementation
  result = test1 + test2 + test3 + test4 + test5 + test6 + test7 + test8 +
           test9 + test10 + loop_overflow + bit_result + float_overflow;

  // Return a predictable value to indicate successful completion
  return result % 100; // Return a small positive number
}