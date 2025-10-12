// Test memory intensive operations
int main() {
    int arr[1000];
    int sum = 0;
    
    // Initialize array
    for (int i = 0; i < 1000; i = i + 1) {
        arr[i] = i;
    }
    
    // Process array
    for (int i = 0; i < 1000; i = i + 1) {
        sum = sum + arr[i];
    }
    
    return sum % 1000;  // Return modulo to keep result small
}