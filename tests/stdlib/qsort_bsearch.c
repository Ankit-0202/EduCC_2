#include <stddef.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs) {
  const int a = *(const int *)lhs;
  const int b = *(const int *)rhs;
  if (a < b)
    return -1;
  if (a > b)
    return 1;
  return 0;
}

static int is_sorted(const int *values, size_t count) {
  for (size_t i = 1; i < count; ++i) {
    if (values[i - 1] > values[i]) {
      return 0;
    }
  }
  return 1;
}

int main(void) {
  int numbers[] = {42, -7, 19, 0, 5, 99, 12, 12};
  const size_t count = sizeof(numbers) / sizeof(numbers[0]);

  qsort(numbers, count, sizeof(numbers[0]), compare_ints);
  if (!is_sorted(numbers, count)) {
    return 1;
  }

  int key = 19;
  int *found = bsearch(&key, numbers, count, sizeof(numbers[0]), compare_ints);
  if (!found || *found != key) {
    return 2;
  }

  key = 1234;
  found = bsearch(&key, numbers, count, sizeof(numbers[0]), compare_ints);
  if (found) {
    return 3;
  }

  return 0;
}


