// Test ternary operator
int main() {
    int a = 10;
    int b = 5;
    
    int max = (a > b) ? a : b;
    int min = (a < b) ? a : b;
    int abs_diff = (a > b) ? (a - b) : (b - a);
    
    return max + min + abs_diff;
}
