int main() {
  int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  // Test basic access
  if (matrix[0][0] != 1)
    return 1;
  if (matrix[0][1] != 2)
    return 1;
  if (matrix[0][2] != 3)
    return 1;
  if (matrix[1][0] != 4)
    return 1;
  if (matrix[1][1] != 5)
    return 1;
  if (matrix[1][2] != 6)
    return 1;
  if (matrix[2][0] != 7)
    return 1;
  if (matrix[2][1] != 8)
    return 1;
  if (matrix[2][2] != 9)
    return 1;

  // Test modification
  matrix[1][1] = 50;
  if (matrix[1][1] != 50)
    return 1;

  // Test 3D array
  int cube[2][2][2] = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};

  if (cube[0][0][0] != 1)
    return 1;
  if (cube[0][0][1] != 2)
    return 1;
  if (cube[0][1][0] != 3)
    return 1;
  if (cube[0][1][1] != 4)
    return 1;
  if (cube[1][0][0] != 5)
    return 1;
  if (cube[1][0][1] != 6)
    return 1;
  if (cube[1][1][0] != 7)
    return 1;
  if (cube[1][1][1] != 8)
    return 1;

  return 0;
}