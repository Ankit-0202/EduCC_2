#include <stdio.h>

struct S {
    int x;
};

struct S make_s(int v) {
    struct S s;
    s.x = v;
    return s;
}

int main() {
    struct S s = make_s(42);
    printf("%d\n", s.x);
    return 0;
}

