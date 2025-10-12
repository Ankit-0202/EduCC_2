// Test function pointers
int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

int main() {
    int (*func_ptr)(int, int);
    
    func_ptr = add;
    int result1 = func_ptr(5, 3);
    
    func_ptr = multiply;
    int result2 = func_ptr(5, 3);
    
    return result1 + result2;
}
