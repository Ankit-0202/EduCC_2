#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    printf("%d\n", MIN(10, 20));
    printf("%d\n", MIN(30, 5));
    return 0;
}

