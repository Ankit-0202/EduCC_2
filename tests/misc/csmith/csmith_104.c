// Options:   --seed 200104 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_104.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_3 = 1L;
static int32_t g_4 = 1L;
static volatile int32_t g_5 = 1L;
static volatile int32_t g_6[4][2] = {{0xF7D65121L, 0x01FC3EEEL},
                                     {0x01FC3EEEL, 0xF7D65121L},
                                     {0x01FC3EEEL, 0x01FC3EEEL},
                                     {0xF7D65121L, 0x01FC3EEEL}};
static int32_t g_7 = 0x8999D94BL;
static int32_t g_11 = (-1L);
static uint16_t g_30 = 1UL;
static int32_t *volatile g_50[2][1] = {{(void *)0}, {(void *)0}};
static float g_53 = 0xE.3202F6p-79;

static uint16_t func_1(void);
static float func_16(uint32_t p_17);

static uint16_t func_1(void) {
  uint8_t l_2[4] = {0x0EL, 0x0EL, 0x0EL, 0x0EL};
  uint32_t l_13 = 18446744073709551615UL;
  int32_t l_31 = 0L;
  int i;
  for (g_4 = 0; (g_4 <= 3); g_4 += 1) {
    int32_t *l_27 = &g_11;
    uint16_t *l_28 = (void *)0;
    uint16_t *l_29 = &g_30;
    float *l_52[4] = {&g_53, &g_53, &g_53, &g_53};
    uint32_t l_54 = 0x62B41911L;
    int i;
    for (g_7 = 3; (g_7 >= 0); g_7 -= 1) {
      int32_t *l_8 = (void *)0;
      int32_t *l_9 = (void *)0;
      int32_t *l_10 = &g_11;
      int32_t *l_12[1];
      int i;
      for (i = 0; i < 1; i++)
        l_12[i] = &g_11;
      --l_13;
      if (l_2[g_7])
        break;
    }
    l_54 = func_16(
        ((!0xD373EE76L) &&
         (l_31 =
              ((safe_lshift_func_int16_t_s_u(
                   (((safe_div_func_uint8_t_u_u(
                         (((safe_mul_func_int16_t_s_s(
                               0x1311L,
                               ((*l_29) = (safe_mod_func_uint16_t_u_u(
                                    ((l_27 = &g_11) != (void *)0), l_2[1]))))) |
                           g_6[0][1]) < g_11),
                         g_11)) != g_4) ^
                    g_7),
                   11)) |
               0x2F37FC0336AE3D47LL))));
  }
  return l_31;
}

static float func_16(uint32_t p_17) {
  int32_t l_34 = 0xF1636717L;
  int8_t l_35[4][3];
  uint16_t *l_41[4][3];
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++)
      l_35[i][j] = 0x1EL;
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++)
      l_41[i][j] = (void *)0;
  }
  for (p_17 = (-14); (p_17 <= 39); p_17++) {
    int8_t l_46 = 0xC9L;
    int32_t l_49 = 0xCC114FF6L;
    int32_t *l_51 = &g_7;
    if ((l_35[1][1] = l_34)) {
      uint16_t *l_40 = &g_30;
      uint16_t **l_42 = &l_41[2][1];
      int32_t *l_43 = &l_34;
      (*l_43) &= (safe_mul_func_int16_t_s_s(
          (-1L), ((safe_rshift_func_uint16_t_u_s(
                      (l_40 == ((*l_42) = l_41[1][2])), g_6[2][0])) &&
                  g_4)));
    } else {
      return p_17;
    }
    (*l_51) =
        ((((l_49 ^= ((l_34 = g_5) == (safe_mul_func_int16_t_s_s(
                                         l_46, ((safe_mod_func_uint8_t_u_u(
                                                    (1L < l_35[1][1]), l_46)) ==
                                                g_4))))) >= g_11) &
          g_4) |
         p_17);
  }
  return p_17;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_6[i][j];
    }
  }
  csmith_sink_ = g_7;
  csmith_sink_ = g_11;
  csmith_sink_ = g_30;
  csmith_sink_ = g_53;
  platform_main_end(0, 0);
  return 0;
}
