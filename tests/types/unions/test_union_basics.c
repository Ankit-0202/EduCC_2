/*
 * Test: Basic union operations
 * Purpose: Verify that union declaration, member access and memory sharing work
 * correctly Expected Behavior: Unions should share memory between members and
 * handle type conversions properly Test Cases:
 *   - Union declaration and member access
 *   - Memory sharing between members
 *   - Union with different member types
 *   - Union arrays
 *   - Union assignment
 *   - Union with struct members
 * Dependencies: Basic integer, float and char types
 */

// Simple union
union Data {
  int i;
  float f;
  char c;
};

// Union with array members
union ArrayUnion {
  int int_array[4];
  char char_array[16];
  float float_array[4];
};

// Union with struct members
struct Point {
  int x;
  int y;
};

union Shape {
  struct Point point;
  int coordinates[2];
};

// Union with different sized members
union MixedUnion {
  char c;
  short s;
  int i;
  long l;
};

int main() {
  int result = 0;

  // Test basic union
  union Data data;

  // Test integer member
  data.i = 42;
  int int_test = data.i;

  // Test float member (overwrites int)
  data.f = 3.14f;
  float float_test = data.f;
  int overwritten_int = data.i; // Should be reinterpreted as int

  // Test char member (overwrites float)
  data.c = 'A';
  char char_test = data.c;
  int overwritten_float = data.i; // Should be reinterpreted as int

  // Test union with array members
  union ArrayUnion arr_union;

  // Initialize int array
  for (int i = 0; i < 4; i++) {
    arr_union.int_array[i] = i + 1;
  }

  int array_sum = 0;
  for (int i = 0; i < 4; i++) {
    array_sum += arr_union.int_array[i];
  }
  // Expected: 1 + 2 + 3 + 4 = 10

  // Test char array access (should share memory with int array)
  int char_sum = 0;
  for (int i = 0; i < 4; i++) {
    char_sum += arr_union.char_array[i];
  }

  // Test union with struct
  union Shape shape;
  shape.point.x = 10;
  shape.point.y = 20;

  int point_sum = shape.point.x + shape.point.y;
  int coord_sum = shape.coordinates[0] + shape.coordinates[1];

  // Test mixed union
  union MixedUnion mixed;
  mixed.c = 'X';
  char mixed_char = mixed.c;

  mixed.s = 12345;
  short mixed_short = mixed.s;

  mixed.i = 987654321;
  int mixed_int = mixed.i;

  // Test union assignment
  union Data data1, data2;
  data1.i = 100;
  data2 = data1;
  int assignment_test = data2.i;

  // Test union with conditional
  union Data cond_data;
  cond_data.i = 50;

  int conditional_sum = 0;
  if (cond_data.i > 25) {
    conditional_sum += cond_data.i;
  }

  cond_data.f = 2.5f;
  if (cond_data.f > 2.0f) {
    conditional_sum += (int)cond_data.f;
  }

  // Test union array
  union Data data_array[3];
  data_array[0].i = 1;
  data_array[1].f = 2.0f;
  data_array[2].c = 'C';

  int array_union_sum = 0;
  array_union_sum += data_array[0].i;
  array_union_sum += (int)data_array[1].f;
  array_union_sum += data_array[2].c;

  // Test union with pointer
  union Data *data_ptr = &data1;
  int pointer_test = data_ptr->i;

  // Test union with function-like behavior
  union Data create_data(int value) {
    union Data d;
    d.i = value;
    return d;
  }

  union Data func_data = create_data(999);
  int func_test = func_data.i;

  // Test union with arithmetic
  union Data arith_data;
  arith_data.i = 10;
  int arith_result = arith_data.i * 2 + 5;

  // Verify results
  if (int_test != 42)
    return 1;
  if (float_test < 3.13f || float_test > 3.15f)
    return 2;
  if (char_test != 'A')
    return 3;
  if (array_sum != 10)
    return 4;
  if (point_sum != 30)
    return 5; // 10 + 20 = 30
  if (coord_sum != 30)
    return 6; // Should be same as point_sum
  if (mixed_char != 'X')
    return 7;
  if (mixed_short != 12345)
    return 8;
  if (mixed_int != 987654321)
    return 9;
  if (assignment_test != 100)
    return 10;
  if (conditional_sum != 52)
    return 11; // 50 + 2 = 52
  if (array_union_sum != 70)
    return 12; // 1 + 2 + 67 = 70
  if (pointer_test != 100)
    return 13;
  if (func_test != 999)
    return 14;
  if (arith_result != 25)
    return 15; // 10 * 2 + 5 = 25

  // Test union with complex expressions
  union Data complex_data;
  complex_data.i = 5;
  int complex_test = complex_data.i * complex_data.i + complex_data.i;
  // Expected: 5 * 5 + 5 = 30

  if (complex_test != 30)
    return 16;

  return 0; // All tests passed
}