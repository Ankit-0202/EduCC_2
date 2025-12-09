// Options:   --seed 200158 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_158.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint32_t f0;
  int32_t f1;
};

static uint64_t g_8 = 0x7207182B4746A1C1LL;
static int32_t g_11 = 0xFE81720DL;
static struct S0 g_14 = {4294967295UL, -1L};

static int32_t func_1(void);
static struct S0 func_2(uint32_t p_3, uint64_t p_4, float p_5, int8_t p_6);

static int32_t func_1(void) {
  int64_t l_7[4][4] = {{(-1L), 0L, 0L, (-1L)},
                       {(-1L), 0L, 0L, (-1L)},
                       {(-1L), 0L, 0L, (-1L)},
                       {(-1L), 0L, 0L, (-1L)}};
  int32_t l_9[4][1];
  struct S0 *l_15 = &g_14;
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 1; j++)
      l_9[i][j] = 0x61FBC9FAL;
  }
  (*l_15) = func_2((l_7[2][1] |= 4UL),
                   ((g_8 < (g_8, 0xB583DC0E3E763161LL)) ^ g_8), l_9[3][0], g_8);
  return g_14.f1;
}

static struct S0 func_2(uint32_t p_3, uint64_t p_4, float p_5, int8_t p_6) {
  int32_t *l_10 = &g_11;
  int32_t **l_12[3];
  int32_t *l_13 = &g_11;
  int i;
  for (i = 0; i < 3; i++)
    l_12[i] = &l_10;
  l_13 = l_10;
  return g_14;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_8;
  csmith_sink_ = g_11;
  csmith_sink_ = g_14.f0;
  csmith_sink_ = g_14.f1;
  platform_main_end(0, 0);
  return 0;
}
