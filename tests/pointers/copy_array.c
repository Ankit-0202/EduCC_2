int main() {
    int src[] = {10, 20, 30, 40, 50};
    int dest[5];
    int *pSrc = src;
    int *pDest = dest;
    int i;
    for (i = 0; i < 5; i++) {
        *(pDest + i) = *(pSrc + i);
    }
    // Calculate sum of the copied array elements
    int sum = 0;
    for (i = 0; i < 5; i++) {
        sum += *(pDest + i);
    }
    return sum;  // returns 150
}
