int add(int a, int b) { return a + b; }

int multiply(int a, int b) { return a * b; }

int subtract(int a, int b) { return a - b; }

int divide(int a, int b) { return a / b; }

int complex_calculation(int x, int y, int z) {
  return add(multiply(x, y), subtract(z, 5));
}

int nested_expression(int a, int b, int c) {
  return add(multiply(a, b), divide(c, 2));
}

int main() {
  // Test nested function calls
  int result1 = add(multiply(3, 4), subtract(10, 5));
  if (result1 != 17)
    return 1; // (3*4) + (10-5) = 12 + 5 = 17

  int result2 = multiply(add(2, 3), subtract(8, 3));
  if (result2 != 25)
    return 1; // (2+3) * (8-3) = 5 * 5 = 25

  int result3 = complex_calculation(2, 3, 10);
  if (result3 != 11)
    return 1; // (2*3) + (10-5) = 6 + 5 = 11

  int result4 = nested_expression(4, 5, 10);
  if (result4 != 25)
    return 1; // (4*5) + (10/2) = 20 + 5 = 25

  return 0;
}