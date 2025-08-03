/*
 * Test: Comma operator and comma expressions
 * Purpose: Verify that the comma operator works correctly with proper
 * evaluation order Expected Behavior: Comma operator should evaluate left
 * operand, discard result, then evaluate right operand Test Cases:
 *   - Basic comma operator
 *   - Comma operator with side effects
 *   - Comma operator in expressions
 *   - Comma operator with function calls
 *   - Comma operator with assignments
 *   - Comma operator in loops
 * Dependencies: Basic integer types, functions, assignments
 */

// Function to test side effects
int side_effect_func(int *counter) {
  (*counter)++;
  return *counter;
}

// Function that returns a value
int return_value_func(int x) { return x * 2; }

int main() {
  int result = 0;

  // Test basic comma operator
  int basic_comma = (1, 2);
  int basic_comma2 = (3, 4, 5);
  // Expected: 2, 5 (last value is the result)

  // Test comma operator with side effects
  int counter = 0;
  int side_effect_result =
      (side_effect_func(&counter), side_effect_func(&counter));
  // Expected: counter becomes 2, result is 2

  // Test comma operator with assignments
  int a = 0, b = 0;
  int assign_result = (a = 5, b = 10, a + b);
  // Expected: a = 5, b = 10, result = 15

  // Test comma operator with arithmetic
  int arith_result = (1 + 2, 3 * 4, 5 - 6);
  // Expected: 3, 12, -1 (result is -1)

  // Test comma operator with comparison
  int comp_result = (1 < 2, 3 > 4, 5 == 5);
  // Expected: 1, 0, 1 (result is 1)

  // Test comma operator with logical operations
  int logical_result = (1 && 1, 0 || 1, 1 && 0);
  // Expected: 1, 1, 0 (result is 0)

  // Test comma operator with bitwise operations
  int bitwise_result = (1 & 1, 2 | 1, 3 ^ 1);
  // Expected: 1, 3, 2 (result is 2)

  // Test comma operator with function calls
  int func_result =
      (return_value_func(1), return_value_func(2), return_value_func(3));
  // Expected: 2, 4, 6 (result is 6)

  // Test comma operator in conditional
  int cond_result = 0;
  if (1, 0) {
    cond_result = 1;
  }
  // Expected: cond_result = 0 (since 0 is false)

  // Test comma operator in ternary
  int ternary_result = (1, 0) ? 10 : 20;
  // Expected: 20 (since 0 is false)

  // Test comma operator in loop
  int loop_sum = 0;
  for (int i = 0; i < 3; i++, loop_sum += i) {
    // Loop body
  }
  // Expected: loop_sum = 6 (1 + 2 + 3)

  // Test comma operator with multiple assignments
  int x = 0, y = 0, z = 0;
  int multi_assign = (x = 1, y = 2, z = 3, x + y + z);
  // Expected: x = 1, y = 2, z = 3, result = 6

  // Test comma operator with pointer operations
  int ptr_val = 100;
  int *ptr = &ptr_val;
  int ptr_result = (*ptr = 200, *ptr + 50);
  // Expected: ptr_val = 200, result = 250

  // Test comma operator with array operations
  int arr[3] = {1, 2, 3};
  int arr_result =
      (arr[0] = 10, arr[1] = 20, arr[2] = 30, arr[0] + arr[1] + arr[2]);
  // Expected: arr = {10, 20, 30}, result = 60

  // Test comma operator with struct operations
  struct TestStruct {
    int a;
    int b;
  };
  struct TestStruct ts = {0, 0};
  int struct_result = (ts.a = 5, ts.b = 10, ts.a * ts.b);
  // Expected: ts.a = 5, ts.b = 10, result = 50

  // Test comma operator with complex expressions
  int complex_result = (1 + 2 * 3, 4 - 5 / 2, 6 % 4);
  // Expected: 7, 1, 2 (result is 2)

  // Test comma operator with nested expressions
  int nested_result = ((1, 2), (3, 4), (5, 6));
  // Expected: 2, 4, 6 (result is 6)

  // Test comma operator with conditional expressions
  int cond_expr_result = (1 > 0, 2 < 1, 3 == 3);
  // Expected: 1, 0, 1 (result is 1)

  // Test comma operator with arithmetic chains
  int arith_chain_result = (1 + 1, 2 * 2, 3 - 1, 4 / 2);
  // Expected: 2, 4, 2, 2 (result is 2)

  // Test comma operator with comparison chains
  int comp_chain_result = (1 < 2, 2 < 3, 3 < 4, 4 < 5);
  // Expected: 1, 1, 1, 1 (result is 1)

  // Test comma operator with logical chains
  int logical_chain_result = (1 && 1, 1 && 0, 0 && 1, 0 && 0);
  // Expected: 1, 0, 0, 0 (result is 0)

  // Test comma operator with bitwise chains
  int bitwise_chain_result = (1 & 1, 2 & 1, 3 & 1, 4 & 1);
  // Expected: 1, 0, 1, 0 (result is 0)

  // Test comma operator with function call chains
  int func_chain_result = (return_value_func(1), return_value_func(2),
                           return_value_func(3), return_value_func(4));
  // Expected: 2, 4, 6, 8 (result is 8)

  // Test comma operator with mixed operations
  int mixed_result = (1 + 2, 3 * 4, 5 > 3, 6 < 10);
  // Expected: 3, 12, 1, 1 (result is 1)

  // Test comma operator with side effect chains
  int side_effect_chain = 0;
  int side_chain_result = (side_effect_func(&side_effect_chain),
                           side_effect_func(&side_effect_chain),
                           side_effect_func(&side_effect_chain),
                           side_effect_func(&side_effect_chain));
  // Expected: side_effect_chain = 4, result = 4

  // Test comma operator with assignment chains
  int assign_chain_a = 0, assign_chain_b = 0, assign_chain_c = 0;
  int assign_chain_result =
      (assign_chain_a = 1, assign_chain_b = assign_chain_a * 2,
       assign_chain_c = assign_chain_b * 3,
       assign_chain_a + assign_chain_b + assign_chain_c);
  // Expected: a = 1, b = 2, c = 6, result = 9

  // Test comma operator with pointer arithmetic
  int ptr_arith_val = 100;
  int *ptr_arith = &ptr_arith_val;
  int ptr_arith_result =
      (*ptr_arith = 200, *(ptr_arith + 0) = 300, *ptr_arith + 50);
  // Expected: ptr_arith_val = 300, result = 350

  // Test comma operator with array arithmetic
  int arr_arith[3] = {1, 2, 3};
  int arr_arith_result =
      (arr_arith[0] = arr_arith[0] * 2, arr_arith[1] = arr_arith[1] * 2,
       arr_arith[2] = arr_arith[2] * 2,
       arr_arith[0] + arr_arith[1] + arr_arith[2]);
  // Expected: arr = {2, 4, 6}, result = 12

  // Verify results
  if (basic_comma != 2)
    return 1;
  if (basic_comma2 != 5)
    return 2;
  if (side_effect_result != 2)
    return 3;
  if (counter != 2)
    return 4;
  if (assign_result != 15)
    return 5;
  if (arith_result != -1)
    return 6;
  if (comp_result != 1)
    return 7;
  if (logical_result != 0)
    return 8;
  if (bitwise_result != 2)
    return 9;
  if (func_result != 6)
    return 10;
  if (cond_result != 0)
    return 11;
  if (ternary_result != 20)
    return 12;
  if (loop_sum != 6)
    return 13;
  if (multi_assign != 6)
    return 14;
  if (ptr_result != 250)
    return 15;
  if (arr_result != 60)
    return 16;
  if (struct_result != 50)
    return 17;
  if (complex_result != 2)
    return 18;
  if (nested_result != 6)
    return 19;
  if (cond_expr_result != 1)
    return 20;
  if (arith_chain_result != 2)
    return 21;
  if (comp_chain_result != 1)
    return 22;
  if (logical_chain_result != 0)
    return 23;
  if (bitwise_chain_result != 0)
    return 24;
  if (func_chain_result != 8)
    return 25;
  if (mixed_result != 1)
    return 26;
  if (side_chain_result != 4)
    return 27;
  if (side_effect_chain != 4)
    return 28;
  if (assign_chain_result != 9)
    return 29;
  if (ptr_arith_result != 350)
    return 30;
  if (arr_arith_result != 12)
    return 31;

  // Test comma operator with edge cases
  int edge_result = (0, 0, 0, 1);
  if (edge_result != 1)
    return 32;

  // Test comma operator with single expression
  int single_result = (42);
  if (single_result != 42)
    return 33;

  return 0; // All tests passed
}