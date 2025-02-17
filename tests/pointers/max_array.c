int main() {
    int arr[] = {3, 7, 2, 9, 5};
    int *ptr = arr;
    int max = *ptr;
    int i;
    for (i = 1; i < 5; i++) {
        if (*(ptr + i) > max)
            max = *(ptr + i);
    }
    return max;  // returns 9
}
