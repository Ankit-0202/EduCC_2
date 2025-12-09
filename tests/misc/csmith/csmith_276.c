// Options:   --seed 300276 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_276.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  volatile int64_t f0;
  int16_t f1;
  int8_t f2;
};

static int32_t g_2 = 9L;
static int32_t g_6 = 0xF5A9C4C8L;
static int32_t g_17[2] = {0xAED6B657L, 0xAED6B657L};
static int32_t **g_25 = (void *)0;
static int32_t ***g_24 = &g_25;
static volatile int32_t g_30[3] = {0x491BA6B4L, 0x491BA6B4L, 0x491BA6B4L};
static volatile int32_t g_31 = 0x7C14AB65L;
static int32_t g_32 = 8L;
static int32_t *g_38 = &g_2;
static int32_t **volatile g_37 = &g_38;
static int32_t g_53 = 7L;
static struct S0 g_55 = {0x45104F36CCC853D3LL, -10L, 0L};
static struct S0 **volatile g_56[3] = {(void *)0, (void *)0, (void *)0};

static uint64_t func_1(void);
static int32_t func_7(const int32_t p_8, int32_t *p_9);
static int32_t *func_11(int32_t *p_12, uint16_t p_13, int64_t p_14,
                        int32_t *p_15);

static uint64_t func_1(void) {
  int32_t l_16 = (-6L);
  int32_t *l_18 = &g_2;
  int32_t l_44 = 0L;
  int32_t l_45 = (-7L);
  int32_t l_46 = (-1L);
  struct S0 *const l_54[1] = {&g_55};
  int i;
  for (g_2 = 26; (g_2 > 9); g_2 = safe_sub_func_uint32_t_u_u(g_2, 1)) {
    int32_t *l_5 = &g_6;
    int32_t *l_10 = &g_6;
    int32_t **l_26 = (void *)0;
    int32_t **l_27 = (void *)0;
    int32_t l_42 = 0xFD996437L;
    uint64_t l_47 = 0x0A061FA46B4C01F9LL;
    (*l_5) |= (g_2 > g_2);
    if (func_7(((*l_10) = g_6), (l_5 = func_11(&g_2, l_16, g_17[1], l_18)))) {
      int8_t l_40 = 1L;
      int32_t l_41[2][3] = {{1L, 1L, 1L}, {(-2L), (-2L), (-2L)}};
      int32_t *l_43[2][3];
      int i, j;
      for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++)
          l_43[i][j] = &g_6;
      }
      ++l_47;
      g_30[2] = (safe_rshift_func_int8_t_s_u(
          ((((*l_10) ^= ((+(g_53 = ((((void *)0 != &l_18), 0xF74B76FEL) <
                                    0L))) < g_17[1])) < g_17[0]) |
           (-5L)),
          g_32));
    } else {
      struct S0 *l_58 = &g_55;
      struct S0 **l_57 = &l_58;
      (*l_57) = ((g_2 != g_6), l_54[0]);
    }
  }
  for (g_6 = 0; (g_6 <= 2); g_6 += 1) {
    int32_t *l_59[1][1];
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 1; j++)
        l_59[i][j] = &g_32;
    }
    for (l_46 = 0; (l_46 <= 2); l_46 += 1) {
      int32_t **l_64 = &l_59[0][0];
      int i;
      (*l_64) =
          func_11(l_59[0][0], g_30[l_46],
                  (safe_lshift_func_uint16_t_u_u(
                      (safe_mod_func_uint32_t_u_u(g_6, 0x4C26B3FAL)), (*l_18))),
                  &l_46);
      if ((*l_18))
        break;
    }
    for (g_53 = 0; (g_53 <= 2); g_53 += 1) {
      int32_t *l_65 = &l_46;
      int32_t **l_66 = &l_59[0][0];
      (*g_37) = ((*l_66) = l_65);
    }
  }
  return g_30[1];
}

static int32_t func_7(const int32_t p_8, int32_t *p_9) {
  uint32_t l_39 = 1UL;
  for (g_6 = 2; (g_6 >= 28); g_6 = safe_add_func_uint8_t_u_u(g_6, 5)) {
    for (g_32 = 0; (g_32 != 18); g_32 = safe_add_func_int8_t_s_s(g_32, 9)) {
      int32_t *l_36 = &g_6;
      int32_t **l_35 = &l_36;
      (*g_37) = ((*l_35) = (void *)0);
    }
  }
  return l_39;
}

static int32_t *func_11(int32_t *p_12, uint16_t p_13, int64_t p_14,
                        int32_t *p_15) {
  int32_t **l_19 = (void *)0;
  int32_t ***l_20 = (void *)0;
  int32_t ***l_21[3];
  int32_t *l_23 = (void *)0;
  int32_t **l_22 = &l_23;
  int i;
  for (i = 0; i < 3; i++)
    l_21[i] = (void *)0;
  l_22 = l_19;
  l_21[2] = (g_24 = g_24);
  return p_15;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_6;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_17[i];
  }
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_30[i];
  }
  csmith_sink_ = g_31;
  csmith_sink_ = g_32;
  csmith_sink_ = g_53;
  csmith_sink_ = g_55.f0;
  csmith_sink_ = g_55.f1;
  csmith_sink_ = g_55.f2;
  platform_main_end(0, 0);
  return 0;
}
