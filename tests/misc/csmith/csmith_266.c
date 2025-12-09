// Options:   --seed 300266 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_266.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile uint8_t g_5 = 0UL;
static int32_t g_17 = 0xE815F842L;
static int32_t *g_16 = &g_17;
static int8_t g_40 = (-10L);
static int16_t g_41 = 1L;
static int8_t g_43 = 0xE0L;
static int32_t *g_47 = &g_17;
static int64_t g_59 = 0x6DF3F1863D476FC5LL;
static volatile uint16_t g_60[3] = {0x9DF7L, 0x9DF7L, 0x9DF7L};

static uint16_t func_1(void);
static int32_t *func_18(int32_t *p_19, int32_t *p_20);
static int32_t *func_21(int16_t p_22, int16_t p_23);

static uint16_t func_1(void) {
  int32_t l_2 = 0xB4E1A362L;
  int32_t l_3 = (-7L);
  int32_t *l_4[2][3] = {{&l_3, &l_3, &l_3}, {&l_3, &l_3, &l_3}};
  int32_t **l_57 = &l_4[1][2];
  int32_t *l_58 = &l_3;
  int i, j;
  g_5--;
  if ((safe_rshift_func_int8_t_s_u(
          (safe_div_func_int32_t_s_s(
              g_5,
              (safe_add_func_int16_t_s_s(
                  (((safe_mul_func_uint8_t_u_u(
                        (((g_16 != ((*l_57) = func_18(func_21(g_17, g_17),
                                                      &l_3))) < 0x28543B57L),
                         0x3EL),
                        l_2)),
                    l_58) == g_16),
                  g_59)))),
          g_59))) {
    --g_60[1];
  } else {
    uint64_t l_65 = 1UL;
    l_65 ^= (safe_add_func_int16_t_s_s(
        (((*g_16) == ((0xF2F470B9C45D1882LL || g_17) || (*l_58))), 0x68F5L),
        0x1411L));
  }
  return g_59;
}

static int32_t *func_18(int32_t *p_19, int32_t *p_20) {
  uint8_t l_55 = 0xEEL;
  for (g_41 = 5; (g_41 != (-13)); g_41 = safe_sub_func_uint8_t_u_u(g_41, 9)) {
    int8_t l_52[2];
    int32_t *l_56 = &g_17;
    int i;
    for (i = 0; i < 2; i++)
      l_52[i] = 5L;
    for (g_17 = 1; (g_17 >= 0); g_17 -= 1) {
      (*p_20) =
          (safe_lshift_func_uint8_t_u_s((l_55 && ((void *)0 == l_56)), g_40));
    }
  }
  return p_20;
}

static int32_t *func_21(int16_t p_22, int16_t p_23) {
  uint32_t l_37 = 4294967295UL;
  int8_t *l_38 = (void *)0;
  int8_t *l_39 = &g_40;
  int8_t *l_42 = &g_43;
  uint8_t l_44[3];
  int32_t *l_49 = &g_17;
  int i;
  for (i = 0; i < 3; i++)
    l_44[i] = 0x9FL;
  (*g_16) =
      (g_17 != ((safe_mul_func_uint16_t_u_u(
                    ((safe_lshift_func_uint8_t_u_u(
                         ((safe_mul_func_int8_t_s_s(
                              ((*l_42) |=
                               ((safe_lshift_func_uint8_t_u_u(
                                    (safe_rshift_func_uint16_t_u_u(
                                        (safe_add_func_uint16_t_u_u(
                                            1UL, ((g_41 |= (+((*l_39) = l_37))),
                                                  65533UL))),
                                        14)),
                                    l_37)) &&
                                p_22)),
                              l_37)) &&
                          l_37),
                         l_37)) == g_17),
                    1UL)) &&
                g_41));
  for (p_22 = 0; (p_22 <= 2); p_22 += 1) {
    int32_t *l_48 = &g_17;
    for (p_23 = 0; (p_23 <= 2); p_23 += 1) {
      int32_t *l_46 = &g_17;
      int32_t **l_45[2];
      int i;
      for (i = 0; i < 2; i++)
        l_45[i] = &l_46;
      l_48 = (g_47 = &g_17);
    }
  }
  return l_49;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_5;
  csmith_sink_ = g_17;
  csmith_sink_ = g_40;
  csmith_sink_ = g_41;
  csmith_sink_ = g_43;
  csmith_sink_ = g_59;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_60[i];
  }
  platform_main_end(0, 0);
  return 0;
}
