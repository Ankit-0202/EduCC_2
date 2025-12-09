#include <stdbool.h>

int main(void) {
  bool flag = true;
  bool values[3] = {true, false, true};

  if (!flag)
    return 1;
  if (values[0] != true)
    return 1;
  if (values[1] != false)
    return 1;
  if (values[2] != true)
    return 1;

  bool combined = (values[0] && !values[1]) || values[1];
  return combined ? 0 : 1;
}
