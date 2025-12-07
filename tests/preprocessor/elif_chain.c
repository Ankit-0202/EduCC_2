#include <stdio.h>

#define VAL 2

int main() {
#if VAL == 1
  printf("1\n");
#elif VAL == 2
  printf("2\n");
#else
  printf("Other\n");
#endif
  return 0;
}
