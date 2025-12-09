#include <stdio.h>

void func(int *p) { printf("Val: %d\n", *p); }

int main() {
  int arr[3] = {1, 2, 3};
  func(arr); // Decay to pointer
  return 0;
}
