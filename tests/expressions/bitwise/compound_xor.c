#include <stdio.h>

int main() {
    int a = 0xFF;
    a ^= 0x0F; // 1111 0000 = F0
    printf("0xFF ^= 0x0F -> %d\n", a);
    
    int b = 10;
    b ^= 10;
    printf("10 ^= 10 -> %d\n", b);

    return 0;
}

