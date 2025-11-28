#include <stdio.h>

#define CONCAT(x, y) x ## y

int main() {
    int xy = 100;
    printf("%d\n", CONCAT(x, y));
    return 0;
}

