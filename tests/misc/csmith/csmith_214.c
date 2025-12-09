// Options:   --seed 300214 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_214.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  uint16_t f0;
  int16_t f1;
};

static volatile int32_t g_3[3][1] = {{(-1L)}, {(-1L)}, {(-1L)}};
static volatile int32_t g_4 = 0xFDDD3F46L;
static int32_t g_5 = 0x5912491EL;
static volatile int32_t g_6[1] = {0x2C25FCC5L};
static volatile int32_t g_7 = 7L;
static int32_t g_8 = 0x091DF82DL;
static union U0 g_22 = {0x623BL};
static uint32_t g_41[1] = {0xA5019003L};
static const union U0 g_44 = {0x8FE2L};
static uint16_t g_47 = 5UL;
static const union U0 ***volatile g_64[3][2] = {
    {(void *)0, (void *)0}, {(void *)0, (void *)0}, {(void *)0, (void *)0}};
static const union U0 *g_67 = (void *)0;
static const union U0 **g_66 = &g_67;
static const union U0 ***volatile g_65 = &g_66;

static const uint32_t func_1(void);
static uint16_t func_13(int32_t p_14, union U0 p_15, uint32_t p_16);
static int16_t func_17(uint32_t p_18);

static const uint32_t func_1(void) {
  int8_t l_2[3][3] = {
      {1L, (-1L), (-1L)}, {1L, (-1L), (-1L)}, {1L, (-1L), (-1L)}};
  int16_t l_19 = 0x6A47L;
  int16_t l_39 = 4L;
  int i, j;
  for (g_5 = 0; (g_5 <= 2); g_5 += 1) {
    for (g_8 = 2; (g_8 >= 0); g_8 -= 1) {
      int i, j;
      return l_2[g_8][g_5];
    }
    if (l_2[0][0])
      continue;
    for (g_8 = 0; (g_8 <= 2); g_8 += 1) {
      int i, j;
      if (l_2[g_5][g_8])
        break;
    }
  }
  if (((safe_mul_func_int16_t_s_s(
           (safe_mul_func_uint16_t_u_u(
               func_13(g_6[0],
                       ((func_17(((((l_2[2][1], ((l_19 = l_2[2][1]) & 1L)),
                                    0x8CL) <= l_2[0][0]) > g_5)) ||
                         1UL),
                        g_22),
                       g_8),
               0x4613L)),
           g_8)) >= l_39)) {
    int32_t l_40 = 0x883781CDL;
    g_41[0] = (l_40 < l_2[0][0]);
  } else {
    const union U0 *l_43[2][2];
    const union U0 **l_42 = &l_43[1][0];
    int32_t l_48[1];
    int32_t *l_49 = &l_48[0];
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++)
        l_43[i][j] = &g_44;
    }
    for (i = 0; i < 1; i++)
      l_48[i] = 0x61F6604CL;
    if (((*l_49) = (((((((*l_42) = &g_22) != (void *)0) &&
                       ((safe_sub_func_int64_t_s_s((g_47 = g_22.f0), l_48[0])) <
                        l_48[0])),
                      (void *)0) == &g_3[2][0]),
                    g_6[0]))) {
      return g_22.f0;
    } else {
      uint16_t *l_62 = &g_47;
      int32_t l_63 = (-1L);
      (*l_49) = (safe_unary_minus_func_int64_t_s((safe_add_func_int8_t_s_s(
          ((safe_mod_func_uint16_t_u_u(
               (safe_unary_minus_func_uint8_t_u((safe_mul_func_int16_t_s_s(
                   (((*l_62) |= ((((*l_49) == 0x3A2CL) &
                                  (safe_mul_func_int16_t_s_s(
                                      ((safe_rshift_func_uint16_t_u_u(
                                           (g_6[0] | 0x7EL), 11)) != 0x9BL),
                                      0xD23EL))) ||
                                 0xD2A6L)) > l_63),
                   g_44.f0)))),
               g_41[0])),
           l_39),
          0x1DL))));
      (*g_65) = &l_43[1][0];
    }
  }
  return g_5;
}

static uint16_t func_13(int32_t p_14, union U0 p_15, uint32_t p_16) {
  union U0 *const l_31 = &g_22;
  union U0 *l_35 = &g_22;
  int32_t l_38 = 1L;
lbl_37:
  for (g_22.f0 = (-24); (g_22.f0 <= 45);
       g_22.f0 = safe_add_func_uint16_t_u_u(g_22.f0, 9)) {
    for (p_15.f0 = 0; (p_15.f0 <= 9); ++p_15.f0) {
      union U0 *l_28[2];
      union U0 **l_27 = &l_28[0];
      int i;
      for (i = 0; i < 2; i++)
        l_28[i] = &g_22;
      (*l_27) = &g_22;
    }
  }
  for (p_14 = 0; (p_14 == 16); p_14 = safe_add_func_int16_t_s_s(p_14, 5)) {
    union U0 *l_32 = &g_22;
    union U0 *l_34 = &g_22;
    union U0 **l_33 = &l_34;
    int32_t *l_36 = &g_5;
    (*l_36) =
        (0L != ((l_31 != (l_35 = ((*l_33) = (l_32 = (void *)0)))) && p_16));
    if (g_22.f0)
      goto lbl_37;
  }
  return l_38;
}

static int16_t func_17(uint32_t p_18) {
  int64_t l_20[1][2];
  int32_t *l_21 = (void *)0;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++)
      l_20[i][j] = 5L;
  }
  for (g_5 = 0; g_5 < 1; g_5 += 1) {
    for (p_18 = 0; p_18 < 2; p_18 += 1) {
      l_20[g_5][p_18] = 0L;
    }
  }
  l_21 = &g_8;
  return g_8;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_3[i][j];
    }
  }
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_6[i];
  }
  csmith_sink_ = g_7;
  csmith_sink_ = g_8;
  csmith_sink_ = g_22.f0;
  csmith_sink_ = g_22.f1;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_41[i];
  }
  csmith_sink_ = g_44.f0;
  csmith_sink_ = g_44.f1;
  csmith_sink_ = g_47;
  platform_main_end(0, 0);
  return 0;
}
