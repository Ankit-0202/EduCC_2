// Test setting individual bits
int main() {
    int flags = 0;

    // Set bit 0
    flags |= (1 << 0);
    if (flags != 1) return 1;

    // Set bit 3
    flags |= (1 << 3);
    if (flags != 9) return 2;  // 0b1001

    // Set bit 7
    flags |= (1 << 7);
    if (flags != 137) return 3;  // 0b10001001

    // Set multiple bits at once
    int mask = 0;
    mask |= (1 << 1) | (1 << 2) | (1 << 4);
    if (mask != 22) return 4;  // 0b10110

    // Check if bit is set
    if (!(flags & (1 << 3))) return 5;

    return 0;
}
