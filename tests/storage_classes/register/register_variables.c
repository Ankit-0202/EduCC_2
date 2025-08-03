int main() {
    register int x = 10;
    register char c = 'C';
    register float f = 1.5;
    
    if (x != 10) return 1;
    if (c != 'C') return 1;
    if (f < 1.4 || f > 1.6) return 1;
    
    x = 25;
    if (x != 25) return 1;
    
    register int sum = 0;
    for (register int i = 0; i < 5; i++) {
        sum += i;
    }
    
    if (sum != 10) return 1;  // 0+1+2+3+4 = 10
    
    return 0;
} 