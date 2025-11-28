#include <stdio.h>

int main() {
    int a = 16;
    a >>= 2;
    printf("16 >>= 2 -> %d\n", a);
    
    int b = 10;
    b >>= 0;
    printf("10 >>= 0 -> %d\n", b);

    return 0;
}
