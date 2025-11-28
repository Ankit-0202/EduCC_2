// Test implicit type conversions
int main() {
    // char to int
    char c = 65;
    int i = c;
    if (i != 65) return 1;

    // int to float
    int x = 10;
    float f = x;
    if (f < 9.9 || f > 10.1) return 2;

    // float to int (truncation)
    float f2 = 3.7;
    int i2 = f2;
    if (i2 != 3) return 3;

    // short to int
    short s = 32000;
    int i3 = s;
    if (i3 != 32000) return 4;

    // int to double
    int i4 = 100;
    double d = i4;
    if (d < 99.9 || d > 100.1) return 5;

    // unsigned to signed
    unsigned int u = 42;
    int i5 = u;
    if (i5 != 42) return 6;

    return 0;
}
