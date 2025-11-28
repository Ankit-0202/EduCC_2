#include <stdio.h>

int main() {
#line 100
    printf("Line: %d\n", __LINE__); // Should be 100 or 101 depending on when it's evaluated
    return 0;
}
