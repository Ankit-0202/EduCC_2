int add_int(int a, int b) {
    return a + b;
}

float add_float(float a, float b) {
    return a + b;
}

int add_three_int(int a, int b, int c) {
    return a + b + c;
}

float add_three_float(float a, float b, float c) {
    return a + b + c;
}

int main() {
    int result1 = add_int(5, 3);
    if (result1 != 8) return 1;
    
    float result2 = add_float(3.5, 2.5);
    if (result2 < 5.9 || result2 > 6.1) return 1;
    
    int result3 = add_three_int(1, 2, 3);
    if (result3 != 6) return 1;
    
    float result4 = add_three_float(1.5, 2.5, 3.5);
    if (result4 < 7.4 || result4 > 7.6) return 1;
    
    return 0;
} 