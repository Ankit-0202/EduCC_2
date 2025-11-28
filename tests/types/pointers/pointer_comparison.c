#include <stdio.h>

int main() {
    int arr[10];
    int *p1 = &arr[2];
    int *p2 = &arr[5];
    if (p1 < p2) printf("p1 < p2\n");
    if (p2 > p1) printf("p2 > p1\n");
    return 0;
}

