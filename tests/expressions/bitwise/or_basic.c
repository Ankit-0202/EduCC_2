#include <stdio.h>

int main() {
    int a = 0b1010; // 10
    int b = 0b1100; // 12
    int c = a | b;  // 1110 -> 14
    printf("10 | 12 = %d\n", c);
    
    int d = 0xF0 | 0x0F;
    printf("0xF0 | 0x0F = %d\n", d);

    int e = 0 | 0;
    printf("0 | 0 = %d\n", e);

    return 0;
}

