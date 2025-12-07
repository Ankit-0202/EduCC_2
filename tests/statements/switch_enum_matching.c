enum mode { MODE_A, MODE_B, MODE_C };

int dispatch(enum mode m) {
  switch (m) {
  case MODE_A:
    return 1;
  case MODE_B:
    return 2;
  case MODE_C:
    return 3;
  default:
    return -1;
  }
}

int main(void) {
  int ok = dispatch(MODE_A) == 1;
  ok &= dispatch(MODE_B) == 2;
  ok &= dispatch(MODE_C) == 3;
  return ok ? 0 : 1;
}
