/*
 * Test: Loop statements (while, for, nested loops)
 * Purpose: Verify that all loop constructs work correctly with proper iteration
 * and control flow Expected Behavior: Loops execute the correct number of
 * iterations and handle control flow properly Test Cases:
 *   - While loops with simple conditions
 *   - For loops with initialization, condition and increment
 *   - Nested loops
 *   - Loop control (break, continue)
 *   - Complex loop conditions
 *   - Edge cases (empty loops, zero iterations)
 * Dependencies: Basic integer types, arithmetic operations
 */

int main() {
  int result = 0;

  // Test while loop
  int i = 0;
  while (i < 5) {
    result += i;
    i++;
  }
  // Expected: 0 + 1 + 2 + 3 + 4 = 10

  // Test for loop
  int sum = 0;
  for (int j = 1; j <= 5; j++) {
    sum += j;
  }
  // Expected: 1 + 2 + 3 + 4 + 5 = 15

  // Test nested loops
  int nested_sum = 0;
  for (int k = 0; k < 3; k++) {
    for (int l = 0; l < 3; l++) {
      nested_sum += k * l;
    }
  }
  // Expected: (0*0 + 0*1 + 0*2) + (1*0 + 1*1 + 1*2) + (2*0 + 2*1 + 2*2) = 9

  // Test while loop with complex condition
  int x = 10;
  int while_result = 0;
  while (x > 0 && x % 2 == 0) {
    while_result += x;
    x -= 2;
  }
  // Expected: 10 + 8 + 6 + 4 + 2 = 30

  // Test for loop with multiple variables
  int multi_sum = 0;
  for (int a = 0, b = 10; a < 5 && b > 5; a++, b--) {
    multi_sum += a * b;
  }
  // Expected: 0*10 + 1*9 + 2*8 + 3*7 + 4*6 = 0 + 9 + 16 + 21 + 24 = 70

  // Test break statement
  int break_sum = 0;
  for (int m = 0; m < 10; m++) {
    if (m == 5) {
      break;
    }
    break_sum += m;
  }
  // Expected: 0 + 1 + 2 + 3 + 4 = 10

  // Test continue statement
  int continue_sum = 0;
  for (int n = 0; n < 6; n++) {
    if (n % 2 == 0) {
      continue;
    }
    continue_sum += n;
  }
  // Expected: 1 + 3 + 5 = 9

  // Test nested break
  int nested_break = 0;
  for (int p = 0; p < 3; p++) {
    for (int q = 0; q < 3; q++) {
      if (p == 1 && q == 1) {
        break;
      }
      nested_break += p + q;
    }
  }
  // Expected: (0+0 + 0+1 + 0+2) + (1+0) + (2+0 + 2+1 + 2+2) = 3 + 1 + 7 = 11

  // Test while loop with decrement
  int decrement_sum = 0;
  int y = 5;
  while (y > 0) {
    decrement_sum += y;
    y--;
  }
  // Expected: 5 + 4 + 3 + 2 + 1 = 15

  // Test for loop with step
  int step_sum = 0;
  for (int z = 0; z < 10; z += 2) {
    step_sum += z;
  }
  // Expected: 0 + 2 + 4 + 6 + 8 = 20

  // Test empty loop
  int empty_count = 0;
  for (int w = 0; w < 0; w++) {
    empty_count++;
  }
  // Expected: 0 (loop should not execute)

  // Test loop with floating point
  float float_sum = 0.0f;
  for (float f = 0.0f; f < 5.0f; f += 1.0f) {
    float_sum += f;
  }
  // Expected: 0.0 + 1.0 + 2.0 + 3.0 + 4.0 = 10.0

  // Verify all results
  if (result != 10)
    return 1; // while loop
  if (sum != 15)
    return 2; // for loop
  if (nested_sum != 9)
    return 3; // nested loops
  if (while_result != 30)
    return 4; // complex while
  if (multi_sum != 70)
    return 5; // multiple variables
  if (break_sum != 10)
    return 6; // break statement
  if (continue_sum != 9)
    return 7; // continue statement
  if (nested_break != 11)
    return 8; // nested break
  if (decrement_sum != 15)
    return 9; // decrement while
  if (step_sum != 20)
    return 10; // step for loop
  if (empty_count != 0)
    return 11; // empty loop
  if (float_sum < 9.9f || float_sum > 10.1f)
    return 12; // float loop

  return 0; // All tests passed
}