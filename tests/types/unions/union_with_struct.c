struct S {
  int x;
};

union Container {
  int i;
  struct S s;
};

int main() {
  union Container c;
  c.i = 15;
  return c.s.x - 15; // Expected: 0
}
