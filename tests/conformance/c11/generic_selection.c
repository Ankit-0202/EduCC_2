int main(void) {
  int a = _Generic(1, int: 1, default: 0);
  double d = 1.0;
  int b = _Generic(d, double: 2, default: 0);
  void *p = 0;
  int c = _Generic(p, void *: 3, default: 0);
  return (a == 1 && b == 2 && c == 3) ? 0 : 1;
}
