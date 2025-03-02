int main() {
  typedef struct {
    struct {
      int y;
    } inner;
  } Outer;
  Outer o;
  o.inner.y = 50;
  return o.inner.y - 50;
}
