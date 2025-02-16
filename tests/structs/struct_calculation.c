struct Inner {
    int a;
    int b;
};

struct Outer {
    struct Inner in;
    int c;
};

int main() {
    struct Outer o;
    o.in.a = 2;
    o.in.b = 3;
    o.c = 4;
    // Calculate: (a + b) * c = (2 + 3) * 4 = 20.
    return (o.in.a + o.in.b) * o.c - 20; // Expected: 0
}
