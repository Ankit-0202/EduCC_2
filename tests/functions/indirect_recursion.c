int power(int base, int exp) {
  if (exp == 0)
    return 1;
  return base * power(base, exp - 1);
}

int main() {
  /* 3^4 = 81 */
  return power(3, 4) - 81;
}
