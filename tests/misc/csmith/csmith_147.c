// Options:   --seed 200147 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_147.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint32_t f0;
};

static volatile int32_t g_8 = 0x25CBD945L;
static const int32_t g_10[2] = {0xF1A0734FL, 0xF1A0734FL};
static int32_t g_16 = (-1L);
static int32_t g_25 = 1L;
static int32_t *volatile g_24 = &g_25;
static struct S0 g_26[3][4] = {
    {{4294967293UL}, {4294967293UL}, {4294967293UL}, {4294967293UL}},
    {{4294967293UL}, {4294967293UL}, {4294967293UL}, {4294967293UL}},
    {{4294967293UL}, {4294967293UL}, {4294967293UL}, {4294967293UL}}};
static uint32_t g_30 = 18446744073709551615UL;

static int8_t func_1(void);
static int32_t func_2(uint8_t p_3, uint64_t p_4, uint32_t p_5,
                      const uint16_t p_6, uint16_t p_7);

static int8_t func_1(void) {
  uint32_t l_9 = 4294967291UL;
  uint32_t l_11 = 0x92C5EB20L;
  int32_t *l_17 = &g_16;
  float l_19[4][4];
  int32_t **l_34 = &l_17;
  int32_t *l_36 = &g_16;
  int32_t **l_35 = &l_36;
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      l_19[i][j] = 0x2.15A609p-51;
  }
  if (((*l_17) = func_2((0x69L >= g_8), l_9, l_9, g_10[0], l_11))) {
    int32_t **l_18 = &l_17;
    (*l_18) = &g_16;
    (**l_18) ^= 0L;
  } else {
    uint32_t l_23 = 0UL;
    for (g_16 = 0; (g_16 <= 3); g_16 += 1) {
      int32_t *l_22 = &g_16;
      struct S0 l_27[4] = {
          {4294967295UL}, {4294967295UL}, {4294967295UL}, {4294967295UL}};
      int i;
      (*g_24) = (l_23 = (safe_lshift_func_int8_t_s_u(
                     ((0xD8F2L == ((void *)0 == l_22)), (*l_22)), 2)));
      l_27[3] = g_26[2][0];
    }
    for (g_16 = 0; (g_16 != 6); g_16 = safe_add_func_uint32_t_u_u(g_16, 2)) {
      uint64_t l_31 = 0x8914BE495EE35D5DLL;
      g_30 = (*l_17);
      l_31--;
    }
  }
  (*l_35) = ((*l_34) = &g_16);
  return (*l_17);
}

static int32_t func_2(uint8_t p_3, uint64_t p_4, uint32_t p_5,
                      const uint16_t p_6, uint16_t p_7) {
  uint32_t l_14[3];
  int32_t *l_15 = &g_16;
  int i;
  for (i = 0; i < 3; i++)
    l_14[i] = 0x4DF6F978L;
  (*l_15) = (((((safe_div_func_uint16_t_u_u(
                    (l_14[2] || ((l_14[2] | p_6) != g_10[0])), 8UL)),
                p_7),
               0xC1DAL) < p_5) |
             0x0D1BL);
  return p_3;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_8;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_10[i];
  }
  csmith_sink_ = g_16;
  csmith_sink_ = g_25;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++) {
    }
  }
  csmith_sink_ = g_30;
  platform_main_end(0, 0);
  return 0;
}
