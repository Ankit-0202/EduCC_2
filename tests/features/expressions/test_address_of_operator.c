/*
 * Test: Address-of operator (&)
 * Purpose: Verify that the address-of operator works correctly for different
 * types of operands Expected Behavior: Address-of operator should return the
 * memory address of its operand Test Cases:
 *   - Address-of for variables
 *   - Address-of for array elements
 *   - Address-of for struct members
 *   - Address-of for function pointers
 *   - Address-of in expressions
 *   - Address-of with const and volatile
 * Dependencies: Basic integer types, arrays, structs, pointers, functions
 */

// Function for testing function pointers
int test_func(int x) { return x * 2; }

// Function that takes a pointer
int test_pointer_func(int *ptr) { return *ptr * 3; }

int main() {
  int result = 0;

  // Test address-of for basic variables
  int var_int = 42;
  char var_char = 'A';
  float var_float = 3.14f;

  int *ptr_int = &var_int;
  char *ptr_char = &var_char;
  float *ptr_float = &var_float;

  // Test address-of for array elements
  int int_array[5] = {1, 2, 3, 4, 5};
  int *ptr_array_first = &int_array[0];
  int *ptr_array_last = &int_array[4];
  int *ptr_array_middle = &int_array[2];

  // Test address-of for struct members
  struct TestStruct {
    int a;
    char b;
    float c;
  };
  struct TestStruct ts = {10, 'B', 2.5f};

  int *ptr_struct_a = &ts.a;
  char *ptr_struct_b = &ts.b;
  float *ptr_struct_c = &ts.c;

  // Test address-of for function pointers
  int (*func_ptr)(int) = &test_func;
  int (*func_ptr2)(int) = test_func; // Function name decays to pointer

  // Test address-of for different types
  short var_short = 100;
  long var_long = 1000L;
  double var_double = 3.14159;

  short *ptr_short = &var_short;
  long *ptr_long = &var_long;
  double *ptr_double = &var_double;

  // Test address-of with const and volatile
  const int const_var = 50;
  volatile int volatile_var = 60;

  const int *ptr_const = &const_var;
  volatile int *ptr_volatile = &volatile_var;

  // Test address-of for pointer variables
  int *ptr_to_ptr = ptr_int;
  int **ptr_ptr = &ptr_int;

  // Test address-of for array
  int *ptr_array = &int_array[0]; // Same as int_array
  int *ptr_array_alt = int_array; // Array name decays to pointer

  // Test address-of for struct
  struct TestStruct *ptr_struct = &ts;

  // Test address-of in expressions
  int expr_result = *(&var_int) + *(&var_char);
  // Expected: 42 + 65 = 107

  // Test address-of with arithmetic
  int arith_result = *(&int_array[0]) + *(&int_array[1]) + *(&int_array[2]);
  // Expected: 1 + 2 + 3 = 6

  // Test address-of with comparison
  int comp_result = 0;
  if (&var_int != 0) {
    comp_result = 1;
  }

  // Test address-of with conditional
  int cond_result = (&var_int != 0) ? 10 : 20;
  // Expected: 10 (since address is not null)

  // Test address-of with function calls
  int func_result = test_pointer_func(&var_int);
  // Expected: 42 * 3 = 126

  // Test address-of with pointer arithmetic
  int *ptr_arith = &int_array[0];
  int arith_ptr_result = *ptr_arith + *(ptr_arith + 1) + *(ptr_arith + 2);
  // Expected: 1 + 2 + 3 = 6

  // Test address-of with array indexing
  int index_result = *(&int_array[0]) + *(&int_array[4]);
  // Expected: 1 + 5 = 6

  // Test address-of with struct member access
  int struct_result = *(&ts.a) + *(&ts.b);
  // Expected: 10 + 66 = 76

  // Test address-of with nested expressions
  int nested_result = *(&(*(&var_int)));
  // Expected: 42

  // Test address-of with complex expressions
  int complex_result = *(&int_array[0]) * *(&int_array[1]) + *(&int_array[2]);
  // Expected: 1 * 2 + 3 = 5

  // Test address-of with conditional expressions
  int cond_expr_result = *(&var_int) > 40 ? *(&var_int) : 0;
  // Expected: 42 (since 42 > 40)

  // Test address-of with arithmetic expressions
  int arith_expr_result = *(&var_int) + *(&var_int) * 2;
  // Expected: 42 + 84 = 126

  // Test address-of with comparison expressions
  int comp_expr_result = *(&var_int) == 42 ? 1 : 0;
  // Expected: 1 (since 42 == 42)

  // Test address-of with logical expressions
  int logical_result = *(&var_int) && *(&var_char);
  // Expected: 1 (since both are non-zero)

  // Test address-of with bitwise expressions
  int bitwise_result = *(&var_int) & *(&var_char);
  // Expected: 42 & 65 = 0

  // Test address-of with cast expressions
  int cast_result = (int)*(&var_char);
  // Expected: 65 ('A')

  // Test address-of with sizeof expressions
  int sizeof_result = sizeof(&var_int);
  // Expected: size of pointer (typically 4 or 8)

  // Test address-of with comma expressions
  int comma_result = (*(&var_int), *(&var_char));
  // Expected: 65 (last value in comma expression)

  // Test address-of with ternary expressions
  int ternary_result = *(&var_int) > 50 ? *(&var_int) : *(&var_char);
  // Expected: 65 (since 42 < 50, use char value)

  // Test address-of with function pointer calls
  int func_ptr_result = func_ptr(21);
  // Expected: 21 * 2 = 42

  int func_ptr_result2 = (*func_ptr2)(10);
  // Expected: 10 * 2 = 20

  // Test address-of with pointer to pointer
  int ptr_ptr_result = **(&ptr_int);
  // Expected: 42 (dereference pointer to pointer)

  // Test address-of with array pointer arithmetic
  int arr_ptr_result = *(&int_array[0]) + *(&int_array[1]) + *(&int_array[2]) +
                       *(&int_array[3]) + *(&int_array[4]);
  // Expected: 1 + 2 + 3 + 4 + 5 = 15

  // Test address-of with struct pointer arithmetic
  int struct_ptr_result = *(&ts.a) + (int)*(&ts.b) + (int)*(&ts.c);
  // Expected: 10 + 66 + 2 = 78

  // Test address-of with const pointer
  int const_ptr_result = *ptr_const;
  // Expected: 50

  // Test address-of with volatile pointer
  int volatile_ptr_result = *ptr_volatile;
  // Expected: 60

  // Test address-of with different sized types
  int short_result = *ptr_short;
  int long_result = *ptr_long;
  int double_result = (int)*ptr_double;
  // Expected: 100, 1000, 3

  // Verify results
  if (expr_result != 107)
    return 1;
  if (arith_result != 6)
    return 2;
  if (comp_result != 1)
    return 3;
  if (cond_result != 10)
    return 4;
  if (func_result != 126)
    return 5;
  if (arith_ptr_result != 6)
    return 6;
  if (index_result != 6)
    return 7;
  if (struct_result != 76)
    return 8;
  if (nested_result != 42)
    return 9;
  if (complex_result != 5)
    return 10;
  if (cond_expr_result != 42)
    return 11;
  if (arith_expr_result != 126)
    return 12;
  if (comp_expr_result != 1)
    return 13;
  if (logical_result != 1)
    return 14;
  if (bitwise_result != 0)
    return 15;
  if (cast_result != 65)
    return 16;
  if (sizeof_result < 4 || sizeof_result > 8)
    return 17;
  if (comma_result != 65)
    return 18;
  if (ternary_result != 65)
    return 19;
  if (func_ptr_result != 42)
    return 20;
  if (func_ptr_result2 != 20)
    return 21;
  if (ptr_ptr_result != 42)
    return 22;
  if (arr_ptr_result != 15)
    return 23;
  if (struct_ptr_result != 78)
    return 24;
  if (const_ptr_result != 50)
    return 25;
  if (volatile_ptr_result != 60)
    return 26;
  if (short_result != 100)
    return 27;
  if (long_result != 1000)
    return 28;
  if (double_result != 3)
    return 29;

  // Test address-of with edge cases
  int edge_var = 0;
  int *edge_ptr = &edge_var;
  int edge_result = *edge_ptr;

  if (edge_result != 0)
    return 30;

  // Test address-of with negative values
  int neg_var = -5;
  int *neg_ptr = &neg_var;
  int neg_result = *neg_ptr;

  if (neg_result != -5)
    return 31;

  // Test address-of with large values
  int large_var = 1000000;
  int *large_ptr = &large_var;
  int large_result = *large_ptr;

  if (large_result != 1000000)
    return 32;

  return 0; // All tests passed
}