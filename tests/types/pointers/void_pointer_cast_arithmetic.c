#include <stdio.h>

int main() {
  int a = 10;
  void *p = &a;
  char *cp = (char *)p;
  cp++;
  printf("Address changed by 1\n");
  return 0;
}
