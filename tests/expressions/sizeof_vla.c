int main(void) {
    int n = 7;
    int values[n];
    int size = (int)sizeof(values);
    return size == (int)(n * sizeof(int)) ? 0 : 1;
}
