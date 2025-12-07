struct __attribute__((aligned(8))) AlignedStruct {
  char a;
  int b;
  char c;
};

struct __attribute__((aligned(16))) AlignedStruct16 {
  char a;
  double b;
  int c;
};

int main() {
  struct AlignedStruct aligned = {'A', 42, 'B'};
  struct AlignedStruct16 aligned16 = {'X', 3.14, 100};

  if (aligned.a != 'A')
    return 1;
  if (aligned.b != 42)
    return 1;
  if (aligned.c != 'B')
    return 1;

  if (aligned16.a != 'X')
    return 1;
  if (aligned16.b < 3.13 || aligned16.b > 3.15)
    return 1;
  if (aligned16.c != 100)
    return 1;

  return 0;
}