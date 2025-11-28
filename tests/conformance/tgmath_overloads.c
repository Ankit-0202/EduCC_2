#include <tgmath.h>
#include <math.h>

int main(void) {
    float f = sqrt(4.0f);          // uses float overload
    double d = sqrt(9.0);          // uses double overload
    double complex c = sqrt(-4.0 + 0.0 * I); // complex overload

    int ok = (fabsf(f - 2.0f) < 1e-6f);
    ok &= fabs(d - 3.0) < 1e-12;
    ok &= fabs(cimag(c) - 2.0) < 1e-12;
    return ok ? 0 : 1;
}
