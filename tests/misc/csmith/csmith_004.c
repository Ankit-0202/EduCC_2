// Options:   --seed 100004 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_004.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint8_t f0;
  uint8_t f1;
};

struct S1 {
  int16_t f0;
  const int16_t f1;
};

static int32_t g_2 = 0x46DB5052L;
static struct S0 g_15[4][2] = {{{0xA9L, 254UL}, {0UL, 5UL}},
                               {{0UL, 5UL}, {0xA9L, 254UL}},
                               {{0UL, 5UL}, {0UL, 5UL}},
                               {{0xA9L, 254UL}, {0UL, 5UL}}};
static int32_t g_21 = 0x9ADB8213L;
static int32_t *const volatile g_20 = &g_21;
static uint64_t g_23 = 18446744073709551615UL;
static int32_t *g_42 = &g_21;
static int32_t **g_41 = &g_42;
static int32_t **g_44[3][3] = {
    {&g_42, &g_42, &g_42}, {&g_42, &g_42, &g_42}, {&g_42, &g_42, &g_42}};

static int32_t func_1(void);
static int32_t func_5(uint32_t p_6, int16_t p_7, int32_t p_8, int16_t p_9,
                      struct S0 p_10);

static int32_t func_1(void) {
  int32_t l_11 = (-3L);
  int32_t ***l_43[2];
  int i;
  for (i = 0; i < 2; i++)
    l_43[i] = &g_41;
  for (g_2 = 0; (g_2 >= (-4)); g_2 = safe_sub_func_uint8_t_u_u(g_2, 6)) {
    uint8_t l_12 = 1UL;
    int32_t *l_22[4] = {&l_11, &l_11, &l_11, &l_11};
    struct S1 *l_33 = (void *)0;
    int i;
    g_23 |=
        func_5(l_11, l_12, (safe_add_func_uint64_t_u_u((0L != 0xCBA8L), l_12)),
               g_2, g_15[3][0]);
    for (g_23 = 0; (g_23 > 7); g_23 = safe_add_func_int32_t_s_s(g_23, 8)) {
      struct S1 *const l_28 = (void *)0;
      struct S1 **l_34 = &l_33;
      for (g_21 = 16; (g_21 > (-7)); --g_21) {
        struct S1 *l_30 = (void *)0;
        struct S1 **l_29 = &l_30;
        (*l_29) = l_28;
        l_11 ^= (*g_20);
      }
      l_11 = (safe_add_func_int16_t_s_s(
          ((((*l_34) = l_33) == (void *)0) ||
           (safe_sub_func_int16_t_s_s(
               (safe_lshift_func_int8_t_s_s(
                   (safe_rshift_func_int16_t_s_s(g_23, 4)), 3)),
               0UL))),
          g_2));
    }
  }
  g_44[1][2] = (g_41 = g_41);
  return (*g_42);
}

static int32_t func_5(uint32_t p_6, int16_t p_7, int32_t p_8, int16_t p_9,
                      struct S0 p_10) {
  int32_t *l_18 = (void *)0;
  int32_t *l_19 = (void *)0;
  (*g_20) |= ((safe_lshift_func_uint16_t_u_s(0x2278L, 1)) > 0xF72BL);
  return (*g_20);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
    }
  }
  csmith_sink_ = g_21;
  csmith_sink_ = g_23;
  platform_main_end(0, 0);
  return 0;
}
