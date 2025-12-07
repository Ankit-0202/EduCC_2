int main() {
  const int x = 10;
  const char c = 'A';
  const float f = 3.14;

  if (x != 10)
    return 1;
  if (c != 'A')
    return 1;
  if (f < 3.13 || f > 3.15)
    return 1;

  const int *ptr = &x;
  if (*ptr != 10)
    return 1;

  return 0;
}