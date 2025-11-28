int main(void) {
    int i = 0;
    int sum = 0;
    while (i < 5) {
        i++;
        if (i == 3) continue;
        sum += i;
    }
    return sum == 12 ? 0 : 1;
}
