/*
 * Test: Multi-dimensional arrays
 * Purpose: Verify that multi-dimensional arrays work correctly with proper
 * indexing and operations Expected Behavior: Multi-dimensional arrays should
 * handle storage, access and manipulation properly Test Cases:
 *   - 2D array declaration and initialization
 *   - 3D array operations
 *   - Array indexing and access
 *   - Array arithmetic
 *   - Nested loops with arrays
 *   - Array with different types
 * Dependencies: Basic integer types, loops
 */

int main() {
  int result = 0;

  // Test 2D array declaration and initialization
  int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

  // Test basic 2D array access
  int sum_2d = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      sum_2d += matrix[i][j];
    }
  }
  // Expected: 1+2+3+4+5+6 = 21

  // Test 2D array with different initialization
  int grid[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      grid[i][j] = i * 3 + j + 1;
    }
  }
  // Expected: {{1,2,3}, {4,5,6}, {7,8,9}}

  int grid_sum = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      grid_sum += grid[i][j];
    }
  }
  // Expected: 1+2+3+4+5+6+7+8+9 = 45

  // Test 3D array
  int cube[2][2][2] = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};

  int cube_sum = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        cube_sum += cube[i][j][k];
      }
    }
  }
  // Expected: 1+2+3+4+5+6+7+8 = 36

  // Test 2D array with arithmetic
  int matrix2[2][2] = {{1, 2}, {3, 4}};
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix2[i][j] *= 2;
    }
  }

  int matrix2_sum = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix2_sum += matrix2[i][j];
    }
  }
  // Expected: (1*2)+(2*2)+(3*2)+(4*2) = 2+4+6+8 = 20

  // Test 2D array with conditional access
  int conditional_matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int conditional_sum = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (conditional_matrix[i][j] > 5) {
        conditional_sum += conditional_matrix[i][j];
      }
    }
  }
  // Expected: 6+7+8+9 = 30

  // Test 2D array with different types
  char char_matrix[2][3] = {{'a', 'b', 'c'}, {'d', 'e', 'f'}};
  int char_sum = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      char_sum += char_matrix[i][j];
    }
  }
  // Expected: 'a'(97) + 'b'(98) + 'c'(99) + 'd'(100) + 'e'(101) + 'f'(102) =
  // 597

  float float_matrix[2][2] = {{1.5f, 2.5f}, {3.5f, 4.5f}};
  float float_sum = 0.0f;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      float_sum += float_matrix[i][j];
    }
  }
  // Expected: 1.5 + 2.5 + 3.5 + 4.5 = 12.0

  // Test 2D array with pointer-like behavior
  int *ptr_matrix[2];
  int row1[3] = {10, 20, 30};
  int row2[3] = {40, 50, 60};
  ptr_matrix[0] = row1;
  ptr_matrix[1] = row2;

  int ptr_sum = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      ptr_sum += ptr_matrix[i][j];
    }
  }
  // Expected: 10+20+30+40+50+60 = 210

  // Test 2D array with struct
  struct Point {
    int x;
    int y;
  };
  struct Point point_matrix[2][2] = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};

  int struct_sum = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      struct_sum += point_matrix[i][j].x + point_matrix[i][j].y;
    }
  }
  // Expected: (1+2) + (3+4) + (5+6) + (7+8) = 3 + 7 + 11 + 15 = 36

  // Test 2D array with function-like behavior
  int func_matrix[2][2] = {{1, 2}, {3, 4}};
  int func_sum = 0;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      func_sum += func_matrix[i][j] * 2;
    }
  }
  // Expected: (1*2) + (2*2) + (3*2) + (4*2) = 2 + 4 + 6 + 8 = 20

  // Test 2D array with complex expressions
  int complex_matrix[2][2] = {{1, 2}, {3, 4}};
  int complex_sum = 0;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      complex_sum += complex_matrix[i][j] * complex_matrix[j][i];
    }
  }
  // Expected: (1*1) + (2*3) + (3*2) + (4*4) = 1 + 6 + 6 + 16 = 29

  // Test 2D array with nested conditionals
  int nested_matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int nested_sum = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == j) {
        nested_sum += nested_matrix[i][j];
      } else if (i + j == 2) {
        nested_sum += nested_matrix[i][j] * 2;
      }
    }
  }
  // Expected: diagonal (1+5+9) + anti-diagonal*2 (3*2 + 5*2 + 7*2) = 15 + 30 =
  // 45

  // Test 2D array with arithmetic operations
  int arith_matrix[2][2] = {{1, 2}, {3, 4}};
  int arith_sum = 0;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      arith_sum += arith_matrix[i][j] + i + j;
    }
  }
  // Expected: (1+0+0) + (2+0+1) + (3+1+0) + (4+1+1) = 1 + 3 + 4 + 6 = 14

  // Verify results
  if (sum_2d != 21)
    return 1;
  if (grid_sum != 45)
    return 2;
  if (cube_sum != 36)
    return 3;
  if (matrix2_sum != 20)
    return 4;
  if (conditional_sum != 30)
    return 5;
  if (char_sum != 597)
    return 6;
  if (float_sum < 11.9f || float_sum > 12.1f)
    return 7;
  if (ptr_sum != 210)
    return 8;
  if (struct_sum != 36)
    return 9;
  if (func_sum != 20)
    return 10;
  if (complex_sum != 29)
    return 11;
  if (nested_sum != 45)
    return 12;
  if (arith_sum != 14)
    return 13;

  // Test 2D array with edge cases
  int edge_matrix[1][1] = {{42}};
  int edge_sum = edge_matrix[0][0];

  if (edge_sum != 42)
    return 14;

  // Test 2D array with large dimensions
  int large_matrix[5][5];
  int large_sum = 0;

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      large_matrix[i][j] = i + j;
      large_sum += large_matrix[i][j];
    }
  }
  // Expected: sum of all i+j for i=0..4, j=0..4 = 100

  if (large_sum != 100)
    return 15;

  return 0; // All tests passed
}