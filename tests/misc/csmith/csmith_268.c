// Options:   --seed 300268 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_268.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_3 = 0L;
static volatile int32_t g_4[3] = {0x822B1658L, 0x822B1658L, 0x822B1658L};
static volatile int32_t g_5 = 0x5D811F07L;
static int32_t g_6 = 0xC662A2B3L;
static int32_t g_8 = 0x44AD3740L;
static volatile int32_t **g_23 = (void *)0;
static const int32_t g_45 = 0L;
static uint32_t g_54 = 1UL;
static int32_t *g_55[1] = {(void *)0};

static const int32_t func_1(void);
static const int32_t func_24(int32_t *const **p_25, uint32_t p_26,
                             int32_t p_27);
static int32_t *const **func_28(int8_t p_29);

static const int32_t func_1(void) {
  int8_t l_2[2];
  int32_t l_9 = 0xB0D193E0L;
  int32_t l_11[2][1];
  int32_t *l_20 = &g_6;
  int32_t l_52[3];
  int i, j;
  for (i = 0; i < 2; i++)
    l_2[i] = 0x9AL;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++)
      l_11[i][j] = 0x2F67D50FL;
  }
  for (i = 0; i < 3; i++)
    l_52[i] = 1L;
  for (g_6 = 0; (g_6 <= 1); g_6 += 1) {
    int32_t *l_7 = &g_8;
    int32_t *l_10 = &l_9;
    int32_t *l_12 = &l_9;
    int32_t *l_13 = &l_11[0][0];
    int32_t *l_14 = &l_11[0][0];
    int32_t *l_15 = &l_9;
    int32_t *l_16[2][2] = {{&l_9, &l_9}, {&l_9, &l_9}};
    uint32_t l_17 = 0x7AB6DAD8L;
    int i, j;
    --l_17;
  }
  if (((*l_20) &= l_11[0][0])) {
    int32_t **l_22[1][3];
    int32_t ***l_21[3][1];
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 3; j++)
        l_22[i][j] = &l_20;
    }
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 1; j++)
        l_21[i][j] = &l_22[0][1];
    }
    g_23 = (void *)0;
  } else {
    const int32_t *l_44 = &g_45;
    int32_t **l_51[3][2];
    uint32_t l_53 = 0xF73E702BL;
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 2; j++)
        l_51[i][j] = (void *)0;
    }
    if (func_24(func_28(g_5), (0x30L == (*l_20)), g_8)) {
      (*l_20) &= 0xDF11CAF1L;
    } else {
      g_54 |= ((((~(((safe_rshift_func_uint16_t_u_s(
                         0UL, (safe_sub_func_int16_t_s_s(
                                  ((((l_44 = (void *)0) ==
                                     ((safe_div_func_int64_t_s_s(
                                          (safe_div_func_int32_t_s_s(
                                              (+(((void *)0 != l_51[0][1]) |
                                                 0xE0EA626AECE01153LL)),
                                              l_52[1])),
                                          (*l_20))),
                                      (void *)0)),
                                    (*l_20)) ||
                                   (*l_20)),
                                  g_3)))),
                     l_53) &
                    g_45)) == g_8),
                0xA24EL) ^
               0xEE04L);
    }
    g_55[0] = &g_8;
  }
  return (*l_20);
}

static const int32_t func_24(int32_t *const **p_25, uint32_t p_26,
                             int32_t p_27) {
  int32_t *l_36 = &g_8;
  int32_t **l_37 = (void *)0;
  int32_t **l_38 = &l_36;
  (*l_38) = l_36;
  return g_3;
}

static int32_t *const **func_28(int8_t p_29) {
  int32_t *l_32 = (void *)0;
  int32_t l_33 = 6L;
  int32_t *l_34 = &l_33;
  int32_t *const **l_35 = (void *)0;
  l_33 = (safe_lshift_func_uint16_t_u_u(p_29, g_8));
  (*l_34) ^= p_29;
  return l_35;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_4[i];
  }
  csmith_sink_ = g_5;
  csmith_sink_ = g_6;
  csmith_sink_ = g_8;
  csmith_sink_ = g_45;
  csmith_sink_ = g_54;
  platform_main_end(0, 0);
  return 0;
}
