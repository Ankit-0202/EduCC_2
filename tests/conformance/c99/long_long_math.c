int main(void) {
    long long big = 1LL << 40;
    long long value = big / 3;
    long long recombined = value * 3 + (big % 3);

    return recombined == big ? 0 : 1;
}
