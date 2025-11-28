// union_reassign.c
union U {
  int i;
  int j;
};

int main() {
  union U u;
  u.i = 10;
  int a = u.i; // a should be 10
  u.j = 20;
  int b = u.i;  // b should now be 20 because u.i and u.j overlap
  return a + b; // Expected: 10 + 20 = 30
}
