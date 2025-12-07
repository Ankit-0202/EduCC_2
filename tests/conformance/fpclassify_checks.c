#include <float.h>
#include <math.h>

int main(void) {
  double zero = 0.0;
  double sub = DBL_MIN / 2.0;
  double normal = 1.0;

  int ok = fpclassify(zero) == FP_ZERO;
  ok &= fpclassify(sub) == FP_SUBNORMAL;
  ok &= fpclassify(normal) == FP_NORMAL;
  return ok ? 0 : 1;
}
