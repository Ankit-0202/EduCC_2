enum forward;

enum forward { FORWARD_A = 3, FORWARD_B };

int main(void) {
  enum forward v = FORWARD_B;
  return v == 4 ? 0 : 1;
}
