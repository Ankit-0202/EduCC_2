#include <stdio.h>

#ifndef GUARD
#define GUARD

int foo() { return 1; }

#endif

#ifndef GUARD
#define GUARD
int foo() { return 2; } // Should not be compiled
#endif

int main() {
  printf("%d\n", foo());
  return 0;
}
