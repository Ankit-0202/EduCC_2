struct InnerFlags {
    unsigned int flag1 : 1;
    unsigned int flag2 : 2;
};

struct Outer {
    struct InnerFlags inner;
    int multiplier;
};

int main() {
    struct Outer o;
    o.inner.flag1 = 1;
    o.inner.flag2 = 2;
    o.multiplier = 10;
    /* (1 + 2) * 10 = 30 */
    return ((o.inner.flag1 + o.inner.flag2) * o.multiplier) - 30;
}
