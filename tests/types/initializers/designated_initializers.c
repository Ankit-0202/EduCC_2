struct Point {
  int x;
  int y;
  char label;
};

struct Rectangle {
  struct Point top_left;
  struct Point bottom_right;
  int color;
};

int main() {
  struct Point p1 = {.x = 10, .y = 20, .label = 'A'};
  struct Point p2 = {.label = 'B', .x = 30, .y = 40};

  if (p1.x != 10)
    return 1;
  if (p1.y != 20)
    return 1;
  if (p1.label != 'A')
    return 1;

  if (p2.x != 30)
    return 1;
  if (p2.y != 40)
    return 1;
  if (p2.label != 'B')
    return 1;

  struct Rectangle rect = {.top_left = {.x = 0, .y = 0, .label = 'T'},
                           .bottom_right = {.x = 100, .y = 50, .label = 'B'},
                           .color = 255};

  if (rect.top_left.x != 0)
    return 1;
  if (rect.top_left.y != 0)
    return 1;
  if (rect.top_left.label != 'T')
    return 1;

  if (rect.bottom_right.x != 100)
    return 1;
  if (rect.bottom_right.y != 50)
    return 1;
  if (rect.bottom_right.label != 'B')
    return 1;

  if (rect.color != 255)
    return 1;

  return 0;
}