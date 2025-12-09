// Options:   --seed 300244 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_244.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  uint64_t f0;
};

static volatile int32_t g_2[2] = {0xB7C7CE53L, 0xB7C7CE53L};
static int32_t g_3 = (-1L);
static const int32_t g_16 = 0x754320E3L;
static const int32_t *g_15 = &g_16;
static int32_t g_18 = 0x25681085L;
static int8_t g_19 = 0xD4L;
static const int32_t **volatile g_31 = &g_15;
static int32_t g_36 = 0xB1C2FBF3L;
static const int32_t **volatile g_39[1] = {&g_15};
static const int32_t **volatile g_40[2] = {&g_15, &g_15};
static const int32_t **volatile g_41 = &g_15;
static int32_t *g_43 = &g_36;
static int32_t **volatile g_42[2][1] = {{&g_43}, {&g_43}};
static int32_t **volatile g_44 = &g_43;
static const union U0 g_55 = {7UL};

static uint8_t func_1(void);
static int32_t *func_6(const int32_t *p_7, int32_t *p_8);
static int32_t *func_9(uint16_t p_10, const int32_t *p_11, int32_t *p_12,
                       int32_t p_13, int16_t p_14);

static uint8_t func_1(void) {
  uint8_t l_20 = 0UL;
  int32_t l_57 = 0x882D7787L;
  int32_t *const **l_58[3];
  int i;
  for (i = 0; i < 3; i++)
    l_58[i] = (void *)0;
  for (g_3 = 0; (g_3 == 11); ++g_3) {
    int32_t *l_17 = &g_18;
    (*g_44) = func_6(
        func_9(
            g_3, (g_15 = &g_3),
            (((g_19 = ((*l_17) = (g_16 > 0xE23A266D210EC320LL))) ^ l_20), &g_3),
            g_2[0], g_3),
        l_17);
    for (l_20 = (-22); (l_20 < 50); ++l_20) {
      if ((**g_31))
        break;
      (*l_17) = (-7L);
    }
  }
  if ((~l_20)) {
    int64_t l_52 = 0x6CBABA27FA52E963LL;
    (*g_43) =
        (g_36, (l_52 = ((safe_sub_func_int64_t_s_s(
                            g_16, (safe_add_func_int8_t_s_s(
                                      ((g_19 | 0L) != 0xFC5A51F3L), g_18)))) ^
                        18446744073709551615UL)));
  } else {
    int32_t *l_56[3][1];
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 1; j++)
        l_56[i][j] = &g_3;
    }
    l_57 = ((*g_43) = (253UL && ((safe_rshift_func_int16_t_s_u(g_2[1], 14)) &&
                                 (g_55, g_18))));
    l_58[1] = (void *)0;
  }
  return g_19;
}

static int32_t *func_6(const int32_t *p_7, int32_t *p_8) {
  int16_t l_33 = 2L;
  int32_t l_34 = 5L;
  l_34 |= (l_33, 9L);
  for (g_18 = 1; (g_18 >= 0); g_18 -= 1) {
    for (l_34 = 0; (l_34 <= 1); l_34 += 1) {
      int32_t *l_35 = &g_36;
      int i;
      (*l_35) &= ((void *)0 == &g_15);
      (*l_35) = (safe_lshift_func_uint8_t_u_u(
          (0UL <= ((4294967287UL != g_2[l_34]) | g_16)), 6));
    }
    (*g_41) = (*g_31);
  }
  return p_8;
}

static int32_t *func_9(uint16_t p_10, const int32_t *p_11, int32_t *p_12,
                       int32_t p_13, int16_t p_14) {
  int32_t l_23 = (-3L);
  int32_t *l_25 = &g_18;
  int32_t **l_24 = &l_25;
  uint64_t l_26 = 0x639E6A4137D6C505LL;
  l_26 ^= (safe_sub_func_int64_t_s_s(
      l_23, (((((((((*l_24) = &g_18) != &g_18), p_13) <= p_14) >= p_14) >=
               1L) != g_2[0]) ^
             p_10)));
  for (p_14 = 0; (p_14 > (-28)); p_14 = safe_sub_func_int16_t_s_s(p_14, 9)) {
    for (g_18 = 18; (g_18 <= (-10));
         g_18 = safe_sub_func_int64_t_s_s(g_18, 4)) {
      (*g_31) = &g_16;
      if ((**g_31))
        break;
    }
    if ((&l_25 != &p_12)) {
      uint8_t l_32 = 0x04L;
      (*l_25) ^= l_32;
    } else {
      if ((*p_12))
        break;
      (**l_24) &= 0x550E3526L;
    }
  }
  return &g_3;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_2[i];
  }
  csmith_sink_ = g_3;
  csmith_sink_ = g_16;
  csmith_sink_ = g_18;
  csmith_sink_ = g_19;
  csmith_sink_ = g_36;
  csmith_sink_ = g_55.f0;
  platform_main_end(0, 0);
  return 0;
}
