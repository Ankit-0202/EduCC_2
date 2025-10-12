// Test complex expression evaluation
int main() {
    int a = 10;
    int b = 5;
    int c = 3;
    
    int result = (a + b) * c - (a / b) + (b % c);
    result = result + (a > b ? a : b);
    result = result + (a == 10 ? 1 : 0);
    result = result + (b != 5 ? 0 : 1);
    
    return result;
}
