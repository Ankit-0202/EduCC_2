#include <stdio.h>

int x = 10;

int main() {
    int x = 20;
    printf("%d\n", x);
    {
        extern int x; // Should refer to global? Or shadow? Extern usually refers to global.
        // Actually, let's just test scope.
    }
    return 0;
}
