#include <stdio.h>

int main() {
  int a = 0xAA;
  int b = 0x55;
  int c = a ^ b;     // 0xFF
  int d = c << 4;    // 0xFF0
  int e = d | 0xF;   // 0xFFF
  int f = e & 0x0F0; // 0x0F0
  printf("Res: %X\n", f);
  return 0;
}
