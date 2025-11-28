// Test octal literals
int main() {
    int a = 010;
    if (a != 8) return 1;

    int b = 077;
    if (b != 63) return 2;

    int c = 0100;
    if (c != 64) return 3;

    int d = 0777;
    if (d != 511) return 4;

    int e = 00;
    if (e != 0) return 5;

    int f = 012345;
    if (f != 5349) return 6;

    return 0;
}
