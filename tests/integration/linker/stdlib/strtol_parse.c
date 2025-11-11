#include <errno.h>
#include <stdlib.h>

int main(void) {
  const char *decimal = "  -42xyz";
  char *end = NULL;
  errno = 0;
  long value = strtol(decimal, &end, 10);
  if (errno != 0) {
    return 1;
  }
  if (value != -42) {
    return 2;
  }
  if (!end || *end != 'x') {
    return 3;
  }

  const char *hexadecimal = "0x1f";
  errno = 0;
  end = NULL;
  long second = strtol(hexadecimal, &end, 0);
  if (errno != 0 || !end || *end != '\0') {
    return 4;
  }
  if (second != 31) {
    return 5;
  }

  return 0;
}


