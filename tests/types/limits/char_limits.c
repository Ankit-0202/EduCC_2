// Test char limits
int main() {
    // Max signed char
    char max_char = 127;
    if (max_char != 127) return 1;

    // Min signed char
    char min_char = -128;
    if (min_char != -128) return 2;

    // Max unsigned char
    unsigned char max_uchar = 255;
    if (max_uchar != 255) return 3;

    // Min unsigned char
    unsigned char min_uchar = 0;
    if (min_uchar != 0) return 4;

    // Char arithmetic
    char c1 = 100;
    char c2 = 20;
    int result = c1 + c2;
    if (result != 120) return 5;

    // Character wraparound
    unsigned char c3 = 250;
    c3 = c3 + 10;
    if (c3 != 4) return 6;  // 260 % 256 = 4

    return 0;
}
