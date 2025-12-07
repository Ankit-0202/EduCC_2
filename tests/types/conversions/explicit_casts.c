// Test explicit type casts
int main() {
  // float to int cast
  float f = 3.9;
  int i = (int)f;
  if (i != 3)
    return 1;

  // int to char cast
  int x = 300;
  char c = (char)x; // Should wrap around
  if (c != 44)
    return 2; // 300 % 256 = 44

  // double to float cast
  double d = 3.14159265359;
  float f2 = (float)d;
  if (f2 < 3.14 || f2 > 3.15)
    return 3;

  // pointer to int cast (address)
  int value = 42;
  int *ptr = &value;
  long addr = (long)ptr;
  int *ptr2 = (int *)addr;
  if (*ptr2 != 42)
    return 4;

  // char to int explicit
  char c2 = -1;
  int i2 = (int)c2;
  if (i2 != -1)
    return 5;

  return 0;
}
