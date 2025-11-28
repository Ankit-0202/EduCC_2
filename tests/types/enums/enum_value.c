// Enum with explicit initializers and implicit values.
enum Days { MON = 1, TUE, WED = 5, THU, FRI };

int main() {
  // MON is 1, TUE is 2, WED is 5, THU is 6, FRI is 7.
  int total = MON + TUE + WED + THU + FRI;
  return total;
}
