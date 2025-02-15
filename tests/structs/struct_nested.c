struct Point {
  int x;
  int y;
};

struct Rectangle {
  struct Point topLeft;
  struct Point bottomRight;
};

int main() {
  struct Rectangle rect;
  rect.topLeft.x = 1;
  rect.topLeft.y = 2;
  rect.bottomRight.x = 3;
  rect.bottomRight.y = 4;

  int sum =
      rect.topLeft.x + rect.topLeft.y + rect.bottomRight.x + rect.bottomRight.y;
  return sum; // Returns 10
}