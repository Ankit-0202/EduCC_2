#define A 0
#define B 1

#if A
int unused() { return 0; }
#elif B
#if 0
  int never() { return -1; }
#else
int main() { return 1; }
#endif
#else
int main() { return 2; }
#endif
