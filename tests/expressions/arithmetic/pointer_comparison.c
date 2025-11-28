// Test pointer comparison operations
int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int *p1 = &arr[0];
    int *p2 = &arr[2];
    int *p3 = &arr[4];

    // Less than
    if (!(p1 < p2)) return 1;
    if (!(p2 < p3)) return 2;

    // Greater than
    if (!(p3 > p2)) return 3;
    if (!(p2 > p1)) return 4;

    // Equal
    int *p4 = &arr[0];
    if (p1 != p4) return 5;

    // Not equal
    if (p1 == p2) return 6;

    // Less than or equal
    if (!(p1 <= p2)) return 7;
    if (!(p1 <= p4)) return 8;

    // Greater than or equal
    if (!(p3 >= p2)) return 9;
    if (!(p1 >= p4)) return 10;

    return 0;
}
