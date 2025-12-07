int add(int a, int b) { return a + b; }

int multiply(int a, int b) { return a * b; }

int subtract(int a, int b) { return a - b; }

int process_numbers(int a, int b, int (*operation)(int, int)) {
  return operation(a, b);
}

int apply_to_array(int arr[], int size, int (*func)(int)) {
  int result = 0;
  for (int i = 0; i < size; i++) {
    result += func(arr[i]);
  }
  return result;
}

int square(int x) { return x * x; }

int double_value(int x) { return x * 2; }

int main() {
  // Test with different operations
  int result1 = process_numbers(10, 5, add);
  if (result1 != 15)
    return 1;

  int result2 = process_numbers(10, 5, multiply);
  if (result2 != 50)
    return 1;

  int result3 = process_numbers(10, 5, subtract);
  if (result3 != 5)
    return 1;

  // Test with array processing
  int arr[5] = {1, 2, 3, 4, 5};

  int sum_squares = apply_to_array(arr, 5, square);
  if (sum_squares != 55)
    return 1; // 1+4+9+16+25 = 55

  int sum_doubles = apply_to_array(arr, 5, double_value);
  if (sum_doubles != 30)
    return 1; // 2+4+6+8+10 = 30

  return 0;
}