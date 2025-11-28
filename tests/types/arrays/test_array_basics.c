/*
 * Test: Basic array operations
 * Purpose: Verify that array declaration, initialization, access and
 * manipulation work correctly Expected Behavior: Arrays handle storage, access
 * and manipulation of elements properly Test Cases:
 *   - Array declaration and initialization
 *   - Array element access and modification
 *   - Array bounds checking
 *   - Multi-dimensional arrays
 *   - Array arithmetic
 * Dependencies: Basic integer types, loops
 */

int main() {
  // Test 1D array declaration and initialization
  int arr1[5] = {1, 2, 3, 4, 5};
  int arr2[3];
  arr2[0] = 10;
  arr2[1] = 20;
  arr2[2] = 30;

  // Test array element access
  int sum1 = arr1[0] + arr1[1] + arr1[2] + arr1[3] + arr1[4];
  int sum2 = arr2[0] + arr2[1] + arr2[2];

  // Test array modification
  arr1[0] = 100;
  arr1[4] = 500;
  int modified_sum = arr1[0] + arr1[1] + arr1[2] + arr1[3] + arr1[4];

  // Test array with loop
  int arr3[5];
  for (int i = 0; i < 5; i++) {
    arr3[i] = i * i;
  }
  int loop_sum = 0;
  for (int i = 0; i < 5; i++) {
    loop_sum += arr3[i];
  }
  // Expected: 0 + 1 + 4 + 9 + 16 = 30

  // Test 2D array
  int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
  int matrix_sum = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      matrix_sum += matrix[i][j];
    }
  }
  // Expected: 1+2+3+4+5+6 = 21

  // Test array with different types
  char char_arr[4] = {'a', 'b', 'c', 'd'};
  float float_arr[3] = {1.5f, 2.5f, 3.5f};

  int char_sum = char_arr[0] + char_arr[1] + char_arr[2] + char_arr[3];
  float float_sum = float_arr[0] + float_arr[1] + float_arr[2];

  // Test array bounds (should not cause errors in this test)
  int bounds_test = arr1[4];  // Valid access
  int bounds_test2 = arr2[2]; // Valid access

  // Test array arithmetic
  int arr4[5] = {1, 2, 3, 4, 5};
  for (int i = 0; i < 5; i++) {
    arr4[i] = arr4[i] * 2;
  }
  int arithmetic_sum = 0;
  for (int i = 0; i < 5; i++) {
    arithmetic_sum += arr4[i];
  }
  // Expected: 2+4+6+8+10 = 30

  // Test array with conditional access
  int arr5[5] = {10, 20, 30, 40, 50};
  int conditional_sum = 0;
  for (int i = 0; i < 5; i++) {
    if (arr5[i] > 25) {
      conditional_sum += arr5[i];
    }
  }
  // Expected: 30 + 40 + 50 = 120

  // Verify results
  if (sum1 != 15)
    return 1; // 1+2+3+4+5 = 15
  if (sum2 != 60)
    return 2; // 10+20+30 = 60
  if (modified_sum != 610)
    return 3; // 100+2+3+4+500 = 609
  if (loop_sum != 30)
    return 4; // 0+1+4+9+16 = 30
  if (matrix_sum != 21)
    return 5; // 1+2+3+4+5+6 = 21
  if (char_sum != 394)
    return 6; // 'a'(97) + 'b'(98) + 'c'(99) + 'd'(100) = 394
  if (float_sum < 7.4f || float_sum > 7.6f)
    return 7; // 1.5+2.5+3.5 = 7.5
  if (bounds_test != 500)
    return 8; // arr1[4] should be 500
  if (bounds_test2 != 30)
    return 9; // arr2[2] should be 30
  if (arithmetic_sum != 30)
    return 10; // 2+4+6+8+10 = 30
  if (conditional_sum != 120)
    return 11; // 30+40+50 = 120

  return 0; // All tests passed
}