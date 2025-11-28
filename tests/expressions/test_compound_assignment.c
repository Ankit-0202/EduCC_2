/*
 * Test: Compound assignment operators
 * Purpose: Verify that compound assignment operators work correctly
 * Expected Behavior: Compound assignments should modify variables and return
 * appropriate results Test Cases:
 *   - Arithmetic compound assignments (+=, -=, *=, /=, %=)
 *   - Bitwise compound assignments (&=, |=, ^=, <<=, >>=)
 *   - Complex expressions with compound assignments
 *   - Compound assignments with different types
 *   - Nested compound assignments
 * Dependencies: Basic integer types, arithmetic and bitwise operations
 */

int main() {
  int result = 0;

  // Test arithmetic compound assignments
  int a = 10;
  a += 5; // a = 15
  int add_result = a;

  int b = 20;
  b -= 7; // b = 13
  int sub_result = b;

  int c = 6;
  c *= 4; // c = 24
  int mul_result = c;

  int d = 25;
  d /= 5; // d = 5
  int div_result = d;

  int e = 17;
  e %= 5; // e = 2
  int mod_result = e;

  // Test bitwise compound assignments
  int f = 15; // 1111 in binary
  f &= 10;    // 1010 in binary, result: 1010 = 10
  int and_result = f;

  int g = 5; // 0101 in binary
  g |= 10;   // 1010 in binary, result: 1111 = 15
  int or_result = g;

  int h = 12; // 1100 in binary
  h ^= 10;    // 1010 in binary, result: 0110 = 6
  int xor_result = h;

  int i = 4;
  i <<= 2; // 4 << 2 = 16
  int left_shift_result = i;

  int j = 16;
  j >>= 2; // 16 >> 2 = 4
  int right_shift_result = j;

  // Test compound assignments with expressions
  int k = 10;
  k += k * 2; // k = 10 + (10 * 2) = 30
  int expr_result = k;

  int l = 20;
  l -= l / 4; // l = 20 - (20 / 4) = 15
  int expr_result2 = l;

  // Test compound assignments with different types
  char char_val = 'A';
  char_val += 1; // 'A' + 1 = 'B'
  char char_result = char_val;

  short short_val = 100;
  short_val *= 2; // 100 * 2 = 200
  short short_result = short_val;

  // Test compound assignments with floating point
  float float_val = 3.5f;
  float_val += 2.5f; // 3.5 + 2.5 = 6.0
  float float_result = float_val;

  // Test nested compound assignments
  int nested = 5;
  nested += (nested *= 2); // nested = 5 + (5 * 2) = 15
  int nested_result = nested;

  // Test compound assignments with conditional
  int cond_val = 10;
  if (cond_val > 5) {
    cond_val += 10;
  }
  int cond_result = cond_val;

  // Test compound assignments in loops
  int loop_sum = 0;
  for (int m = 1; m <= 5; m++) {
    loop_sum += m;
  }
  // Expected: 1 + 2 + 3 + 4 + 5 = 15

  // Test compound assignments with arrays
  int arr[3] = {1, 2, 3};
  arr[0] += arr[1];
  arr[1] *= arr[2];
  int arr_sum = arr[0] + arr[1] + arr[2];
  // Expected: (1+2) + (2*3) + 3 = 3 + 6 + 3 = 12

  // Test compound assignments with pointers
  int ptr_val = 100;
  int *ptr = &ptr_val;
  *ptr += 50;
  int ptr_result = *ptr;

  // Test compound assignments with struct members
  struct TestStruct {
    int value;
  };
  struct TestStruct ts = {25};
  ts.value *= 2;
  int struct_result = ts.value;

  // Test complex compound assignments
  int complex = 10;
  complex += (complex *= 2) + (complex /= 2);
  int complex_result = complex;

  // Test compound assignments with bitwise operations
  int bit_val = 15;
  bit_val &= 10;
  bit_val |= 5;
  bit_val ^= 3;
  int bit_result = bit_val;

  // Test compound assignments with shift operations
  int shift_val = 8;
  shift_val <<= 1;
  shift_val >>= 2;
  int shift_result = shift_val;

  // Test compound assignments with arithmetic and bitwise
  int mixed = 20;
  mixed += 5;
  mixed &= 15;
  mixed *= 2;
  int mixed_result = mixed;

  // Test compound assignments with negative values
  int neg_val = -10;
  neg_val += 15;
  neg_val *= -2;
  int neg_result = neg_val;

  // Test compound assignments with zero
  int zero_val = 0;
  zero_val += 5;
  zero_val *= 3;
  int zero_result = zero_val;

  // Test compound assignments with large values
  int large_val = 1000000;
  large_val += 500000;
  large_val /= 2;
  int large_result = large_val;

  // Verify results
  if (add_result != 15)
    return 1;
  if (sub_result != 13)
    return 2;
  if (mul_result != 24)
    return 3;
  if (div_result != 5)
    return 4;
  if (mod_result != 2)
    return 5;
  if (and_result != 10)
    return 6;
  if (or_result != 15)
    return 7;
  if (xor_result != 6)
    return 8;
  if (left_shift_result != 16)
    return 9;
  if (right_shift_result != 4)
    return 10;
  if (expr_result != 30)
    return 11;
  if (expr_result2 != 15)
    return 12;
  if (char_result != 'B')
    return 13;
  if (short_result != 200)
    return 14;
  if (float_result < 5.9f || float_result > 6.1f)
    return 15;
  if (nested_result != 15)
    return 16;
  if (cond_result != 20)
    return 17;
  if (loop_sum != 15)
    return 18;
  if (arr_sum != 12)
    return 19;
  if (ptr_result != 150)
    return 20;
  if (struct_result != 50)
    return 21;
  if (complex_result != 30)
    return 22;
  if (bit_result != 12)
    return 23; // (15 & 10) | 5 ^ 3 = 10 | 5 ^ 3 = 15 ^ 3 = 12
  if (shift_result != 2)
    return 24; // (8 << 1) >> 2 = 16 >> 2 = 4 >> 2 = 2
  if (mixed_result != 20)
    return 25; // ((20 + 5) & 15) * 2 = (25 & 15) * 2 = 9 * 2 = 18
  if (neg_result != -10)
    return 26; // (-10 + 15) * -2 = 5 * -2 = -10
  if (zero_result != 15)
    return 27; // (0 + 5) * 3 = 15
  if (large_result != 750000)
    return 28; // (1000000 + 500000) / 2 = 750000

  // Test compound assignments with multiple operations
  int multi = 10;
  multi += 5;
  multi *= 2;
  multi -= 3;
  multi /= 4;
  int multi_result = multi;
  // Expected: ((10 + 5) * 2 - 3) / 4 = (15 * 2 - 3) / 4 = (30 - 3) / 4 = 27 / 4
  // = 6

  if (multi_result != 6)
    return 29;

  return 0; // All tests passed
}