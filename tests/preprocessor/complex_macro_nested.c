#define MUL(a, b) ((a) * (b))
#define ADD(a, b) ((a) + (b))
#define SUB(a, b) ((a) - (b))
#define COMPLEX_OP(a, b, c) ADD(MUL(a, b), SUB(c, a))
int main() {
  // COMPLEX_OP(3, 4, 10) expands to ((3*4) + (10-3)) = (12 + 7) = 19.
  return COMPLEX_OP(3, 4, 10) - 19;
}
