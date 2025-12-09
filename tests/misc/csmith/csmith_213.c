// Options:   --seed 300213 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_213.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  uint32_t f0;
};

union U3 {
  int64_t f0;
};

static int16_t g_7[2][1] = {{0xC371L}, {0xC371L}};
static const struct S1 g_15 = {18446744073709551615UL};
static int32_t g_17 = (-4L);
static int32_t *g_16[2][1] = {{&g_17}, {&g_17}};
static volatile union U3 *g_19 = (void *)0;
static volatile union U3 **volatile g_20[1] = {&g_19};
static volatile union U3 g_22 = {0x8E5034859BB7A140LL};
static int32_t *volatile g_24 = &g_17;

static uint32_t func_1(void);
static int32_t *func_2(uint64_t p_3, uint64_t p_4, union U3 p_5, uint32_t p_6);
static int32_t func_11(const int16_t p_12, uint64_t p_13);

static uint32_t func_1(void) {
  int32_t l_8 = 0L;
  union U3 l_9 = {8L};
  int8_t l_10 = 0x8BL;
  int32_t *l_25 = (void *)0;
  l_25 = func_2(g_7[0][0], l_8, l_9, l_10);
  return g_15.f0;
}

static int32_t *func_2(uint64_t p_3, uint64_t p_4, union U3 p_5, uint32_t p_6) {
  int32_t *l_18 = (void *)0;
  (*g_24) = func_11(p_5.f0, (!(g_15, ((g_16[0][0] = g_16[1][0]) != l_18))));
  return &g_17;
}

static int32_t func_11(const int16_t p_12, uint64_t p_13) {
  volatile union U3 *l_21 = &g_22;
  int32_t l_23 = (-1L);
  for (p_13 = 0; (p_13 <= 0); p_13 += 1) {
    l_21 = g_19;
    for (g_17 = 0; (g_17 <= 0); g_17 += 1) {
      int i, j;
      if (p_13)
        break;
    }
  }
  return l_23;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_7[i][j];
    }
  }
  csmith_sink_ = g_15.f0;
  csmith_sink_ = g_17;
  csmith_sink_ = g_22.f0;
  platform_main_end(0, 0);
  return 0;
}
