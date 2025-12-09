// Options:   --seed 100055 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_055.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2 = 1L;
static int32_t g_7 = 0xF6DD8D13L;
static volatile uint64_t g_10 = 1UL;

static int32_t func_1(void);

static int32_t func_1(void) {
  int64_t l_5[3];
  int64_t l_13 = 0x2CB3A3FC4B03E386LL;
  int i;
  for (i = 0; i < 3; i++)
    l_5[i] = 0x5C6F1BF506E60B0CLL;
  for (g_2 = 0; (g_2 >= (-29)); g_2--) {
    int32_t *l_6 = &g_7;
    int32_t *l_8 = &g_7;
    int32_t *l_9[4][2] = {{(void *)0, (void *)0},
                          {(void *)0, (void *)0},
                          {(void *)0, (void *)0},
                          {(void *)0, (void *)0}};
    int i, j;
    g_10++;
  }
  return l_13;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_7;
  csmith_sink_ = g_10;
  platform_main_end(0, 0);
  return 0;
}
