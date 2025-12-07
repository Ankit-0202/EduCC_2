#include <stdio.h>

int main() {
  char a = 100;
  char b = 100;
  // a*b = 10000, which fits in int, but not char. Should promote to int.
  int c = a * b;
  printf("100 * 100 = %d\n", c);
  return 0;
}
