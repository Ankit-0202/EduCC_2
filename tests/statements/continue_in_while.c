#include <stdio.h>

int main() {
    int i = 0;
    while (i < 5) {
        i++;
        if (i == 3) continue;
        printf("i = %d\n", i);
    }
    return 0;
}
