struct Flags {
    unsigned int flag1 : 1;
    unsigned int flag2 : 2;
};

int main() {
    struct Flags f;
    f.flag1 = 1;  // maximum value for 1 bit is 1
    f.flag2 = 2;  // maximum value for 2 bits is 3, but we set 2
    // Compute a value using bitfields: (flag1 * 10) + flag2 should be 12.
    return (f.flag1 * 10) + f.flag2 - 12; // Expected: 0
}
