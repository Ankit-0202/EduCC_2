// Test array initialization
int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int sum = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        sum = sum + arr[i];
    }
    
    return sum;
}
