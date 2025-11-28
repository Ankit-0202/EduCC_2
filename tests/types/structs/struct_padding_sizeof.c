#include <stdio.h>

struct S {
    char c;
    int i;
};

int main() {
    // Usually padding inserted after c to align i.
    // sizeof(S) usually 8.
    printf("%zu\n", sizeof(struct S));
    return 0;
}

