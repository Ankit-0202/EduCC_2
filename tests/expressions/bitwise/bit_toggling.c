// Test toggling individual bits
int main() {
    int flags = 0;

    // Toggle bit 0 (0 -> 1)
    flags ^= (1 << 0);
    if (flags != 1) return 1;

    // Toggle bit 0 again (1 -> 0)
    flags ^= (1 << 0);
    if (flags != 0) return 2;

    // Toggle bit 3
    flags ^= (1 << 3);
    if (flags != 8) return 3;

    // Toggle multiple bits
    int mask = 0b10101010;
    mask ^= 0b11111111;
    if (mask != 0b01010101) return 4;

    // Toggle twice returns to original
    int x = 42;
    int original = x;
    x ^= 0xFF;
    x ^= 0xFF;
    if (x != original) return 5;

    return 0;
}
