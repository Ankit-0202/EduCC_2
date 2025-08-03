// union_basic.c
union Data {
  int i;
  float f;
  char c;
};

int main() {
  union Data d;
  d.i = 42;
  int x = d.i; // Expected: 42
  return x;
}
