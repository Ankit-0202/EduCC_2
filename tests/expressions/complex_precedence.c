// Test complex operator precedence
int main() {
  // Arithmetic precedence
  int a = 2 + 3 * 4 - 5;
  if (a != 9)
    return 1; // 2 + 12 - 5 = 9

  // Bitwise AND has lower precedence than comparison
  int b = (5 & 3) == 1;
  if (b != 1)
    return 2;

  // Logical AND has lower precedence than comparison
  int c = 5 > 3 && 2 < 4;
  if (c != 1)
    return 3;

  // Shift and addition
  int d = 1 << 2 + 1;
  if (d != 8)
    return 4; // 1 << (2 + 1) = 1 << 3 = 8

  // Mixed operators
  int e = 10 * 2 + 5 / 5 - 3;
  if (e != 18)
    return 5; // 20 + 1 - 3 = 18

  // Parentheses override
  int f = (2 + 3) * (4 - 1);
  if (f != 15)
    return 6;

  return 0;
}
