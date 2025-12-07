#include <stdio.h>

#define A 1
#undef A

int main() {
#ifdef A
  printf("Defined\n");
#else
  printf("Undefined\n");
#endif
  return 0;
}
