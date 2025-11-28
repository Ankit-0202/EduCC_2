// Test bitwise OR assignment operator |=
int main() {
    int a = 0x0F;
    a |= 0xF0;
    if (a != 0xFF) return 1;

    int b = 0b00001111;
    b |= 0b11110000;
    if (b != 0b11111111) return 2;

    int c = 0;
    c |= 42;
    if (c != 42) return 3;

    int d = 0xAAAA;
    d |= 0x5555;
    if (d != 0xFFFF) return 4;

    int e = 255;
    e |= 0;
    if (e != 255) return 5;

    return 0;
}
