#include <stddef.h>

int main(void) {
    int data[5] = {0, 1, 2, 3, 4};
    int *p = &data[1];
    int *q = &data[4];
    ptrdiff_t diff = q - p;
    return diff == 3 ? 0 : 1;
}
