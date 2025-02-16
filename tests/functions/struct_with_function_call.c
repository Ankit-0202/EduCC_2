struct Pair {
  int a;
  int b;
};

int sumPair(struct Pair p) { return p.a + p.b; }

int main() {
  struct Pair p;
  p.a = 7;
  p.b = 8;
  return sumPair(p) - 15;
}
