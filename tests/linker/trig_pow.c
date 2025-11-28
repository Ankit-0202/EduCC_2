#include <math.h>

static int nearly_equal(double a, double b) {
  const double diff = fabs(a - b);
  return diff < 1e-12;
}

int main(void) {
  double s = sin(0.25);
  double c = cos(0.25);
  if (!nearly_equal(s * s + c * c, 1.0)) {
    return 1;
  }

  double root = pow(81.0, 0.25);
  if (!nearly_equal(root, 3.0)) {
    return 2;
  }

  return 0;
}


