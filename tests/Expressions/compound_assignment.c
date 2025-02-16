int main() {
  int x = 10;
  x = x + 5;     // Simulate x += 5.
  x = x - 3;     // Simulate x -= 3.
  return x - 12; // 10+5-3 = 12, expected: 0.
}
