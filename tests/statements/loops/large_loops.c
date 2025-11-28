int main() {
    int sum = 0;
    
    // Large loop
    for (int i = 0; i < 10000; i++) {
        sum += i;
    }
    
    if (sum != 49995000) return 1;  // Sum of 0 to 9999
    
    // Nested loops
    int product = 0;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            product += i * j;
        }
    }
    
    if (product != 24502500) return 1;  // Sum of i*j for i,j in [0,99]
    
    // Loop with complex condition
    int count = 0;
    for (int i = 0; i < 1000; i++) {
        if (i % 2 == 0 && i % 3 == 0) {
            count++;
        }
    }
    
    if (count != 167) return 1;  // Numbers divisible by both 2 and 3
    
    return 0;
} 