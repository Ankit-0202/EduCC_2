/*
 * Test: Bitwise operations
 * Purpose: Verify that all bitwise operations work correctly
 * Expected Behavior: Bitwise operations produce correct results for all
 * operators Test Cases:
 *   - Bitwise AND (&) or (|), XOR (^), NOT (~)
 *   - Left shift (<<), right shift (>>)
 *   - Complex bitwise expressions
 *   - Bit manipulation patterns
 * Dependencies: Basic integer types
 */

int main() {
  // Test basic bitwise operations
  int a = 5; // 0101 in binary
  int b = 3; // 0011 in binary

  // Bitwise AND
  int and_result = a & b; // 0101 & 0011 = 0001 = 1

  // Bitwise OR
  int or_result = a | b; // 0101 | 0011 = 0111 = 7

  // Bitwise XOR
  int xor_result = a ^ b; // 0101 ^ 0011 = 0110 = 6

  // Bitwise NOT
  int not_a = ~a; // ~0101 = 1111...1010 (depends on int size)

  // Left shift
  int left_shift = a << 2; // 0101 << 2 = 10100 = 20

  // Right shift
  int right_shift = a >> 1; // 0101 >> 1 = 0010 = 2

  // Test with larger numbers
  int large1 = 255; // 11111111
  int large2 = 240; // 11110000

  int large_and = large1 & large2; // 11110000 = 240
  int large_or = large1 | large2;  // 11111111 = 255
  int large_xor = large1 ^ large2; // 00001111 = 15

  // Test shift operations with different amounts
  int shift1 = 1 << 0; // 1
  int shift2 = 1 << 1; // 2
  int shift3 = 1 << 2; // 4
  int shift4 = 1 << 3; // 8
  int shift5 = 1 << 4; // 16

  // Test right shift with different numbers
  int rshift1 = 16 >> 1; // 8
  int rshift2 = 16 >> 2; // 4
  int rshift3 = 16 >> 3; // 2
  int rshift4 = 16 >> 4; // 1

  // Test complex bitwise expressions
  int complex1 = (a & b) | (a ^ b);   // (1) | (6) = 7
  int complex2 = (a << 1) & (b << 2); // (10) & (12) = 8
  int complex3 = ~(a | b) & 0xFF;     // ~(7) & 255 = 248 (assuming 8-bit)

  // Test bit manipulation patterns
  int set_bit = a | (1 << 2);    // Set bit 2: 0101 | 0100 = 0111 = 7
  int clear_bit = a & ~(1 << 0); // Clear bit 0: 0101 & 1110 = 0100 = 4
  int toggle_bit = a ^ (1 << 1); // Toggle bit 1: 0101 ^ 0010 = 0111 = 7

  // Verify basic operations
  if (and_result != 1)
    return 1;
  if (or_result != 7)
    return 2;
  if (xor_result != 6)
    return 3;

  if (left_shift != 20)
    return 4;
  if (right_shift != 2)
    return 5;

  // Verify large number operations
  if (large_and != 240)
    return 6;
  if (large_or != 255)
    return 7;
  if (large_xor != 15)
    return 8;

  // Verify shift operations
  if (shift1 != 1)
    return 9;
  if (shift2 != 2)
    return 10;
  if (shift3 != 4)
    return 11;
  if (shift4 != 8)
    return 12;
  if (shift5 != 16)
    return 13;

  if (rshift1 != 8)
    return 14;
  if (rshift2 != 4)
    return 15;
  if (rshift3 != 2)
    return 16;
  if (rshift4 != 1)
    return 17;

  // Verify complex expressions
  if (complex1 != 7)
    return 18;
  if (complex2 != 8)
    return 19;

  // Verify bit manipulation
  if (set_bit != 7)
    return 20;
  if (clear_bit != 4)
    return 21;
  if (toggle_bit != 7)
    return 22;

  // Test edge cases
  int zero = 0;
  int all_ones = ~0;

  int edge1 = zero & a;     // 0
  int edge2 = zero | a;     // 5
  int edge3 = zero ^ a;     // 5
  int edge4 = all_ones & a; // 5
  int edge5 = all_ones | a; // all_ones
  int edge6 = all_ones ^ a; // ~5

  if (edge1 != 0)
    return 23;
  if (edge2 != 5)
    return 24;
  if (edge3 != 5)
    return 25;
  if (edge4 != 5)
    return 26;

  return 0; // All tests passed
}