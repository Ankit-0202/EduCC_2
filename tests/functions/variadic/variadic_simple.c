#include <stdio.h>
#include <stdarg.h>

void print_nums(int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        printf("%d ", va_arg(args, int));
    }
    va_end(args);
    printf("\n");
}

int main() {
    print_nums(3, 10, 20, 30);
    return 0;
}

