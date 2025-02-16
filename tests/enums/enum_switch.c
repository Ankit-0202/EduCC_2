enum Weekday { MON, TUE, WED, THU, FRI };

int main() {
  enum Weekday day = WED;
  switch (day) {
  case MON:
    return 1;
  case TUE:
    return 2;
  case WED:
    return 3;
  case THU:
    return 4;
  case FRI:
    return 5;
  default:
    return 0;
  }
}
