// Options:   --seed 300261 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_261.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_5 = (-2L);
static int32_t *g_4[3][3] = {
    {&g_5, (void *)0, &g_5}, {&g_5, (void *)0, &g_5}, {&g_5, (void *)0, &g_5}};

static int16_t func_1(void);
static int32_t func_2(int32_t *p_3);

static int16_t func_1(void) {
  uint32_t l_11 = 0x288586FDL;
  int32_t **l_12 = &g_4[1][1];
  (*l_12) = (((func_2(g_4[0][0]) <= ((l_11 | g_5) & l_11)) == 4UL), &g_5);
  return g_5;
}

static int32_t func_2(int32_t *p_3) {
  int32_t *l_6 = &g_5;
  int32_t *l_7[2];
  uint16_t l_8 = 0x4163L;
  int i;
  for (i = 0; i < 2; i++)
    l_7[i] = &g_5;
  l_8--;
  return (*l_6);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_5;
  platform_main_end(0, 0);
  return 0;
}
