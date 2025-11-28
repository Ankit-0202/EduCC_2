#include <stdio.h>

int main() {
    int x = 10;
    {
        int y = 20;
        printf("%d %d\n", x, y);
    }
    // y is not visible here
    return 0;
}
