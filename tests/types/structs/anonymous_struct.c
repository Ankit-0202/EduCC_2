#include <stdio.h>

struct S {
  struct {
    int x;
  };
};

int main() {
  struct S s;
  s.x = 10;
  printf("%d\n", s.x);
  return 0;
}
