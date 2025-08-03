int constant_folding() {
    int a = 2 + 3 * 4;  // Should be optimized to 14
    int b = (2 + 3) * 4;  // Should be optimized to 20
    return a + b;  // 14 + 20 = 34
}

int dead_code_elimination() {
    int x = 10;
    int y = 20;
    int z = x + y;  // This should be optimized away if not used
    return x;  // Only x is used
}

int loop_optimization() {
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += i;
    }
    return sum;  // Should be optimized to 45 (0+1+2+...+9)
}

int strength_reduction() {
    int result = 0;
    for (int i = 0; i < 5; i++) {
        result += i * 2;  // Should be optimized to addition
    }
    return result;  // 0+2+4+6+8 = 20
}

int main() {
    if (constant_folding() != 34) return 1;
    if (dead_code_elimination() != 10) return 1;
    if (loop_optimization() != 45) return 1;
    if (strength_reduction() != 20) return 1;
    
    return 0;
} 