#include <stdio.h>

struct S {
    unsigned int a : 2; // max 3
};

int main() {
    struct S s;
    s.a = 5; // Overflow 2 bits -> 101 -> 01 -> 1
    printf("%u\n", s.a);
    return 0;
}

