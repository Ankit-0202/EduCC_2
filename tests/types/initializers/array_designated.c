int main() {
  int arr1[5] = {[0] = 10, [2] = 30, [4] = 50};

  if (arr1[0] != 10)
    return 1;
  if (arr1[1] != 0)
    return 1; // default initialized
  if (arr1[2] != 30)
    return 1;
  if (arr1[3] != 0)
    return 1; // default initialized
  if (arr1[4] != 50)
    return 1;

  char str[10] = {[0] = 'H', [1] = 'e', [2] = 'l', [3] = 'l', [4] = 'o'};

  if (str[0] != 'H')
    return 1;
  if (str[1] != 'e')
    return 1;
  if (str[2] != 'l')
    return 1;
  if (str[3] != 'l')
    return 1;
  if (str[4] != 'o')
    return 1;
  if (str[5] != '\0')
    return 1; // default initialized

  int matrix[3][3] = {
      [0][0] = 1, [0][1] = 2, [0][2] = 3, [1][0] = 4, [1][1] = 5,
      [1][2] = 6, [2][0] = 7, [2][1] = 8, [2][2] = 9};

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

  return 0;
}