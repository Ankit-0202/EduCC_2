#include <math.h>

static int nearly_equal(double a, double b) {
  const double diff = fabs(a - b);
  return diff < 1e-12;
}

int main(void) {
  double x = 1.3;
  double y = log(exp(x));
  if (!nearly_equal(x, y)) {
    return 1;
  }

  double z = log1p(1e-4);
  if (!nearly_equal(z, log(1.0 + 1e-4))) {
    return 2;
  }

  double w = expm1(2e-5);
  if (!nearly_equal(w, exp(2e-5) - 1.0)) {
    return 3;
  }

  return 0;
}


