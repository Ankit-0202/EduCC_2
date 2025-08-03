int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

int subtract(int a, int b) {
    return a - b;
}

int main() {
    int (*func_ptr)(int, int);
    
    func_ptr = add;
    if (func_ptr(5, 3) != 8) return 1;
    
    func_ptr = multiply;
    if (func_ptr(4, 6) != 24) return 1;
    
    func_ptr = subtract;
    if (func_ptr(10, 4) != 6) return 1;
    
    return 0;
} 