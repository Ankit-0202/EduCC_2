union Overlap {
  int a;
  int b;
};

int main() {
  union Overlap o;
  o.a = 123;
  /* Both fields share the same memory */
  return o.b - 123;
}
