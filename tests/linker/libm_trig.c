#include <math.h>

int main(void) {
  double x = 0.75;
  double value = sin(x) * sin(x) + cos(x) * cos(x);

  double delta = fabs(value - 1.0);
  return (delta < 1e-6) ? 0 : 1;
}
