#include <stddef.h>

struct offsets {
  char c;
  int x;
  double d;
};

int main(void) {
  size_t off_x = offsetof(struct offsets, x);
  size_t off_d = offsetof(struct offsets, d);
  return (off_x > 0 && off_d > off_x) ? 0 : 1;
}
