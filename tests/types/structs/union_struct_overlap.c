#include <stdio.h>

struct S {
  int x;
};

union U {
  struct S s;
  int i;
};

int main() {
  union U u;
  u.i = 10;
  printf("Struct member: %d\n",
         u.s.x); // Should be 10 assuming no padding/layout weirdness for single
                 // int
  return 0;
}
