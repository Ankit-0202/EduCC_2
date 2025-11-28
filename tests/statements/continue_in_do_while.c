#include <stdio.h>

int main() {
    int i = 0;
    do {
        i++;
        if (i == 3) continue;
        printf("i = %d\n", i);
    } while (i < 5);
    return 0;
}

