#include <stdio.h>

void inc() {
  static int i = 0;
  i++;
  printf("%d\n", i);
}

int main() {
  inc();
  inc();
  inc();
  return 0;
}
