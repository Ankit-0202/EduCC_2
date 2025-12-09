#include <stdio.h>

union U {
  int i;
  float f;
};

int main() {
  union U u;
  u.i = 1065353216; // 1.0 in float bit representation
  printf("As float: %.1f\n", u.f);
  return 0;
}
