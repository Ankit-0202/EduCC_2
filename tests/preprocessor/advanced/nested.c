#define INC(x) ((x) + 1)
#define DOUBLE(x) ((x) + (x))
#define COMPOSE(x) DOUBLE(INC(x))

int main() {
  return COMPOSE(
      5); // Expected: DOUBLE(INC(5)) expands to (((5) + 1) + ((5) + 1))
}
