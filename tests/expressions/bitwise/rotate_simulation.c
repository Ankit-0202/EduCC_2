// Test bit rotation simulation (C has no rotate operator)
int main() {
    // Rotate left: take top bits and OR them at bottom
    unsigned int val = 0x12345678;
    int n = 4;

    // Left rotate by 4
    unsigned int rotated_left = (val << n) | (val >> (32 - n));
    if (rotated_left != 0x23456781) return 1;

    // Right rotate by 4
    val = 0x12345678;
    unsigned int rotated_right = (val >> n) | (val << (32 - n));
    if (rotated_right != 0x81234567) return 2;

    // Rotate by 8 bits (1 byte)
    unsigned char byte = 0xA5;  // 10100101
    unsigned char rot_left = (byte << 1) | (byte >> 7);
    if (rot_left != 0x4B) return 3;  // 01001011

    // Rotate by 16 bits (full half)
    unsigned int val2 = 0xABCD0000;
    unsigned int rot16 = (val2 << 16) | (val2 >> 16);
    if (rot16 != 0x0000ABCD) return 4;

    return 0;
}
