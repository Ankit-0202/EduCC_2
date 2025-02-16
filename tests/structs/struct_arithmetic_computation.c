struct Calculator {
  int x;
  int y;
};

int compute(struct Calculator calc) { return (calc.x * 2) + (calc.y * 3); }

int main() {
  struct Calculator calc;
  calc.x = 4;
  calc.y = 5;
  /* (4*2)+(5*3) = 8+15 = 23 */
  return compute(calc) - 23;
}
