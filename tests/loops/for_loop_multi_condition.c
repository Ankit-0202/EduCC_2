int main() {
  int sum = 0;
  int i;
  for (i = 1; i <= 5; i = i + 1) {
    if (i % 2 == 0) {
      sum = sum + i;
    } else {
      sum = sum + 0;
    }
  }
  /* Even numbers: 2 + 4 = 6 */
  return sum - 6;
}
