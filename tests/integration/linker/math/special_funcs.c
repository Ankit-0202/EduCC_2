#include <math.h>

static int nearly_equal(double a, double b) {
  const double diff = fabs(a - b);
  return diff < 1e-12;
}

int main(void) {
  double mod = fmod(17.5, 4.0);
  if (!nearly_equal(mod, 1.5)) {
    return 1;
  }

  if (!nearly_equal(fabs(-123.0), 123.0)) {
    return 2;
  }

  if (!nearly_equal(floor(3.7), 3.0)) {
    return 3;
  }

  if (!nearly_equal(ceil(-2.5), -2.0)) {
    return 4;
  }

  return 0;
}


