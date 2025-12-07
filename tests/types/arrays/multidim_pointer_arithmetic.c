// Test pointer arithmetic with multi-dimensional arrays
int main() {
  int matrix[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

  // Access via array notation
  if (matrix[0][0] != 1)
    return 1;
  if (matrix[1][2] != 7)
    return 2;
  if (matrix[2][3] != 12)
    return 3;

  // Pointer to first row
  int *p = &matrix[0][0];
  if (*p != 1)
    return 4;
  if (*(p + 5) != 6)
    return 5; // matrix[1][1]
  if (*(p + 11) != 12)
    return 6; // matrix[2][3]

  // Row pointers
  int *row0 = matrix[0];
  int *row1 = matrix[1];
  int *row2 = matrix[2];

  if (row0[2] != 3)
    return 7;
  if (row1[3] != 8)
    return 8;
  if (row2[1] != 10)
    return 9;

  // Pointer arithmetic on rows
  if (*(row1 + 2) != 7)
    return 10;

  return 0;
}
