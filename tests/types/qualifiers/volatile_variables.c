int main() {
  volatile int x = 10;
  volatile char c = 'B';
  volatile float f = 2.5;

  if (x != 10)
    return 1;
  if (c != 'B')
    return 1;
  if (f < 2.4 || f > 2.6)
    return 1;

  x = 20;
  if (x != 20)
    return 1;

  volatile int *ptr = &x;
  if (*ptr != 20)
    return 1;

  return 0;
}