#include <stdio.h>

int main() {
    int a = 100;
    printf("100 >> 1 = %d\n", a >> 1);
    printf("100 >> 2 = %d\n", a >> 2);
    
    unsigned int b = 0xFFFFFFFF;
    printf("0xFFFFFFFFu >> 4 = %X\n", b >> 4);

    int c = -4; 
    printf("-4 >> 1 = %d\n", c >> 1);

    return 0;
}

