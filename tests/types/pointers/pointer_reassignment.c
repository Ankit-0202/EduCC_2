#include <stdio.h>

int main() {
  int a = 1;
  int b = 2;
  int *p = &a;
  printf("%d\n", *p);
  p = &b;
  printf("%d\n", *p);
  return 0;
}
