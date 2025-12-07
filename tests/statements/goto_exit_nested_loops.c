int main(void) {
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      count++;
      if (i == 1 && j == 1)
        goto done;
    }
  }

done:
  return count == 5 ? 0 : 1;
}
