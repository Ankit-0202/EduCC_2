#include <math.h>

int main(void) {
  double pos = 0.0;
  double neg = -0.0;

  double inv_pos = 1.0 / pos;
  double inv_neg = 1.0 / neg;

  int ok = isinf(inv_pos) && isinf(inv_neg);
  ok &= !signbit(inv_pos);
  ok &= signbit(inv_neg);
  return ok ? 0 : 1;
}
