/*
 * Test: Logical operations and short-circuit evaluation
 * Purpose: Verify that logical operations work correctly with proper
 * short-circuit behavior Expected Behavior: Logical expressions evaluate
 * correctly with proper short-circuit evaluation Test Cases:
 *   - Logical AND (&&) or (||), NOT (!)
 *   - Short-circuit evaluation
 *   - Complex logical expressions
 *   - Truth tables verification
 *   - Mixed logical and arithmetic operations
 * Dependencies: Basic integer types
 */

int main() {
  // Test basic logical operations
  int true_val = 1;
  int false_val = 0;

  // Logical AND
  int and_true = true_val && true_val;     // 1
  int and_false1 = true_val && false_val;  // 0
  int and_false2 = false_val && true_val;  // 0
  int and_false3 = false_val && false_val; // 0

  // Logical OR
  int or_true1 = true_val || true_val;   // 1
  int or_true2 = true_val || false_val;  // 1
  int or_true3 = false_val || true_val;  // 1
  int or_false = false_val || false_val; // 0

  // Logical NOT
  int not_true = !true_val;   // 0
  int not_false = !false_val; // 1
  int not_zero = !0;          // 1
  int not_nonzero = !42;      // 0

  // Test short-circuit evaluation
  int side_effect = 0;
  int short_circuit1 =
      false_val && (side_effect = 1); // Should not set side_effect
  int short_circuit2 =
      true_val || (side_effect = 1); // Should not set side_effect

  // Test complex logical expressions
  int a = 5;
  int b = 10;
  int c = 0;

  int complex1 = (a < b) && (b > c) && (a != 0); // true && true && true = true
  int complex2 =
      (a > b) || (b < c) || (a == 5);   // false || false || true = true
  int complex3 = !(a == b) && (b != c); // !false && true = true

  // Test mixed logical and arithmetic
  int mixed1 = (a + b > 10) && (a * b < 100); // true && false = false
  int mixed2 = (a - b < 0) || (a / b > 0);    // true || false = true

  // Verify basic logical operations
  if (and_true != 1)
    return 1;
  if (and_false1 != 0)
    return 2;
  if (and_false2 != 0)
    return 3;
  if (and_false3 != 0)
    return 4;

  if (or_true1 != 1)
    return 5;
  if (or_true2 != 1)
    return 6;
  if (or_true3 != 1)
    return 7;
  if (or_false != 0)
    return 8;

  if (not_true != 0)
    return 9;
  if (not_false != 1)
    return 10;
  if (not_zero != 1)
    return 11;
  if (not_nonzero != 0)
    return 12;

  // Verify short-circuit behavior
  if (side_effect != 0)
    return 13; // side_effect should remain 0

  // Verify complex expressions
  if (complex1 != 1)
    return 14;
  if (complex2 != 1)
    return 15;
  if (complex3 != 1)
    return 16;

  // Verify mixed expressions
  if (mixed1 != 0)
    return 17;
  if (mixed2 != 1)
    return 18;

  // Test edge cases with non-zero values
  int non_zero1 = 42;
  int non_zero2 = -1;

  int edge1 = non_zero1 && non_zero2; // true && true = true
  int edge2 = non_zero1 || non_zero2; // true || true = true
  int edge3 = !non_zero1;             // !true = false

  if (edge1 != 1)
    return 19;
  if (edge2 != 1)
    return 20;
  if (edge3 != 0)
    return 21;

  return 0; // All tests passed
}