int main() {
  int max_int = 2147483647;  // INT_MAX
  int min_int = -2147483648; // INT_MIN

  // Test overflow
  int overflow_result = max_int + 1;  // Should wrap around
  int underflow_result = min_int - 1; // Should wrap around

  // Test multiplication overflow
  int a = 1000000;
  int b = 1000000;
  int mult_result = a * b; // Should overflow

  // Test unsigned overflow
  unsigned int u_max = 4294967295;     // UINT_MAX
  unsigned int u_overflow = u_max + 1; // Should wrap to 0

  // Test char overflow
  char c = 127;            // CHAR_MAX
  char c_overflow = c + 1; // Should wrap around

  return 0; // If we get here, overflow didn't cause a crash
}