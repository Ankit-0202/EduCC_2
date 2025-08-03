/*
 * Test: Sizeof operator
 * Purpose: Verify that the sizeof operator works correctly for different types
 * and expressions Expected Behavior: Sizeof should return the correct size in
 * bytes for types, variables and expressions Test Cases:
 *   - Sizeof for basic types
 *   - Sizeof for arrays
 *   - Sizeof for structs
 *   - Sizeof for pointers
 *   - Sizeof for expressions
 *   - Sizeof with const and volatile
 * Dependencies: Basic integer types, arrays, structs, pointers
 */

int main() {
  int result = 0;

  // Test sizeof for basic types
  int sizeof_int = sizeof(int);
  int sizeof_char = sizeof(char);
  int sizeof_short = sizeof(short);
  int sizeof_long = sizeof(long);
  int sizeof_float = sizeof(float);
  int sizeof_double = sizeof(double);

  // Test sizeof for variables
  int var_int = 42;
  char var_char = 'A';
  float var_float = 3.14f;
  int sizeof_var_int = sizeof(var_int);
  int sizeof_var_char = sizeof(var_char);
  int sizeof_var_float = sizeof(var_float);

  // Test sizeof for arrays
  int int_array[5] = {1, 2, 3, 4, 5};
  char char_array[10] = "Hello";
  int sizeof_int_array = sizeof(int_array);
  int sizeof_char_array = sizeof(char_array);
  int sizeof_int_array_element = sizeof(int_array[0]);
  int sizeof_char_array_element = sizeof(char_array[0]);

  // Test sizeof for 2D arrays
  int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
  int sizeof_matrix = sizeof(matrix);
  int sizeof_matrix_row = sizeof(matrix[0]);
  int sizeof_matrix_element = sizeof(matrix[0][0]);

  // Test sizeof for structs
  struct TestStruct {
    int a;
    char b;
    float c;
  };
  struct TestStruct ts;
  int sizeof_struct = sizeof(struct TestStruct);
  int sizeof_struct_var = sizeof(ts);

  // Test sizeof for pointers
  int *int_ptr = &var_int;
  char *char_ptr = &var_char;
  int sizeof_int_ptr = sizeof(int_ptr);
  int sizeof_char_ptr = sizeof(char_ptr);
  int sizeof_ptr_to_ptr = sizeof(&int_ptr);

  // Test sizeof for expressions
  int sizeof_expr1 = sizeof(5 + 3);
  int sizeof_expr2 = sizeof(var_int + var_int);
  int sizeof_expr3 = sizeof(int_array[0] + int_array[1]);

  // Test sizeof with const and volatile
  const int const_var = 10;
  volatile int volatile_var = 20;
  int sizeof_const = sizeof(const_var);
  int sizeof_volatile = sizeof(volatile_var);
  int sizeof_const_int = sizeof(const int);
  int sizeof_volatile_int = sizeof(volatile int);

  // Test sizeof for different array types
  short short_array[3] = {1, 2, 3};
  long long_array[2] = {100L, 200L};
  int sizeof_short_array = sizeof(short_array);
  int sizeof_long_array = sizeof(long_array);

  // Test sizeof for nested structs
  struct NestedStruct {
    int x;
    struct {
      char a;
      char b;
    } inner;
    float y;
  };
  struct NestedStruct ns;
  int sizeof_nested_struct = sizeof(struct NestedStruct);
  int sizeof_nested_struct_var = sizeof(ns);

  // Test sizeof for unions
  union TestUnion {
    int i;
    char c;
    float f;
  };
  union TestUnion tu;
  int sizeof_union = sizeof(union TestUnion);
  int sizeof_union_var = sizeof(tu);

  // Test sizeof for enums
  enum TestEnum { ENUM_A = 1, ENUM_B = 2, ENUM_C = 3 };
  enum TestEnum te = ENUM_A;
  int sizeof_enum = sizeof(enum TestEnum);
  int sizeof_enum_var = sizeof(te);

  // Test sizeof for function pointers
  int (*func_ptr)(int, int);
  int sizeof_func_ptr = sizeof(func_ptr);

  // Test sizeof for complex expressions
  int sizeof_complex1 = sizeof(int_array) / sizeof(int_array[0]);
  int sizeof_complex2 = sizeof(char_array) / sizeof(char_array[0]);
  int sizeof_complex3 = sizeof(matrix) / sizeof(matrix[0][0]);

  // Test sizeof with conditional
  int sizeof_cond = sizeof(var_int > 0 ? var_int : 0);

  // Test sizeof with arithmetic
  int sizeof_arith = sizeof(var_int + var_int);

  // Test sizeof with comparison
  int sizeof_comp = sizeof(var_int == var_int);

  // Test sizeof with logical operations
  int sizeof_logical = sizeof(var_int && var_int);

  // Test sizeof with bitwise operations
  int sizeof_bitwise = sizeof(var_int & var_int);

  // Test sizeof with cast
  int sizeof_cast = sizeof((float)var_int);

  // Test sizeof with address-of
  int sizeof_addr = sizeof(&var_int);

  // Test sizeof with dereference
  int sizeof_deref = sizeof(*int_ptr);

  // Test sizeof with array indexing
  int sizeof_index = sizeof(int_array[0]);

  // Test sizeof with struct member access
  int sizeof_member = sizeof(ts.a);

  // Test sizeof with function call simulation
  int sizeof_func_call = sizeof(sizeof(var_int));

  // Test sizeof with multiple operators
  int sizeof_multi = sizeof(sizeof(sizeof(var_int)));

  // Verify that sizeof returns reasonable values
  // Note: Exact sizes depend on the platform, so we check for reasonable ranges

  // Basic types should have reasonable sizes
  if (sizeof_int < 2 || sizeof_int > 8)
    return 1;
  if (sizeof_char != 1)
    return 2;
  if (sizeof_short < 2 || sizeof_short > 4)
    return 3;
  if (sizeof_long < 4 || sizeof_long > 8)
    return 4;
  if (sizeof_float < 4 || sizeof_float > 8)
    return 5;
  if (sizeof_double < 8 || sizeof_double > 16)
    return 6;

  // Variable sizes should match type sizes
  if (sizeof_var_int != sizeof_int)
    return 7;
  if (sizeof_var_char != sizeof_char)
    return 8;
  if (sizeof_var_float != sizeof_float)
    return 9;

  // Array sizes should be correct
  if (sizeof_int_array != sizeof_int * 5)
    return 10;
  if (sizeof_char_array != sizeof_char * 10)
    return 11;
  if (sizeof_int_array_element != sizeof_int)
    return 12;
  if (sizeof_char_array_element != sizeof_char)
    return 13;

  // Matrix sizes should be correct
  if (sizeof_matrix != sizeof_int * 6)
    return 14; // 2 * 3 * sizeof(int)
  if (sizeof_matrix_row != sizeof_int * 3)
    return 15; // 3 * sizeof(int)
  if (sizeof_matrix_element != sizeof_int)
    return 16;

  // Struct size should be reasonable
  if (sizeof_struct < 8 || sizeof_struct > 16)
    return 17;
  if (sizeof_struct_var != sizeof_struct)
    return 18;

  // Pointer sizes should be the same
  if (sizeof_int_ptr != sizeof_char_ptr)
    return 19;
  if (sizeof_ptr_to_ptr != sizeof_int_ptr)
    return 20;

  // Expression sizes should match operand types
  if (sizeof_expr1 != sizeof_int)
    return 21;
  if (sizeof_expr2 != sizeof_int)
    return 22;
  if (sizeof_expr3 != sizeof_int)
    return 23;

  // Const and volatile should not affect size
  if (sizeof_const != sizeof_int)
    return 24;
  if (sizeof_volatile != sizeof_int)
    return 25;
  if (sizeof_const_int != sizeof_int)
    return 26;
  if (sizeof_volatile_int != sizeof_int)
    return 27;

  // Array sizes should be correct
  if (sizeof_short_array != sizeof(short) * 3)
    return 28;
  if (sizeof_long_array != sizeof(long) * 2)
    return 29;

  // Nested struct size should be reasonable
  if (sizeof_nested_struct < 8 || sizeof_nested_struct > 20)
    return 30;
  if (sizeof_nested_struct_var != sizeof_nested_struct)
    return 31;

  // Union size should be the size of the largest member
  if (sizeof_union < 4 || sizeof_union > 8)
    return 32;
  if (sizeof_union_var != sizeof_union)
    return 33;

  // Enum size should match int size
  if (sizeof_enum != sizeof_int)
    return 34;
  if (sizeof_enum_var != sizeof_enum)
    return 35;

  // Function pointer size should match other pointer sizes
  if (sizeof_func_ptr != sizeof_int_ptr)
    return 36;

  // Complex expressions should work
  if (sizeof_complex1 != 5)
    return 37; // sizeof(int_array) / sizeof(int) = 5
  if (sizeof_complex2 != 10)
    return 38; // sizeof(char_array) / sizeof(char) = 10
  if (sizeof_complex3 != 6)
    return 39; // sizeof(matrix) / sizeof(int) = 6

  // Conditional, arithmetic, comparison, logical, bitwise should work
  if (sizeof_cond != sizeof_int)
    return 40;
  if (sizeof_arith != sizeof_int)
    return 41;
  if (sizeof_comp != sizeof_int)
    return 42;
  if (sizeof_logical != sizeof_int)
    return 43;
  if (sizeof_bitwise != sizeof_int)
    return 44;

  // Cast, address-of, dereference should work
  if (sizeof_cast != sizeof_float)
    return 45;
  if (sizeof_addr != sizeof_int_ptr)
    return 46;
  if (sizeof_deref != sizeof_int)
    return 47;

  // Array indexing and struct member access should work
  if (sizeof_index != sizeof_int)
    return 48;
  if (sizeof_member != sizeof_int)
    return 49;

  // Function call simulation should work
  if (sizeof_func_call != sizeof_int)
    return 50; // sizeof returns size_t, which is typically int

  // Multiple sizeof should work
  if (sizeof_multi != sizeof_int)
    return 51; // sizeof(sizeof(sizeof(int))) = sizeof(int)

  return 0; // All tests passed
}