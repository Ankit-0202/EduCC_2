int main(void) {
  int sum = 0;
  for (int i = 0, j = 5; i < j; ++i, --j) {
    sum += i + j;
  }
  return sum == 15 ? 0 : 1;
}
