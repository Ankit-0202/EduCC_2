// Test array of function pointers
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

int main() {
    // Array of function pointers
    int (*ops[4])(int, int) = {add, sub, mul, divide};

    // Call add
    int r1 = ops[0](10, 5);
    if (r1 != 15) return 1;

    // Call sub
    int r2 = ops[1](10, 5);
    if (r2 != 5) return 2;

    // Call mul
    int r3 = ops[2](10, 5);
    if (r3 != 50) return 3;

    // Call divide
    int r4 = ops[3](10, 5);
    if (r4 != 2) return 4;

    // Loop through operations
    int results[4];
    for (int i = 0; i < 4; i++) {
        results[i] = ops[i](20, 4);
    }

    if (results[0] != 24) return 5;  // add
    if (results[1] != 16) return 6;  // sub
    if (results[2] != 80) return 7;  // mul
    if (results[3] != 5) return 8;   // divide

    return 0;
}
