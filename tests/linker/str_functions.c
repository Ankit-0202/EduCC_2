#include <string.h>

int main(void) {
  const char *alpha = "alphabet";
  const char *beta = "beta";
  if (strcmp(alpha, beta) >= 0) {
    return 1;
  }
  if (strncmp(alpha, "alpha", 5) != 0) {
    return 2;
  }

  const char *location = strchr(beta, 't');
  if (!location || *location != 't' || *(location + 1) != 'a') {
    return 3;
  }

  const char *needle = "pha";
  const char *found = strstr(alpha, needle);
  if (!found || found != alpha + 2) {
    return 4;
  }

  return 0;
}
