// Test checking if specific bits are set
int main() {
    int flags = 0b10101010;

    // Test bit 1 is set
    if (!(flags & (1 << 1))) return 1;

    // Test bit 0 is not set
    if (flags & (1 << 0)) return 2;

    // Test bit 3 is set
    if (!(flags & (1 << 3))) return 3;

    // Test bit 4 is not set
    if (flags & (1 << 4)) return 4;

    // Test multiple bits
    int mask = 0b00001010;
    if ((flags & mask) != mask) return 5;

    // Test any bit set in mask
    int mask2 = 0b00000001;
    if (flags & mask2) return 6;

    return 0;
}
