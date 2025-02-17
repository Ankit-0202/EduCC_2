int multiply(int a, int b) {
    return a * b;
}

int main() {
    int (*func_ptr)(int, int) = multiply;
    int x = 5, y = 4;
    int result = func_ptr(x, y);
    return result;  // returns 20
}
