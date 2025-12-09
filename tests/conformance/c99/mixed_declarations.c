int main(void) {
  int total = 1;
  total += 2;
  int mid = total * 3; // declaration after statements (C99)
  total += mid;

  for (int i = 0; i < 3; i++) {
    total += i;
  }

  return total == 15 ? 0 : 1;
}
