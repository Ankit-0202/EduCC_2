// Test different integer sizes
int main() {
    // char (1 byte)
    char c = 127;
    if (c != 127) return 1;

    // short (2 bytes)
    short s = 32767;
    if (s != 32767) return 2;

    // int (4 bytes)
    int i = 2147483647;
    if (i != 2147483647) return 3;

    // long (4 or 8 bytes)
    long l = 2147483647L;
    if (l != 2147483647L) return 4;

    // Unsigned variants
    unsigned char uc = 255;
    if (uc != 255) return 5;

    unsigned short us = 65535;
    if (us != 65535) return 6;

    unsigned int ui = 4294967295U;
    if (ui != 4294967295U) return 7;

    // Size comparisons
    if (sizeof(char) != 1) return 8;
    if (sizeof(short) < sizeof(char)) return 9;
    if (sizeof(int) < sizeof(short)) return 10;
    if (sizeof(long) < sizeof(int)) return 11;

    return 0;
}
