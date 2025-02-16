union Data {
  int i;
  int j;
};

int main() {
  union Data d;
  d.i = 50;
  d.j = d.i;       // Overwrite, but value remains the same
  return d.j - 50; // Expected: 0
}
