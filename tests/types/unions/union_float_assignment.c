union Data {
  int i;
  float f;
  char str[20];
};

int main() {
  union Data data;

  data.f = 3.14;
  if (data.f < 3.13 || data.f > 3.15)
    return 1;

  return 0;
}