int safe_array_access(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        return -1;  // error
    }
    return arr[index];
}

int safe_string_copy(char dest[], int dest_size, const char src[]) {
    int i = 0;
    while (i < dest_size - 1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return i;
}

int validate_input(int value, int min, int max) {
    if (value < min || value > max) {
        return 0;  // invalid
    }
    return 1;  // valid
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    
    // Test valid access
    if (safe_array_access(arr, 5, 2) != 3) return 1;
    
    // Test out of bounds access
    if (safe_array_access(arr, 5, 10) != -1) return 1;
    if (safe_array_access(arr, 5, -1) != -1) return 1;
    
    // Test string copy
    char dest[10];
    int copied = safe_string_copy(dest, 10, "Hello");
    if (copied != 5) return 1;
    if (dest[0] != 'H') return 1;
    if (dest[4] != 'o') return 1;
    if (dest[5] != '\0') return 1;
    
    // Test input validation
    if (!validate_input(5, 1, 10)) return 1;
    if (validate_input(0, 1, 10)) return 1;
    if (validate_input(15, 1, 10)) return 1;
    
    return 0;
} 