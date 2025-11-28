#include <stdio.h>

int main() {
    int a = 10;
    printf("sizeof(a) = %zu\n", sizeof(a));
    printf("sizeof(a + 5) = %zu\n", sizeof(a + 5)); // sizeof(int)
    printf("sizeof(10.5) = %zu\n", sizeof(10.5)); // sizeof(double)
    return 0;
}

