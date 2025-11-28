/*
 * Test: Switch statements and case handling
 * Purpose: Verify that switch statements work correctly with proper case
 * matching and fallthrough Expected Behavior: Switch statements should execute
 * the correct case and handle fallthrough properly Test Cases:
 *   - Basic switch with integer cases
 *   - Switch with char cases
 *   - Switch with fallthrough
 *   - Switch with default case
 *   - Nested switch statements
 *   - Switch with complex expressions
 * Dependencies: Basic integer and char types, control flow
 */

int main() {
  int result = 0;

  // Test basic switch with integer
  int switch_value = 2;
  int basic_result = 0;

  switch (switch_value) {
  case 1:
    basic_result = 10;
    break;
  case 2:
    basic_result = 20;
    break;
  case 3:
    basic_result = 30;
    break;
  default:
    basic_result = 0;
    break;
  }

  // Test switch with char
  char char_value = 'B';
  int char_result = 0;

  switch (char_value) {
  case 'A':
    char_result = 1;
    break;
  case 'B':
    char_result = 2;
    break;
  case 'C':
    char_result = 3;
    break;
  default:
    char_result = 0;
    break;
  }

  // Test switch with fallthrough
  int fallthrough_value = 1;
  int fallthrough_result = 0;

  switch (fallthrough_value) {
  case 1:
    fallthrough_result += 1;
    // Fallthrough to case 2
  case 2:
    fallthrough_result += 2;
    break;
  case 3:
    fallthrough_result += 3;
    break;
  default:
    fallthrough_result += 0;
    break;
  }

  // Test switch with default case
  int default_value = 99;
  int default_result = 0;

  switch (default_value) {
  case 1:
    default_result = 10;
    break;
  case 2:
    default_result = 20;
    break;
  default:
    default_result = 100;
    break;
  }

  // Test nested switch
  int outer_value = 1;
  int inner_value = 2;
  int nested_result = 0;

  switch (outer_value) {
  case 1:
    switch (inner_value) {
    case 1:
      nested_result = 11;
      break;
    case 2:
      nested_result = 12;
      break;
    default:
      nested_result = 10;
      break;
    }
    break;
  case 2:
    nested_result = 20;
    break;
  default:
    nested_result = 0;
    break;
  }

  // Test switch with expressions
  int expr_value = 5;
  int expr_result = 0;

  switch (expr_value + 1) {
  case 6:
    expr_result = 60;
    break;
  case 7:
    expr_result = 70;
    break;
  default:
    expr_result = 0;
    break;
  }

  // Test switch with multiple fallthrough
  int multi_value = 1;
  int multi_result = 0;

  switch (multi_value) {
  case 1:
    multi_result += 1;
  case 2:
    multi_result += 2;
  case 3:
    multi_result += 3;
    break;
  case 4:
    multi_result += 4;
    break;
  default:
    multi_result += 0;
    break;
  }

  // Test switch with variables
  int var1 = 3;
  int var2 = 4;
  int var_result = 0;

  switch (var1) {
  case 1:
    var_result = var2 * 1;
    break;
  case 2:
    var_result = var2 * 2;
    break;
  case 3:
    var_result = var2 * 3;
    break;
  default:
    var_result = 0;
    break;
  }

  // Test switch with conditional
  int cond_value = 2;
  int cond_result = 0;

  if (cond_value > 0) {
    switch (cond_value) {
    case 1:
      cond_result = 100;
      break;
    case 2:
      cond_result = 200;
      break;
    default:
      cond_result = 0;
      break;
    }
  }

  // Test switch with arithmetic in cases
  int arith_value = 10;
  int arith_result = 0;

  switch (arith_value / 2) {
  case 5:
    arith_result = 50;
    break;
  case 6:
    arith_result = 60;
    break;
  default:
    arith_result = 0;
    break;
  }

  // Test switch with enum
  enum TestEnum { ONE = 1, TWO = 2, THREE = 3 };
  enum TestEnum enum_value = TWO;
  int enum_result = 0;

  switch (enum_value) {
  case ONE:
    enum_result = 1;
    break;
  case TWO:
    enum_result = 2;
    break;
  case THREE:
    enum_result = 3;
    break;
  default:
    enum_result = 0;
    break;
  }

  // Verify results
  if (basic_result != 20)
    return 1; // case 2
  if (char_result != 2)
    return 2; // case 'B'
  if (fallthrough_result != 3)
    return 3; // 1 + 2 (fallthrough)
  if (default_result != 100)
    return 4; // default case
  if (nested_result != 12)
    return 5; // outer case 1, inner case 2
  if (expr_result != 60)
    return 6; // 5 + 1 = 6
  if (multi_result != 6)
    return 7; // 1 + 2 + 3 (multiple fallthrough)
  if (var_result != 12)
    return 8; // 3 * 4 = 12
  if (cond_result != 200)
    return 9; // case 2
  if (arith_result != 50)
    return 10; // 10 / 2 = 5
  if (enum_result != 2)
    return 11; // TWO = 2

  // Test switch with complex expressions
  int complex_value = 8;
  int complex_result = 0;

  switch (complex_value % 3) {
  case 0:
    complex_result = complex_value * 2;
    break;
  case 1:
    complex_result = complex_value + 10;
    break;
  case 2:
    complex_result = complex_value - 5;
    break;
  default:
    complex_result = 0;
    break;
  }

  if (complex_result != 3)
    return 12; // 8 % 3 = 2, so 8 - 5 = 3

  return 0; // All tests passed
}