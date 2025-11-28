#include <stdio.h>

#define A 1
#define A 1 // Redefinition with same token sequence is allowed

int main() {
    printf("%d\n", A);
    return 0;
}

