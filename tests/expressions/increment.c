int main() {
  int x = 5;
  int y = x; // Simulate post-increment: y gets 5.
  x = x + 1; // Now x becomes 6.
  int z = x; // Simulate pre-increment: z gets 6.
  x = x + 1; // x becomes 7.
  // Sum y + z + x should equal 5 + 6 + 7 = 18.
  return (y + z + x) - 18; // Expected: 0
}
