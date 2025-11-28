#include <stdio.h>

int main() {
    // & lower than ==
    int a = 1 & 0 == 0; // 1 & (0==0) -> 1 & 1 -> 1
    printf("1 & 0 == 0 -> %d\n", a);

    // | lower than ^
    int b = 1 | 2 ^ 3; // 1 | (2^3) -> 1 | 1 -> 1
    printf("1 | 2 ^ 3 -> %d\n", b);
    
    // ^ lower than &
    int c = 1 ^ 3 & 2; // 1 ^ (3 & 2) -> 1 ^ 2 -> 3
    printf("1 ^ 3 & 2 -> %d\n", c);

    return 0;
}

