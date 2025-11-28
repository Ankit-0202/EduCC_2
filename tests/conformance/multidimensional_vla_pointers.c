int sum_matrix(int rows, int cols, int matrix[rows][cols]) {
    int total = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            total += matrix[i][j];
        }
    }
    return total;
}

int main(void) {
    int rows = 2;
    int cols = 3;
    int matrix[rows][cols];
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = value++;
        }
    }
    return sum_matrix(rows, cols, matrix) == 21 ? 0 : 1;
}
