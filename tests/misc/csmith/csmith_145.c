// Options:   --seed 200145 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_145.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  volatile int32_t f0;
  uint16_t f1;
};

union U1 {
  int64_t f0;
};

static uint8_t g_2[4] = {0x29L, 0x29L, 0x29L, 0x29L};
static int32_t g_4 = 0x90BE4438L;
static volatile int32_t g_15 = (-5L);
static volatile int32_t *volatile g_14 = &g_15;
static float g_27 = 0x9.1p+1;
static int16_t g_30 = 0xA26CL;
static uint32_t g_31 = 0x06E3268DL;
static volatile int32_t g_40 = 0x70D97802L;
static volatile int32_t *g_39 = &g_40;
static volatile int32_t *volatile *g_38 = &g_39;
static int64_t g_42[2] = {(-2L), (-2L)};
static int16_t ***volatile g_45 = (void *)0;
static int16_t *g_47 = &g_30;
static int16_t **g_46 = &g_47;
static volatile union U0 g_56 = {0x78FF5F6FL};

static uint8_t func_1(void);
static uint32_t func_19(uint32_t p_20, const union U1 p_21, const int8_t p_22,
                        int32_t **p_23);

static uint8_t func_1(void) {
  int32_t *l_3 = &g_4;
  const int32_t l_12 = 0xDC8DFBA2L;
  int16_t *l_44 = &g_30;
  int16_t **const l_43 = &l_44;
  int32_t l_50 = 0x319B20E9L;
  volatile int32_t *volatile l_60 = (void *)0;
  if (((*l_3) ^= g_2[1])) {
    const int32_t *l_9 = &g_4;
    int32_t l_10 = (-7L);
    int32_t l_11 = 0x948B0815L;
    const union U1 l_24 = {0x9D66DE6B9338886ALL};
    int32_t **l_25[4][4] = {{&l_3, &l_3, &l_3, &l_3},
                            {&l_3, &l_3, &l_3, &l_3},
                            {&l_3, &l_3, &l_3, &l_3},
                            {&l_3, &l_3, &l_3, &l_3}};
    int i, j;
    if (((safe_add_func_int16_t_s_s(
             (safe_div_func_int64_t_s_s((l_11 = (l_10 = ((void *)0 != l_9))),
                                        ((*l_3), (*l_3)))),
             l_12)),
         (*l_3))) {
      int32_t **l_13[2];
      int i;
      for (i = 0; i < 2; i++)
        l_13[i] = &l_3;
      g_14 = (void *)0;
    } else {
      float l_26 = 0x7.7B69C9p+6;
      int32_t l_28 = 7L;
      int16_t *l_29 = &g_30;
      g_31 &=
          (+((((*l_29) = (safe_mul_func_int16_t_s_s(
                   (func_19((*l_3), l_24, g_2[1], l_25[2][1]) & 0x3F36A5B5L),
                   l_28))) != g_15) <= l_12));
    }
    if ((safe_sub_func_uint8_t_u_u(
            (safe_mod_func_int64_t_s_s(
                g_2[3], (safe_lshift_func_int8_t_s_u(
                            g_15, (((((g_38 == &l_3) != 4294967293UL), g_31),
                                    0x37L) == 0xABL))))),
            0x6DL))) {
      int64_t l_41 = 0x0F8393131EC8E12BLL;
      (*g_38) = (*g_38);
      l_41 ^= (**g_38);
    } else {
      (*g_38) = (*g_38);
    }
  } else {
    (*g_39) &= (((((g_42[1] = ((-8L) <= (*l_3))) >= (*l_3)) != 4294967287UL),
                 (*l_3)) != (-3L));
    g_46 = l_43;
  }
  for (g_4 = 0; (g_4 <= 23); ++g_4) {
    int64_t l_57 = 0xEB8EFB6675F713ECLL;
    int32_t l_58 = 0xCEA67F41L;
    if ((l_50 ^= (*l_3))) {
      const int32_t *l_51 = (void *)0;
      uint8_t *l_59 = &g_2[1];
      l_51 = (void *)0;
      l_60 = (((safe_lshift_func_uint8_t_u_u(
                   ((*l_59) = (safe_mod_func_int16_t_s_s(
                        ((65535UL >=
                          ((l_57 = ((((18446744073709551606UL ==
                                       (g_56, g_56.f0)) >= g_4) != 0x26L) ||
                                    18446744073709551615UL)) &
                           g_42[1])) ^
                         g_42[1]),
                        l_58))),
                   g_31)) |
               0x93A78091L),
              (*g_38));
    } else {
      (**g_38) ^= 1L;
      return g_2[1];
    }
  }
  return g_42[0];
}

static uint32_t func_19(uint32_t p_20, const union U1 p_21, const int8_t p_22,
                        int32_t **p_23) {
  (**p_23) &= (-9L);
  return g_2[1];
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_2[i];
  }
  csmith_sink_ = g_4;
  csmith_sink_ = g_15;
  csmith_sink_ = g_27;
  csmith_sink_ = g_30;
  csmith_sink_ = g_31;
  csmith_sink_ = g_40;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_42[i];
  }
  csmith_sink_ = g_56.f0;
  csmith_sink_ = g_56.f1;
  platform_main_end(0, 0);
  return 0;
}
