#include <stdio.h>

union U {
    int arr[2];
    long long l; // Assuming 64-bit long long, same as 2x 32-bit int
};

int main() {
    union U u;
    u.arr[0] = 0;
    u.arr[1] = 0;
    printf("Long: %lld\n", u.l);
    return 0;
}

