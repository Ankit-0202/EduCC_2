// Options:   --seed 200192 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_192.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U2 {
  const uint32_t f0;
};

static uint16_t g_4 = 1UL;
static int32_t g_9 = 0x58E17C10L;
static int32_t *volatile g_8 = &g_9;
static union U2 g_13 = {0xC67EE39FL};
static int32_t g_20 = 0L;
static int16_t g_34 = 0x3933L;
static volatile uint16_t g_36 = 0xC3F1L;
static int32_t g_42 = 1L;

static int8_t func_1(void);
static int8_t func_10(union U2 p_11, int32_t *p_12);

static int8_t func_1(void) {
  int32_t l_7[4][3] = {{0x55950707L, 0L, 0x64FD9E2AL},
                       {0x9EDBDA7FL, 0L, 0x9EDBDA7FL},
                       {(-10L), 0x55950707L, 0x64FD9E2AL},
                       {(-10L), (-10L), 0x55950707L}};
  int32_t *l_41 = &g_42;
  int i, j;
  (*g_8) = ((safe_div_func_float_f_f(
                0xB.4E1265p-68,
                (g_4 < (safe_sub_func_float_f_f(0x7.AB3921p+71, l_7[2][0]))))),
            l_7[2][0]);
  (*l_41) ^= (func_10(g_13, &g_9) != g_13.f0);
  return (*l_41);
}

static int8_t func_10(union U2 p_11, int32_t *p_12) {
  uint32_t l_16 = 0x13D0BB94L;
  int32_t *l_30 = (void *)0;
  int32_t **l_29 = &l_30;
  int32_t **l_31 = &l_30;
  int32_t l_33 = 0x7F4A1D2DL;
  int32_t **l_39 = &l_30;
  if ((safe_div_func_int8_t_s_s(p_11.f0, l_16))) {
    int32_t *l_27 = &g_20;
    int32_t **l_26 = &l_27;
    int32_t ***l_25 = &l_26;
    int32_t ***l_28[4];
    int i;
    for (i = 0; i < 4; i++)
      l_28[i] = (void *)0;
    for (g_9 = 0; (g_9 < (-23)); --g_9) {
      int32_t *l_19 = &g_20;
      (*l_19) = (*g_8);
    }
    l_31 = (l_29 = ((*l_25) =
                        ((safe_div_func_int8_t_s_s(
                             l_16, (safe_div_func_int16_t_s_s(
                                       (((-1L) > g_20) <= p_11.f0), p_11.f0)))),
                         (void *)0)));
  } else {
    int32_t *l_32[4][1];
    int16_t l_35 = 3L;
    int32_t ***l_40 = &l_39;
    int i, j;
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 1; j++)
        l_32[i][j] = &g_9;
    }
    ++g_36;
    (*p_12) = ((((*l_40) = l_39) != (void *)0) >= g_13.f0);
  }
  return g_36;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  csmith_sink_ = g_9;
  csmith_sink_ = g_13.f0;
  csmith_sink_ = g_20;
  csmith_sink_ = g_34;
  csmith_sink_ = g_36;
  csmith_sink_ = g_42;
  platform_main_end(0, 0);
  return 0;
}
