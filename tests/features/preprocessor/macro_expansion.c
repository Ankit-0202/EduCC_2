// Test macro expansion
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SQUARE(x) ((x) * (x))
#define ADD(a, b) ((a) + (b))

int main() {
    int a = 5;
    int b = 3;
    
    int max_val = MAX(a, b);
    int square_val = SQUARE(a);
    int sum_val = ADD(a, b);
    
    return max_val + square_val + sum_val;
}
