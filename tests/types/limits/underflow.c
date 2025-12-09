// Test underflow scenarios
int main() {
  // Unsigned underflow
  unsigned int u = 0;
  unsigned int result = u - 1;
  if (result != 4294967295U)
    return 1;

  // Unsigned short underflow
  unsigned short us = 0;
  us = us - 1;
  if (us != 65535)
    return 2;

  // Unsigned char underflow
  unsigned char uc = 0;
  uc = uc - 1;
  if (uc != 255)
    return 3;

  // Multiple underflows
  unsigned char uc2 = 10;
  uc2 = uc2 - 20;
  if (uc2 != 246)
    return 4; // 10 - 20 = -10, wraps to 246

  return 0;
}
