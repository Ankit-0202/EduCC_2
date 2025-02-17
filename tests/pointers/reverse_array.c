int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int *start = arr;
    int *end = arr + 4;
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
    // Return the first element of the reversed array (should be 5)
    return arr[0];
}
