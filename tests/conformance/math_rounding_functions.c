#include <math.h>

int main(void) {
  double a = nearbyint(2.3);
  double b = nearbyint(-2.7);
  long c = lrint(3.8);
  return (a == 2.0 && b == -3.0 && c == 4) ? 0 : 1;
}
