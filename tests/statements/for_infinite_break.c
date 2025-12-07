#include <stdio.h>

int main() {
  int i = 0;
  for (;;) {
    if (i >= 3)
      break;
    printf("Infinite %d\n", i);
    i++;
  }
  return 0;
}
