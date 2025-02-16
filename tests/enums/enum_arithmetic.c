enum MathOps { ADD = 1, SUB = 2, MUL = 3 };

int main() {
  // Perform a simple arithmetic: (MUL * ADD) - SUB = (3 * 1) - 2 = 1.
  int result = (MUL * ADD) - SUB;
  return result - 1; // Expected: 0
}
