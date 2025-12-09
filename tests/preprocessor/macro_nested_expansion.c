#include <stdio.h>

#define A 10
#define B A + 5
#define C B * 2

int main() {
  printf("%d\n",
         C); // 10 + 5 * 2 = 20, or (10+5)*2 if grouped? Macros are text subst.
  // B -> 10 + 5
  // C -> 10 + 5 * 2 -> 10 + 10 = 20
  return 0;
}
