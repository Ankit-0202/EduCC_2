// Options:   --seed 200161 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_161.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_8 = 0x283066C9L;
static int16_t g_12 = 0xA61FL;
static int64_t g_14 = (-8L);
static float g_15[1] = {0x9.150FAEp+39};
static uint32_t g_16[4] = {1UL, 1UL, 1UL, 1UL};
static int32_t g_24 = 0x5ADF851FL;
static int8_t g_37[4][4] = {{0x83L, 0x35L, 0x83L, 0x35L},
                            {0x83L, 0x35L, 0x83L, 0x35L},
                            {0x83L, 0x35L, 0x83L, 0x35L},
                            {0x83L, 0x35L, 0x83L, 0x35L}};
static int32_t *g_41 = &g_24;
static int32_t **volatile g_40 = &g_41;
static int32_t g_44 = 1L;
static volatile int64_t g_45 = 0L;
static volatile uint32_t g_46[4][4] = {
    {0x870A6552L, 0UL, 0UL, 0x870A6552L},
    {0UL, 0x870A6552L, 0x3F01E835L, 18446744073709551615UL},
    {0UL, 0x3F01E835L, 0UL, 1UL},
    {0x870A6552L, 18446744073709551615UL, 1UL, 1UL}};

static const uint32_t func_1(void);
static int32_t *func_2(const int64_t p_3, const uint32_t p_4,
                       int32_t *const p_5);

static const uint32_t func_1(void) {
  const uint64_t l_6[1][4] = {{0x88A137B1891F782ALL, 0x88A137B1891F782ALL,
                               0x88A137B1891F782ALL, 0x88A137B1891F782ALL}};
  int32_t *l_7[3][3] = {
      {&g_8, &g_8, &g_8}, {&g_8, &g_8, &g_8}, {&g_8, &g_8, &g_8}};
  int8_t *l_13[1][3];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++)
      l_13[i][j] = (void *)0;
  }
  (*g_40) =
      func_2(l_6[0][0],
             ((g_8 ^= l_6[0][0]) <=
              (+((safe_lshift_func_int8_t_s_u(
                     ((((g_16[3] = (g_14 ^= g_12)) != (-9L)) < g_12) <= g_12),
                     7)) == 6UL))),
             l_7[0][0]);
  for (g_12 = 0; (g_12 < 19); g_12 = safe_add_func_uint8_t_u_u(g_12, 3)) {
    --g_46[1][1];
  }
  return g_16[3];
}

static int32_t *func_2(const int64_t p_3, const uint32_t p_4,
                       int32_t *const p_5) {
  uint64_t l_20 = 0x3FA9DFEEE83ADEB9LL;
  int32_t l_28 = 0x0D6B1F84L;
  for (g_14 = 0; (g_14 <= 0); g_14 += 1) {
    for (g_12 = 0; (g_12 <= 0); g_12 += 1) {
      int32_t *l_17 = (void *)0;
      int32_t *l_18 = &g_8;
      int32_t *l_19[1];
      int i;
      for (i = 0; i < 1; i++)
        l_19[i] = &g_8;
      l_20--;
      if (l_20)
        continue;
    }
    for (l_20 = 0; (l_20 <= 0); l_20 += 1) {
      int32_t *l_23 = &g_24;
      (*l_23) ^= g_8;
    }
  }
  for (g_8 = 0; (g_8 <= 3); g_8 += 1) {
    uint64_t *l_27 = &l_20;
    int16_t *l_29[3];
    uint32_t l_33 = 0UL;
    int8_t *l_36 = &g_37[1][3];
    int i;
    for (i = 0; i < 3; i++)
      l_29[i] = &g_12;
    l_28 = (safe_rshift_func_int8_t_s_s(
        0L,
        (g_16[g_8] |
         (((((*l_27) = (p_4 || 0xB9L)), l_20) ^ 0x2BE8CA404523830ALL), g_24))));
    if (((((g_12 = (p_3 & p_4)) <= p_3) || g_16[0]) >= g_14)) {
      int32_t *l_30 = (void *)0;
      int32_t *l_31 = &g_24;
      int32_t *l_32 = &g_24;
      int8_t *l_38 = &g_37[2][1];
      int8_t **l_39 = &l_38;
      l_33++;
      (*l_32) |= (l_36 == ((*l_39) = l_38));
    } else {
      if ((*p_5))
        break;
    }
  }
  return &g_8;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_8;
  csmith_sink_ = g_12;
  csmith_sink_ = g_14;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_15[i];
  }
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_16[i];
  }
  csmith_sink_ = g_24;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_37[i][j];
    }
  }
  csmith_sink_ = g_44;
  csmith_sink_ = g_45;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_46[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
