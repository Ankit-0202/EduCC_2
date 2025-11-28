int main(void) {
    int n = 5;
    int values[n];

    for (int i = 0; i < n; i++) {
        values[i] = i + 1;
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += values[i];
    }

    return sum == 15 ? 0 : 1;
}
