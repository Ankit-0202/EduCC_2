int main(void) {
  volatile int counter = 0;
  for (int i = 0; i < 5; i++) {
    counter++;
  }
  return counter == 5 ? 0 : 1;
}
