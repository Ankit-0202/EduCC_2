int main() {
  int a, b, c;

  // Basic comma operator
  a = (1, 2, 3);
  if (a != 3)
    return 1;

  // Comma operator in for loop
  for (a = 0, b = 10; a < 5; a++, b--) {
    c = a + b;
  }
  if (a != 5)
    return 1;
  if (b != 5)
    return 1;

  // Comma operator in function call
  int result = (a = 10, b = 20, a + b);
  if (result != 30)
    return 1;
  if (a != 10)
    return 1;
  if (b != 20)
    return 1;

  // Comma operator in conditional
  int x = 5;
  int y = (x > 3) ? (x = 10, x + 5) : (x = 0, x);
  if (y != 15)
    return 1;
  if (x != 10)
    return 1;

  return 0;
}