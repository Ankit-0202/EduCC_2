#include <math.h>

int main(void) {
  double value = fma(2.0, 0.5, 0.5);
  return fabs(value - 1.5) < 1e-12 ? 0 : 1;
}
