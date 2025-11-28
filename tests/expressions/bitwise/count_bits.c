// Test bit counting algorithms
int main() {
    // Count set bits in a number
    int n = 0b10110101;
    int count = 0;
    int temp = n;

    while (temp) {
        count += temp & 1;
        temp >>= 1;
    }
    if (count != 5) return 1;

    // Count bits in 0xFF
    count = 0;
    temp = 0xFF;
    while (temp) {
        count += temp & 1;
        temp >>= 1;
    }
    if (count != 8) return 2;

    // Count bits in power of 2 (should be 1)
    count = 0;
    temp = 64;
    while (temp) {
        count += temp & 1;
        temp >>= 1;
    }
    if (count != 1) return 3;

    // Check if power of 2 (n & (n-1) == 0)
    int p2 = 16;
    if ((p2 & (p2 - 1)) != 0) return 4;

    int not_p2 = 15;
    if ((not_p2 & (not_p2 - 1)) == 0) return 5;

    return 0;
}
