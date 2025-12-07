int main() {
  int sum = 0;

  // Simple loop that could be unrolled
  for (int i = 0; i < 4; i++) {
    sum += i;
  }

  if (sum != 6)
    return 1; // 0+1+2+3 = 6

  // Loop with multiplication
  int product = 1;
  for (int i = 1; i <= 5; i++) {
    product *= i;
  }

  if (product != 120)
    return 1; // 1*2*3*4*5 = 120

  // Loop with array access
  int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  int array_sum = 0;

  for (int i = 0; i < 8; i++) {
    array_sum += arr[i];
  }

  if (array_sum != 36)
    return 1; // 1+2+3+4+5+6+7+8 = 36

  return 0;
}