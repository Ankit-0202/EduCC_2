#define VALUE 5
#define DOUBLE(x) (x + x)
#define QUADRUPLE(x) DOUBLE(DOUBLE(x))
int main() {
  return QUADRUPLE(VALUE) - 20; // 5*4 = 20, should return 0.
}
