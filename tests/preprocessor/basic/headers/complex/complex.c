// tests/preprocessor/complex.c
#include "include_test.h"

#define MULTIPLY(x, y) ((x) * (y))
#define USE_ADD 0

#if USE_ADD
#define OPERATION(a, b) add(a, b)
#else
#define OPERATION(a, b) MULTIPLY(a, b)
#endif

int main() {
  int result = OPERATION(3, 4);
  return result;
}
