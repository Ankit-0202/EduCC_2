#include <stdio.h>

struct S {
  unsigned int a : 1;
  unsigned int b : 3;
};

int main() {
  struct S s;
  s.a = 1;
  s.b = 5;
  printf("%u %u\n", s.a, s.b);
  return 0;
}
