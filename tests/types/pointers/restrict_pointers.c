int add_arrays(int *restrict a, int *restrict b, int *restrict result,
               int size) {
  for (int i = 0; i < size; i++) {
    result[i] = a[i] + b[i];
  }
  return 0;
}

int multiply_arrays(int *restrict a, int *restrict b, int *restrict result,
                    int size) {
  for (int i = 0; i < size; i++) {
    result[i] = a[i] * b[i];
  }
  return 0;
}

int main() {
  int a[5] = {1, 2, 3, 4, 5};
  int b[5] = {10, 20, 30, 40, 50};
  int result[5];

  add_arrays(a, b, result, 5);

  if (result[0] != 11)
    return 1;
  if (result[1] != 22)
    return 1;
  if (result[2] != 33)
    return 1;
  if (result[3] != 44)
    return 1;
  if (result[4] != 55)
    return 1;

  multiply_arrays(a, b, result, 5);

  if (result[0] != 10)
    return 1;
  if (result[1] != 40)
    return 1;
  if (result[2] != 90)
    return 1;
  if (result[3] != 160)
    return 1;
  if (result[4] != 250)
    return 1;

  return 0;
}