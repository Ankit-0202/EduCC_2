struct Data {
  char flag;
  int value;
};

int main() {
  struct Data d;
  d.flag = 'y';
  d.value = 42;

  if (d.flag == 'y') {
    return d.value; // Returns 42
  } else {
    return 0;
  }
}