// Test integer literal suffixes (U, L, UL, LL, ULL)
int main() {
  // Unsigned suffix
  unsigned int a = 100U;
  if (a != 100)
    return 1;

  // Long suffix
  long b = 1000L;
  if (b != 1000)
    return 2;

  // Unsigned long suffix
  unsigned long c = 5000UL;
  if (c != 5000)
    return 3;

  // Long long suffix
  long long d = 1000000LL;
  if (d != 1000000)
    return 4;

  // Unsigned long long suffix
  unsigned long long e = 9999999ULL;
  if (e != 9999999)
    return 5;

  // Lowercase suffixes
  unsigned int f = 42u;
  long g = 42l;
  if (f != 42 || g != 42)
    return 6;

  // Hex with suffix
  unsigned int h = 0xFFU;
  if (h != 255)
    return 7;

  return 0;
}
