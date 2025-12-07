enum color { RED = 1, GREEN = 2, BLUE = 4 };

struct pixel {
  enum color c : 3;
  unsigned int intensity : 5;
};

int main(void) {
  struct pixel p = {RED, 17};
  return (p.c == RED && p.intensity == 17) ? 0 : 1;
}
