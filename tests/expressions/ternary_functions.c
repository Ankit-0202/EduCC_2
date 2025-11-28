int func1() { return 10; }
int func2() { return 20; }

int main() {
    int a = 5;
    int func_result = (a > 3) ? func1() : func2();
    if (func_result != 10) return 1;
    
    return 0;
} 