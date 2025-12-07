extern int global_x;
extern char global_c;
extern float global_f;

int get_global_x() { return global_x; }

char get_global_c() { return global_c; }

float get_global_f() { return global_f; }

int main() {
  if (get_global_x() != 100)
    return 1;
  if (get_global_c() != 'E')
    return 1;
  if (get_global_f() < 5.9 || get_global_f() > 6.1)
    return 1;

  return 0;
}