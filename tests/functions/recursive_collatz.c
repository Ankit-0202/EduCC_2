int collatz(int n) {
    if(n == 1)
        return 0;
    if(n % 2 == 0)
        return 1 + collatz(n / 2);
    else
        return 1 + collatz(n * 3 + 1);
}

int main() {
    /* For n = 6, sequence: 6 -> 3 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1 (8 steps) */
    return collatz(6) - 8;
}
