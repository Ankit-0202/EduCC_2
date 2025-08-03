int fib(int n, int a, int b) {
  if (n == 0)
    return a;
  return fib(n - 1, b, a + b);
}

int main() {
  /* fib(10,0,1) should compute Fibonacci(10) == 55 */
  return fib(10, 0, 1) - 55;
}
