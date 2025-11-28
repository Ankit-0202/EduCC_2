#include <stdlib.h>

int main(void) {
  srand(1234);
  int first = rand();
  int second = rand();

  srand(1234);
  if (rand() != first) {
    return 1;
  }

  if (second == first) {
    return 2;
  }

  srand(5678);
  if (rand() == first) {
    return 3;
  }

  return 0;
}
