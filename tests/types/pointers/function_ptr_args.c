#include <stdio.h>

int add(int a, int b) { return a + b; }

int main() {
  int (*op)(int, int) = add;
  printf("%d\n", op(10, 20));
  return 0;
}
