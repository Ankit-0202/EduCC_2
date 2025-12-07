#include <stdio.h>

int main() {
  int a = 1, b = 2;
  int *arr[2];
  arr[0] = &a;
  arr[1] = &b;
  printf("%d %d\n", *arr[0], *arr[1]);
  return 0;
}
