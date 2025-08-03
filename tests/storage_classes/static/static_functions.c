static int internal_add(int a, int b) {
    return a + b;
}

static int internal_multiply(int a, int b) {
    return a * b;
}

int public_function(int x) {
    return internal_add(x, 5) + internal_multiply(x, 2);
}

int main() {
    if (public_function(3) != 14) return 1;  // (3+5) + (3*2) = 8 + 6 = 14
    if (public_function(5) != 20) return 1;  // (5+5) + (5*2) = 10 + 10 = 20
    
    return 0;
} 