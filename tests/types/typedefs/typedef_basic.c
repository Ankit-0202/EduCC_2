typedef int Integer;
typedef char Character;
typedef float Real;

int main() {
    Integer x = 10;
    Character c = 'F';
    Real f = 3.5;
    
    if (x != 10) return 1;
    if (c != 'F') return 1;
    if (f < 3.4 || f > 3.6) return 1;
    
    Integer sum = 0;
    for (Integer i = 0; i < 4; i++) {
        sum += i;
    }
    
    if (sum != 6) return 1;  // 0+1+2+3 = 6
    
    return 0;
} 