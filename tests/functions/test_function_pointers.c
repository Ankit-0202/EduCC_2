/*
 * Test: Function pointers
 * Purpose: Verify that function pointers work correctly for declaration,
 * assignment and calling Expected Behavior: Function pointers should allow
 * calling functions through pointers Test Cases:
 *   - Function pointer declaration
 *   - Function pointer assignment
 *   - Calling functions through pointers
 *   - Function pointer arrays
 *   - Function pointer with different signatures
 *   - Function pointer as parameters
 * Dependencies: Basic integer types, functions
 */

// Function definitions for testing
int add(int a, int b) { return a + b; }

int multiply(int a, int b) { return a * b; }

int subtract(int a, int b) { return a - b; }

float divide(float a, float b) { return a / b; }

int square(int x) { return x * x; }

int cube(int x) { return x * x * x; }

// Function that takes a function pointer as parameter
int apply_function(int (*func)(int, int), int a, int b) { return func(a, b); }

// Function that returns a function pointer
int (*get_operation(char op))(int, int) {
  if (op == '+')
    return add;
  if (op == '*')
    return multiply;
  if (op == '-')
    return subtract;
  return add; // default
}

int main() {
  int result = 0;

  // Test basic function pointer declaration and assignment
  int (*func_ptr)(int, int);
  func_ptr = add;

  // Test calling through function pointer
  int call_result = func_ptr(5, 3);
  // Expected: 5 + 3 = 8

  // Test reassigning function pointer
  func_ptr = multiply;
  int call_result2 = func_ptr(4, 6);
  // Expected: 4 * 6 = 24

  // Test function pointer with different signature
  float (*float_func_ptr)(float, float);
  float_func_ptr = divide;
  float float_result = float_func_ptr(10.0f, 2.0f);
  // Expected: 10.0 / 2.0 = 5.0

  // Test function pointer array
  int (*func_array[3])(int, int);
  func_array[0] = add;
  func_array[1] = multiply;
  func_array[2] = subtract;

  int array_result1 = func_array[0](5, 3);  // add
  int array_result2 = func_array[1](4, 2);  // multiply
  int array_result3 = func_array[2](10, 4); // subtract
  // Expected: 8, 8, 6

  // Test function pointer with single parameter
  int (*single_func_ptr)(int);
  single_func_ptr = square;
  int single_result = single_func_ptr(5);
  // Expected: 5 * 5 = 25

  // Test function pointer with cube function
  single_func_ptr = cube;
  int cube_result = single_func_ptr(3);
  // Expected: 3 * 3 * 3 = 27

  // Test function pointer as parameter
  int apply_result1 = apply_function(add, 10, 5);
  int apply_result2 = apply_function(multiply, 6, 7);
  int apply_result3 = apply_function(subtract, 20, 8);
  // Expected: 15, 42, 12

  // Test function that returns function pointer
  int (*op_func)(int, int);
  op_func = get_operation('+');
  int op_result1 = op_func(5, 3);

  op_func = get_operation('*');
  int op_result2 = op_func(4, 6);

  op_func = get_operation('-');
  int op_result3 = op_func(10, 4);
  // Expected: 8, 24, 6

  // Test function pointer with conditional
  int (*cond_func_ptr)(int, int);
  int cond_val = 5;

  if (cond_val > 3) {
    cond_func_ptr = add;
  } else {
    cond_func_ptr = multiply;
  }
  int cond_result = cond_func_ptr(3, 2);
  // Expected: 5 (since cond_val > 3, use add)

  // Test function pointer with arithmetic
  int (*arith_func_ptr)(int, int);
  arith_func_ptr = add;
  int arith_result = arith_func_ptr(5, 3) * 2;
  // Expected: (5 + 3) * 2 = 16

  // Test function pointer with comparison
  int (*comp_func_ptr)(int, int);
  comp_func_ptr = multiply;
  int comp_result = 0;
  if (comp_func_ptr(3, 4) > 10) {
    comp_result = 1;
  }
  // Expected: 1 (since 3 * 4 = 12 > 10)

  // Test function pointer with loop
  int (*loop_func_ptr)(int, int);
  loop_func_ptr = add;
  int loop_sum = 0;
  for (int i = 1; i <= 3; i++) {
    loop_sum += loop_func_ptr(i, i);
  }
  // Expected: (1+1) + (2+2) + (3+3) = 2 + 4 + 6 = 12

  // Test function pointer with array access
  int (*array_func_ptr)(int, int);
  array_func_ptr = func_array[1]; // multiply
  int array_access_result = array_func_ptr(5, 4);
  // Expected: 5 * 4 = 20

  // Test function pointer with struct
  struct TestStruct {
    int (*operation)(int, int);
    int value;
  };
  struct TestStruct ts = {add, 10};
  int struct_result = ts.operation(ts.value, 5);
  // Expected: 10 + 5 = 15

  // Test function pointer with pointer arithmetic
  int (*ptr_arith_func)(int, int);
  ptr_arith_func = &add; // Explicit address
  int ptr_arith_result = (*ptr_arith_func)(6, 4);
  // Expected: 6 + 4 = 10

  // Test function pointer with complex expressions
  int (*complex_func_ptr)(int, int);
  complex_func_ptr = (cond_val > 3) ? add : multiply;
  int complex_result = complex_func_ptr(7, 3);
  // Expected: 7 + 3 = 10 (since cond_val > 3)

  // Test function pointer with nested calls
  int (*nested_func_ptr)(int, int);
  nested_func_ptr = add;
  int nested_result = nested_func_ptr(nested_func_ptr(2, 3), 4);
  // Expected: (2 + 3) + 4 = 9

  // Verify results
  if (call_result != 8)
    return 1;
  if (call_result2 != 24)
    return 2;
  if (float_result < 4.9f || float_result > 5.1f)
    return 3;
  if (array_result1 != 8)
    return 4;
  if (array_result2 != 8)
    return 5;
  if (array_result3 != 6)
    return 6;
  if (single_result != 25)
    return 7;
  if (cube_result != 27)
    return 8;
  if (apply_result1 != 15)
    return 9;
  if (apply_result2 != 42)
    return 10;
  if (apply_result3 != 12)
    return 11;
  if (op_result1 != 8)
    return 12;
  if (op_result2 != 24)
    return 13;
  if (op_result3 != 6)
    return 14;
  if (cond_result != 5)
    return 15;
  if (arith_result != 16)
    return 16;
  if (comp_result != 1)
    return 17;
  if (loop_sum != 12)
    return 18;
  if (array_access_result != 20)
    return 19;
  if (struct_result != 15)
    return 20;
  if (ptr_arith_result != 10)
    return 21;
  if (complex_result != 10)
    return 22;
  if (nested_result != 9)
    return 23;

  // Test function pointer with void functions
  void (*void_func_ptr)(void);
  // Note: We can't easily test void functions in this context

  // Test function pointer with different return types
  float (*float_return_func)(int, int);
  // Note: We don't have a float-returning function with int parameters

  return 0; // All tests passed
}