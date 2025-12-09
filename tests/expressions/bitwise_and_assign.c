// Test bitwise AND assignment operator &=
int main() {
  int a = 0xFF;
  a &= 0x0F;
  if (a != 0x0F)
    return 1;

  int b = 0b11110000;
  b &= 0b00111100;
  if (b != 0b00110000)
    return 2;

  int c = 255;
  c &= 127;
  if (c != 127)
    return 3;

  int d = 0xAAAA;
  d &= 0x5555;
  if (d != 0)
    return 4;

  int e = 0xFFFF;
  e &= 0xFFFF;
  if (e != 0xFFFF)
    return 5;

  return 0;
}
