int main() {
    int arr[2][3] = { {1, 2, 3}, {4, 5, 6} };
    int sum = 0;
    int *ptr = &arr[0][0];
    int i;
    for (i = 0; i < 6; i++) {
        sum += *(ptr + i);
    }
    return sum;  // returns 21
}
