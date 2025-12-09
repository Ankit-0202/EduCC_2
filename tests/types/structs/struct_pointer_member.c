#include <stdio.h>

struct S {
  int *p;
};

int main() {
  int a = 10;
  struct S s;
  s.p = &a;
  printf("%d\n", *s.p);
  return 0;
}
