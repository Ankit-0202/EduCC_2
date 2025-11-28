int sum_vla(int n, int data[n]) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += data[i];
    }
    return total;
}

int main(void) {
    int data[] = {1, 2, 3, 4};
    return sum_vla(4, data) == 10 ? 0 : 1;
}
