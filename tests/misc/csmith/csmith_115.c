// Options:   --seed 200115 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_115.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  int8_t f0;
};

static volatile int32_t g_2 = 0L;
static volatile int32_t g_3[3] = {0x79763266L, 0x79763266L, 0x79763266L};
static volatile int32_t g_4 = 0xBACD7953L;
static volatile int32_t g_5 = 8L;
static volatile int32_t g_6 = (-1L);
static int32_t g_7 = 0x25CBD945L;
static float g_11 = 0xE.673292p-63;
static uint8_t g_20 = 0UL;
static int8_t g_22[4] = {0x3AL, 0x3AL, 0x3AL, 0x3AL};
static int32_t *volatile g_29 = &g_7;
static int32_t *g_35 = (void *)0;
static int32_t *g_36 = &g_7;
static int32_t g_49 = 0xF02C1994L;
static uint8_t g_51 = 255UL;
static volatile int16_t g_56 = 0xD63AL;

static int16_t func_1(void);
static union U0 func_12(uint64_t p_13, float p_14, float *p_15);

static int16_t func_1(void) {
  uint32_t l_18 = 0xC863CC1DL;
  uint8_t *l_19 = &g_20;
  int8_t *l_21 = &g_22[3];
  float *l_23 = &g_11;
  float *l_24 = &g_11;
  union U0 l_37 = {-1L};
  int32_t l_39 = 0x7A0B8914L;
  int32_t l_53[3][4] = {{0x8C87C631L, (-8L), 0x8C87C631L, (-8L)},
                        {0x8C87C631L, (-8L), 0x8C87C631L, (-8L)},
                        {0x8C87C631L, (-8L), 0x8C87C631L, (-8L)}};
  int16_t l_58 = 0L;
  int i, j;
  for (g_7 = 0; (g_7 <= 21); g_7 = safe_add_func_int32_t_s_s(g_7, 1)) {
    float *l_10 = &g_11;
    (*l_10) = 0x1.3F1A07p+72;
  }
  if ((func_12(
           (((g_6 |
              (((((*l_21) = ((safe_sub_func_uint32_t_u_u(
                                 (((*l_19) ^= (g_7 < l_18)) >= g_7), g_7)) &&
                             4294967295UL)) ^
                 g_7) |
                0L),
               g_22[2])),
             (void *)0) != l_23),
           g_11, l_24),
       (*g_29))) {
    int32_t *l_34[2];
    uint32_t *l_38[1];
    float *l_40 = (void *)0;
    uint32_t l_43[1][3];
    int16_t l_50 = 0x2393L;
    int i, j;
    for (i = 0; i < 2; i++)
      l_34[i] = &g_7;
    for (i = 0; i < 1; i++)
      l_38[i] = &l_18;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 3; j++)
        l_43[i][j] = 4294967286UL;
    }
    g_36 = (g_35 = l_34[1]);
    if ((func_12((g_4 < (l_39 ^= ((l_37, l_37.f0) & 0xCEL))), g_7, l_40),
         (*g_35))) {
      int64_t *l_48 = (void *)0;
      g_51 ^= (safe_rshift_func_int8_t_s_s(
          ((--l_43[0][2]) &
           (safe_rshift_func_int8_t_s_u(
               (((l_50 ^= (g_49 ^= 1L)) > g_7) > (g_22[3], g_4)), 3))),
          g_22[3]));
      return l_37.f0;
    } else {
      int32_t l_52 = (-1L);
      int32_t l_54 = 0L;
      int32_t l_55 = 0x2EE36085L;
      int32_t l_57 = (-1L);
      int32_t l_59[1][1];
      int32_t l_60 = 1L;
      uint8_t l_61 = 0UL;
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 1; j++)
          l_59[i][j] = 0x3CE50763L;
      }
      (*l_23) = ((void *)0 != l_34[1]);
      l_61--;
    }
  } else {
    float l_68 = 0xB.9F6D4Bp-3;
    int32_t l_69[2][2];
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++)
        l_69[i][j] = 0L;
    }
    for (g_51 = (-16); (g_51 >= 50);
         g_51 = safe_add_func_uint16_t_u_u(g_51, 1)) {
      l_53[2][3] ^= (safe_lshift_func_uint8_t_u_s(1UL, 2));
      return g_4;
    }
    (*g_36) |= l_69[0][0];
  }
  return l_58;
}

static union U0 func_12(uint64_t p_13, float p_14, float *p_15) {
  union U0 l_33 = {0x17L};
  for (p_13 = 23; (p_13 > 48); p_13++) {
    int32_t *volatile *l_30 = &g_29;
    if (p_13) {
      (*g_29) |=
          (safe_mod_func_int8_t_s_s((p_13 >= (g_20 > 0x0DFC1F7BL)), 0x07L));
    } else {
      l_30 = &g_29;
    }
    for (g_20 = 0; (g_20 < 3); g_20 = safe_add_func_int64_t_s_s(g_20, 2)) {
      if (p_13)
        break;
    }
  }
  return l_33;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_3[i];
  }
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  csmith_sink_ = g_6;
  csmith_sink_ = g_7;
  csmith_sink_ = g_11;
  csmith_sink_ = g_20;
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_22[i];
  }
  csmith_sink_ = g_49;
  csmith_sink_ = g_51;
  csmith_sink_ = g_56;
  platform_main_end(0, 0);
  return 0;
}
