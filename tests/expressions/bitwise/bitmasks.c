// Test various bitmask operations
int main() {
    // Extract lower nibble
    int value = 0xAB;
    int lower = value & 0x0F;
    if (lower != 0x0B) return 1;

    // Extract upper nibble
    int upper = (value >> 4) & 0x0F;
    if (upper != 0x0A) return 2;

    // Combine nibbles
    int combined = (0x0C << 4) | 0x0D;
    if (combined != 0xCD) return 3;

    // Mask off upper bits
    int masked = 0xFFFF & 0x00FF;
    if (masked != 0x00FF) return 4;

    // Create mask of n bits
    int n = 5;
    int mask = (1 << n) - 1;
    if (mask != 0b11111) return 5;

    // Extract bit range (bits 2-5 of 0b11110110)
    int val = 0b11110110;
    int extracted = (val >> 2) & 0b1111;
    if (extracted != 0b1101) return 6;

    return 0;
}
