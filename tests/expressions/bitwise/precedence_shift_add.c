#include <stdio.h>

int main() {
    // << lower than +
    int a = 1 << 2 + 1; // 1 << (2+1) -> 1 << 3 -> 8
    printf("1 << 2 + 1 -> %d\n", a);

    // >> lower than -
    int b = 16 >> 5 - 3; // 16 >> (5-3) -> 16 >> 2 -> 4
    printf("16 >> 5 - 3 -> %d\n", b);

    return 0;
}

