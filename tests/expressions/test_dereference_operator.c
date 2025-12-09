/*
 * Test: Dereference operator (*)
 * Purpose: Verify that the dereference operator works correctly for different
 * types of pointers Expected Behavior: Dereference operator should return the
 * value pointed to by the pointer Test Cases:
 *   - Dereference for basic pointers
 *   - Dereference for array pointers
 *   - Dereference for struct pointers
 *   - Dereference for function pointers
 *   - Dereference in expressions
 *   - Dereference with const and volatile
 * Dependencies: Basic integer types, arrays, structs, pointers, functions
 */

// Function for testing function pointers
int test_func(int x) { return x * 2; }

// Function that takes a pointer and returns dereferenced value
int test_deref_func(int *ptr) { return *ptr * 3; }

int main() {
  int result = 0;

  // Test dereference for basic pointers
  int var_int = 42;
  char var_char = 'A';
  float var_float = 3.14f;

  int *ptr_int = &var_int;
  char *ptr_char = &var_char;
  float *ptr_float = &var_float;

  int deref_int = *ptr_int;
  char deref_char = *ptr_char;
  float deref_float = *ptr_float;
  // Expected: 42, 'A', 3.14

  // Test dereference for array pointers
  int int_array[5] = {1, 2, 3, 4, 5};
  int *ptr_array = int_array;

  int deref_array_first = *ptr_array;
  int deref_array_second = *(ptr_array + 1);
  int deref_array_last = *(ptr_array + 4);
  // Expected: 1, 2, 5

  // Test dereference for struct pointers
  struct TestStruct {
    int a;
    char b;
    float c;
  };
  struct TestStruct ts = {10, 'B', 2.5f};
  struct TestStruct *ptr_struct = &ts;

  int deref_struct_a = (*ptr_struct).a;
  char deref_struct_b = (*ptr_struct).b;
  float deref_struct_c = (*ptr_struct).c;
  // Expected: 10, 'B', 2.5

  // Test dereference for function pointers
  int (*func_ptr)(int) = &test_func;
  int func_ptr_result_initial = (*func_ptr)(21);
  // Expected: 21 * 2 = 42

  // Test dereference for different types
  short var_short = 100;
  long var_long = 1000L;
  double var_double = 3.14159;

  short *ptr_short = &var_short;
  long *ptr_long = &var_long;
  double *ptr_double = &var_double;

  short deref_short = *ptr_short;
  long deref_long = *ptr_long;
  double deref_double = *ptr_double;
  // Expected: 100, 1000, 3.14159

  // Test dereference with const and volatile
  const int const_var = 50;
  volatile int volatile_var = 60;

  const int *ptr_const = &const_var;
  volatile int *ptr_volatile = &volatile_var;

  int deref_const = *ptr_const;
  int deref_volatile = *ptr_volatile;
  // Expected: 50, 60

  // Test dereference for pointer to pointer
  int **ptr_ptr = &ptr_int;
  int deref_ptr_ptr = **ptr_ptr;
  // Expected: 42

  // Test dereference in expressions
  int expr_result = *ptr_int + *ptr_char;
  // Expected: 42 + 65 = 107

  // Test dereference with arithmetic
  int arith_result = *ptr_array + *(ptr_array + 1) + *(ptr_array + 2);
  // Expected: 1 + 2 + 3 = 6

  // Test dereference with comparison
  int comp_result = 0;
  if (*ptr_int > 40) {
    comp_result = 1;
  }
  // Expected: 1 (since 42 > 40)

  // Test dereference with conditional
  int cond_result = (*ptr_int > 50) ? *ptr_int : *ptr_char;
  // Expected: 65 (since 42 < 50, use char value)

  // Test dereference with function calls
  int func_result_call = test_deref_func(ptr_int);
  // Expected: 42 * 3 = 126

  // Test dereference with pointer arithmetic
  int *ptr_arith = int_array;
  int arith_ptr_result = *ptr_arith + *(ptr_arith + 1) + *(ptr_arith + 2);
  // Expected: 1 + 2 + 3 = 6

  // Test dereference with array indexing
  int index_result = *ptr_array + *(ptr_array + 4);
  // Expected: 1 + 5 = 6

  // Test dereference with struct member access
  int struct_result = (*ptr_struct).a + (*ptr_struct).b;
  // Expected: 10 + 66 = 76

  // Test dereference with nested expressions
  int nested_result = *(*(&ptr_int));
  // Expected: 42

  // Test dereference with complex expressions
  int complex_result = *ptr_array * *(ptr_array + 1) + *(ptr_array + 2);
  // Expected: 1 * 2 + 3 = 5

  // Test dereference with conditional expressions
  int cond_expr_result = *ptr_int > 40 ? *ptr_int : 0;
  // Expected: 42 (since 42 > 40)

  // Test dereference with arithmetic expressions
  int arith_expr_result = *ptr_int + *ptr_int * 2;
  // Expected: 42 + 84 = 126

  // Test dereference with comparison expressions
  int comp_expr_result = *ptr_int == 42 ? 1 : 0;
  // Expected: 1 (since 42 == 42)

  // Test dereference with logical expressions
  int logical_result = *ptr_int && *ptr_char;
  // Expected: 1 (since both are non-zero)

  // Test dereference with bitwise expressions
  int bitwise_result = *ptr_int & *ptr_char;
  // Expected: 42 & 65 = 0

  // Test dereference with cast expressions
  int cast_result = (int)*ptr_char;
  // Expected: 65 ('A')

  // Test dereference with sizeof expressions
  int sizeof_result = sizeof(*ptr_int);
  // Expected: size of int (typically 4)

  // Test dereference with comma expressions
  int comma_result = (*ptr_int, *ptr_char);
  // Expected: 65 (last value in comma expression)

  // Test dereference with ternary expressions
  int ternary_result = *ptr_int > 50 ? *ptr_int : *ptr_char;
  // Expected: 65 (since 42 < 50, use char value)

  // Test dereference with function pointer calls
  int func_ptr_result = (*func_ptr)(10);
  // Expected: 10 * 2 = 20

  // Test dereference with array pointer arithmetic
  int arr_ptr_result = *ptr_array + *(ptr_array + 1) + *(ptr_array + 2) +
                       *(ptr_array + 3) + *(ptr_array + 4);
  // Expected: 1 + 2 + 3 + 4 + 5 = 15

  // Test dereference with struct pointer arithmetic
  int struct_ptr_result =
      (*ptr_struct).a + (int)(*ptr_struct).b + (int)(*ptr_struct).c;
  // Expected: 10 + 66 + 2 = 78

  // Test dereference with const pointer
  int const_ptr_result = *ptr_const;
  // Expected: 50

  // Test dereference with volatile pointer
  int volatile_ptr_result = *ptr_volatile;
  // Expected: 60

  // Test dereference with different sized types
  int short_result = *ptr_short;
  int long_result = *ptr_long;
  int double_result = (int)*ptr_double;
  // Expected: 100, 1000, 3

  // Test dereference with pointer to pointer arithmetic
  int **ptr_ptr_arith = &ptr_int;
  int ptr_ptr_arith_result = **ptr_ptr_arith;
  // Expected: 42

  // Test dereference with array of pointers
  int *ptr_array_elements[3] = {&int_array[0], &int_array[1], &int_array[2]};
  int deref_array_elements =
      *ptr_array_elements[0] + *ptr_array_elements[1] + *ptr_array_elements[2];
  // Expected: 1 + 2 + 3 = 6

  // Test dereference with struct array
  struct TestStruct struct_array[2] = {{1, 'A', 1.5f}, {2, 'B', 2.5f}};
  struct TestStruct *ptr_struct_array = struct_array;
  int struct_array_result = (*ptr_struct_array).a + (*(ptr_struct_array + 1)).a;
  // Expected: 1 + 2 = 3

  // Test dereference with union
  union TestUnion {
    int i;
    char c;
    float f;
  };
  union TestUnion tu = {42};
  union TestUnion *ptr_union = &tu;
  int union_result = (*ptr_union).i;
  // Expected: 42

  // Test dereference with enum
  enum TestEnum { ENUM_A = 1, ENUM_B = 2, ENUM_C = 3 };
  enum TestEnum te = ENUM_B;
  enum TestEnum *ptr_enum = &te;
  int enum_result = *ptr_enum;
  // Expected: 2

  // Test dereference with void pointer
  void *void_ptr = &var_int;
  int void_result = *(int *)void_ptr;
  // Expected: 42

  // Test dereference with null pointer (should be avoided in real code)
  int *null_ptr = 0;
  // Note: Dereferencing null pointer is undefined behavior

  // Verify results
  if (deref_int != 42)
    return 1;
  if (deref_char != 'A')
    return 2;
  if (deref_float < 3.13f || deref_float > 3.15f)
    return 3;
  if (deref_array_first != 1)
    return 4;
  if (deref_array_second != 2)
    return 5;
  if (deref_array_last != 5)
    return 6;
  if (deref_struct_a != 10)
    return 7;
  if (deref_struct_b != 'B')
    return 8;
  if (deref_struct_c < 2.4f || deref_struct_c > 2.6f)
    return 9;
  if (func_ptr_result_initial != 42)
    return 10;
  if (deref_short != 100)
    return 11;
  if (deref_long != 1000)
    return 12;
  if (deref_double < 3.14158 || deref_double > 3.14160)
    return 13;
  if (deref_const != 50)
    return 14;
  if (deref_volatile != 60)
    return 15;
  if (deref_ptr_ptr != 42)
    return 16;
  if (expr_result != 107)
    return 17;
  if (arith_result != 6)
    return 18;
  if (comp_result != 1)
    return 19;
  if (cond_result != 65)
    return 20;
  if (func_result_call != 126)
    return 21;
  if (arith_ptr_result != 6)
    return 22;
  if (index_result != 6)
    return 23;
  if (struct_result != 76)
    return 24;
  if (nested_result != 42)
    return 25;
  if (complex_result != 5)
    return 26;
  if (cond_expr_result != 42)
    return 27;
  if (arith_expr_result != 126)
    return 28;
  if (comp_expr_result != 1)
    return 29;
  if (logical_result != 1)
    return 30;
  if (bitwise_result != 0)
    return 31;
  if (cast_result != 65)
    return 32;
  if (sizeof_result < 2 || sizeof_result > 8)
    return 33;
  if (comma_result != 65)
    return 34;
  if (ternary_result != 65)
    return 35;
  if (func_ptr_result != 20)
    return 36;
  if (arr_ptr_result != 15)
    return 37;
  if (struct_ptr_result != 78)
    return 38;
  if (const_ptr_result != 50)
    return 39;
  if (volatile_ptr_result != 60)
    return 40;
  if (short_result != 100)
    return 41;
  if (long_result != 1000)
    return 42;
  if (double_result != 3)
    return 43;
  if (ptr_ptr_arith_result != 42)
    return 44;
  if (deref_array_elements != 6)
    return 45;
  if (struct_array_result != 3)
    return 46;
  if (union_result != 42)
    return 47;
  if (enum_result != 2)
    return 48;
  if (void_result != 42)
    return 49;

  // Test dereference with edge cases
  int edge_var = 0;
  int *edge_ptr = &edge_var;
  int edge_result = *edge_ptr;

  if (edge_result != 0)
    return 50;

  // Test dereference with negative values
  int neg_var = -5;
  int *neg_ptr = &neg_var;
  int neg_result = *neg_ptr;

  if (neg_result != -5)
    return 51;

  // Test dereference with large values
  int large_var = 1000000;
  int *large_ptr = &large_var;
  int large_result = *large_ptr;

  if (large_result != 1000000)
    return 52;

  return 0; // All tests passed
}
