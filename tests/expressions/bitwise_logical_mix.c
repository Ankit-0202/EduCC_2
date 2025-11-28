// Test mixing bitwise and logical operators
int main() {
    // Bitwise AND vs logical AND
    int a = 5 & 3;
    int b = 5 && 3;
    if (a != 1) return 1;
    if (b != 1) return 2;

    // Bitwise OR vs logical OR
    int c = 4 | 2;
    int d = 4 || 2;
    if (c != 6) return 3;
    if (d != 1) return 4;

    // Complex expression
    int e = (5 & 3) && (2 | 1);
    if (e != 1) return 5;

    // Precedence: & has lower precedence than ==
    int f = 5 & 4 == 4;
    if (f != 0) return 6;  // 5 & (4 == 4) = 5 & 1 = 1

    // Logical short-circuit
    int g = 0;
    int h = 0 && (g = 1);
    if (g != 0) return 7;  // g should not be modified

    return 0;
}
