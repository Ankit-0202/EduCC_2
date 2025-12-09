#include <stdio.h>

int main() {
  int arr[3] = {1, 2, 3};
  int (*p)[3] = &arr;
  printf("First: %d\n", (*p)[0]);
  return 0;
}
