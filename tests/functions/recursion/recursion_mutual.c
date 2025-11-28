int is_even(int n);
int is_odd(int n);

int is_even(int n) {
    if (n == 0) return 1;
    if (n == 1) return 0;
    return is_odd(n - 1);
}

int is_odd(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return is_even(n - 1);
}

int main() {
    if (!is_even(0)) return 1;
    if (is_even(1)) return 1;
    if (!is_even(2)) return 1;
    if (is_even(3)) return 1;
    if (!is_even(4)) return 1;
    
    if (is_odd(0)) return 1;
    if (!is_odd(1)) return 1;
    if (is_odd(2)) return 1;
    if (!is_odd(3)) return 1;
    if (is_odd(4)) return 1;
    
    return 0;
} 