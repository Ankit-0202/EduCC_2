int sum_rows(int (*matrix)[3], int rows) {
  int total = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < 3; j++) {
      total += matrix[i][j];
    }
  }
  return total;
}

int main(void) {
  int data[2][3] = {{1, 2, 3}, {4, 5, 6}};
  return sum_rows(data, 2) == 21 ? 0 : 1;
}
