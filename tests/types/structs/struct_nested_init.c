#include <stdio.h>

struct Inner {
  int x;
};

struct Outer {
  struct Inner in;
  int y;
};

int main() {
  struct Outer o = {{1}, 2};
  printf("%d %d\n", o.in.x, o.y);
  return 0;
}
