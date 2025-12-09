#include <math.h>

int main(void) {
  double pos = INFINITY;
  double neg = -INFINITY;
  return (isinf(pos) && isinf(neg) && signbit(neg)) ? 0 : 1;
}
