#include <stdio.h>

int main() {
    int x = 1;
    switch (x) {
        case 1:
            printf("One\n");
            // fallthrough
        case 2:
            printf("Two\n");
            break;
        case 3:
            printf("Three\n");
    }
    return 0;
}
