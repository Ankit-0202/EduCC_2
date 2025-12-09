#include <stdio.h>

int main() {
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (j == 1)
        continue; // Should continue inner
      printf("i=%d, j=%d\n", i, j);
    }
  }
  return 0;
}
