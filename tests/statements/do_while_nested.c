#include <stdio.h>

int main() {
  int i = 0;
  do {
    int j = 0;
    do {
      printf("i=%d, j=%d\n", i, j);
      j++;
    } while (j < 2);
    i++;
  } while (i < 2);
  return 0;
}
