int main() {
    int sum = 0;
    
    // Break in for loop
    for (int i = 0; i < 10; i++) {
        if (i == 5) break;
        sum += i;
    }
    
    if (sum != 10) return 1;  // 0+1+2+3+4 = 10
    
    // Continue in for loop
    sum = 0;
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) continue;
        sum += i;
    }
    
    if (sum != 25) return 1;  // 1+3+5+7+9 = 25
    
    // Break in while loop
    int i = 0;
    sum = 0;
    while (i < 10) {
        if (i == 7) break;
        sum += i;
        i++;
    }
    
    if (sum != 21) return 1;  // 0+1+2+3+4+5+6 = 21
    
    // Continue in while loop
    i = 0;
    sum = 0;
    while (i < 10) {
        i++;
        if (i % 3 == 0) continue;
        sum += i;
    }
    
    if (sum != 37) return 1;  // 1+2+4+5+7+8+10 = 37
    
    return 0;
} 