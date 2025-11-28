#include <stdio.h>

int main() {
    unsigned int a = 10;
    unsigned int b = 20;
    unsigned int c = a - b; // Should be large positive
    printf("10u - 20u = %u\n", c);
    return 0;
}

