// Test right shift assignment operator >>=
int main() {
  int a = 16;
  a >>= 2;
  if (a != 4)
    return 1;

  int b = 128;
  b >>= 3;
  if (b != 16)
    return 2;

  int c = 0xFF;
  c >>= 4;
  if (c != 0x0F)
    return 3;

  int d = 1024;
  d >>= 10;
  if (d != 1)
    return 4;

  int e = 100;
  e >>= 1;
  if (e != 50)
    return 5;

  return 0;
}
