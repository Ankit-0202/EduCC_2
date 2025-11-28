int sum_variadic(int count, ...) {
    int sum = 0;
    int i;
    __builtin_va_list args;
    __builtin_va_start(args, count);
    
    for (i = 0; i < count; i++) {
        sum += __builtin_va_arg(args, int);
    }
    
    __builtin_va_end(args);
    return sum;
}

int max_variadic(int count, ...) {
    int max_val = 0;
    int i;
    __builtin_va_list args;
    __builtin_va_start(args, count);
    
    if (count > 0) {
        max_val = __builtin_va_arg(args, int);
        for (i = 1; i < count; i++) {
            int val = __builtin_va_arg(args, int);
            if (val > max_val) max_val = val;
        }
    }
    
    __builtin_va_end(args);
    return max_val;
}

int main() {
    if (sum_variadic(3, 1, 2, 3) != 6) return 1;
    if (sum_variadic(5, 10, 20, 30, 40, 50) != 150) return 1;
    
    if (max_variadic(3, 5, 2, 8) != 8) return 1;
    if (max_variadic(4, 1, 9, 3, 7) != 9) return 1;
    
    return 0;
} 