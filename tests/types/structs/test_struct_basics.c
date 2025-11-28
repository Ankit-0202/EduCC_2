/*
 * Test: Basic struct operations
 * Purpose: Verify that struct declaration, member access and manipulation work
 * correctly Expected Behavior: Structs handle member storage, access and
 * manipulation properly Test Cases:
 *   - Struct declaration and definition
 *   - Member access and modification
 *   - Nested structs
 *   - Struct arrays
 *   - Struct with different member types
 *   - Struct assignment
 * Dependencies: Basic integer, float and char types
 */

// Simple struct
struct Point {
  int x;
  int y;
};

// Struct with different types
struct Person {
  char name[20];
  int age;
  float height;
};

// Nested struct
struct Rectangle {
  struct Point top_left;
  struct Point bottom_right;
};

// Struct with array member
struct ArrayStruct {
  int numbers[5];
  char letters[3];
};

int main() {
  // Test basic struct
  struct Point p1;
  p1.x = 10;
  p1.y = 20;
  int point_sum = p1.x + p1.y;

  // Test struct initialization
  struct Point p2 = {5, 15};
  int point_sum2 = p2.x + p2.y;

  // Test struct with different types
  struct Person person1;
  person1.age = 25;
  person1.height = 1.75f;
  person1.name[0] = 'J';
  person1.name[1] = 'o';
  person1.name[2] = 'h';
  person1.name[3] = 'n';
  person1.name[4] = '\0';

  int person_test = person1.age + (int)person1.height;
  int name_test = person1.name[0] + person1.name[1];

  // Test nested struct
  struct Rectangle rect;
  rect.top_left.x = 0;
  rect.top_left.y = 0;
  rect.bottom_right.x = 10;
  rect.bottom_right.y = 10;

  int rect_area = (rect.bottom_right.x - rect.top_left.x) *
                  (rect.bottom_right.y - rect.top_left.y);

  // Test struct array
  struct Point points[3];
  for (int i = 0; i < 3; i++) {
    points[i].x = i * 2;
    points[i].y = i * 3;
  }

  int array_sum = 0;
  for (int i = 0; i < 3; i++) {
    array_sum += points[i].x + points[i].y;
  }
  // Expected: (0+0) + (2+3) + (4+6) = 15

  // Test struct with array member
  struct ArrayStruct arr_struct;
  for (int i = 0; i < 5; i++) {
    arr_struct.numbers[i] = i + 1;
  }
  arr_struct.letters[0] = 'A';
  arr_struct.letters[1] = 'B';
  arr_struct.letters[2] = 'C';

  int array_struct_sum = 0;
  for (int i = 0; i < 5; i++) {
    array_struct_sum += arr_struct.numbers[i];
  }
  int letters_sum =
      arr_struct.letters[0] + arr_struct.letters[1] + arr_struct.letters[2];

  // Test struct assignment
  struct Point p3 = p1;
  int assignment_test = p3.x + p3.y;

  // Test struct with conditional
  struct Point p4 = {15, 25};
  int conditional_sum = 0;
  if (p4.x > 10) {
    conditional_sum += p4.x;
  }
  if (p4.y > 20) {
    conditional_sum += p4.y;
  }

  // Test struct member modification
  struct Point p5 = {1, 2};
  p5.x *= 3;
  p5.y += 5;
  int modification_test = p5.x + p5.y;

  // Test struct with pointer
  struct Point *ptr = &p1;
  int pointer_test = ptr->x + ptr->y;

  // Test struct with function call simulation
  struct Point p6 = {100, 200};
  int function_sim = p6.x + p6.y;

  // Verify results
  if (point_sum != 30)
    return 1; // 10 + 20 = 30
  if (point_sum2 != 20)
    return 2; // 5 + 15 = 20
  if (person_test != 26)
    return 3; // 25 + 1 = 26
  if (name_test != 155)
    return 4; // 'J'(74) + 'o'(111) = 185
  if (rect_area != 100)
    return 5; // 10 * 10 = 100
  if (array_sum != 15)
    return 6; // (0+0) + (2+3) + (4+6) = 15
  if (array_struct_sum != 15)
    return 7; // 1+2+3+4+5 = 15
  if (letters_sum != 198)
    return 8; // 'A'(65) + 'B'(66) + 'C'(67) = 198
  if (assignment_test != 30)
    return 9; // 10 + 20 = 30
  if (conditional_sum != 40)
    return 10; // 15 + 25 = 40
  if (modification_test != 10)
    return 11; // (1*3) + (2+5) = 3 + 7 = 10
  if (pointer_test != 30)
    return 12; // 10 + 20 = 30
  if (function_sim != 300)
    return 13; // 100 + 200 = 300

  // Test struct with complex expressions
  struct Point p7 = {8, 12};
  int complex_test = p7.x * p7.y + p7.x - p7.y;
  // Expected: 8 * 12 + 8 - 12 = 96 + 8 - 12 = 92

  if (complex_test != 92)
    return 14;

  return 0; // All tests passed
}