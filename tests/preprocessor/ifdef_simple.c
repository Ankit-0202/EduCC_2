#include <stdio.h>

#define FOO

int main() {
#ifdef FOO
  printf("FOO defined\n");
#else
  printf("FOO not defined\n");
#endif
  return 0;
}
