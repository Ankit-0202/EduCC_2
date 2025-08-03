/*
 * Test: Volatile qualifiers and volatile expressions
 * Purpose: Verify that volatile qualifiers work correctly for variables,
 * pointers and parameters Expected Behavior: Volatile variables should be
 * treated as potentially changing and volatile expressions should work properly
 * Test Cases:
 *   - Volatile variable declarations
 *   - Volatile pointers
 *   - Volatile function parameters
 *   - Volatile arrays
 *   - Volatile struct members
 *   - Volatile expressions
 * Dependencies: Basic integer types, pointers, structs
 */

// Function with volatile parameter
int test_volatile_param(volatile int value) { return value * 2; }

// Function with volatile pointer parameter
int test_volatile_ptr(volatile int *ptr) { return *ptr * 3; }

// Function that returns volatile value
volatile int get_volatile_value() { return 42; }

int main() {
  int result = 0;

  // Test volatile variable declarations
  volatile int volatile_val = 10;
  volatile float volatile_float = 3.14f;
  volatile char volatile_char = 'A';

  // Test volatile expressions
  int volatile_expr = volatile_val * 2;
  float volatile_float_expr = volatile_float * 2.0f;
  int volatile_char_expr = volatile_char + 1;
  // Expected: 20, 6.28, 66 ('B')

  // Test volatile with arithmetic
  volatile int volatile_arith = 5;
  int arith_result = volatile_arith + 3;
  int arith_result2 = volatile_arith * 4;
  // Expected: 8, 20

  // Test volatile with comparison
  volatile int volatile_comp = 7;
  int comp_result = 0;
  if (volatile_comp > 5) {
    comp_result = 1;
  }
  // Expected: 1

  // Test volatile with conditional
  volatile int volatile_cond = 3;
  int cond_result = (volatile_cond > 2) ? volatile_cond * 2 : volatile_cond;
  // Expected: 6 (since 3 > 2)

  // Test volatile with function call
  int func_result = test_volatile_param(volatile_val);
  // Expected: 10 * 2 = 20

  // Test volatile pointer
  int regular_val = 15;
  volatile int *volatile_ptr = &regular_val;
  int ptr_result = test_volatile_ptr(volatile_ptr);
  // Expected: 15 * 3 = 45

  // Test volatile array
  volatile int volatile_array[3] = {1, 2, 3};
  int array_sum = 0;
  for (int i = 0; i < 3; i++) {
    array_sum += volatile_array[i];
  }
  // Expected: 1 + 2 + 3 = 6

  // Test volatile struct
  struct VolatileStruct {
    volatile int value;
    int regular_value;
  };
  struct VolatileStruct vs = {10, 20};
  int struct_result = vs.value + vs.regular_value;
  // Expected: 10 + 20 = 30

  // Test volatile with different types
  volatile short volatile_short = 100;
  volatile long volatile_long = 1000L;
  int type_result = volatile_short + volatile_long;
  // Expected: 100 + 1000 = 1100

  // Test volatile with bitwise operations
  volatile int volatile_bit = 5;
  int bit_result = volatile_bit << 2;
  // Expected: 5 << 2 = 20

  // Test volatile with logical operations
  volatile int volatile_logical = 0;
  int logical_result = !volatile_logical;
  // Expected: 1 (since !0 = 1)

  // Test volatile with ternary operator
  volatile int volatile_ternary = 8;
  int ternary_result = (volatile_ternary > 5) ? volatile_ternary : 0;
  // Expected: 8 (since 8 > 5)

  // Test volatile with expressions
  volatile int volatile_expr1 = 3;
  volatile int volatile_expr2 = 4;
  int expr_result = volatile_expr1 * volatile_expr2 + volatile_expr1;
  // Expected: 3 * 4 + 3 = 15

  // Test volatile with function-like behavior
  volatile int volatile_func = 6;
  int func_like_result = volatile_func * volatile_func;
  // Expected: 6 * 6 = 36

  // Test volatile with pointer arithmetic
  volatile int volatile_ptr_val = 25;
  volatile int *volatile_ptr2 = &volatile_ptr_val;
  int ptr_arith_result = *volatile_ptr2 + 5;
  // Expected: 25 + 5 = 30

  // Test volatile with array indexing
  volatile int volatile_index_array[4] = {10, 20, 30, 40};
  int index_result = volatile_index_array[1] + volatile_index_array[3];
  // Expected: 20 + 40 = 60

  // Test volatile with struct member access
  struct VolatileMemberStruct {
    volatile int volatile_member;
    int regular_member;
  };
  struct VolatileMemberStruct vms = {15, 25};
  int member_result = vms.volatile_member + vms.regular_member;
  // Expected: 15 + 25 = 40

  // Test volatile with complex expressions
  volatile int volatile_complex1 = 2;
  volatile int volatile_complex2 = 3;
  volatile int volatile_complex3 = 4;
  int complex_result =
      volatile_complex1 * volatile_complex2 + volatile_complex3;
  // Expected: 2 * 3 + 4 = 10

  // Test volatile with conditional expressions
  volatile int volatile_cond_expr = 12;
  int cond_expr_result =
      (volatile_cond_expr > 10) ? volatile_cond_expr * 2 : volatile_cond_expr;
  // Expected: 12 * 2 = 24 (since 12 > 10)

  // Test volatile with loop
  volatile int volatile_loop = 5;
  int loop_sum = 0;
  for (int i = 0; i < volatile_loop; i++) {
    loop_sum += i;
  }
  // Expected: 0 + 1 + 2 + 3 + 4 = 10

  // Test volatile with nested expressions
  volatile int volatile_nested = 7;
  int nested_result =
      volatile_nested + (volatile_nested * 2) + (volatile_nested / 2);
  // Expected: 7 + 14 + 3 = 24

  // Test volatile with comparison chains
  volatile int volatile_chain = 6;
  int chain_result = 0;
  if (volatile_chain > 5 && volatile_chain < 10) {
    chain_result = volatile_chain * 3;
  }
  // Expected: 6 * 3 = 18

  // Test volatile with arithmetic chains
  volatile int volatile_chain_arith = 4;
  int chain_arith_result = volatile_chain_arith + volatile_chain_arith * 2 +
                           volatile_chain_arith / 2;
  // Expected: 4 + 8 + 2 = 14

  // Test volatile with const combination
  volatile const int volatile_const = 50;
  int volatile_const_result = volatile_const * 2;
  // Expected: 50 * 2 = 100

  // Test volatile with multiple qualifiers
  volatile int *volatile volatile_ptr_ptr = &regular_val;
  int volatile_ptr_ptr_result = *volatile_ptr_ptr + 10;
  // Expected: 15 + 10 = 25

  // Test volatile with function return
  volatile int volatile_return = get_volatile_value();
  int return_result = volatile_return + 8;
  // Expected: 42 + 8 = 50

  // Verify results
  if (volatile_expr != 20)
    return 1;
  if (volatile_float_expr < 6.27f || volatile_float_expr > 6.29f)
    return 2;
  if (volatile_char_expr != 66)
    return 3;
  if (arith_result != 8)
    return 4;
  if (arith_result2 != 20)
    return 5;
  if (comp_result != 1)
    return 6;
  if (cond_result != 6)
    return 7;
  if (func_result != 20)
    return 8;
  if (ptr_result != 45)
    return 9;
  if (array_sum != 6)
    return 10;
  if (struct_result != 30)
    return 11;
  if (type_result != 1100)
    return 12;
  if (bit_result != 20)
    return 13;
  if (logical_result != 1)
    return 14;
  if (ternary_result != 8)
    return 15;
  if (expr_result != 15)
    return 16;
  if (func_like_result != 36)
    return 17;
  if (ptr_arith_result != 30)
    return 18;
  if (index_result != 60)
    return 19;
  if (member_result != 40)
    return 20;
  if (complex_result != 10)
    return 21;
  if (cond_expr_result != 24)
    return 22;
  if (loop_sum != 10)
    return 23;
  if (nested_result != 24)
    return 24;
  if (chain_result != 18)
    return 25;
  if (chain_arith_result != 14)
    return 26;
  if (volatile_const_result != 100)
    return 27;
  if (volatile_ptr_ptr_result != 25)
    return 28;
  if (return_result != 50)
    return 29;

  // Test volatile with edge cases
  volatile int volatile_edge = 0;
  int edge_result = volatile_edge + 1;

  if (edge_result != 1)
    return 30;

  // Test volatile with negative values
  volatile int volatile_neg = -5;
  int neg_result = volatile_neg * -2;

  if (neg_result != 10)
    return 31;

  return 0; // All tests passed
}