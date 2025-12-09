// Test integer overflow and wraparound
int main() {
  // Unsigned overflow wraps around
  unsigned char uc = 255;
  uc = uc + 1;
  if (uc != 0)
    return 1;

  // Unsigned underflow wraps around
  unsigned char uc2 = 0;
  uc2 = uc2 - 1;
  if (uc2 != 255)
    return 2;

  // Unsigned short overflow
  unsigned short us = 65535;
  us = us + 1;
  if (us != 0)
    return 3;

  // Multiple wraparounds
  unsigned char uc3 = 200;
  uc3 = uc3 + 100;
  if (uc3 != 44)
    return 4; // (200 + 100) % 256 = 44

  // Multiplication overflow
  unsigned char uc4 = 20;
  uc4 = uc4 * 20;
  if (uc4 != 144)
    return 5; // 400 % 256 = 144

  return 0;
}
