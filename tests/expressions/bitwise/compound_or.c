#include <stdio.h>

int main() {
  int a = 0xF0;
  a |= 0x0F;
  printf("0xF0 |= 0x0F -> %d\n", a);

  int b = 10;
  b |= 20; // 01010 | 10100 = 11110 = 30
  printf("10 |= 20 -> %d\n", b);

  return 0;
}
