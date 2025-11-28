#include <stdio.h>

int main() {
    int arr[10];
    int *p1 = &arr[2];
    int *p2 = &arr[5];
    printf("Diff: %ld\n", p2 - p1);
    return 0;
}

