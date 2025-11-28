/*
 * Test: Arithmetic operations and operator precedence
 * Purpose: Verify that all arithmetic operations work correctly with proper
 * precedence Expected Behavior: All arithmetic expressions evaluate to correct
 * results following C precedence rules Test Cases:
 *   - Basic arithmetic operations (+, -, *, /, %)
 *   - Operator precedence rules
 *   - Parentheses grouping
 *   - Mixed type arithmetic
 *   - Unary operators (+, -)
 * Dependencies: Basic integer and floating point types
 */

int main() {
  // Test basic arithmetic operations
  int a = 10;
  int b = 3;
  int c = 7;

  // Addition, subtraction, multiplication, division
  int sum = a + b;       // 13
  int diff = a - b;      // 7
  int product = a * b;   // 30
  int quotient = a / b;  // 3
  int remainder = a % b; // 1

  // Test operator precedence
  int precedence1 = a + b * c;   // 10 + (3 * 7) = 31
  int precedence2 = (a + b) * c; // (10 + 3) * 7 = 91
  int precedence3 = a * b + c;   // (10 * 3) + 7 = 37

  // Test unary operators
  int unary_neg = -a; // -10
  int unary_pos = +b; // 3

  // Test complex expressions
  int d = 10;
  int e = 5;
  int complex1 = a + b * c - d / e; // 10 + 21 - 2 = 29
  int complex2 = (a + b) * (c - d); // 13 * -3 = -39

  // Test mixed type arithmetic
  float f = 3.5f;
  int mixed = a + f; // 10 + 3.5 = 13.5 (truncated to 13)

  // Verify results
  if (sum != 13)
    return 1;
  if (diff != 7)
    return 2;
  if (product != 30)
    return 3;
  if (quotient != 3)
    return 4;
  if (remainder != 1)
    return 5;

  if (precedence1 != 31)
    return 6;
  if (precedence2 != 91)
    return 7;
  if (precedence3 != 37)
    return 8;

  if (unary_neg != -10)
    return 9;
  if (unary_pos != 3)
    return 10;

  // Test large numbers
  int large1 = 1000000;
  int large2 = 2000000;
  int large_sum = large1 + large2; // 3000000

  if (large_sum != 3000000)
    return 11;

  return 0; // All tests passed
}