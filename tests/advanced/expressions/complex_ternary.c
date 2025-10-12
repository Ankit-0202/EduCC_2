// Test complex ternary expressions
int main() {
    int a = 10;
    int b = 5;
    int c = 3;
    
    int result = (a > b) ? 
        ((b > c) ? a + b : a + c) : 
        ((a > c) ? b + a : b + c);
    
    return result;
}
