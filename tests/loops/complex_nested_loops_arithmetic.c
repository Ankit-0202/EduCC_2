int main() {
    int sum = 0;
    int i = 1;
    while (i <= 3) {
        int j = 1;
        while (j <= 3) {
            int k = 1;
            while (k <= 3) {
                sum = sum + i * j * k;
                k = k + 1;
            }
            j = j + 1;
        }
        i = i + 1;
    }
    /* (1+2+3)^3 = 6^3 = 216 */
    return sum - 216;
}
