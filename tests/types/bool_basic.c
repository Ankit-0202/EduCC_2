#include <stdio.h>
#include <stdbool.h>

int main() {
    bool b = true;
    if (b) {
        printf("True\n");
    }
    b = false;
    if (!b) {
        printf("False\n");
    }
    return 0;
}

