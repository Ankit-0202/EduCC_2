// Options:   --seed 300205 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_205.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static const int32_t g_3[3][1] = {{0x4F833FCBL}, {0x4F833FCBL}, {0x4F833FCBL}};
static const int32_t g_6 = 1L;
static const int32_t *g_5 = &g_6;
static uint8_t g_13[3] = {0x04L, 0x04L, 0x04L};
static int32_t g_21 = 1L;
static int32_t *volatile g_20 = &g_21;
static int32_t g_26 = 7L;
static volatile int8_t g_28 = 1L;
static volatile int32_t g_30 = 0x2AD21DD8L;
static volatile uint16_t g_32 = 1UL;
static int32_t *g_37[2][2] = {{&g_26, &g_26}, {&g_26, &g_26}};
static int32_t **g_36 = &g_37[0][0];

static int64_t func_1(void);
static int32_t func_7(int32_t *const *const p_8, int32_t **p_9, int32_t *p_10);
static int32_t *const *func_11(int64_t p_12);

static int64_t func_1(void) {
  const int32_t *l_2 = &g_3[1][0];
  const int32_t **l_4[2];
  int32_t *l_38[3];
  int i;
  for (i = 0; i < 2; i++)
    l_4[i] = &l_2;
  for (i = 0; i < 3; i++)
    l_38[i] = &g_26;
  g_5 = l_2;
  (**g_36) = func_7(func_11(g_3[1][0]), g_36, l_38[0]);
  return g_30;
}

static int32_t func_7(int32_t *const *const p_8, int32_t **p_9, int32_t *p_10) {
  const int32_t *const l_39 = &g_21;
  const int32_t **l_40 = &g_5;
  int32_t *l_41 = &g_26;
  int32_t *l_42 = &g_26;
  int32_t *l_43 = &g_26;
  int32_t *l_44 = &g_21;
  int32_t *l_45 = &g_26;
  int32_t l_46[1][2];
  int32_t *l_47 = &l_46[0][1];
  int32_t *l_48 = &l_46[0][1];
  int32_t *l_49[3];
  int32_t l_50 = 0x40947845L;
  uint32_t l_51 = 0UL;
  int64_t l_54 = 0x773301997FBCB15ELL;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++)
      l_46[i][j] = 1L;
  }
  for (i = 0; i < 3; i++)
    l_49[i] = &g_21;
  (*l_40) = l_39;
  l_51++;
  return l_54;
}

static int32_t *const *func_11(int64_t p_12) {
  uint32_t l_19 = 8UL;
  int32_t l_24 = 0L;
  int32_t l_25 = 0x19909D07L;
  int32_t l_27 = 0xEACB2D50L;
  int8_t l_29 = 0xE6L;
  int32_t *const *l_35 = (void *)0;
  for (p_12 = 2; (p_12 >= 0); p_12 -= 1) {
    const int32_t **l_14 = &g_5;
    int32_t l_31 = 0x7F5E1753L;
    int i;
    (*l_14) = &g_6;
    if (g_13[p_12]) {
      int32_t *l_22 = &g_21;
      int32_t *l_23[3][2] = {{&g_21, &g_21}, {&g_21, &g_21}, {&g_21, &g_21}};
      int i, j;
      (*g_20) = (0xC9CA3191B4956E74LL &
                 (safe_mul_func_int8_t_s_s(
                     ((safe_add_func_uint8_t_u_u(
                          (((((((l_14 != &g_5) > g_13[p_12]) >= g_13[1]) |
                              g_3[1][0]) != l_19) ^
                            (-3L)),
                           0x94L),
                          5L)) ^
                      g_13[p_12]),
                     p_12)));
      g_32--;
    } else {
      l_31 = ((g_6, (g_21, l_29)) <= g_6);
    }
  }
  return l_35;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_3[i][j];
    }
  }
  csmith_sink_ = g_6;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_13[i];
  }
  csmith_sink_ = g_21;
  csmith_sink_ = g_26;
  csmith_sink_ = g_28;
  csmith_sink_ = g_30;
  csmith_sink_ = g_32;
  platform_main_end(0, 0);
  return 0;
}
