int factorial(int n) {
  if (n <= 1)
    return 1;
  return n * factorial(n - 1);
}

int fibonacci(int n) {
  if (n <= 1)
    return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

int sum_recursive(int n) {
  if (n <= 0)
    return 0;
  return n + sum_recursive(n - 1);
}

int main() {
  if (factorial(5) != 120)
    return 1; // 5! = 120
  if (factorial(3) != 6)
    return 1; // 3! = 6

  if (fibonacci(6) != 8)
    return 1; // F(6) = 8
  if (fibonacci(7) != 13)
    return 1; // F(7) = 13

  if (sum_recursive(5) != 15)
    return 1; // 1+2+3+4+5 = 15
  if (sum_recursive(10) != 55)
    return 1; // 1+2+...+10 = 55

  return 0;
}