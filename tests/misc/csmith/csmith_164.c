// Options:   --seed 200164 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_164.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2 = (-6L);
static const int64_t g_11 = (-1L);
static const int64_t *g_10 = &g_11;
static int64_t *g_12[1][2] = {{(void *)0, (void *)0}};
static int32_t g_16 = (-4L);
static int32_t *g_18 = &g_16;
static int32_t **volatile g_17 = &g_18;

static uint32_t func_1(void);
static uint32_t func_5(const int64_t *p_6, uint32_t p_7, const int64_t *p_8,
                       int64_t *p_9);

static uint32_t func_1(void) {
  int64_t *l_3 = (void *)0;
  int32_t l_4 = 1L;
  int32_t l_14 = (-1L);
  int32_t *l_15 = &g_16;
  (*l_15) &= (0UL && ((l_4 = g_2) >=
                      ((func_5(l_3, g_2, g_10, g_12[0][0]) & l_14) ^ g_2)));
  (*g_17) = &g_16;
  return g_2;
}

static uint32_t func_5(const int64_t *p_6, uint32_t p_7, const int64_t *p_8,
                       int64_t *p_9) {
  int8_t l_13 = (-7L);
  return l_13;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_11;
  csmith_sink_ = g_16;
  platform_main_end(0, 0);
  return 0;
}
