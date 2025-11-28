// Test pointer and array index equivalence
int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int *p = arr;

    // arr[i] == *(arr + i)
    if (arr[0] != *(arr + 0)) return 1;
    if (arr[1] != *(arr + 1)) return 2;
    if (arr[4] != *(arr + 4)) return 3;

    // p[i] == *(p + i)
    if (p[0] != *(p + 0)) return 4;
    if (p[2] != *(p + 2)) return 5;

    // arr[i] == p[i]
    for (int i = 0; i < 5; i++) {
        if (arr[i] != p[i]) return 6;
    }

    // i[arr] == arr[i] (commutative)
    if (0[arr] != arr[0]) return 7;
    if (3[arr] != arr[3]) return 8;

    return 0;
}
