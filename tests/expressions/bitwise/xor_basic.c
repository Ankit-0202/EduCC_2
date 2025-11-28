#include <stdio.h>

int main() {
    int a = 0b1010; // 10
    int b = 0b1100; // 12
    int c = a ^ b;  // 0110 -> 6
    printf("10 ^ 12 = %d\n", c);
    
    int d = 0xFF ^ 0xFF;
    printf("0xFF ^ 0xFF = %d\n", d);

    int e = 0 ^ 123;
    printf("0 ^ 123 = %d\n", e);

    return 0;
}

