union Multi {
  int a;
  int b;
  int c;
};

int main() {
  union Multi m;
  m.a = 77;
  // Reading any member should yield the same underlying bits.
  return m.b - 77; // Expected: 0
}
