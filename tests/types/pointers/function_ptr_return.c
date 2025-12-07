#include <stdio.h>

int func() { return 5; }
typedef int (*FuncPtr)();

FuncPtr get_func() { return func; }

int main() {
  printf("%d\n", get_func()());
  return 0;
}
