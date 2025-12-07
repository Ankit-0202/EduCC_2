#include <stdlib.h>

struct numbers {
  int len;
  int values[];
};

int main(void) {
  int len = 5;
  struct numbers *nums = malloc(sizeof(struct numbers) + (sizeof(int) * len));
  if (!nums)
    return 1;

  nums->len = len;
  for (int i = 0; i < len; i++) {
    nums->values[i] = i * i;
  }

  int sum = 0;
  for (int i = 0; i < nums->len; i++) {
    sum += nums->values[i];
  }

  free(nums);
  return sum == 30 ? 0 : 1;
}
