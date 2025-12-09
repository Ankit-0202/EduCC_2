// Test pointer to entire array
int main() {
  int arr[5] = {1, 2, 3, 4, 5};

  // Pointer to array of 5 ints
  int (*ptr)[5] = &arr;

  // Dereference to get array, then index
  if ((*ptr)[0] != 1)
    return 1;
  if ((*ptr)[2] != 3)
    return 2;
  if ((*ptr)[4] != 5)
    return 3;

  // 2D array with pointer to array
  int matrix[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

  int (*rowptr)[4] = matrix;

  // Access first row
  if (rowptr[0][0] != 1)
    return 4;
  if (rowptr[0][3] != 4)
    return 5;

  // Access second row
  if (rowptr[1][0] != 5)
    return 6;
  if (rowptr[1][3] != 8)
    return 7;

  // Increment to next row
  rowptr++;
  if (rowptr[0][0] != 5)
    return 8;
  if (rowptr[1][0] != 9)
    return 9;

  return 0;
}
