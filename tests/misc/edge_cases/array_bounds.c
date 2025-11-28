int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    
    // Test out of bounds access
    int value1 = arr[10];  // Out of bounds
    int value2 = arr[-1];  // Out of bounds
    
    // Test out of bounds assignment
    arr[10] = 100;  // Out of bounds
    arr[-1] = 200;  // Out of bounds
    
    // Test with pointer arithmetic
    int *ptr = arr;
    int value3 = ptr[10];  // Out of bounds
    int value4 = ptr[-1];  // Out of bounds
    
    // Test with different array types
    char str[10] = "Hello";
    char c = str[20];  // Out of bounds
    
    return 0;  // If we get here, out of bounds access didn't crash
} 