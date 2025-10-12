// Test string comparison
int main() {
    char str1[] = "Hello";
    char str2[] = "World";
    char str3[] = "Hello";
    
    int result = 0;
    
    // Simple character comparison
    if (str1[0] == str3[0]) {
        result = result + 1;
    }
    
    if (str1[0] != str2[0]) {
        result = result + 1;
    }
    
    return result;
}
