#include <stdio.h>

int main() {
    int x = 10;
    switch (x) {
        default:
            printf("Only default matched\n");
            break;
    }
    return 0;
}
