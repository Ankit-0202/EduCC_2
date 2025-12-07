#include <math.h>

int main(void) {
  double val = NAN;
  return isnan(val + 1.0) ? 0 : 1;
}
