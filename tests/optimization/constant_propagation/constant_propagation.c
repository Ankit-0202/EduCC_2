int main() {
    const int a = 5;
    const int b = 10;
    const int c = a + b;  // Should be optimized to 15
    
    int result = c * 2;  // Should be optimized to 30
    
    if (result != 30) return 1;
    
    // Test with more complex expressions
    const int x = 3;
    const int y = 4;
    const int z = x * y + 2;  // Should be optimized to 14
    
    int final_result = z * 3;  // Should be optimized to 42
    
    if (final_result != 42) return 1;
    
    // Test with conditional constant propagation
    const int flag = 1;
    int conditional_result;
    
    if (flag) {
        conditional_result = 100;
    } else {
        conditional_result = 200;
    }
    
    if (conditional_result != 100) return 1;
    
    return 0;
} 