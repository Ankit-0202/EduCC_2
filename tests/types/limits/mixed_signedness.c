// Test mixing signed and unsigned in edge cases
int main() {
  // Unsigned and signed comparison
  unsigned int u = 10;
  int s = 10;
  if (u != s)
    return 1;

  // Negative signed with unsigned
  unsigned int u2 = 10;
  int s2 = -5;
  unsigned int result = u2 + s2;
  if (result != 5)
    return 2;

  // Large unsigned with signed
  unsigned int u3 = 4000000000U;
  int s3 = 1000000000;
  if (u3 < s3)
    return 3; // Should be false

  // Zero comparisons
  unsigned int u4 = 0;
  int s4 = 0;
  if (u4 != s4)
    return 4;

  // Multiplication
  unsigned int u5 = 100;
  int s5 = 100;
  unsigned int prod = u5 * s5;
  if (prod != 10000)
    return 5;

  return 0;
}
