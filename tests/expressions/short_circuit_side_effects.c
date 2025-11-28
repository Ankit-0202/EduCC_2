int main(void) {
    int x = 0;
    if (0 && ++x) return 1;
    if (x != 0) return 1;

    if (1 || ++x) {
        // short-circuit keeps x unchanged
    }
    return x == 0 ? 0 : 1;
}
