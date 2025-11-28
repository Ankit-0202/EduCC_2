// Test pointer subtraction
int main() {
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int *p1 = &arr[0];
    int *p2 = &arr[5];

    // Distance between pointers
    int diff = p2 - p1;
    if (diff != 5) return 1;

    // Reverse subtraction
    diff = p1 - p2;
    if (diff != -5) return 2;

    // Adjacent elements
    int *p3 = &arr[3];
    int *p4 = &arr[4];
    diff = p4 - p3;
    if (diff != 1) return 3;

    // Same pointer
    diff = p1 - p1;
    if (diff != 0) return 4;

    // Use difference for indexing
    int *start = &arr[2];
    int *end = &arr[7];
    int distance = end - start;
    if (distance != 5) return 5;

    return 0;
}
