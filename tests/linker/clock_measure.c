#include <time.h>

int main(void) {
  clock_t start = clock();
  if (start == (clock_t)-1) {
    return 1;
  }

  volatile double sink = 0.0;
  for (int i = 0; i < 100000; ++i) {
    sink += i * 0.0001;
  }

  clock_t end = clock();
  if (end == (clock_t)-1) {
    return 2;
  }
  if (end < start) {
    return 3;
  }

  double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  if (elapsed < 0.0) {
    return 4;
  }

  return sink > 0.0 ? 0 : 5;
}


