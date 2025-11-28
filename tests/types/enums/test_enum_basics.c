/*
 * Test: Basic enum operations
 * Purpose: Verify that enum declaration, value assignment and arithmetic work
 * correctly Expected Behavior: Enums should behave like integers with proper
 * value assignment and arithmetic Test Cases:
 *   - Basic enum declaration
 *   - Enum with explicit values
 *   - Enum arithmetic
 *   - Enum in expressions
 *   - Enum with gaps in values
 *   - Enum comparison
 * Dependencies: Basic integer types, arithmetic operations
 */

// Basic enum
enum Color { RED, GREEN, BLUE, YELLOW };

// Enum with explicit values
enum Status { OK = 0, ERROR = 1, WARNING = 2, INFO = 3 };

// Enum with gaps
enum Flags {
  FLAG_NONE = 0,
  FLAG_READ = 1,
  FLAG_WRITE = 2,
  FLAG_EXECUTE = 4,
  FLAG_ALL = 7
};

// Enum with negative values
enum Direction { NORTH = -1, SOUTH = 1, EAST = 2, WEST = -2 };

int main() {
  int result = 0;

  // Test basic enum values
  enum Color c1 = RED;
  enum Color c2 = GREEN;
  enum Color c3 = BLUE;
  enum Color c4 = YELLOW;

  int color_sum = c1 + c2 + c3 + c4;
  // Expected: 0 + 1 + 2 + 3 = 6

  // Test enum with explicit values
  enum Status s1 = OK;
  enum Status s2 = ERROR;
  enum Status s3 = WARNING;
  enum Status s4 = INFO;

  int status_sum = s1 + s2 + s3 + s4;
  // Expected: 0 + 1 + 2 + 3 = 6

  // Test enum arithmetic
  enum Color color_arithmetic = RED + GREEN;       // 0 + 1 = 1
  enum Status status_arithmetic = ERROR * WARNING; // 1 * 2 = 2

  // Test enum comparison
  int comparison_result = 0;
  if (RED < GREEN)
    comparison_result += 1;
  if (GREEN < BLUE)
    comparison_result += 2;
  if (BLUE < YELLOW)
    comparison_result += 4;
  if (OK == 0)
    comparison_result += 8;
  if (ERROR == 1)
    comparison_result += 16;

  // Test enum with gaps
  enum Flags f1 = FLAG_NONE;
  enum Flags f2 = FLAG_READ;
  enum Flags f3 = FLAG_WRITE;
  enum Flags f4 = FLAG_EXECUTE;
  enum Flags f5 = FLAG_ALL;

  int flags_sum = f1 + f2 + f3 + f4 + f5;
  // Expected: 0 + 1 + 2 + 4 + 7 = 14

  // Test enum with negative values
  enum Direction d1 = NORTH;
  enum Direction d2 = SOUTH;
  enum Direction d3 = EAST;
  enum Direction d4 = WEST;

  int direction_sum = d1 + d2 + d3 + d4;
  // Expected: -1 + 1 + 2 + (-2) = 0

  // Test enum in expressions
  int expr1 = (RED + GREEN) * BLUE;   // (0 + 1) * 2 = 2
  int expr2 = ERROR + WARNING + INFO; // 1 + 2 + 3 = 6
  int expr3 = FLAG_READ | FLAG_WRITE; // 1 | 2 = 3

  // Test enum assignment
  enum Color assigned_color = RED;
  assigned_color = GREEN;
  int assignment_test = assigned_color;

  // Test enum with conditional
  int conditional_sum = 0;
  if (RED == 0)
    conditional_sum += 1;
  if (GREEN == 1)
    conditional_sum += 2;
  if (BLUE == 2)
    conditional_sum += 4;
  if (YELLOW == 3)
    conditional_sum += 8;

  // Test enum with switch
  int switch_result = 0;
  enum Color switch_color = GREEN;
  switch (switch_color) {
  case RED:
    switch_result = 1;
    break;
  case GREEN:
    switch_result = 2;
    break;
  case BLUE:
    switch_result = 3;
    break;
  case YELLOW:
    switch_result = 4;
    break;
  }

  // Test enum with function-like behavior
  enum Status get_status(int value) {
    if (value == 0)
      return OK;
    if (value == 1)
      return ERROR;
    if (value == 2)
      return WARNING;
    return INFO;
  }

  enum Status func_test1 = get_status(0);
  enum Status func_test2 = get_status(1);
  enum Status func_test3 = get_status(2);
  enum Status func_test4 = get_status(3);

  int func_sum = func_test1 + func_test2 + func_test3 + func_test4;
  // Expected: 0 + 1 + 2 + 3 = 6

  // Verify results
  if (color_sum != 6)
    return 1;
  if (status_sum != 6)
    return 2;
  if (color_arithmetic != 1)
    return 3;
  if (status_arithmetic != 2)
    return 4;
  if (comparison_result != 31)
    return 5; // 1 + 2 + 4 + 8 + 16 = 31
  if (flags_sum != 14)
    return 6;
  if (direction_sum != 0)
    return 7;
  if (expr1 != 2)
    return 8;
  if (expr2 != 6)
    return 9;
  if (expr3 != 3)
    return 10;
  if (assignment_test != 1)
    return 11;
  if (conditional_sum != 15)
    return 12; // 1 + 2 + 4 + 8 = 15
  if (switch_result != 2)
    return 13;
  if (func_sum != 6)
    return 14;

  // Test enum with array
  enum Color color_array[4] = {RED, GREEN, BLUE, YELLOW};
  int array_sum = 0;
  for (int i = 0; i < 4; i++) {
    array_sum += color_array[i];
  }
  if (array_sum != 6)
    return 15;

  return 0; // All tests passed
}