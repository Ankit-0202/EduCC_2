// Test arrays of strings
int main() {
  char *strings[5] = {"first", "second", "third", "fourth", "fifth"};

  // Check first characters
  if (strings[0][0] != 'f')
    return 1;
  if (strings[1][0] != 's')
    return 2;
  if (strings[2][0] != 't')
    return 3;

  // Check length by counting to null terminator
  int len = 0;
  while (strings[0][len] != '\0') {
    len++;
  }
  if (len != 5)
    return 4;

  // Access different characters
  if (strings[4][1] != 'i')
    return 5;
  if (strings[3][2] != 'u')
    return 6;

  // Pointer arithmetic on string array
  char *first = strings[0];
  char *second = strings[1];
  if (first[0] != 'f')
    return 7;
  if (second[1] != 'e')
    return 8;

  return 0;
}
