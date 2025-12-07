inline int square(int x) { return x * x; }

inline int cube(int x) { return x * x * x; }

inline int max(int a, int b) { return (a > b) ? a : b; }

int main() {
  if (square(5) != 25)
    return 1;
  if (square(3) != 9)
    return 1;

  if (cube(2) != 8)
    return 1;
  if (cube(3) != 27)
    return 1;

  if (max(10, 5) != 10)
    return 1;
  if (max(3, 7) != 7)
    return 1;
  if (max(5, 5) != 5)
    return 1;

  return 0;
}