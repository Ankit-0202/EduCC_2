enum Day { MON = 1, TUE, WED, THU, FRI, SAT, SUN };

int main() {
  enum Day today = THU;
  int result = 0;
  switch (today) {
  case MON:
  case TUE:
    result = 1;
  case WED:
  case THU:
    result = 2;
  case FRI:
    result = 3;
  default:
    result = 0;
  }
  // For THU, result should be 2.
  return result - 2; // Expected: 0
}
