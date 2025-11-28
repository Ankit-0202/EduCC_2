// Test integer limits and boundaries
int main() {
    // Maximum positive int
    int max_int = 2147483647;
    if (max_int != 2147483647) return 1;

    // Minimum negative int
    int min_int = -2147483648;
    if (min_int != -2147483648) return 2;

    // Near maximum
    int near_max = 2147483646;
    if (near_max + 1 != max_int) return 3;

    // Zero
    int zero = 0;
    if (zero != 0) return 4;

    // Negative values
    int neg = -42;
    if (neg != -42) return 5;

    // Operations near limits
    int x = 1000000;
    int y = x * 2;
    if (y != 2000000) return 6;

    return 0;
}
