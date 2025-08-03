int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

int main() {
    int (*operations[4])(int, int) = {add, subtract, multiply, divide};
    
    if (operations[0](10, 5) != 15) return 1;  // add
    if (operations[1](10, 5) != 5) return 1;   // subtract
    if (operations[2](10, 5) != 50) return 1;  // multiply
    if (operations[3](10, 5) != 2) return 1;   // divide
    
    // Test with different values
    if (operations[0](20, 10) != 30) return 1;
    if (operations[1](20, 10) != 10) return 1;
    if (operations[2](20, 10) != 200) return 1;
    if (operations[3](20, 10) != 2) return 1;
    
    return 0;
} 