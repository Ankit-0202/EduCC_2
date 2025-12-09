// Options:   --seed 100022 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_022.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint32_t g_7 = 4294967289UL;
static const volatile int8_t g_11[2][3] = {{0xC3L, 0x6CL, 0xC3L},
                                           {0xC3L, 0x6CL, 0xC3L}};
static uint64_t g_12 = 0x773672D714F98CAFLL;
static int32_t g_14[3] = {0L, 0L, 0L};
static uint8_t g_27 = 0UL;
static int8_t g_30 = (-1L);
static int32_t *g_32 = &g_14[2];
static int32_t **volatile g_31[2][3] = {{(void *)0, &g_32, (void *)0},
                                        {(void *)0, &g_32, (void *)0}};
static uint16_t g_35 = 0x9F41L;
static volatile uint8_t g_37 = 0xF7L;
static volatile uint8_t *const g_36 = &g_37;
static volatile int8_t g_38[1] = {9L};
static volatile int8_t *volatile *volatile g_41 = (void *)0;
static const int32_t g_48 = 4L;
static const int32_t *g_47 = &g_48;

static int32_t func_1(void);
static const int64_t func_15(uint32_t p_16, uint32_t *p_17, int16_t p_18,
                             uint16_t p_19);

static int32_t func_1(void) {
  uint32_t *l_5 = (void *)0;
  uint32_t *l_6 = &g_7;
  int32_t l_10[3];
  uint8_t l_34 = 0x81L;
  int32_t *l_55 = &g_14[2];
  int32_t *l_56[3][2] = {
      {&l_10[1], &l_10[1]}, {&l_10[1], &l_10[1]}, {&l_10[1], &l_10[1]}};
  uint16_t l_57 = 0UL;
  int i, j;
  for (i = 0; i < 3; i++)
    l_10[i] = (-1L);
  if (((~(safe_unary_minus_func_uint16_t_u(
           ((((!(0x21L &&
                 (((*l_6) = 1UL), (safe_add_func_int8_t_s_s(g_7, l_10[1]))))),
              l_10[1]) >= l_10[1]) >= g_11[0][1])))) != g_12)) {
    for (g_12 = 0; (g_12 <= 2); g_12 += 1) {
      uint8_t *l_26[1];
      int32_t l_28 = 0x9E56E623L;
      int8_t *l_29 = &g_30;
      int i;
      for (i = 0; i < 1; i++)
        l_26[i] = &g_27;
      for (g_7 = 0; (g_7 <= 2); g_7 += 1) {
        int32_t *l_13 = &g_14[2];
        int i;
        (*l_13) ^= l_10[g_7];
        if (g_11[0][2])
          break;
      }
      g_35 ^=
          (func_15(
               ((safe_mul_func_int8_t_s_s(
                    ((*l_29) = (0xC2E607D1L !=
                                ((safe_lshift_func_int8_t_s_u(l_10[g_12], 3)) ^
                                 (safe_mod_func_uint8_t_u_u(
                                     (g_27 = (l_28 = 0x08L)), g_12))))),
                    g_12)) > l_10[0]),
               &g_7, g_11[0][1], g_14[1]),
           l_34);
    }
  } else {
    int8_t *l_44 = &g_30;
    int8_t **l_43 = &l_44;
    int32_t l_45[2][3] = {{0x7E8F5349L, 0x7E8F5349L, 0xDCF8610FL},
                          {0x7E8F5349L, 0x7E8F5349L, 0xDCF8610FL}};
    int i, j;
    if ((((g_7 | ((g_36 != (void *)0) > g_37)), g_38[0]) <= g_27)) {
      for (g_30 = 0; (g_30 < (-10));
           g_30 = safe_sub_func_uint16_t_u_u(g_30, 4)) {
        int16_t l_42[4] = {0x52EEL, 0x52EEL, 0x52EEL, 0x52EEL};
        int i;
        g_41 = g_41;
        if (l_42[2])
          continue;
      }
      (*g_32) ^= (l_43 == (l_45[1][1], g_41));
    } else {
      int32_t *l_46 = &g_14[0];
      (*l_46) = ((((l_46 != (g_47 = &l_10[2])) &
                   (safe_sub_func_uint64_t_u_u(
                       ((safe_lshift_func_int16_t_s_u(
                            (((((safe_mod_func_uint64_t_u_u(g_30, (*l_46))),
                                (*l_46)) >= 0x02B5L),
                              g_14[2]) != g_35),
                            4)) >= g_14[2]),
                       (*l_46)))),
                  (*l_46)) < g_38[0]);
    }
  }
  l_57--;
  return (*l_55);
}

static const int64_t func_15(uint32_t p_16, uint32_t *p_17, int16_t p_18,
                             uint16_t p_19) {
  int32_t **l_33 = &g_32;
  (*l_33) = &g_14[2];
  (**l_33) = (-1L);
  return (**l_33);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_7;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_11[i][j];
    }
  }
  csmith_sink_ = g_12;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_14[i];
  }
  csmith_sink_ = g_27;
  csmith_sink_ = g_30;
  csmith_sink_ = g_35;
  csmith_sink_ = g_37;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_38[i];
  }
  csmith_sink_ = g_48;
  platform_main_end(0, 0);
  return 0;
}
