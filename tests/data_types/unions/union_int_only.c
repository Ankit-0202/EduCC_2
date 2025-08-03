// union_int_only.c
union Number {
  int a;
  int b;
};

int main() {
  union Number n;
  n.a = 100;
  // Now assign via the second member; this will overwrite the memory.
  n.b = 200;
  int x = n.a; // Expected: 200
  return x;
}
