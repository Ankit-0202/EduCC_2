// Test bitwise operators
int main() {
    int a = 12;  // 1100 in binary
    int b = 10;  // 1010 in binary
    
    int and = a & b;   // 1000 = 8
    int or = a | b;    // 1110 = 14
    int xor = a ^ b;   // 0110 = 6
    int left_shift = a << 1;  // 24
    int right_shift = a >> 1; // 6
    
    return and + or + xor + left_shift + right_shift;
}
