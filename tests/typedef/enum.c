int main() {
  typedef enum { RED = 1, GREEN, BLUE } Color;
  Color c = GREEN;
  /* GREEN should have the value 2 */
  return c - 2;
}
