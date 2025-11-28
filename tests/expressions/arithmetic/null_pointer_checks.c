// Test null pointer handling
int main() {
    int *p1 = 0;
    int *p2 = 0;

    // Null pointer comparison
    if (p1 != p2) return 1;

    // Null check
    if (p1) return 2;

    // Non-null check
    int value = 42;
    int *p3 = &value;
    if (!p3) return 3;

    // Comparison with zero
    if (p1 != 0) return 4;
    if (p3 == 0) return 5;

    // Assignment and check
    int *p4 = &value;
    p4 = 0;
    if (p4 != 0) return 6;

    return 0;
}
