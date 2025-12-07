#include <math.h>
#include <stdio.h>

int main(void) {
  double x = 3.0;
  double y = 4.0;
  double h = hypot(x, y);
  printf("hypot=%.4f\n", h);
  return (fabs(h - 5.0) < 1e-6) ? 0 : 1;
}
