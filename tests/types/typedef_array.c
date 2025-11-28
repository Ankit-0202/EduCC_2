typedef int row3[3];

int main(void) {
    row3 r = {1, 2, 3};
    int sum = 0;
    for (int i = 0; i < 3; i++) sum += r[i];
    return sum == 6 ? 0 : 1;
}
