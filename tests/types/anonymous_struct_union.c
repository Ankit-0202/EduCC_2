struct wrapper {
    union {
        int i;
        double d;
    };
    int tag;
};

int main(void) {
    struct wrapper w = {.i = 7, .tag = 1};
    if (w.i != 7 || w.tag != 1) return 1;
    w.d = 4.0;
    return (int)w.d == 4 ? 0 : 1;
}
