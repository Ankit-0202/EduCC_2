#include <stdio.h>

int main() {
  int a = 10;
  const int *p = &a;
  p++; // OK
  // *p = 20; // Error if checked
  printf("%d\n",
         *p); // Undefined behavior if outside bounds, but syntax check mostly
  return 0;
}
