// Options:   --seed 200134 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_134.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int8_t g_12 = 0x2CL;
static uint32_t g_13 = 0xBF38C088L;
static uint64_t g_22[1] = {0x44ADCA1A1F050678LL};
static int16_t g_39 = (-1L);
static uint8_t g_41 = 0xEEL;
static volatile int32_t g_43[3][1] = {{(-7L)}, {(-7L)}, {(-7L)}};
static volatile int32_t *const volatile g_42 = &g_43[2][0];
static volatile int32_t g_45 = 0x98962600L;
static volatile int32_t *g_44 = &g_45;
static float g_52 = 0xB.996340p-39;
static float *volatile g_51[2][1] = {{&g_52}, {&g_52}};

static uint16_t func_1(void);
static int32_t func_2(int16_t p_3, uint32_t p_4, uint64_t p_5);

static uint16_t func_1(void) {
  float l_6 = 0x2.B57E8Bp+89;
  int32_t l_7 = 1L;
  int64_t l_15[4][1];
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 1; j++)
      l_15[i][j] = (-1L);
  }
  if (func_2(l_7,
             (safe_lshift_func_uint16_t_u_u(
                 (safe_mul_func_int16_t_s_s(0L, g_12)), 12)),
             g_13)) {
    for (l_7 = 0; (l_7 <= 0); l_7 += 1) {
      if (g_12)
        break;
    }
  } else {
    uint32_t l_28 = 0xDB74A71AL;
    int32_t l_37 = 0x9A9D0127L;
    int16_t l_46[3];
    int i;
    for (i = 0; i < 3; i++)
      l_46[i] = 1L;
    for (l_7 = 0; (l_7 > 10); l_7 = safe_add_func_int16_t_s_s(l_7, 4)) {
      uint64_t *l_21 = &g_22[0];
      int64_t *l_34 = &l_15[2][0];
      int32_t l_35 = 0xE97312B9L;
      int32_t *l_36[1][1];
      int16_t *l_38 = &g_39;
      int32_t l_40 = 0x1CF717C9L;
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 1; j++)
          l_36[i][j] = (void *)0;
      }
      g_41 |=
          (1UL ==
           (((safe_unary_minus_func_uint16_t_u((
                 ((((safe_rshift_func_int16_t_s_s(
                        ((*l_38) =
                             ((++(*l_21)) <
                              ((l_37 = (((safe_lshift_func_uint16_t_u_s(
                                             (~(l_28 ^
                                                (safe_mul_func_int8_t_s_s(
                                                    ((safe_div_func_int64_t_s_s(
                                                         (+((((*l_34) ^= l_28),
                                                             65535UL),
                                                            65535UL)),
                                                         l_35)) ^
                                                     g_13),
                                                    0xAEL)))),
                                             0)),
                                         0UL),
                                        g_12)) |
                               g_13))),
                        13)) == g_13) |
                   255UL) ||
                  l_40) != l_7))) &
             g_13),
            g_39));
      l_46[0] &= ((g_42 == g_44) & (g_39 > g_22[0]));
    }
    return g_41;
  }
  for (g_13 = 0; (g_13 > 48); g_13++) {
    float *l_53[4][2] = {
        {&l_6, &l_6}, {&l_6, &l_6}, {&l_6, &l_6}, {&l_6, &l_6}};
    int i, j;
    l_7 = ((safe_div_func_float_f_f(
               (0x0.5p+1 >= 0x5.470E98p+74),
               ((((g_39 ^ g_39) & 0x84ADL), (void *)0) == (void *)0))) <= g_41);
  }
  return g_22[0];
}

static int32_t func_2(int16_t p_3, uint32_t p_4, uint64_t p_5) {
  int32_t l_14 = 0x744D0289L;
  return l_14;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_12;
  csmith_sink_ = g_13;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_22[i];
  }
  csmith_sink_ = g_39;
  csmith_sink_ = g_41;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_43[i][j];
    }
  }
  csmith_sink_ = g_45;
  csmith_sink_ = g_52;
  platform_main_end(0, 0);
  return 0;
}
