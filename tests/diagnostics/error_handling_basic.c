int divide_safe(int a, int b, int* result) {
    if (b == 0) {
        return 0;  // error
    }
    *result = a / b;
    return 1;  // success
}

int array_access_safe(int arr[], int size, int index, int* result) {
    if (index < 0 || index >= size) {
        return 0;  // error
    }
    *result = arr[index];
    return 1;  // success
}

int main() {
    int result;
    
    // Test successful division
    if (!divide_safe(10, 2, &result)) return 1;
    if (result != 5) return 1;
    
    // Test division by zero
    if (divide_safe(10, 0, &result)) return 1;
    
    int arr[5] = {1, 2, 3, 4, 5};
    
    // Test successful array access
    if (!array_access_safe(arr, 5, 2, &result)) return 1;
    if (result != 3) return 1;
    
    // Test out of bounds access
    if (array_access_safe(arr, 5, 10, &result)) return 1;
    if (array_access_safe(arr, 5, -1, &result)) return 1;
    
    return 0;
} 