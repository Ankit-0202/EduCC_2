int main() {
    int a = 5, b = 10;
    int val1 = 100, val2 = 200;
    int *ptr = (a > b) ? &val1 : &val2;
    if (*ptr != 200) return 1;
    
    return 0;
} 