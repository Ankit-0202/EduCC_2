// Test pointer aliasing scenarios
int main() {
    int value = 10;
    int *p1 = &value;
    int *p2 = &value;

    // Both pointers point to same location
    if (p1 != p2) return 1;

    // Modify through p1
    *p1 = 20;
    if (*p2 != 20) return 2;

    // Modify through p2
    *p2 = 30;
    if (*p1 != 30) return 3;
    if (value != 30) return 4;

    // Array aliasing
    int arr[5] = {1, 2, 3, 4, 5};
    int *pa = arr;
    int *pb = &arr[0];

    if (pa != pb) return 5;
    if (*pa != *pb) return 6;

    *pa = 100;
    if (arr[0] != 100) return 7;
    if (*pb != 100) return 8;

    return 0;
}
