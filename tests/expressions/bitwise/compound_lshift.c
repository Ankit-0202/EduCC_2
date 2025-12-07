#include <stdio.h>

int main() {
  int a = 1;
  a <<= 3;
  printf("1 <<= 3 -> %d\n", a);

  int b = 10;
  b <<= 0;
  printf("10 <<= 0 -> %d\n", b);

  return 0;
}
