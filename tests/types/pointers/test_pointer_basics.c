/*
 * Test: Basic pointer operations
 * Purpose: Verify that pointer declaration, dereferencing, arithmetic and
 * manipulation work correctly Expected Behavior: Pointers handle memory
 * addresses, dereferencing and arithmetic operations properly Test Cases:
 *   - Pointer declaration and initialization
 *   - Dereferencing operations
 *   - Pointer arithmetic
 *   - Pointer-to-pointer
 *   - Null pointer handling
 *   - Pointer comparison
 * Dependencies: Basic integer types, arrays
 */

int main() {
  // Test basic pointer operations
  int x = 42;
  int *ptr1 = &x;
  int **ptr2 = &ptr1;

  // Test dereferencing
  int deref1 = *ptr1;
  int deref2 = **ptr2;

  // Test pointer arithmetic
  int arr[5] = {1, 2, 3, 4, 5};
  int *arr_ptr = arr;

  int sum1 = *arr_ptr + *(arr_ptr + 1) + *(arr_ptr + 2);
  int sum2 = arr_ptr[0] + arr_ptr[1] + arr_ptr[2];

  // Test pointer increment/decrement
  int *ptr3 = arr;
  int increment_sum = 0;
  for (int i = 0; i < 5; i++) {
    increment_sum += *ptr3;
    ptr3++;
  }

  // Test pointer comparison
  int *ptr4 = arr;
  int *ptr5 = arr + 3;
  int comparison_result = 0;

  if (ptr4 < ptr5) {
    comparison_result = 1;
  }
  if (ptr4 == arr) {
    comparison_result += 2;
  }
  if (ptr5 == arr + 3) {
    comparison_result += 4;
  }

  // Test pointer with different types
  char char_var = 'A';
  char *char_ptr = &char_var;
  int char_as_int = *char_ptr;

  float float_var = 3.14f;
  float *float_ptr = &float_var;
  float deref_float = *float_ptr;

  // Test null pointer
  int *null_ptr = 0;
  int null_test = 0;
  if (null_ptr == 0) {
    null_test = 1;
  }

  // Test pointer arithmetic with different types
  char char_arr[4] = {'a', 'b', 'c', 'd'};
  char *char_arr_ptr = char_arr;
  int char_sum = 0;
  for (int i = 0; i < 4; i++) {
    char_sum += char_arr_ptr[i];
  }

  // Test pointer to pointer arithmetic
  int **ptr_to_ptr = &ptr1;
  int ptr_deref = **ptr_to_ptr;

  // Test pointer assignment
  int y = 100;
  int *ptr6 = &x;
  ptr6 = &y;
  int assignment_test = *ptr6;

  // Test pointer with conditional
  int *ptr7 = &x;
  int conditional_sum = 0;
  if (*ptr7 > 40) {
    conditional_sum += *ptr7;
  }
  if (*(ptr7 + 0) == 42) {
    conditional_sum += 10;
  }

  // Verify results
  if (deref1 != 42)
    return 1;
  if (deref2 != 42)
    return 2;
  if (sum1 != 6)
    return 3; // 1+2+3 = 6
  if (sum2 != 6)
    return 4; // 1+2+3 = 6
  if (increment_sum != 15)
    return 5; // 1+2+3+4+5 = 15
  if (comparison_result != 7)
    return 6; // 1+2+4 = 7
  if (char_as_int != 65)
    return 7; // 'A' = 65
  if (deref_float < 3.13f || deref_float > 3.15f)
    return 8; // 3.14
  if (null_test != 1)
    return 9;
  if (char_sum != 394)
    return 10; // 'a'(97) + 'b'(98) + 'c'(99) + 'd'(100) = 394
  if (ptr_deref != 42)
    return 11;
  if (assignment_test != 100)
    return 12;
  if (conditional_sum != 52)
    return 13; // 42 + 10 = 52

  // Test pointer arithmetic edge cases
  int *edge_ptr = arr;
  int edge_sum = 0;
  for (int i = 0; i < 5; i++) {
    edge_sum += *(edge_ptr + i);
  }
  if (edge_sum != 15)
    return 14; // 1+2+3+4+5 = 15

  // Test pointer with array indexing
  int *index_ptr = arr;
  int index_sum = 0;
  for (int i = 0; i < 5; i++) {
    index_sum += index_ptr[i];
  }
  if (index_sum != 15)
    return 15; // 1+2+3+4+5 = 15

  return 0; // All tests passed
}