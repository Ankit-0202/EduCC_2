// Test pointer arrays
int main() {
    int arr[3] = {10, 20, 30};
    int *ptr_arr[3];
    
    for (int i = 0; i < 3; i = i + 1) {
        ptr_arr[i] = &arr[i];
    }
    
    int sum = 0;
    for (int i = 0; i < 3; i = i + 1) {
        sum = sum + *ptr_arr[i];
    }
    
    return sum;
}
