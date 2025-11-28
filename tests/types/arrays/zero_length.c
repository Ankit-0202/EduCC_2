// Test zero-initialized arrays
int main() {
    // All zeros
    int arr1[10] = {0};
    for (int i = 0; i < 10; i++) {
        if (arr1[i] != 0) return 1;
    }

    // Implicit zeros
    int arr2[5] = {1};
    if (arr2[0] != 1) return 2;
    for (int i = 1; i < 5; i++) {
        if (arr2[i] != 0) return 3;
    }

    // Float array zeros
    float farr[5] = {0.0f};
    for (int i = 0; i < 5; i++) {
        if (farr[i] != 0.0f) return 4;
    }

    // Char array zeros
    char carr[8] = {0};
    for (int i = 0; i < 8; i++) {
        if (carr[i] != 0) return 5;
    }

    return 0;
}
