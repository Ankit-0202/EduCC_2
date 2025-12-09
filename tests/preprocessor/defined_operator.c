#include <stdio.h>

#define A

int main() {
#if defined(A) && !defined(B)
  printf("A yes B no\n");
#endif
  return 0;
}
