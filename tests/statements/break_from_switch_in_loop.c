int main(void) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        switch (i) {
            case 2:
                break;
            case 3:
                sum += 3;
                break;
            default:
                sum += 1;
        }
        if (i == 3) break;
    }
    return sum == 5 ? 0 : 1;
}
