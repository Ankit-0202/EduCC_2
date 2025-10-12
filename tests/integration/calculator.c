// Comprehensive calculator test
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

int main() {
    int a = 20;
    int b = 4;
    
    int sum = add(a, b);
    int diff = subtract(a, b);
    int prod = multiply(a, b);
    int quot = divide(a, b);
    
    return sum + diff + prod + quot;
}
