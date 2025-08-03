int main() {
    int result = 0;
    
    // Multiplication by power of 2 should be optimized to shift
    for (int i = 0; i < 10; i++) {
        result += i * 2;  // Should be optimized to i << 1
    }
    
    if (result != 90) return 1;  // 0+2+4+6+8+10+12+14+16+18 = 90
    
    // Division by power of 2 should be optimized to shift
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += i / 2;  // Should be optimized to i >> 1
    }
    
    if (sum != 20) return 1;  // 0+0+1+1+2+2+3+3+4+4 = 20
    
    return 0;
} 