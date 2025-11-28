// Test partial array initialization
int main() {
    // Partial init - rest should be zero
    int arr1[5] = {1, 2};
    if (arr1[0] != 1) return 1;
    if (arr1[1] != 2) return 2;
    if (arr1[2] != 0) return 3;
    if (arr1[3] != 0) return 4;
    if (arr1[4] != 0) return 5;

    // Single element init
    int arr2[10] = {42};
    if (arr2[0] != 42) return 6;
    if (arr2[1] != 0) return 7;
    if (arr2[9] != 0) return 8;

    // Empty init - all zeros
    int arr3[5] = {0};
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += arr3[i];
    }
    if (sum != 0) return 9;

    // Partial with gap
    int arr4[7] = {1, 2, 3};
    if (arr4[2] != 3) return 10;
    if (arr4[6] != 0) return 11;

    return 0;
}
