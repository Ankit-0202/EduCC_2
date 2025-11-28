#include <stdio.h>

int main() {
    short a = 32767;
    short b = 1;
    // result of a+b is promoted to int usually, then we print it.
    printf("32767 + 1 = %d\n", a + b);
    
    short c = -32768;
    printf("Min short: %d\n", c);
    return 0;
}

