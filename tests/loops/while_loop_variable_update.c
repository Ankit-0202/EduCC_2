int main() {
  int x = 1;
  int y = 0;
  while (x < 100) {
    y = y + x;
    x = x + 10;
  }
  /* x: 1, 11, 21, ..., 91 -> Sum = 1+11+21+31+41+51+61+71+81+91 = 460 */
  return y - 460;
}
