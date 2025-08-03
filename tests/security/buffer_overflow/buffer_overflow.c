int main() {
    char buffer[10];
    char source[20] = "This is too long for buffer";
    
    // This should cause buffer overflow
    int i = 0;
    while (source[i] != '\0') {
        buffer[i] = source[i];  // Buffer overflow
        i++;
    }
    buffer[i] = '\0';
    
    // Test with different buffer sizes
    char small_buffer[5];
    char long_string[10] = "Too long";
    
    for (int j = 0; j < 10; j++) {
        small_buffer[j] = long_string[j];  // Buffer overflow
    }
    
    // Test with integer overflow leading to buffer overflow
    int size = 5;
    int index = 10;
    
    char test_buffer[5];
    test_buffer[index] = 'X';  // Out of bounds access
    
    return 0;  // If we get here, buffer overflow didn't crash
} 