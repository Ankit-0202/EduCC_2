/*
 * Test: Type casting and conversions
 * Purpose: Verify that type casting works correctly between different data
 * types Expected Behavior: Type conversions should work properly with
 * appropriate precision and truncation Test Cases:
 *   - Implicit type conversions
 *   - Explicit type casting
 *   - Float to int conversion
 *   - Int to float conversion
 *   - Char to int conversion
 *   - Pointer type casting
 *   - Complex type conversions
 * Dependencies: Basic integer, float and char types
 */

int main() {
  int result = 0;

  // Test implicit conversions
  int int_val = 42;
  float float_val = 3.14f;
  char char_val = 'A';

  // Int to float (implicit)
  float int_to_float = int_val;

  // Float to int (implicit - truncation)
  int float_to_int = float_val;

  // Char to int (implicit)
  int char_to_int = char_val;

  // Test explicit casting
  int explicit_int = (int)3.7f;
  float explicit_float = (float)5;
  char explicit_char = (char)66;

  // Test casting with arithmetic
  int arith_cast1 = (int)(3.14f + 2.86f);
  float arith_cast2 = (float)(10 / 3);
  int arith_cast3 = (int)(char_val + 1);

  // Test casting with different sizes
  short short_val = 12345;
  int short_to_int = (int)short_val;
  short int_to_short = (short)123456;

  long long_val = 123456789L;
  int long_to_int = (int)long_val;
  long int_to_long = (long)42;

  // Test casting with negative values
  int neg_int = -42;
  float neg_float = (float)neg_int;
  int neg_float_to_int = (int)(-3.7f);

  // Test casting with large values
  int large_int = 2147483647;
  float large_int_to_float = (float)large_int;
  int large_float_to_int = (int)1e10f;

  // Test casting with precision
  float precise_float = 3.14159f;
  int precise_int = (int)precise_float;
  float precise_float_again = (float)precise_int;

  // Test casting with expressions
  int expr_cast1 = (int)(3.5f * 2.0f);
  float expr_cast2 = (float)(10 + 5);
  int expr_cast3 = (int)(char_val * 2);

  // Test casting with conditional
  int cond_cast = 0;
  if ((float)5 > 4.5f) {
    cond_cast = (int)(5.5f);
  }

  // Test casting with arrays
  int int_array[3] = {1, 2, 3};
  float float_array[3];
  for (int i = 0; i < 3; i++) {
    float_array[i] = (float)int_array[i];
  }
  float array_sum = float_array[0] + float_array[1] + float_array[2];

  // Test casting with pointers
  int *int_ptr = &int_val;
  void *void_ptr = (void *)int_ptr;
  int *back_to_int = (int *)void_ptr;
  int pointer_cast_test = *back_to_int;

  // Test casting with struct members
  struct TestStruct {
    int i;
    float f;
  };
  struct TestStruct ts;
  ts.i = 100;
  ts.f = (float)ts.i;
  int struct_cast_test = (int)ts.f;

  // Test casting with function-like behavior
  int func_cast_test = (int)((float)42 + 0.5f);

  // Test casting with bitwise operations
  int bit_cast1 = (int)((float)(1 << 3));
  float bit_cast2 = (float)((1 << 2) + 1);

  // Verify results
  if (int_to_float < 41.9f || int_to_float > 42.1f)
    return 1;
  if (float_to_int != 3)
    return 2; // 3.14 truncated to 3
  if (char_to_int != 65)
    return 3; // 'A' = 65
  if (explicit_int != 3)
    return 4; // 3.7 truncated to 3
  if (explicit_float < 4.9f || explicit_float > 5.1f)
    return 5;
  if (explicit_char != 'B')
    return 6; // 66 = 'B'
  if (arith_cast1 != 6)
    return 7; // (int)(3.14 + 2.86) = 6
  if (arith_cast2 < 3.3f || arith_cast2 > 3.4f)
    return 8; // (float)(10/3) ≈ 3.33
  if (arith_cast3 != 66)
    return 9; // 'A'(65) + 1 = 66
  if (short_to_int != 12345)
    return 10;
  if (int_to_short != -7616)
    return 11; // 123456 truncated to 16 bits
  if (long_to_int != 123456789)
    return 12;
  if (int_to_long != 42)
    return 13;
  if (neg_float < -42.1f || neg_float > -41.9f)
    return 14;
  if (neg_float_to_int != -3)
    return 15;
  if (large_int_to_float < 2.147e9f || large_int_to_float > 2.148e9f)
    return 16;
  if (precise_int != 3)
    return 17;
  if (precise_float_again < 2.9f || precise_float_again > 3.1f)
    return 18;
  if (expr_cast1 != 7)
    return 19; // (int)(3.5 * 2.0) = 7
  if (expr_cast2 < 14.9f || expr_cast2 > 15.1f)
    return 20;
  if (expr_cast3 != 130)
    return 21; // 65 * 2 = 130
  if (cond_cast != 5)
    return 22; // (int)(5.5) = 5
  if (array_sum < 5.9f || array_sum > 6.1f)
    return 23; // 1.0 + 2.0 + 3.0 = 6.0
  if (pointer_cast_test != 42)
    return 24;
  if (struct_cast_test != 100)
    return 25;
  if (func_cast_test != 42)
    return 26;
  if (bit_cast1 != 8)
    return 27; // (int)((float)(1<<3)) = 8
  if (bit_cast2 < 4.9f || bit_cast2 > 5.1f)
    return 28; // (float)(4+1) = 5.0

  // Test complex casting scenarios
  int complex_cast1 = (int)((float)((char)100) + 0.5f);
  float complex_cast2 = (float)((int)(3.7f) + 2);
  int complex_cast3 = (int)((float)((short)1000) / 10.0f);

  if (complex_cast1 != 100)
    return 29;
  if (complex_cast2 < 4.9f || complex_cast2 > 5.1f)
    return 30; // (float)(3 + 2) = 5.0
  if (complex_cast3 != 100)
    return 31; // (int)((float)(1000) / 10.0) = 100

  return 0; // All tests passed
}