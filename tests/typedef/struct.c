int main() {
  typedef struct {
    int x;
  } MyStruct;
  MyStruct s;
  s.x = 100;
  return s.x - 100;
}
