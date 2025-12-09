#include <stdio.h>

int main() {
  int i = 0;
  goto start;

end:
  printf("End\n");
  return 0;

middle:
  printf("Middle\n");
  goto end;

start:
  printf("Start\n");
  goto middle;
}
