int main() {
  typedef union {
    int i;
    float f;
  } MyUnion;
  MyUnion u;
  u.i = 123;
  return u.i - 123;
}
