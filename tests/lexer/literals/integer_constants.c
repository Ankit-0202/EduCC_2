// Test various integer constant formats
int main() {
  // Decimal
  int dec = 12345;
  if (dec != 12345)
    return 1;

  // Hex
  int hex = 0x1A2B;
  if (hex != 6699)
    return 2;

  // Octal
  int oct = 0123;
  if (oct != 83)
    return 3;

  // Zero in different formats
  int zero_dec = 0;
  int zero_hex = 0x0;
  int zero_oct = 00;
  if (zero_dec != 0 || zero_hex != 0 || zero_oct != 0)
    return 4;

  // Large numbers
  int large = 2147483647;
  if (large != 2147483647)
    return 5;

  // Negative numbers
  int neg = -42;
  if (neg != -42)
    return 6;

  // Unsigned max
  unsigned int umax = 4294967295U;
  if (umax != 4294967295U)
    return 7;

  return 0;
}
