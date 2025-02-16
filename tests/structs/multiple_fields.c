struct Data {
  int a;
  int b;
  int c;
};

int main() {
  struct Data d;
  d.a = 1;
  d.b = 2;
  d.c = 3;
  return d.a + d.b + d.c; // Expected: 6
}
