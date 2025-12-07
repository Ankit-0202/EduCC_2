#include <stdio.h>

int foo(); // Forward decl

int main() {
  printf("%d\n", foo());
  return 0;
}

int foo() { return 42; }
