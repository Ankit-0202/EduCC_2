// Test bitwise XOR assignment operator ^=
int main() {
    int a = 0xFF;
    a ^= 0xFF;
    if (a != 0) return 1;

    int b = 0b10101010;
    b ^= 0b01010101;
    if (b != 0b11111111) return 2;

    int c = 42;
    c ^= 0;
    if (c != 42) return 3;

    int d = 0xAAAA;
    d ^= 0x5555;
    if (d != 0xFFFF) return 4;

    // XOR swap trick
    int x = 10, y = 20;
    x ^= y;
    y ^= x;
    x ^= y;
    if (x != 20 || y != 10) return 5;

    return 0;
}
