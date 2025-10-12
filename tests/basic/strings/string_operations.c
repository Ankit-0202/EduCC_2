// Test string operations
int main() {
    char str[] = "Hello";
    int len = 0;
    
    // Calculate length
    while (str[len] != '\0') {
        len = len + 1;
    }
    
    return len;
}
