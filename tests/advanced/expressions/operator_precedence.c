// Test operator precedence
int main() {
    int a = 2;
    int b = 3;
    int c = 4;
    
    int result = a + b * c - (a + b) / c + a % b;
    result = result + (a > b ? a : b) * c;
    result = result + (a && b || c) ? 1 : 0;
    
    return result;
}
