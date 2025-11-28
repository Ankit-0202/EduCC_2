int main() {
    int i = 0;
    int sum = 0;
    
    // Basic do-while
    do {
        sum += i;
        i++;
    } while (i < 5);
    
    if (sum != 10) return 1;  // 0+1+2+3+4 = 10
    if (i != 5) return 1;
    
    // Do-while with break
    i = 0;
    sum = 0;
    
    do {
        if (i == 3) break;
        sum += i;
        i++;
    } while (i < 10);
    
    if (sum != 3) return 1;  // 0+1+2 = 3
    if (i != 3) return 1;
    
    // Do-while with continue
    i = 0;
    sum = 0;
    
    do {
        i++;
        if (i % 2 == 0) continue;
        sum += i;
    } while (i < 6);
    
    if (sum != 9) return 1;  // 1+3+5 = 9
    
    return 0;
} 