struct Pair {
    int a;
    int b;
};

int main() {
    struct Pair p;
    p.a = 5;
    p.b = 10;
    return p.a + p.b; // Returns 15
}