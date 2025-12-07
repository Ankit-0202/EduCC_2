#include <stdio.h>

int main() {
  int arr[3] = {1, 2, 3};
  int *p = arr;
  printf("%d\n", p[2]); // Equivalent to *(p+2)
  return 0;
}
