#include <complex.h>

int main() {
  double complex z1 = 3.0 + 4.0 * I;
  double complex z2 = 1.0 - 2.0 * I;

  double complex sum = z1 + z2;
  double complex product = z1 * z2;
  double complex conjugate = conj(z1);

  if (creal(sum) < 3.9 || creal(sum) > 4.1)
    return 1;
  if (cimag(sum) < 1.9 || cimag(sum) > 2.1)
    return 1;

  if (creal(product) < 10.9 || creal(product) > 11.1)
    return 1;
  if (cimag(product) < -1.9 || cimag(product) > -1.7)
    return 1;

  if (creal(conjugate) < 2.9 || creal(conjugate) > 3.1)
    return 1;
  if (cimag(conjugate) < -4.1 || cimag(conjugate) > -3.9)
    return 1;

  return 0;
}