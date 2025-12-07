int putchar(int c);

void print_int(int n) {
  if (n < 0) {
    putchar((int)'-');
    n = -n;
  }
  if (n / 10) {
    print_int(n / 10);
  }
  putchar((int)(n % 10 + '0'));
}

int main() {
  int c = 10 & 12; // 8
  print_int(c);
  putchar((int)'\n');
  return 0;
}