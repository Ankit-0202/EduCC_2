int main() {
    // Basic types
    if (sizeof(char) != 1) return 1;
    if (sizeof(int) != 4) return 1;  // Assuming 32-bit int
    if (sizeof(float) != 4) return 1;
    if (sizeof(double) != 8) return 1;
    
    // Variables
    int x = 10;
    char c = 'A';
    float f = 3.14;
    
    if (sizeof(x) != 4) return 1;
    if (sizeof(c) != 1) return 1;
    if (sizeof(f) != 4) return 1;
    
    // Arrays
    int arr[5];
    char str[10];
    
    if (sizeof(arr) != 20) return 1;  // 5 * 4
    if (sizeof(str) != 10) return 1;
    
    // Pointers
    int *ptr = &x;
    char *cptr = &c;
    
    if (sizeof(ptr) != 8) return 1;   // Assuming 64-bit pointers
    if (sizeof(cptr) != 8) return 1;
    
    // Structs
    struct {
        int a;
        char b;
        float c;
    } s;
    
    if (sizeof(s) < 8) return 1;  // At least 8 bytes (with padding)
    
    return 0;
} 