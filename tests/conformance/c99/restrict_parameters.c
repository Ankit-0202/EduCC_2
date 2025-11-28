int add_arrays(int n, int *restrict dst, const int *restrict src) {
    for (int i = 0; i < n; i++) {
        dst[i] += src[i];
    }
    return 0;
}

int main(void) {
    int a[3] = {1, 2, 3};
    int b[3] = {4, 5, 6};

    add_arrays(3, a, b);

    if (a[0] != 5) return 1;
    if (a[1] != 7) return 1;
    if (a[2] != 9) return 1;

    return 0;
}
