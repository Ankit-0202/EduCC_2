// Test modulo assignment operator %=
int main() {
    int a = 10;
    a %= 3;
    if (a != 1) return 1;

    int b = 17;
    b %= 5;
    if (b != 2) return 2;

    int c = 100;
    c %= 7;
    if (c != 2) return 3;

    int d = 15;
    d %= 15;
    if (d != 0) return 4;

    int e = 123;
    e %= 10;
    if (e != 3) return 5;

    return 0;
}
