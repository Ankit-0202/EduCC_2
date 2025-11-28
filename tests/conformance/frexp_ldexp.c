#include <math.h>

int main(void) {
    int exponent = 0;
    double mantissa = frexp(48.0, &exponent);
    double rebuilt = ldexp(mantissa, exponent);
    return fabs(rebuilt - 48.0) < 1e-12 ? 0 : 1;
}
