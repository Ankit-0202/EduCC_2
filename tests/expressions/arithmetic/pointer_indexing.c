// Test various pointer indexing patterns
int main() {
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Array indexing
    int *p = arr;
    if (p[0] != 0) return 1;
    if (p[5] != 5) return 2;
    if (p[9] != 9) return 3;

    // Pointer offset indexing
    int *p2 = &arr[3];
    if (p2[0] != 3) return 4;
    if (p2[2] != 5) return 5;

    // Negative indexing from middle
    int *p3 = &arr[5];
    if (p3[-1] != 4) return 6;
    if (p3[-5] != 0) return 7;

    // Mixed positive and negative
    if (p3[-2] != 3) return 8;
    if (p3[2] != 7) return 9;

    return 0;
}
