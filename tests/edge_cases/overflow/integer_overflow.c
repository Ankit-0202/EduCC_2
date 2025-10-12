// Test integer overflow behavior
int main() {
    int max_int = 2147483647;  // 2^31 - 1
    int result = max_int + 1;   // Should overflow
    
    return result;
}