// Test hexadecimal literals
int main() {
    int a = 0x10;
    if (a != 16) return 1;

    int b = 0xFF;
    if (b != 255) return 2;

    int c = 0xDEADBEEF;
    if (c != 3735928559) return 3;

    int d = 0x0;
    if (d != 0) return 4;

    int e = 0xABCD;
    if (e != 43981) return 5;

    // Lowercase hex
    int f = 0xabcd;
    if (f != 43981) return 6;

    // Mixed case
    int g = 0xAbCd;
    if (g != 43981) return 7;

    return 0;
}
