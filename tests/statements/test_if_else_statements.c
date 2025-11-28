/*
 * Test: If-else statements and conditional execution
 * Purpose: Verify that if-else statements work correctly with proper branching
 * Expected Behavior: Conditional statements execute the correct branch based on
 * condition evaluation Test Cases:
 *   - Simple if statements
 *   - If-else statements
 *   - Nested if-else statements
 *   - Complex boolean conditions
 *   - Edge cases (zero, negative values)
 * Dependencies: Basic integer types, logical operations
 */

int main() {
  int result = 0;

  // Test simple if statement
  int a = 5;
  int b = 10;

  if (a < b) {
    result += 1; // Should execute
  }

  if (a > b) {
    result += 10; // Should not execute
  }

  // Test if-else statement
  if (a == 5) {
    result += 2; // Should execute
  } else {
    result += 20; // Should not execute
  }

  if (a == 10) {
    result += 30; // Should not execute
  } else {
    result += 3; // Should execute
  }

  // Test nested if-else
  if (a > 0) {
    if (b > 0) {
      result += 4; // Should execute
    } else {
      result += 40; // Should not execute
    }
  } else {
    result += 400; // Should not execute
  }

  // Test complex boolean conditions
  if (a > 0 && b > 0 && a < b) {
    result += 5; // Should execute
  }

  if (a > 0 || b < 0) {
    result += 6; // Should execute (a > 0 is true)
  }

  if (!(a > b)) {
    result += 7; // Should execute (!false = true)
  }

  // Test edge cases
  int zero = 0;
  int negative = -5;

  if (zero) {
    result += 50; // Should not execute
  } else {
    result += 8; // Should execute
  }

  if (negative) {
    result += 9; // Should execute (non-zero is true)
  } else {
    result += 60; // Should not execute
  }

  if (!zero) {
    result += 10; // Should execute (!0 = true)
  }

  if (!negative) {
    result += 70; // Should not execute (!(-5) = false)
  }

  // Test multiple conditions
  int c = 15;

  if (a < b && b < c) {
    result += 11; // Should execute (5 < 10 && 10 < 15)
  }

  if (a > b || b < c) {
    result += 12; // Should execute (false || true = true)
  }

  if ((a + b) > c) {
    result += 13; // Should execute (5 + 10 = 15 > 15 = false)
  } else {
    result += 14; // Should execute (15 is not > 15)
  }

  // Test with floating point
  float f = 3.14f;

  if (f > 3.0f) {
    result += 15; // Should execute
  }

  if (f < 4.0f) {
    result += 16; // Should execute
  }

  // Verify final result
  // Expected: 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 + 11 + 12 + 14 + 15 + 16 =
  // 123
  if (result != 123) {
    return 1; // Incorrect result
  }

  return 0; // All tests passed
}