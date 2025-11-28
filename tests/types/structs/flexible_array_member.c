#include <stdio.h>
#include <stdlib.h>

struct S {
    int len;
    int data[]; // Flexible array
};

int main() {
    struct S *s = malloc(sizeof(struct S) + sizeof(int) * 3);
    s->len = 3;
    s->data[0] = 10;
    s->data[2] = 30;
    printf("%d %d\n", s->data[0], s->data[2]);
    free(s);
    return 0;
}

