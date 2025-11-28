// Test automatic type promotion in expressions
int main() {
    // char promoted to int in arithmetic
    char a = 10;
    char b = 20;
    int result = a + b;
    if (result != 30) return 1;

    // short promoted to int
    short s1 = 100;
    short s2 = 200;
    int r2 = s1 * s2;
    if (r2 != 20000) return 2;

    // int promoted to float
    int i1 = 10;
    float f1 = 3.5;
    float r3 = i1 + f1;
    if (r3 < 13.4 || r3 > 13.6) return 3;

    // float promoted to double
    float f2 = 2.5;
    double d1 = 3.5;
    double r4 = f2 + d1;
    if (r4 < 5.9 || r4 > 6.1) return 4;

    // unsigned int and int
    unsigned int u = 10;
    int i2 = 20;
    unsigned int r5 = u + i2;
    if (r5 != 30) return 5;

    return 0;
}
