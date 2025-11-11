#include <ctype.h>

int main(void) {
  if (!isdigit('7')) {
    return 1;
  }
  if (isalpha('9')) {
    return 2;
  }
  if (!isupper('Q')) {
    return 3;
  }
  if (tolower('A') != 'a') {
    return 4;
  }
  if (!isspace('\n')) {
    return 5;
  }
  if (!isxdigit('f')) {
    return 6;
  }
  return 0;
}


