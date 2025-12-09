// Options:   --seed 300235 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_235.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  volatile int64_t f0;
  const uint32_t f1;
};

union U1 {
  struct S0 f0;
  uint64_t f1;
};

union U2 {
  uint32_t f0;
  volatile uint16_t f1;
};

static int32_t g_2 = 3L;
static volatile int32_t g_5 = 0x95010F7AL;
static int32_t g_6 = 0x2D672A83L;
static int32_t g_13 = 0L;
static int32_t *volatile g_15 = &g_13;
static int32_t g_17[2][3] = {{0x282D564CL, 0x282D564CL, 0x282D564CL},
                             {(-1L), (-1L), (-1L)}};
static int32_t *g_30 = &g_13;
static volatile union U1 g_43 = {{0x2DC870AF03FA9A18LL, 0x4524BE18L}};
static int16_t g_46 = (-1L);
static int32_t *const volatile g_54 = &g_17[1][0];
static int32_t *volatile g_59 = &g_17[1][0];
static volatile union U2 g_63 = {0x8928FFEAL};
static union U1 g_67 = {{0xD42A80B09DE24E56LL, 0UL}};

static union U1 func_1(void);
static int32_t func_9(int32_t p_10, int8_t p_11);
static int32_t *func_19(int8_t p_20, int16_t p_21, uint32_t p_22, int16_t p_23,
                        int64_t p_24);

static union U1 func_1(void) {
  uint32_t l_42 = 0x945AD33DL;
lbl_60:
  for (g_2 = 24; (g_2 > 22); --g_2) {
    uint32_t l_14 = 18446744073709551615UL;
    int32_t l_18[1][2];
    int32_t *l_32 = &g_17[1][1];
    int32_t **l_31 = &l_32;
    uint32_t *l_44 = &l_14;
    int16_t *l_45 = &g_46;
    int32_t *l_47[1][2];
    uint32_t l_48[1][3];
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 2; j++)
        l_18[i][j] = 0x885EA6EDL;
    }
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 2; j++)
        l_47[i][j] = &g_6;
    }
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 3; j++)
        l_48[i][j] = 0xB8909FF4L;
    }
    for (g_6 = 0; (g_6 <= 14); g_6 = safe_add_func_int64_t_s_s(g_6, 6)) {
      int32_t *l_12 = &g_13;
      int32_t *l_16[1];
      int i;
      for (i = 0; i < 1; i++)
        l_16[i] = &g_17[1][0];
      l_18[0][0] &= func_9(((*l_12) = g_2), l_14);
      g_15 = func_19(g_5, g_17[1][0], (*l_12), g_17[1][0], l_18[0][0]);
    }
    l_48[0][1] |= (safe_sub_func_uint32_t_u_u(
        (safe_mul_func_int16_t_s_s(
            ((*l_45) =
                 (((*l_44) ^= (l_18[0][0] ||
                               (((*l_31) = (g_30 = &g_17[1][0])) !=
                                ((((safe_rshift_func_uint8_t_u_s(
                                       ((safe_unary_minus_func_int32_t_s(
                                            (safe_rshift_func_int16_t_s_s(
                                                ((safe_add_func_uint64_t_u_u(
                                                     (safe_mul_func_int16_t_s_s(
                                                         0x7835L, 0xC6F4L)),
                                                     4UL)),
                                                 l_42),
                                                10)))) &&
                                        l_42),
                                       g_17[1][1])),
                                   g_13),
                                  g_43),
                                 (void *)0)))),
                  1L)),
            4L)),
        g_2));
  }
  for (g_13 = (-30); (g_13 > 19); g_13++) {
    const uint32_t *l_52 = (void *)0;
    int16_t *l_56 = &g_46;
    int32_t l_58 = 5L;
    if ((*g_15)) {
      int16_t *l_51 = &g_46;
      const uint32_t **l_53 = &l_52;
      int32_t l_57 = 0x82856065L;
      (*g_54) = ((((*l_51) = (0xC83BL || 0x680DL)), ((*l_53) = l_52)) == g_15);
      (*g_59) = ((safe_unary_minus_func_int64_t_s(
                     (((((((l_56 != (void *)0) & (0x9E43L & g_46)) > l_57),
                         0x29B61F2865603B64LL) != 0x176A90D2634D7F48LL) ==
                       l_42) < (-1L)))) < l_58);
    } else {
      if (g_2)
        goto lbl_60;
    }
    for (g_46 = (-7); (g_46 > (-5)); g_46++) {
      int32_t *l_66 = &l_58;
      (*l_66) = (g_63, (safe_mul_func_uint16_t_u_u(0xF859L, g_63.f0)));
      if (l_58)
        continue;
    }
  }
  return g_67;
}

static int32_t func_9(int32_t p_10, int8_t p_11) {
  (*g_15) |= p_10;
  return (*g_15);
}

static int32_t *func_19(int8_t p_20, int16_t p_21, uint32_t p_22, int16_t p_23,
                        int64_t p_24) {
  int32_t *l_25 = &g_17[1][0];
  (*l_25) = (-1L);
  return &g_17[1][0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_5;
  csmith_sink_ = g_6;
  csmith_sink_ = g_13;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_17[i][j];
    }
  }
  csmith_sink_ = g_43.f0.f0;
  csmith_sink_ = g_43.f0.f1;
  csmith_sink_ = g_46;
  csmith_sink_ = g_63.f0;
  csmith_sink_ = g_63.f1;
  csmith_sink_ = g_67.f0.f0;
  csmith_sink_ = g_67.f0.f1;
  platform_main_end(0, 0);
  return 0;
}
