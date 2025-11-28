#include <stdio.h>

void hello() {
    printf("Hello\n");
}

int main() {
    void (*f)() = hello;
    f();
    return 0;
}

