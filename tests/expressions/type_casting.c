int main() {
  // Integer to float
  int i = 10;
  float f = (float)i;
  if (f < 9.9 || f > 10.1)
    return 1;

  // Float to integer
  float f2 = 3.7;
  int i2 = (int)f2;
  if (i2 != 3)
    return 1;

  // Integer to char
  int i3 = 65;
  char c = (char)i3;
  if (c != 'A')
    return 1;

  // Char to integer
  char c2 = 'B';
  int i4 = (int)c2;
  if (i4 != 66)
    return 1;

  // Pointer casting
  int x = 42;
  void *vptr = (void *)&x;
  int *iptr = (int *)vptr;
  if (*iptr != 42)
    return 1;

  // Float to double
  float f3 = 3.14;
  double d = (double)f3;
  if (d < 3.13 || d > 3.15)
    return 1;

  // Double to float
  double d2 = 2.718;
  float f4 = (float)d2;
  if (f4 < 2.71 || f4 > 2.72)
    return 1;

  // Unsigned to signed
  unsigned int u = 10;
  int s = (int)u;
  if (s != 10)
    return 1;

  // Signed to unsigned
  int s2 = -5;
  unsigned int u2 = (unsigned int)s2;
  // Note: This is implementation-dependent, but should not crash

  return 0;
}