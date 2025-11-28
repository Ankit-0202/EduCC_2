// Test various bit shift patterns
int main() {
    // Power of 2 via left shift
    int pow2 = 1 << 10;
    if (pow2 != 1024) return 1;

    // Divide by 2 via right shift
    int div2 = 100 >> 1;
    if (div2 != 50) return 2;

    // Multiply by 8 via left shift
    int mul8 = 5 << 3;
    if (mul8 != 40) return 3;

    // Divide by 16 via right shift
    int div16 = 160 >> 4;
    if (div16 != 10) return 4;

    // Shift all bits out
    int x = 0xFF;
    x >>= 8;
    if (x != 0) return 5;

    // Shift zeros in from left
    int y = 0x01;
    y <<= 8;
    if (y != 0x100) return 6;

    // Multiple shifts
    int z = 1;
    z <<= 2;
    z <<= 2;
    z <<= 2;
    if (z != 64) return 7;

    return 0;
}
