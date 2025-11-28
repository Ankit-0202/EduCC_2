#include <stdio.h>

int main() {
    int i = 0;
    for (i = 0; ; i++) {
        if (i >= 3) break;
        printf("i = %d\n", i);
    }
    return 0;
}
