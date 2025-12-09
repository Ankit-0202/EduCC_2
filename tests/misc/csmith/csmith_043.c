// Options:   --seed 100043 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_043.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  uint32_t f0;
};

static int32_t g_3 = 0x02526041L;
static uint16_t g_9 = 65534UL;
static union U0 g_18 = {0xE6F885EAL};
static int32_t *volatile g_31[1] = {&g_3};
static int32_t *volatile g_33 = &g_3;
static int32_t g_34[3][1] = {{1L}, {1L}, {1L}};

static uint16_t func_1(void);
static int16_t func_12(const int32_t *p_13, union U0 p_14, union U0 p_15,
                       int32_t *p_16);

static uint16_t func_1(void) {
  int32_t *l_2 = &g_3;
  int32_t *l_4 = &g_3;
  int32_t *l_5 = (void *)0;
  int32_t *l_6 = (void *)0;
  int32_t l_7 = 1L;
  int32_t *l_8[4][1] = {{&l_7}, {&g_3}, {&l_7}, {&g_3}};
  const int32_t *l_17 = &l_7;
  int i, j;
  ++g_9;
  (*l_2) = ((func_12(l_17, g_18, g_18, &l_7), g_9) == g_34[0][0]);
  return g_34[1][0];
}

static int16_t func_12(const int32_t *p_13, union U0 p_14, union U0 p_15,
                       int32_t *p_16) {
  int32_t l_19 = 0xB0AD8EA5L;
  if (((*p_16) |= l_19)) {
    for (g_9 = 10; (g_9 < 45); g_9 = safe_add_func_uint16_t_u_u(g_9, 5)) {
      for (g_18.f0 = 0; (g_18.f0 >= 41); g_18.f0++) {
        if (g_3)
          break;
        (*p_16) = g_3;
      }
      if ((*p_13))
        break;
    }
    return g_18.f0;
  } else {
    int32_t *l_32 = (void *)0;
    (*g_33) |= (safe_mul_func_uint16_t_u_u(
        (((safe_unary_minus_func_uint64_t_u(2UL)) >=
          (((((safe_rshift_func_int16_t_s_u(
                  ((((safe_mod_func_int8_t_s_s(((0UL | 0UL) == 0x321A0783L),
                                               p_14.f0)),
                     4294967295UL) &&
                    2L) == l_19),
                  p_15.f0)) >= 18446744073709551615UL) < 0x8483L) <= (*p_16)) ||
           (*p_13))) < p_15.f0),
        l_19));
    l_32 = p_16;
  }
  return g_9;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_9;
  csmith_sink_ = g_18.f0;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_34[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
