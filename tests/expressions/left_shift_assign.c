// Test left shift assignment operator <<=
int main() {
  int a = 1;
  a <<= 3;
  if (a != 8)
    return 1;

  int b = 5;
  b <<= 2;
  if (b != 20)
    return 2;

  int c = 0xFF;
  c <<= 4;
  if (c != 0xFF0)
    return 3;

  int d = 1;
  d <<= 10;
  if (d != 1024)
    return 4;

  int e = 7;
  e <<= 1;
  if (e != 14)
    return 5;

  return 0;
}
