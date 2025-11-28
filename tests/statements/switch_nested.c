#include <stdio.h>

int main() {
    int x = 1;
    int y = 2;
    switch (x) {
        case 1:
            switch (y) {
                case 2:
                    printf("Nested match\n");
                    break;
                default:
                    printf("Nested default\n");
            }
            break;
        default:
            printf("Outer default\n");
    }
    return 0;
}
