#include <stdio.h>

struct S {
  int arr[3];
};

int main() {
  struct S s = {{1, 2, 3}};
  printf("%d\n", s.arr[1]);
  return 0;
}
