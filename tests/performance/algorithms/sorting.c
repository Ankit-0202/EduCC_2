int main() {
    int arr[5] = {5, 2, 4, 1, 3};
    
    // Bubble sort
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    if (arr[0] != 1) return 1;
    if (arr[1] != 2) return 1;
    if (arr[2] != 3) return 1;
    if (arr[3] != 4) return 1;
    if (arr[4] != 5) return 1;
    
    return 0;
} 