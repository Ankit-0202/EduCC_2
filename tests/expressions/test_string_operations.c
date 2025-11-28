/*
 * Test: String operations and character arrays
 * Purpose: Verify that string operations work correctly with character arrays
 * and literals Expected Behavior: String operations should handle character
 * arrays and string literals properly Test Cases:
 *   - Character array declaration and initialization
 *   - String literal handling
 *   - Character array manipulation
 *   - String comparison
 *   - String concatenation simulation
 *   - String length calculation
 * Dependencies: Basic char and int types, arrays
 */

int main() {
  int result = 0;

  // Test character array declaration and initialization
  char str1[10] = "Hello";
  char str2[] = "World";
  char str3[5] = {'H', 'e', 'l', 'l', 'o'};

  // Test character array access
  int char_sum1 = 0;
  for (int i = 0; str1[i] != '\0'; i++) {
    char_sum1 += str1[i];
  }
  // Expected: 'H'(72) + 'e'(101) + 'l'(108) + 'l'(108) + 'o'(111) = 500

  int char_sum2 = 0;
  for (int i = 0; str2[i] != '\0'; i++) {
    char_sum2 += str2[i];
  }
  // Expected: 'W'(87) + 'o'(111) + 'r'(114) + 'l'(108) + 'd'(100) = 520

  // Test string literal handling
  char *str_literal = "Test";
  int literal_sum = 0;
  for (int i = 0; str_literal[i] != '\0'; i++) {
    literal_sum += str_literal[i];
  }
  // Expected: 'T'(84) + 'e'(101) + 's'(115) + 't'(116) = 416

  // Test character array with arithmetic
  char alpha[5] = "ABCD";
  for (int i = 0; i < 4; i++) {
    alpha[i] += 1; // Shift each character by 1
  }

  int alpha_sum = 0;
  for (int i = 0; i < 4; i++) {
    alpha_sum += alpha[i];
  }
  // Expected: 'B'(66) + 'C'(67) + 'D'(68) + 'E'(69) = 270

  // Test character array with conditional
  char test_str[6] = "Hello";
  int conditional_sum = 0;

  for (int i = 0; test_str[i] != '\0'; i++) {
    if (test_str[i] >= 'a' && test_str[i] <= 'z') {
      conditional_sum += test_str[i] - 'a' + 1;
    } else if (test_str[i] >= 'A' && test_str[i] <= 'Z') {
      conditional_sum += test_str[i] - 'A' + 1;
    }
  }
  // Expected: H(8) + e(5) + l(12) + l(12) + o(15) = 52

  // Test character array with comparison
  char comp_str1[4] = "ABC";
  char comp_str2[4] = "ABD";
  int comparison_result = 0;

  for (int i = 0; i < 3; i++) {
    if (comp_str1[i] < comp_str2[i]) {
      comparison_result = -1;
      break;
    } else if (comp_str1[i] > comp_str2[i]) {
      comparison_result = 1;
      break;
    }
  }
  // Expected: -1 (ABC < ABD)

  // Test character array with loop
  char loop_str[6] = "Hello";
  int loop_sum = 0;

  for (int i = 0; loop_str[i] != '\0'; i++) {
    loop_sum += loop_str[i] * (i + 1);
  }
  // Expected: H*1 + e*2 + l*3 + l*4 + o*5 = 72 + 202 + 324 + 432 + 555 = 1585

  // Test character array with array indexing
  char index_str[5] = "Test";
  int index_sum = 0;

  for (int i = 0; i < 4; i++) {
    index_sum += index_str[i] + i;
  }
  // Expected: T+0 + e+1 + s+2 + t+3 = 84 + 102 + 117 + 119 = 422

  // Test character array with function-like behavior
  char func_str[5] = "ABCD";
  int func_sum = 0;

  for (int i = 0; i < 4; i++) {
    func_sum += func_str[i] - 'A' + 1;
  }
  // Expected: A(1) + B(2) + C(3) + D(4) = 10

  // Test character array with bitwise operations
  char bit_str[4] = "ABC";
  int bit_sum = 0;

  for (int i = 0; i < 3; i++) {
    bit_sum += bit_str[i] & 0x7F; // Clear high bit
  }
  // Expected: A & 0x7F + B & 0x7F + C & 0x7F = 65 + 66 + 67 = 198

  // Test character array with struct
  struct StringStruct {
    char str[5];
    int length;
  };
  struct StringStruct ss = {"Test", 4};

  int struct_sum = 0;
  for (int i = 0; i < ss.length; i++) {
    struct_sum += ss.str[i];
  }
  // Expected: T + e + s + t = 84 + 101 + 115 + 116 = 416

  // Test character array with pointer
  char *ptr_str = "Pointer";
  int ptr_sum = 0;

  for (int i = 0; ptr_str[i] != '\0'; i++) {
    ptr_sum += ptr_str[i];
  }
  // Expected: P + o + i + n + t + e + r = 80 + 111 + 105 + 110 + 116 + 101 +
  // 114 = 737

  // Test character array with complex expressions
  char complex_str[6] = "Hello";
  int complex_sum = 0;

  for (int i = 0; complex_str[i] != '\0'; i++) {
    complex_sum += (complex_str[i] - 'A' + 1) * (i + 1);
  }
  // Expected: H(8)*1 + e(5)*2 + l(12)*3 + l(12)*4 + o(15)*5 = 8 + 10 + 36 + 48
  // + 75 = 177

  // Test character array with nested loops
  char nested_str[4] = "ABC";
  int nested_sum = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j <= i; j++) {
      nested_sum += nested_str[j];
    }
  }
  // Expected: A + (A+B) + (A+B+C) = 65 + (65+66) + (65+66+67) = 65 + 131 + 198
  // = 394

  // Test character array with conditional arithmetic
  char cond_arith_str[5] = "Test";
  int cond_arith_sum = 0;

  for (int i = 0; i < 4; i++) {
    if (cond_arith_str[i] >= 'A' && cond_arith_str[i] <= 'Z') {
      cond_arith_sum += cond_arith_str[i] - 'A' + 1;
    } else {
      cond_arith_sum += cond_arith_str[i] - 'a' + 1;
    }
  }
  // Expected: T(20) + e(5) + s(19) + t(20) = 64

  // Verify results
  if (char_sum1 != 500)
    return 1;
  if (char_sum2 != 520)
    return 2;
  if (literal_sum != 416)
    return 3;
  if (alpha_sum != 270)
    return 4;
  if (conditional_sum != 52)
    return 5;
  if (comparison_result != -1)
    return 6;
  if (loop_sum != 1585)
    return 7;
  if (index_sum != 422)
    return 8;
  if (func_sum != 10)
    return 9;
  if (bit_sum != 198)
    return 10;
  if (struct_sum != 416)
    return 11;
  if (ptr_sum != 737)
    return 12;
  if (complex_sum != 177)
    return 13;
  if (nested_sum != 394)
    return 14;
  if (cond_arith_sum != 64)
    return 15;

  // Test character array with edge cases
  char edge_str[1] = {'A'};
  int edge_sum = edge_str[0];

  if (edge_sum != 65)
    return 16; // 'A' = 65

  // Test character array with empty string
  char empty_str[1] = {'\0'};
  int empty_sum = 0;

  for (int i = 0; empty_str[i] != '\0'; i++) {
    empty_sum += empty_str[i];
  }

  if (empty_sum != 0)
    return 17;

  return 0; // All tests passed
}