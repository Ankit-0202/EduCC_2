#include <stdio.h>

int main() {
#ifndef BAR
  printf("BAR not defined\n");
#else
  printf("BAR defined\n");
#endif
  return 0;
}
