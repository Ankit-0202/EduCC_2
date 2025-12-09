// Options:   --seed 300270 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_270.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int32_t f0;
  uint16_t f1;
};

struct S1 {
  const uint16_t f0;
  volatile struct S0 f1;
  volatile uint32_t f2;
};

static volatile uint16_t g_16[3][3] = {
    {0UL, 0UL, 0UL}, {65535UL, 65535UL, 65535UL}, {0UL, 0UL, 0UL}};
static uint16_t g_17[3][3] = {{65533UL, 0UL, 65533UL},
                              {65535UL, 65535UL, 65535UL},
                              {65533UL, 0UL, 65533UL}};
static uint32_t g_22 = 4294967295UL;
static volatile int32_t g_28 = 0x3BE46552L;
static volatile int32_t *volatile g_27 = &g_28;
static int64_t g_30 = (-1L);
static int32_t g_31 = 0x503B5B0DL;
static int32_t g_33[3] = {(-1L), (-1L), (-1L)};
static struct S1 g_35 = {1UL, {0xBB9CEC02L, 0xFCE9L}, 0x866B3883L};
static struct S1 *g_37[3][3] = {
    {&g_35, &g_35, &g_35}, {&g_35, &g_35, &g_35}, {&g_35, &g_35, &g_35}};
static struct S1 **volatile g_36 = &g_37[0][0];
static const struct S1 g_47 = {65527UL, {0x3177355AL, 6UL}, 4294967295UL};

static const struct S1 func_1(void);
static int32_t *func_2(uint64_t p_3);
static uint64_t func_4(uint32_t p_5, uint16_t p_6, int32_t p_7, uint16_t p_8);

static const struct S1 func_1(void) {
  int8_t l_15 = 0xEEL;
  int32_t **l_40 = (void *)0;
  int32_t *l_42 = &g_33[2];
  int32_t **l_41 = &l_42;
  (*l_41) = func_2(func_4(
      (safe_mod_func_int8_t_s_s(
          ((((safe_add_func_int16_t_s_s(
                 ((safe_sub_func_uint32_t_u_u(
                      (((l_15 || l_15), (0x4AL & 0xE2L)) || (-1L)), l_15)) <=
                  l_15),
                 g_16[1][0])) == g_17[1][0]),
            l_15) |
           0x48A2B8EAL),
          g_17[1][0])),
      l_15, l_15, g_17[1][2]));
  (*g_27) = (safe_rshift_func_uint16_t_u_s(
      g_35.f0, (safe_rshift_func_int16_t_s_s(((*g_27) | (0xC3L != g_35.f0)),
                                             g_17[1][2]))));
  return g_47;
}

static int32_t *func_2(uint64_t p_3) {
  struct S1 *l_34 = &g_35;
  int32_t *l_39 = &g_33[2];
  (*g_36) = l_34;
  for (g_22 = 0; (g_22 <= 2); g_22 += 1) {
    uint32_t l_38[2][1];
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 1; j++)
        l_38[i][j] = 1UL;
    }
    l_38[1][0] = (-7L);
    for (g_31 = 2; (g_31 >= 0); g_31 -= 1) {
      return &g_33[2];
    }
  }
  return l_39;
}

static uint64_t func_4(uint32_t p_5, uint16_t p_6, int32_t p_7, uint16_t p_8) {
  uint32_t l_20 = 0UL;
  uint32_t *l_21 = &g_22;
  int64_t *l_29 = &g_30;
  int32_t *l_32 = &g_33[2];
  (*l_32) = (g_31 |= (0xC4F32B7B88CDF8ABLL >=
                      ((safe_sub_func_int32_t_s_s(l_20, (--(*l_21)))) &
                       (((((*l_29) = (safe_add_func_int8_t_s_s(
                               ((void *)0 == g_27), g_17[1][0]))) ||
                          g_30) ^
                         0x19AE86A6L),
                        (*g_27)))));
  return (*l_32);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_16[i][j];
    }
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_17[i][j];
    }
  }
  csmith_sink_ = g_22;
  csmith_sink_ = g_28;
  csmith_sink_ = g_30;
  csmith_sink_ = g_31;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_33[i];
  }
  csmith_sink_ = g_35.f0;
  csmith_sink_ = g_35.f1.f0;
  csmith_sink_ = g_35.f1.f1;
  csmith_sink_ = g_35.f2;
  csmith_sink_ = g_47.f0;
  csmith_sink_ = g_47.f1.f0;
  csmith_sink_ = g_47.f1.f1;
  csmith_sink_ = g_47.f2;
  platform_main_end(0, 0);
  return 0;
}
