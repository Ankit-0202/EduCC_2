enum Letter { A = 1, B = 2, C = 3 };

int main() {
  enum Letter l = B;
  int result = 0;
  switch (l) {
  case A:
    result = 10;
    break;
  case C:
    result = 30;
    break;
  default:
    result = 20;
  }
  /* With l == B, default should be taken -> result = 20 */
  return result - 20;
}
