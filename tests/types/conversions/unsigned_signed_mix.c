// Test mixing unsigned and signed integers
int main() {
    // Unsigned + signed (positive)
    unsigned int u1 = 10;
    int s1 = 5;
    unsigned int r1 = u1 + s1;
    if (r1 != 15) return 1;

    // Unsigned - signed
    unsigned int u2 = 20;
    int s2 = 5;
    unsigned int r2 = u2 - s2;
    if (r2 != 15) return 2;

    // Unsigned * signed
    unsigned int u3 = 6;
    int s3 = 7;
    unsigned int r3 = u3 * s3;
    if (r3 != 42) return 3;

    // Comparison: unsigned vs signed
    unsigned int u4 = 10;
    int s4 = 10;
    if (u4 != s4) return 4;

    // Unsigned with negative signed (wraps to large unsigned)
    unsigned int u5 = 10;
    int s5 = -5;
    int r5 = (int)(u5 + s5);
    if (r5 != 5) return 5;

    return 0;
}
