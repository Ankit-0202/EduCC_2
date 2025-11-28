/*
 * Test: Integer data types
 * Purpose: Verify that all integer types (int, short, long, char) work
 * correctly Expected Behavior: All integer operations produce correct results
 * and proper type handling Test Cases:
 *   - Declaration and initialization of different integer types
 *   - Arithmetic operations on different integer types
 *   - Type conversion between integer types
 *   - Size and range verification
 * Dependencies: None
 */

int main() {
  // Test different integer types
  char c = 65; // ASCII 'A'
  short s = 1000;
  int i = 42;
  long l = 123456789L;

  // Test arithmetic operations
  int sum = c + s + i + (int)l;

  // Test type conversions
  char converted = (char)i; // 42 -> '*'
  int char_as_int = c;      // 65

  // Test overflow behavior
  char overflow = 300; // Should wrap around

  // Verify results
  if (sum != (65 + 1000 + 42 + 123456789)) {
    return 1; // Sum calculation error
  }

  if (converted != 42) {
    return 2; // Type conversion error
  }

  if (char_as_int != 65) {
    return 3; // Char to int conversion error
  }

  if (overflow != 44) { // 300 % 256 = 44
    return 4;           // Overflow handling error
  }

  return 0; // All tests passed
}