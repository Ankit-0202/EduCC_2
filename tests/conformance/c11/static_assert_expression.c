#include <stddef.h>

_Static_assert(1 + 2 == 3, "basic arithmetic should hold at compile time");
_Static_assert(sizeof(size_t) >= sizeof(void *),
               "size_t large enough for pointer");

int main(void) {
  int array[sizeof(long long) >= sizeof(long) ? 1 : -1];
  return (int)(sizeof array) - 1;
}
