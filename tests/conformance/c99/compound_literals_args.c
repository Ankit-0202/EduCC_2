int sum(const int *values, int len) {
    int total = 0;
    for (int i = 0; i < len; i++) {
        total += values[i];
    }
    return total;
}

int main(void) {
    int total = sum((int[]){2, 4, 6, 8}, 4);
    total += sum((int[]){1, -1, 1, -1, 2}, 5);
    return total == 12 ? 0 : 1;
}
