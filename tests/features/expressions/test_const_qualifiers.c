/*
 * Test: Const qualifiers and constant expressions
 * Purpose: Verify that const qualifiers work correctly for variables, pointers
 * and parameters Expected Behavior: Const variables should not be modifiable
 * and const expressions should work properly Test Cases:
 *   - Const variable declarations
 *   - Const pointers
 *   - Const function parameters
 *   - Const arrays
 *   - Const struct members
 *   - Const expressions
 * Dependencies: Basic integer types, pointers, structs
 */

// Function with const parameter
int test_const_param(const int value) { return value * 2; }

// Function with const pointer parameter
int test_const_ptr(const int *ptr) { return *ptr * 3; }

// Function that returns const value
const int get_const_value() { return 42; }

int main() {
  int result = 0;

  // Test const variable declarations
  const int const_val = 10;
  const float const_float = 3.14f;
  const char const_char = 'A';

  // Test const expressions
  int const_expr = const_val * 2;
  float const_float_expr = const_float * 2.0f;
  int const_char_expr = const_char + 1;
  // Expected: 20, 6.28, 66 ('B')

  // Test const with arithmetic
  const int const_arith = 5;
  int arith_result = const_arith + 3;
  int arith_result2 = const_arith * 4;
  // Expected: 8, 20

  // Test const with comparison
  const int const_comp = 7;
  int comp_result = 0;
  if (const_comp > 5) {
    comp_result = 1;
  }
  // Expected: 1

  // Test const with conditional
  const int const_cond = 3;
  int cond_result = (const_cond > 2) ? const_cond * 2 : const_cond;
  // Expected: 6 (since 3 > 2)

  // Test const with function call
  int func_result = test_const_param(const_val);
  // Expected: 10 * 2 = 20

  // Test const pointer
  int regular_val = 15;
  const int *const_ptr = &regular_val;
  int ptr_result = test_const_ptr(const_ptr);
  // Expected: 15 * 3 = 45

  // Test const array
  const int const_array[3] = {1, 2, 3};
  int array_sum = 0;
  for (int i = 0; i < 3; i++) {
    array_sum += const_array[i];
  }
  // Expected: 1 + 2 + 3 = 6

  // Test const struct
  struct ConstStruct {
    const int value;
    int regular_value;
  };
  struct ConstStruct cs = {10, 20};
  int struct_result = cs.value + cs.regular_value;
  // Expected: 10 + 20 = 30

  // Test const with different types
  const short const_short = 100;
  const long const_long = 1000L;
  int type_result = const_short + const_long;
  // Expected: 100 + 1000 = 1100

  // Test const with bitwise operations
  const int const_bit = 5;
  int bit_result = const_bit << 2;
  // Expected: 5 << 2 = 20

  // Test const with logical operations
  const int const_logical = 0;
  int logical_result = !const_logical;
  // Expected: 1 (since !0 = 1)

  // Test const with ternary operator
  const int const_ternary = 8;
  int ternary_result = (const_ternary > 5) ? const_ternary : 0;
  // Expected: 8 (since 8 > 5)

  // Test const with expressions
  const int const_expr1 = 3;
  const int const_expr2 = 4;
  int expr_result = const_expr1 * const_expr2 + const_expr1;
  // Expected: 3 * 4 + 3 = 15

  // Test const with function-like behavior
  const int const_func = 6;
  int func_like_result = const_func * const_func;
  // Expected: 6 * 6 = 36

  // Test const with pointer arithmetic
  const int const_ptr_val = 25;
  const int *const_ptr2 = &const_ptr_val;
  int ptr_arith_result = *const_ptr2 + 5;
  // Expected: 25 + 5 = 30

  // Test const with array indexing
  const int const_index_array[4] = {10, 20, 30, 40};
  int index_result = const_index_array[1] + const_index_array[3];
  // Expected: 20 + 40 = 60

  // Test const with struct member access
  struct ConstMemberStruct {
    const int const_member;
    int regular_member;
  };
  struct ConstMemberStruct cms = {15, 25};
  int member_result = cms.const_member + cms.regular_member;
  // Expected: 15 + 25 = 40

  // Test const with complex expressions
  const int const_complex1 = 2;
  const int const_complex2 = 3;
  const int const_complex3 = 4;
  int complex_result = const_complex1 * const_complex2 + const_complex3;
  // Expected: 2 * 3 + 4 = 10

  // Test const with conditional expressions
  const int const_cond_expr = 12;
  int cond_expr_result =
      (const_cond_expr > 10) ? const_cond_expr * 2 : const_cond_expr;
  // Expected: 12 * 2 = 24 (since 12 > 10)

  // Test const with loop
  const int const_loop = 5;
  int loop_sum = 0;
  for (int i = 0; i < const_loop; i++) {
    loop_sum += i;
  }
  // Expected: 0 + 1 + 2 + 3 + 4 = 10

  // Test const with nested expressions
  const int const_nested = 7;
  int nested_result = const_nested + (const_nested * 2) + (const_nested / 2);
  // Expected: 7 + 14 + 3 = 24

  // Test const with comparison chains
  const int const_chain = 6;
  int chain_result = 0;
  if (const_chain > 5 && const_chain < 10) {
    chain_result = const_chain * 3;
  }
  // Expected: 6 * 3 = 18

  // Test const with arithmetic chains
  const int const_chain_arith = 4;
  int chain_arith_result =
      const_chain_arith + const_chain_arith * 2 + const_chain_arith / 2;
  // Expected: 4 + 8 + 2 = 14

  // Verify results
  if (const_expr != 20)
    return 1;
  if (const_float_expr < 6.27f || const_float_expr > 6.29f)
    return 2;
  if (const_char_expr != 66)
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

  // Test const with edge cases
  const int const_edge = 0;
  int edge_result = const_edge + 1;

  if (edge_result != 1)
    return 27;

  // Test const with negative values
  const int const_neg = -5;
  int neg_result = const_neg * -2;

  if (neg_result != 10)
    return 28;

  return 0; // All tests passed
}