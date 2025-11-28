// Anonymous enum declaration; enumerators become global constants.
enum { ZERO, ONE, TWO };

int main() {
  int sum = ZERO + ONE + TWO; // Expected: 0 + 1 + 2 = 3
  return sum;
}
