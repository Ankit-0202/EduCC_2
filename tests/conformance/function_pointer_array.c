int inc(int x) { return x + 1; }
int dec(int x) { return x - 1; }

int apply_all(int (*ops[])(int), int count) {
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += ops[i](i);
    }
    return total;
}

int main(void) {
    int (*ops[2])(int) = {inc, dec};
    return apply_all(ops, 2) == 1 ? 0 : 1;
}
