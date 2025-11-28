typedef int (*op_fn)(int, int);

int add(int a, int b) { return a + b; }
int apply(op_fn fn, int a, int b) { return fn(a, b); }

int main(void) {
    return apply(add, 2, 3) == 5 ? 0 : 1;
}
