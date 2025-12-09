struct Point {
  int x;
  int y;
};

struct Rectangle {
  struct Point top_left;
  struct Point bottom_right;
  int area;
};

int calculate_area(struct Rectangle *rect) {
  int width = rect->bottom_right.x - rect->top_left.x;
  int height = rect->bottom_right.y - rect->top_left.y;
  rect->area = width * height;
  return rect->area;
}

int main() {
  struct Point p1 = {10, 20};
  struct Point *ptr = &p1;

  if (ptr->x != 10)
    return 1;
  if (ptr->y != 20)
    return 1;

  ptr->x = 30;
  ptr->y = 40;

  if (p1.x != 30)
    return 1;
  if (p1.y != 40)
    return 1;

  struct Rectangle rect = {{0, 0}, {10, 5}, 0};
  struct Rectangle *rect_ptr = &rect;

  int area = calculate_area(rect_ptr);
  if (area != 50)
    return 1; // 10 * 5 = 50
  if (rect.area != 50)
    return 1;

  return 0;
}