#include <complex.h>
#include <math.h>

int main(void) {
  double pi = acos(-1.0);
  double complex value = cexp(I * pi);
  return (fabs(creal(value) + 1.0) < 1e-9 && fabs(cimag(value)) < 1e-9) ? 0 : 1;
}
