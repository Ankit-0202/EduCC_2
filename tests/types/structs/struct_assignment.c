#include <stdio.h>

struct S {
  int x;
  int y;
};

int main() {
  struct S a = {1, 2};
  struct S b;
  b = a;
  printf("%d %d\n", b.x, b.y);
  return 0;
}
