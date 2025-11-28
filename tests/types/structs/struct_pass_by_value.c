#include <stdio.h>

struct S {
    int x;
};

void print_s(struct S s) {
    printf("%d\n", s.x);
}

int main() {
    struct S s = {100};
    print_s(s);
    return 0;
}

