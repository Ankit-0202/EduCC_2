// Test clearing individual bits
int main() {
    int flags = 0xFF;  // All bits set

    // Clear bit 0
    flags &= ~(1 << 0);
    if (flags != 0xFE) return 1;

    // Clear bit 3
    flags &= ~(1 << 3);
    if (flags != 0xF6) return 2;  // 11110110

    // Clear bit 7
    flags &= ~(1 << 7);
    if (flags != 0x76) return 3;  // 01110110

    // Clear multiple bits
    int mask = 0xFF;
    mask &= ~((1 << 1) | (1 << 2) | (1 << 4));
    if (mask != 0xE9) return 4;  // 11101001

    // Verify bit is cleared
    if (flags & (1 << 7)) return 5;

    return 0;
}
