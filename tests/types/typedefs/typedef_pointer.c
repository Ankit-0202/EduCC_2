typedef int *IntPtr;
typedef char *CharPtr;
typedef float *FloatPtr;

int main() {
  int x = 20;
  char c = 'G';
  float f = 7.2;

  IntPtr ptr1 = &x;
  CharPtr ptr2 = &c;
  FloatPtr ptr3 = &f;

  if (*ptr1 != 20)
    return 1;
  if (*ptr2 != 'G')
    return 1;
  if (*ptr3 < 7.1 || *ptr3 > 7.3)
    return 1;

  *ptr1 = 30;
  *ptr2 = 'H';
  *ptr3 = 8.5;

  if (x != 30)
    return 1;
  if (c != 'H')
    return 1;
  if (f < 8.4 || f > 8.6)
    return 1;

  return 0;
}