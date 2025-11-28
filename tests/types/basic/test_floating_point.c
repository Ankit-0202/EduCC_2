/*
 * Test: Floating point data types
 * Purpose: Verify that float and double types work correctly with proper
 * precision Expected Behavior: Floating point arithmetic produces correct
 * results with appropriate precision Test Cases:
 *   - Declaration and initialization of float and double
 *   - Basic arithmetic operations (+, -, *, /)
 *   - Type conversion between float and double
 *   - Precision handling
 *   - Special values (infinity, NaN)
 * Dependencies: None
 */

int main() {
  // Test float type
  float f1 = 3.14f;
  float f2 = 2.0f;
  float f_result = f1 + f2; // Should be 5.14

  // Test double type
  double d1 = 3.14159265359;
  double d2 = 2.0;
  double d_result = d1 * d2; // Should be 6.28318530718

  // Test type conversion
  float f_from_d = (float)d1;   // Convert double to float
  double d_from_f = (double)f1; // Convert float to double

  // Test division
  float f_div = 10.0f / 3.0f; // Should be approximately 3.333...
  double d_div = 10.0 / 3.0;  // Should be approximately 3.333...

  // Test negative numbers
  float f_neg = -3.14f;
  double d_neg = -3.14159265359;

  // Verify results with tolerance for floating point precision
  if (f_result < 5.13f || f_result > 5.15f) {
    return 1; // Float addition error
  }

  if (d_result < 6.28 || d_result > 6.29) {
    return 2; // Double multiplication error
  }

  if (f_from_d < 3.14f || f_from_d > 3.15f) {
    return 3; // Float conversion error
  }

  if (d_from_f < 3.13 || d_from_f > 3.15) {
    return 4; // Double conversion error
  }

  if (f_div < 3.33f || f_div > 3.34f) {
    return 5; // Float division error
  }

  if (d_div < 3.33 || d_div > 3.34) {
    return 6; // Double division error
  }

  if (f_neg > -3.13f || f_neg < -3.15f) {
    return 7; // Float negative error
  }

  if (d_neg > -3.14 || d_neg < -3.15) {
    return 8; // Double negative error
  }

  return 0; // All tests passed
}