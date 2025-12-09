// Options:   --seed 200151 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_151.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint8_t g_17 = 255UL;
static volatile int64_t g_19 = (-10L);
static float g_26 = 0x6.9D1FE9p+36;
static int32_t g_28 = 0xD8B26DE0L;
static volatile float g_29 = 0xA.FE0A4Dp-24;
static volatile uint16_t g_30 = 5UL;
static int32_t g_33[4][3] = {{(-9L), (-9L), (-9L)},
                             {0xDAAFE497L, 0xDAAFE497L, 0xDAAFE497L},
                             {(-9L), (-9L), (-9L)},
                             {0xDAAFE497L, 0xDAAFE497L, 0xDAAFE497L}};

static const int8_t func_1(void);
static const int32_t func_2(uint16_t p_3, uint32_t p_4, int8_t p_5);

static const int8_t func_1(void) {
  int64_t l_6 = 0xF1BF506E60B0CEAFLL;
  float *l_43 = &g_26;
  int32_t *l_44 = &g_28;
  if (func_2(l_6, l_6, l_6)) {
    int32_t *l_36 = &g_28;
    for (l_6 = 2; (l_6 >= 0); l_6 -= 1) {
      float l_34 = (-0x1.Cp-1);
      int32_t *l_35 = &g_28;
      (*l_35) &= g_19;
      if (g_19)
        continue;
    }
    (*l_36) = 1L;
  } else {
    int32_t **l_37 = (void *)0;
    int32_t *l_39 = &g_28;
    int32_t **l_38 = &l_39;
    (*l_38) = (void *)0;
    g_28 &= (((((safe_div_func_uint16_t_u_u(
                    (~((l_6 || (l_43 == (void *)0)) ^ g_17)), g_30)),
                (void *)0) == &g_17),
              1UL),
             0xCA19AB63L);
  }
  (*l_44) &= (l_6, l_6);
  return g_30;
}

static const int32_t func_2(uint16_t p_3, uint32_t p_4, int8_t p_5) {
  const int32_t l_22[4] = {0x5DEA311CL, 0x5DEA311CL, 0x5DEA311CL, 0x5DEA311CL};
  int32_t *l_27[3];
  int i;
  for (i = 0; i < 3; i++)
    l_27[i] = &g_28;
  for (p_5 = 0; (p_5 <= (-17)); p_5 = safe_sub_func_int8_t_s_s(p_5, 7)) {
    uint8_t *l_15 = (void *)0;
    uint8_t *l_16[3][2] = {{&g_17, &g_17}, {&g_17, &g_17}, {&g_17, &g_17}};
    int32_t l_18[3][4] = {{0x1B0AE28DL, 0x1B0AE28DL, 0x1B0AE28DL, 0x1B0AE28DL},
                          {0x1B0AE28DL, 0x1B0AE28DL, 0x1B0AE28DL, 0x1B0AE28DL},
                          {0x1B0AE28DL, 0x1B0AE28DL, 0x1B0AE28DL, 0x1B0AE28DL}};
    int32_t l_23 = 0x6A37BD55L;
    int32_t l_24 = 0x413E458CL;
    float *l_25 = &g_26;
    int i, j;
    (*l_25) = (((safe_mul_func_float_f_f(
                    (((((((safe_lshift_func_int8_t_s_u(
                              (+(!(((((l_23 = (((l_18[1][0] = 0UL) != g_19) |
                                               (safe_add_func_int16_t_s_s(
                                                   l_22[0], g_17)))),
                                      0x205FL) < l_24) ||
                                    g_19) > p_5))),
                              l_24)) != 3L),
                         0xDE2A9078L),
                        0xD.A2A4F2p+52) <= l_22[2]) > l_24) == g_17),
                    (-0x4.5p+1))) <= p_3) > 0xB.D76DF3p+94);
  }
  g_30++;
  return p_3;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_17;
  csmith_sink_ = g_19;
  csmith_sink_ = g_26;
  csmith_sink_ = g_28;
  csmith_sink_ = g_29;
  csmith_sink_ = g_30;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_33[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
