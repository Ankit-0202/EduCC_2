typedef struct {
  int x;
  char c;
  float f;
} Point;

typedef struct {
  int width;
  int height;
} Rectangle;

int main() {
  Point p1 = {10, 'I', 2.5};
  Rectangle r1 = {5, 8};

  if (p1.x != 10)
    return 1;
  if (p1.c != 'I')
    return 1;
  if (p1.f < 2.4 || p1.f > 2.6)
    return 1;

  if (r1.width != 5)
    return 1;
  if (r1.height != 8)
    return 1;

  Point p2;
  p2.x = 20;
  p2.c = 'J';
  p2.f = 4.0;

  if (p2.x != 20)
    return 1;
  if (p2.c != 'J')
    return 1;
  if (p2.f < 3.9 || p2.f > 4.1)
    return 1;

  return 0;
}