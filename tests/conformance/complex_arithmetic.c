#include <complex.h>
#include <math.h>

int main(void) {
    double complex z = 1.0 + 2.0 * I;
    double complex w = 3.0 - 1.0 * I;
    double complex result = z * w;
    double complex expected = 5.0 + 5.0 * I;
    double diff = cabs(result - expected);
    return diff < 1e-9 ? 0 : 1;
}
