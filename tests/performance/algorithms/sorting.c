// Test sorting algorithm
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i = i + 1) {
        for (int j = 0; j < n - i - 1; j = j + 1) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[5] = {5, 2, 8, 1, 9};
    bubble_sort(arr, 5);
    
    return arr[0] + arr[4];  // First and last elements
}