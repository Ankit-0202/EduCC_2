// Test unsigned integer limits
int main() {
    // Max unsigned int
    unsigned int max_uint = 4294967295U;
    if (max_uint != 4294967295U) return 1;

    // Min unsigned int
    unsigned int min_uint = 0;
    if (min_uint != 0) return 2;

    // Max unsigned short
    unsigned short max_ushort = 65535;
    if (max_ushort != 65535) return 3;

    // Unsigned arithmetic
    unsigned int u1 = 1000000;
    unsigned int u2 = 2000000;
    unsigned int sum = u1 + u2;
    if (sum != 3000000) return 4;

    // Unsigned never negative
    unsigned int u3 = 10;
    unsigned int u4 = 20;
    unsigned int diff = u3 - u4;  // Wraps around
    if (diff != 4294967286U) return 5;

    return 0;
}
