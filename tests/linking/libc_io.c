#include <stdio.h>
#include <string.h>

int main(void) {
  const char *message = "EduCC";
  size_t length = strlen(message);

  if (length != 5) {
    return 1;
  }

  int printed = printf("%s:%zu\n", message, length);
  if (printed < 0) {
    return 2;
  }

  return 0;
}

