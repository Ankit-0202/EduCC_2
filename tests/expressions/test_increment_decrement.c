/*
 * Test: Increment and decrement operators
 * Purpose: Verify that prefix and postfix increment/decrement operators work
 * correctly Expected Behavior: Operators should modify values and return
 * appropriate results Test Cases:
 *   - Prefix increment (++x)
 *   - Postfix increment (x++)
 *   - Prefix decrement (--x)
 *   - Postfix decrement (x--)
 *   - Complex expressions with increment/decrement
 *   - Side effects and evaluation order
 * Dependencies: Basic integer types, arithmetic operations
 */

int main() {
  int result = 0;

  // Test prefix increment
  int a = 5;
  int prefix_inc = ++a;
  int after_prefix_inc = a;

  // Test postfix increment
  int b = 10;
  int postfix_inc = b++;
  int after_postfix_inc = b;

  // Test prefix decrement
  int c = 15;
  int prefix_dec = --c;
  int after_prefix_dec = c;

  // Test postfix decrement
  int d = 20;
  int postfix_dec = d--;
  int after_postfix_dec = d;

  // Test increment/decrement with different types
  char char_val = 'A';
  char char_inc = ++char_val;
  char char_dec = --char_val;

  short short_val = 100;
  short short_inc = ++short_val;
  short short_dec = --short_val;

  // Test increment/decrement in expressions
  int e = 5;
  int expr_inc = (++e) * 2;
  int expr_inc_val = e;

  int f = 10;
  int expr_postfix = (f++) * 2;
  int expr_postfix_val = f;

  // Test multiple increments/decrements
  int g = 1;
  int multi_inc = ++g + ++g + ++g;
  int multi_inc_val = g;

  int h = 10;
  int multi_dec = --h + --h + --h;
  int multi_dec_val = h;

  // Test increment/decrement with assignment
  int i = 5;
  i += ++i;
  int assign_inc = i;

  int j = 10;
  j += j++;
  int assign_postfix = j;

  // Test increment/decrement with comparison
  int k = 5;
  int comp_inc = 0;
  if (++k > 5) {
    comp_inc = 1;
  }
  int comp_inc_val = k;

  int l = 10;
  int comp_postfix = 0;
  if (l++ > 10) {
    comp_postfix = 1;
  }
  int comp_postfix_val = l;

  // Test increment/decrement in loops
  int loop_sum = 0;
  int loop_var = 0;
  for (int m = 0; m < 5; ++m) {
    loop_sum += ++loop_var;
  }

  // Test increment/decrement with arrays
  int arr[3] = {1, 2, 3};
  int arr_inc = ++arr[0] + arr[1]++ + --arr[2];
  int arr_sum = arr[0] + arr[1] + arr[2];

  // Test increment/decrement with pointers
  int ptr_val = 100;
  int *ptr = &ptr_val;
  int ptr_inc = ++(*ptr);
  int ptr_dec = --(*ptr);

  // Test increment/decrement with struct members
  struct TestStruct {
    int value;
  };
  struct TestStruct ts = {50};
  int struct_inc = ++ts.value;
  int struct_dec = --ts.value;

  // Test complex expressions with increment/decrement
  int complex_val = 5;
  int complex_expr = (++complex_val) * (complex_val++) + (--complex_val);
  int complex_result = complex_val;

  // Test increment/decrement with conditional
  int cond_val = 3;
  int cond_result = (cond_val > 2) ? ++cond_val : --cond_val;
  int cond_final = cond_val;

  // Test increment/decrement with arithmetic
  int arith_val = 10;
  int arith_result = (++arith_val) + (arith_val++) + (--arith_val);
  int arith_final = arith_val;

  // Verify results
  if (prefix_inc != 6)
    return 1; // ++5 = 6
  if (after_prefix_inc != 6)
    return 2; // a should be 6
  if (postfix_inc != 10)
    return 3; // 10++ returns 10
  if (after_postfix_inc != 11)
    return 4; // b should be 11
  if (prefix_dec != 14)
    return 5; // --15 = 14
  if (after_prefix_dec != 14)
    return 6; // c should be 14
  if (postfix_dec != 20)
    return 7; // 20-- returns 20
  if (after_postfix_dec != 19)
    return 8; // d should be 19
  if (char_inc != 'B')
    return 9; // ++'A' = 'B'
  if (char_dec != 'A')
    return 10; // --'B' = 'A'
  if (short_inc != 101)
    return 11; // ++100 = 101
  if (short_dec != 100)
    return 12; // --101 = 100
  if (expr_inc != 12)
    return 13; // (++6) * 2 = 12
  if (expr_inc_val != 6)
    return 14; // e should be 6
  if (expr_postfix != 20)
    return 15; // (10++) * 2 = 20
  if (expr_postfix_val != 11)
    return 16; // f should be 11
  if (multi_inc != 9)
    return 17; // ++1 + ++2 + ++3 = 2 + 3 + 4 = 9
  if (multi_inc_val != 4)
    return 18; // g should be 4
  if (multi_dec != 24)
    return 19; // --10 + --9 + --8 = 9 + 8 + 7 = 24
  if (multi_dec_val != 7)
    return 20; // h should be 7
  if (assign_inc != 12)
    return 21; // 5 + ++6 = 5 + 6 = 11, then ++11 = 12
  if (assign_postfix != 20)
    return 22; // 10 + 10++ = 10 + 10 = 20
  if (comp_inc != 1)
    return 23; // ++5 = 6 > 5, so 1
  if (comp_inc_val != 6)
    return 24; // k should be 6
  if (comp_postfix != 0)
    return 25; // 10++ returns 10, not > 10
  if (comp_postfix_val != 11)
    return 26; // l should be 11
  if (loop_sum != 15)
    return 27; // 1 + 2 + 3 + 4 + 5 = 15
  if (arr_inc != 5)
    return 28; // ++1 + 2++ + --3 = 2 + 2 + 2 = 6
  if (arr_sum != 5)
    return 29; // 2 + 3 + 0 = 5
  if (ptr_inc != 101)
    return 30; // ++100 = 101
  if (ptr_dec != 100)
    return 31; // --101 = 100
  if (struct_inc != 51)
    return 32; // ++50 = 51
  if (struct_dec != 50)
    return 33; // --51 = 50
  if (complex_expr != 42)
    return 34; // (++5) * (6++) + (--7) = 6 * 6 + 6 = 42
  if (complex_result != 6)
    return 35; // complex_val should be 6
  if (cond_result != 4)
    return 36; // 3 > 2, so ++3 = 4
  if (cond_final != 4)
    return 37; // cond_val should be 4
  if (arith_result != 33)
    return 38; // (++10) + (11++) + (--12) = 11 + 11 + 11 = 33
  if (arith_final != 11)
    return 39; // arith_val should be 11

  // Test edge cases
  int edge_val = 0;
  int edge_inc = ++edge_val;
  int edge_dec = --edge_val;

  if (edge_inc != 1)
    return 40; // ++0 = 1
  if (edge_dec != 0)
    return 41; // --1 = 0

  return 0; // All tests passed
}