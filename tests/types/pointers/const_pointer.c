#include <stdio.h>

int main() {
    int a = 10;
    int b = 20;
    int * const p = &a;
    *p = 15; // OK
    printf("%d\n", *p);
    // p = &b; // Error if checked
    return 0;
}
