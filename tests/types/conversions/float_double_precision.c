// Test float vs double precision
int main() {
    // Float precision
    float f1 = 3.14159265f;
    if (f1 < 3.14 || f1 > 3.15) return 1;

    // Double precision
    double d1 = 3.14159265358979;
    if (d1 < 3.14159 || d1 > 3.14160) return 2;

    // Float arithmetic
    float f2 = 1.0f / 3.0f;
    if (f2 < 0.33 || f2 > 0.34) return 3;

    // Double arithmetic
    double d2 = 1.0 / 3.0;
    if (d2 < 0.333 || d2 > 0.334) return 4;

    // Float to double
    float f3 = 2.5f;
    double d3 = f3;
    if (d3 < 2.4 || d3 > 2.6) return 5;

    // Double to float (precision loss)
    double d4 = 1.23456789;
    float f4 = (float)d4;
    if (f4 < 1.23 || f4 > 1.24) return 6;

    return 0;
}
