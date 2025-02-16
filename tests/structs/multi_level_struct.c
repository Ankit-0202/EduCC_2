struct Level1 {
  int x;
};

struct Level2 {
  struct Level1 l1;
  int y;
};

struct Level3 {
  struct Level2 l2;
  int z;
};

int main() {
  struct Level3 s;
  s.l2.l1.x = 1;
  s.l2.y = 2;
  s.z = 3;
  // Return sum: 1 + 2 + 3 = 6.
  return s.l2.l1.x + s.l2.y + s.z - 6; // Expected: 0
}
