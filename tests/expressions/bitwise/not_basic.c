#include <stdio.h>

int main() {
  int a = 0;
  int b = ~a;
  printf("~0 = %d\n", b);

  int c = 0xF0F0F0F0;
  int d = ~c;
  printf("~0xF0F0F0F0 = %X\n", (unsigned int)d); // Use hex to be clear

  unsigned int e = 0;
  printf("~0u = %u\n", ~e);

  return 0;
}
