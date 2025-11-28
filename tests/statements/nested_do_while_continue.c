int main(void) {
    int outer = 0;
    int inner = 0;

    do {
        outer++;
        int j = 0;
        do {
            j++;
            if (j == 2) continue;
            inner++;
        } while (j < 3);
    } while (outer < 2);

    return (outer == 2 && inner == 4) ? 0 : 1;
}
