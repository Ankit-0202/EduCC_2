struct item {
  int a;
  int b;
};

int main(void) {
  struct item items[3] = {{1, 2}, {3, 4}, {5, 6}};
  struct item *ptr = items;
  ptr++;
  return (ptr->a == 3 && (ptr + 1)->b == 6) ? 0 : 1;
}
