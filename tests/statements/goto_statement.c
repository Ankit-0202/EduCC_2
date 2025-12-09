int main() {
  int x = 0;

  goto start;

  x = 100; // This should be skipped

start:
  x = 10;

  if (x != 10)
    return 1;

  // Goto with conditional
  int y = 0;
  if (x > 5) {
    goto increment;
  }
  y = 50;

increment:
  y += 10;

  if (y != 10)
    return 1;

  // Goto in loop
  int sum = 0;
  int i = 0;

loop:
  sum += i;
  i++;
  if (i < 5) {
    goto loop;
  }

  if (sum != 10)
    return 1; // 0+1+2+3+4 = 10

  return 0;
}