struct Inner {
  int a;
};

struct Outer {
  struct Inner in;
  int b;
};

int main() {
  struct Outer o;
  o.in.a = 10;
  o.b = 5;
  return o.in.a - o.b; // Expected: 5
}
