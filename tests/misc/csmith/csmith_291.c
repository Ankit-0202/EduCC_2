// Options:   --seed 300291 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_291.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint32_t g_2 = 0xEF20FE6EL;
static uint32_t g_4 = 0x1DBECCCEL;
static int32_t g_9 = 0x4F147909L;
static uint16_t g_12 = 0x2083L;
static int32_t *volatile g_16 = (void *)0;

static uint64_t func_1(void);
static int32_t func_5(int32_t p_6);

static uint64_t func_1(void) {
  uint32_t *l_3 = &g_4;
  int32_t l_7 = (-1L);
  int32_t *l_17[1];
  int i;
  for (i = 0; i < 1; i++)
    l_17[i] = &l_7;
  g_9 = ((((*l_3) ^= g_2) | func_5(l_7)), l_7);
  return g_12;
}

static int32_t func_5(int32_t p_6) {
  int32_t *l_8 = &g_9;
  int32_t *l_10 = &g_9;
  int32_t *l_11[3][2];
  int32_t **l_15 = &l_8;
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++)
      l_11[i][j] = &g_9;
  }
  --g_12;
  (*l_15) = (((l_8 != (void *)0) != ((void *)0 == l_8)), (void *)0);
  return p_6;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_4;
  csmith_sink_ = g_9;
  csmith_sink_ = g_12;
  platform_main_end(0, 0);
  return 0;
}
