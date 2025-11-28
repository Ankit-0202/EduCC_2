int nested_loops(int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += i * j;
        }
    }
    return sum;
}

int matrix_multiply(int a[3][3], int b[3][3], int result[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return 0;
}

int bubble_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return 0;
}

int main() {
    if (nested_loops(3) != 18) return 1;  // Sum of i*j for i,j in [0,2]
    
    int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int b[3][3] = {{9,8,7},{6,5,4},{3,2,1}};
    int result[3][3];
    
    matrix_multiply(a, b, result);
    
    if (result[0][0] != 30) return 1;
    if (result[0][1] != 24) return 1;
    if (result[0][2] != 18) return 1;
    
    int arr[5] = {5, 2, 4, 1, 3};
    bubble_sort(arr, 5);
    
    if (arr[0] != 1) return 1;
    if (arr[1] != 2) return 1;
    if (arr[2] != 3) return 1;
    if (arr[3] != 4) return 1;
    if (arr[4] != 5) return 1;
    
    return 0;
} 