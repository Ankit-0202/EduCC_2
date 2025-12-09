int main(void) {
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (j == 1)
        continue;
      if (i == 2)
        break;
      count++;
    }
  }
  return count == 4 ? 0 : 1;
}
