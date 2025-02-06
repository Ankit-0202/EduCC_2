#include "dup_prototype.h"

// Another identical prototype is fine
int do_stuff(int x, int y);

int main() {
    int x = 2, y = 8;
    int result = do_stuff(x, y);
    return result; // Expect 16
}

// The definition
int do_stuff(int a, int b) {
    return a * b;
}
