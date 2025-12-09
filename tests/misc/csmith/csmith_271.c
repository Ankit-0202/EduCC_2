// Options:   --seed 300271 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_271.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  volatile int8_t f0;
};

union U1 {
  int16_t f0;
};

union U4 {
  const uint32_t f0;
};

union U5 {
  volatile uint64_t f0;
  uint64_t f1;
};

union U6 {
  volatile int8_t *f0;
};

static volatile union U1 g_12 = {0xFAF4L};
static uint64_t g_15 = 0x57D670012AF0488FLL;
static int8_t g_18 = 1L;
static int32_t g_24 = 0x0E779066L;
static volatile int32_t g_31 = 0x9E8A28D8L;
static int32_t g_32 = 3L;
static volatile int64_t g_34 = 0xCB070FCBC8423537LL;
static uint32_t g_35 = 1UL;
static uint8_t g_41 = 4UL;
static uint32_t g_55[1] = {0x70C68704L};
static union U5 g_59[2][1] = {{{1UL}}, {{1UL}}};
static union U6 g_70 = {0};
static int8_t *g_71 = &g_18;
static volatile union U0 g_75 = {1L};
static uint32_t g_81 = 0x14E4505BL;
static uint32_t g_86 = 0x02817ACDL;
static int32_t g_88 = 1L;

static int32_t func_1(void);
static int32_t *const func_2(union U4 p_3, int8_t *p_4);
static int8_t *func_6(int64_t p_7, uint64_t p_8, int32_t p_9, int16_t p_10,
                      int8_t *p_11);

static int32_t func_1(void) {
  union U4 l_5[1] = {{0xD7865925L}};
  uint64_t *l_14[2];
  int32_t l_16[1][3];
  int8_t *l_17 = &g_18;
  int32_t *l_62 = &l_16[0][0];
  int16_t l_89 = 1L;
  int i, j;
  for (i = 0; i < 2; i++)
    l_14[i] = &g_15;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++)
      l_16[i][j] = 0xA4E86524L;
  }
  l_62 = func_2(l_5[0], func_6((g_12, (~(l_16[0][2] = (5L && 0L)))), g_15, g_15,
                               g_15, l_17));
  for (g_35 = 0; (g_35 <= 0); g_35 += 1) {
    int8_t *l_72 = &g_18;
    int32_t l_84 = (-4L);
    for (g_24 = 1; (g_24 >= 0); g_24 -= 1) {
      int8_t **l_69 = &l_17;
      int8_t *l_74[2][2];
      int8_t **l_73 = &l_74[1][1];
      int i, j;
      for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++)
          l_74[i][j] = &g_18;
      }
      g_31 |= (safe_add_func_uint64_t_u_u(
          (safe_div_func_uint64_t_u_u(
              l_16[g_35][g_35],
              (safe_rshift_func_int8_t_s_u(
                  (((*l_69) = &g_18) ==
                   ((*l_73) = (l_72 = (g_71 = (g_70, &g_18))))),
                  7)))),
          g_55[g_35]));
    }
    for (g_32 = 0; (g_32 >= 0); g_32 -= 1) {
      uint32_t *l_80 = &g_81;
      uint32_t *l_85 = &g_86;
      int32_t *l_87[2];
      int i, j;
      for (i = 0; i < 2; i++)
        l_87[i] = &g_88;
      g_88 |= (g_75,
               ((-1L) > ((((*l_85) = ((safe_mul_func_uint16_t_u_u(
                                          ((safe_add_func_uint32_t_u_u(
                                               ((*l_80)++), l_16[g_35][g_35])),
                                           g_55[g_32]),
                                          l_84)),
                                      g_12.f0)) |
                          l_16[g_35][g_35]) <= (*l_62))));
    }
  }
  return l_89;
}

static int32_t *const func_2(union U4 p_3, int8_t *p_4) {
  int64_t l_56 = (-8L);
  union U5 *l_58 = &g_59[1][0];
  int32_t *const l_61 = &g_24;
  for (g_24 = 0; (g_24 >= 0); g_24 -= 1) {
    int32_t l_57[3];
    union U5 **l_60 = &l_58;
    int i;
    for (i = 0; i < 3; i++)
      l_57[i] = 0x983969C1L;
    if (l_56)
      break;
    (*l_60) = ((l_57[2] <= l_56), l_58);
  }
  return l_61;
}

static int8_t *func_6(int64_t p_7, uint64_t p_8, int32_t p_9, int16_t p_10,
                      int8_t *p_11) {
  union U6 l_19 = {0};
  union U6 *l_20 = &l_19;
  int32_t l_28[2];
  int8_t *l_54 = (void *)0;
  int i;
  for (i = 0; i < 2; i++)
    l_28[i] = 0L;
  if (((p_7, (((*l_20) = l_19), &g_18)) == &g_18)) {
    int16_t l_29 = 0x6344L;
    int32_t l_33 = 0L;
    int32_t *l_38 = &l_33;
    int32_t *l_39 = &l_28[0];
    int32_t *l_40[1];
    int i;
    for (i = 0; i < 1; i++)
      l_40[i] = &l_28[0];
    for (g_15 = 0; (g_15 > 13); ++g_15) {
      int32_t *l_23 = &g_24;
      int32_t *l_25 = &g_24;
      int32_t *l_26 = &g_24;
      int32_t *l_27[2];
      int8_t l_30 = 0x21L;
      int i;
      for (i = 0; i < 2; i++)
        l_27[i] = (void *)0;
      g_35--;
    }
    --g_41;
  } else {
    int32_t l_44 = 0xC8D67996L;
    int32_t *l_47 = &g_24;
  lbl_53:
    (*l_47) &=
        ((l_28[0] > (l_44 > (safe_rshift_func_int16_t_s_u(g_35, 2)))), 1L);
    for (l_44 = 0; (l_44 < (-25)); --l_44) {
      union U6 *l_52 = &l_19;
      (*l_47) |=
          (+(+(l_28[0] = (((void *)0 != l_52) == ((g_12.f0 <= p_9) | p_7)))));
      if (g_15)
        goto lbl_53;
    }
  }
  return l_54;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_12.f0;
  csmith_sink_ = g_15;
  csmith_sink_ = g_18;
  csmith_sink_ = g_24;
  csmith_sink_ = g_31;
  csmith_sink_ = g_32;
  csmith_sink_ = g_34;
  csmith_sink_ = g_35;
  csmith_sink_ = g_41;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_55[i];
  }
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++) {
    }
  }
  csmith_sink_ = g_75.f0;
  csmith_sink_ = g_81;
  csmith_sink_ = g_86;
  csmith_sink_ = g_88;
  platform_main_end(0, 0);
  return 0;
}
