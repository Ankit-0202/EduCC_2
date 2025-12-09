// Options:   --seed 300217 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_217.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U1 {
  volatile uint32_t f0;
  int64_t f1;
};

union U2 {
  uint8_t f0;
  const int32_t f1;
};

static volatile int32_t g_8 = (-9L);
static uint8_t g_13 = 0UL;
static int32_t g_21 = (-1L);
static int32_t g_24[3][1] = {{8L}, {8L}, {8L}};
static int32_t *volatile g_23 = &g_24[2][0];
static int32_t g_40[2] = {0x1DDBC75BL, 0x1DDBC75BL};
static uint64_t g_45 = 0UL;
static uint32_t g_46 = 0x55E3164CL;
static int16_t g_65 = 0xF1DFL;
static int32_t *g_71 = &g_40[1];
static union U1 g_73 = {1UL};
static union U1 *g_76 = &g_73;
static union U1 **volatile g_75 = &g_76;
static volatile uint64_t g_91 = 0xDAD0BAEE16EA25DALL;

static uint64_t func_1(void);
static uint64_t func_9(int32_t p_10);
static uint64_t func_16(union U2 p_17, uint32_t p_18, uint8_t *p_19);

static uint64_t func_1(void) {
  int32_t l_11 = (-1L);
  uint8_t *l_12 = &g_13;
  uint64_t *l_44 = &g_45;
  int32_t l_47 = 0xF642D949L;
  union U2 l_67 = {0x1EL};
  int32_t l_85 = (-7L);
  uint16_t l_86 = 65533UL;
  int64_t l_89[1];
  int32_t l_90[1][3];
  int i, j;
  for (i = 0; i < 1; i++)
    l_89[i] = 0x8752EB69FE437344LL;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++)
      l_90[i][j] = 0x0AD72A74L;
  }
  if ((safe_rshift_func_int16_t_s_u(
          (safe_add_func_int64_t_s_s(
              ((safe_lshift_func_uint16_t_u_u(
                   (((g_8,
                      (((*l_44) |= func_9((((((*l_12) = l_11), (-2L)) | 0xC1L) >
                                           1UL))) < 18446744073709551615UL)) ||
                     3L),
                    0xEA1EL),
                   7)) >= 0xAAF09D89L),
              l_11)),
          g_46))) {
    if (l_11) {
      return g_21;
    } else {
      l_47 ^= l_11;
      return l_47;
    }
  } else {
    int32_t *l_50 = &g_21;
    int32_t *l_60 = &g_24[2][0];
    union U1 *l_72 = &g_73;
    if ((safe_sub_func_uint8_t_u_u(
            (((*l_50) |= 0x089CE376L),
             (safe_mul_func_int8_t_s_s(
                 (((safe_rshift_func_int16_t_s_s(
                       (((~(safe_sub_func_uint16_t_u_u(
                             (safe_div_func_int32_t_s_s(0xD6825D0BL,
                                                        ((*l_60) = g_13))),
                             0L))) == 0x07DFL) >= 9UL),
                       g_8)) ||
                   18446744073709551615UL),
                  g_24[0][0]),
                 l_11))),
            0x3BL))) {
      int8_t l_63 = 0L;
      int16_t *l_64[3];
      int32_t l_66 = 7L;
      int i;
      for (i = 0; i < 3; i++)
        l_64[i] = &g_65;
      l_66 = (safe_rshift_func_uint8_t_u_u(((void *)0 == &g_13),
                                           (((*l_60) = l_63) <= g_40[0])));
    } else {
      int32_t *l_68 = &g_24[1][0];
      int32_t **l_69 = (void *)0;
      int32_t **l_70 = &l_60;
      union U1 **l_74 = &l_72;
      (*l_68) ^= (((*l_70) = (l_67, l_68)) != (g_71 = &g_24[0][0]));
      (*g_75) = ((*l_74) = l_72);
    }
    for (l_11 = 0; (l_11 == 10); l_11 = safe_add_func_uint32_t_u_u(l_11, 3)) {
      (*g_71) = 0x30D26BC8L;
    }
  }
  if ((l_47 &= (g_40[1] | g_40[1]))) {
    return g_46;
  } else {
    int32_t *l_79 = &g_40[1];
    int32_t *l_80 = &g_24[2][0];
    int32_t *l_81 = &g_40[1];
    int32_t *l_82 = &g_40[0];
    int32_t *l_83 = &g_24[2][0];
    int32_t *l_84[1];
    int i;
    for (i = 0; i < 1; i++)
      l_84[i] = &g_40[0];
    ++l_86;
    g_91--;
  }
  return g_8;
}

static uint64_t func_9(int32_t p_10) {
  uint32_t l_15 = 18446744073709551611UL;
  int32_t *l_20 = &g_21;
  union U2 l_22 = {1UL};
  if ((safe_unary_minus_func_int32_t_s((
          (l_15 > (0x9FFF12F3CCD2466ELL &
                   func_16((((*l_20) = (g_13 == g_13)), l_22), p_10, &g_13))) &&
          0UL)))) {
    int32_t *l_35 = &g_24[2][0];
    uint64_t l_38[1];
    int i;
    for (i = 0; i < 1; i++)
      l_38[i] = 18446744073709551612UL;
    for (l_15 = 19; (l_15 != 4); l_15 = safe_sub_func_uint16_t_u_u(l_15, 5)) {
      if ((*g_23))
        break;
    }
    if ((safe_rshift_func_uint16_t_u_s(
            ((safe_sub_func_uint32_t_u_u(
                 (((safe_mul_func_int16_t_s_s(
                       ((void *)0 != l_35), ((((safe_rshift_func_int8_t_s_s(
                                                   ((void *)0 != &p_10), 0)) <
                                               0x033631AF6658D83FLL) > p_10) &&
                                             g_8))) == g_24[2][0]) >
                  18446744073709551608UL),
                 l_38[0])) ||
             (*l_35)),
            7))) {
      int32_t *l_39[3][1];
      int i, j;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++)
          l_39[i][j] = &g_40[1];
      }
      g_40[0] &= (*g_23);
      return p_10;
    } else {
      g_23 = &p_10;
    }
  } else {
    int32_t *l_43 = &g_24[2][0];
    for (l_22.f0 = 0; (l_22.f0 >= 49);
         l_22.f0 = safe_add_func_int8_t_s_s(l_22.f0, 1)) {
      l_43 = l_20;
    }
  }
  return g_13;
}

static uint64_t func_16(union U2 p_17, uint32_t p_18, uint8_t *p_19) {
  int32_t *l_26 = &g_24[2][0];
  (*g_23) = g_21;
  (*l_26) ^= (~0xD6L);
  return p_18;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_8;
  csmith_sink_ = g_13;
  csmith_sink_ = g_21;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_24[i][j];
    }
  }
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_40[i];
  }
  csmith_sink_ = g_45;
  csmith_sink_ = g_46;
  csmith_sink_ = g_65;
  csmith_sink_ = g_73.f0;
  csmith_sink_ = g_91;
  platform_main_end(0, 0);
  return 0;
}
