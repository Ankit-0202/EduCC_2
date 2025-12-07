#include <stdio.h>

int main() {
  int a = 1;
  printf("1 << 0 = %d\n", a << 0);
  printf("1 << 1 = %d\n", a << 1);
  printf("1 << 10 = %d\n", a << 10);

  int b = -1; // All ones usually
  printf("-1 << 1 = %d\n", b << 1);

  int c = 5;
  printf("5 << 2 = %d\n", c << 2);

  return 0;
}
