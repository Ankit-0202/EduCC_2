// Options:   --seed 300274 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_274.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  int16_t f0;
  int8_t *const f1;
};

static int8_t g_6 = (-10L);
static int8_t *g_5 = &g_6;
static int8_t **g_4 = &g_5;
static union U0 g_30 = {2L};
static union U0 *g_32 = &g_30;
static union U0 **const volatile g_31 = &g_32;
static int32_t g_34 = 4L;
static const int8_t *g_39 = &g_6;
static const int8_t **g_38 = &g_39;
static const int8_t ***volatile g_40 = (void *)0;
static const int8_t ***const volatile g_41 = (void *)0;
static const int8_t ***volatile g_43[3][2] = {
    {&g_38, &g_38}, {&g_38, &g_38}, {&g_38, &g_38}};
static const int8_t ***volatile g_44 = &g_38;

static uint8_t func_1(void);
static const int8_t **func_2(int8_t **p_3);
static const int32_t func_13(int8_t **p_14, int16_t p_15, uint16_t p_16,
                             const int64_t p_17);

static uint8_t func_1(void) {
  const int8_t ***l_42 = (void *)0;
  (*g_44) = func_2(g_4);
  return g_6;
}

static const int8_t **func_2(int8_t **p_3) {
  uint64_t l_22 = 0x92F1E5C8A52B4B5ALL;
  int16_t l_23 = 0x0578L;
  int32_t l_35 = 0xDA259C42L;
  const int8_t *l_37 = &g_6;
  const int8_t **l_36 = &l_37;
  for (g_6 = 0; (g_6 < 1); g_6 = safe_add_func_uint32_t_u_u(g_6, 3)) {
    int8_t **l_9 = (void *)0;
    int32_t l_10 = (-1L);
    uint64_t l_25 = 0xE072305ABA9A9843LL;
    uint64_t l_27 = 18446744073709551606UL;
    l_10 = (((l_9 == l_9), (void *)0) != (void *)0);
    for (l_10 = 16; (l_10 >= (-29));
         l_10 = safe_sub_func_int64_t_s_s(l_10, 2)) {
      int64_t l_24 = 0x4E2B79DC86695CD1LL;
      int64_t *l_26[3][3];
      uint8_t l_28 = 248UL;
      int32_t *l_33 = &g_34;
      int i, j;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++)
          l_26[i][j] = &l_24;
      }
      (*l_33) ^= func_13(
          &g_5,
          ((l_27 = ((safe_lshift_func_int16_t_s_s(
                        (((((((((safe_mod_func_int64_t_s_s(
                                    l_22, ((l_23 != l_24) || 1UL))) <= g_6),
                               l_10),
                              g_6) &&
                             l_10) != 6UL) ||
                           l_10) ||
                          l_10) |
                         l_25),
                        l_25)) &&
                    g_6)) != l_28),
          l_28, l_23);
    }
  }
  l_35 &= l_23;
  return g_38;
}

static const int32_t func_13(int8_t **p_14, int16_t p_15, uint16_t p_16,
                             const int64_t p_17) {
  union U0 *l_29 = &g_30;
  (*g_31) = l_29;
  return g_30.f0;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_6;
  csmith_sink_ = g_30.f0;
  csmith_sink_ = g_34;
  platform_main_end(0, 0);
  return 0;
}
