#include <stdio.h>

int main() {
  int a = -1;
  unsigned int b = 1;
  if (a > b) {
    printf("-1 > 1 (unsigned rule)\n");
  } else {
    printf("-1 <= 1\n");
  }
  return 0;
}
