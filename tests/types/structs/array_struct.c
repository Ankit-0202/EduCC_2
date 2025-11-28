struct Point {
  int x;
  int y;
};
int main() {
  struct Point points[3];
  points[0].x = 10;
  return points[0].x;
}
