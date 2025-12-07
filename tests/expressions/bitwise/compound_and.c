#include <stdio.h>

int main() {
  int a = 0xFF;
  a &= 0x0F;
  printf("0xFF &= 0x0F -> %d\n", a);

  int b = 10;
  b &= 20; // 01010 & 10100 = 00000
  printf("10 &= 20 -> %d\n", b);

  return 0;
}
