int main() {
  int a = 5; /* 0101 */
  int b = 3; /* 0011 */
  /* (5 << 1) = 10 (1010), then 1010 XOR 0011 = 1001 (9) */
  int result = (a << 1) ^ b;
  return result - 9;
}
