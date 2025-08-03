int main() {
    int x = 10;
    int y = 0;
    
    // This should cause undefined behavior, but we test that it doesn't crash
    int result = x / y;  // Undefined behavior
    
    // Test modulo with zero
    int mod_result = x % y;  // Undefined behavior
    
    // Test floating point division by zero
    float f1 = 10.0;
    float f2 = 0.0;
    float f_result = f1 / f2;  // Should produce infinity or NaN
    
    return 0;  // If we get here, the program didn't crash
} 