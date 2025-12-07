// Test void pointer casting and usage
int main() {
  int arr[5] = {10, 20, 30, 40, 50};

  // Cast to void pointer
  void *vp = (void *)arr;

  // Cast back to int pointer
  int *ip = (int *)vp;
  if (*ip != 10)
    return 1;
  if (ip[2] != 30)
    return 2;

  // Void pointer with different types
  double d = 3.14;
  void *vp2 = (void *)&d;
  double *dp = (double *)vp2;
  if (*dp < 3.13 || *dp > 3.15)
    return 3;

  // char through void pointer
  char c = 'A';
  void *vp3 = (void *)&c;
  char *cp = (char *)vp3;
  if (*cp != 'A')
    return 4;

  // Array of different types through void pointers
  float farr[3] = {1.0f, 2.0f, 3.0f};
  void *vp4 = (void *)farr;
  float *fp = (float *)vp4;
  if (fp[1] < 1.9f || fp[1] > 2.1f)
    return 5;

  return 0;
}
