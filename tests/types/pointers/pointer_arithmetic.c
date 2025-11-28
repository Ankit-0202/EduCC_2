int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;
    
    // Basic pointer arithmetic
    if (*ptr != 10) return 1;
    if (*(ptr + 1) != 20) return 1;
    if (*(ptr + 2) != 30) return 1;
    if (*(ptr + 3) != 40) return 1;
    if (*(ptr + 4) != 50) return 1;
    
    // Pointer increment/decrement
    ptr++;
    if (*ptr != 20) return 1;
    ptr++;
    if (*ptr != 30) return 1;
    ptr--;
    if (*ptr != 20) return 1;
    
    // Pointer comparison
    int *ptr2 = arr + 3;
    if (ptr >= ptr2) return 1;
    if (ptr2 <= ptr) return 1;
    
    // Pointer subtraction
    int diff = ptr2 - ptr;
    if (diff != 3) return 1;
    
    return 0;
} 