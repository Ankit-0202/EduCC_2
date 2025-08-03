int main() {
    int a = 5, b = 10;
    
    // Basic ternary
    int max = (a > b) ? a : b;
    if (max != 10) return 1;
    
    // Nested ternary
    int x = 15;
    int result = (x > 10) ? ((x > 20) ? 30 : 20) : 10;
    if (result != 20) return 1;
    
    // Ternary with different types
    int y = 7;
    char c = (y > 5) ? 'A' : 'B';
    if (c != 'A') return 1;
    
    // Ternary with expressions
    int z = 3;
    int sum = (z > 0) ? (z + 5) : (z - 5);
    if (sum != 8) return 1;
    
    // Ternary with function calls
    int func1() { return 10; }
    int func2() { return 20; }
    
    int func_result = (a > 3) ? func1() : func2();
    if (func_result != 10) return 1;
    
    // Ternary with pointers
    int val1 = 100, val2 = 200;
    int *ptr = (a > b) ? &val1 : &val2;
    if (*ptr != 200) return 1;
    
    return 0;
} 