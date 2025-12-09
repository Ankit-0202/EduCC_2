// Options:   --seed 300295 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_295.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U3 {
  const uint32_t f0;
  int8_t f1;
};

union U4 {
  volatile int32_t f0;
  int32_t f1;
};

static int32_t g_5[3][2] = {{0x215E1ABEL, 0x215E1ABEL},
                            {0x215E1ABEL, 0x215E1ABEL},
                            {0x215E1ABEL, 0x215E1ABEL}};
static int32_t *g_4[2] = {&g_5[0][0], &g_5[0][0]};
static union U4 g_11 = {1L};
static uint16_t g_15[2][1] = {{3UL}, {3UL}};
static volatile uint32_t g_42[1][1] = {{0UL}};
static uint8_t g_46 = 0xDCL;
static uint8_t g_62 = 0x5AL;
static int32_t **g_68 = &g_4[1];
static int32_t ***volatile g_67 = &g_68;
static int32_t **volatile g_70 = &g_4[1];

static int64_t func_1(void);
static int32_t *func_2(int32_t *p_3);
static int32_t **func_6(uint16_t p_7, int32_t *p_8, union U3 p_9, int32_t p_10);

static int64_t func_1(void) {
  int32_t *l_69 = &g_5[0][0];
  (*g_70) = (l_69 = func_2(g_4[1]));
  return (*l_69);
}

static int32_t *func_2(int32_t *p_3) {
  uint16_t *l_14 = &g_15[1][0];
  int32_t *l_18 = &g_11.f1;
  union U3 l_19 = {0x860A421EL};
  uint32_t l_20[3][3] = {{0x27359B50L, 18446744073709551615UL, 0x27359B50L},
                         {0x93826A05L, 0x93826A05L, 0x93826A05L},
                         {0x27359B50L, 18446744073709551615UL, 0x27359B50L}};
  int i, j;
  (*g_67) = func_6((g_11, (safe_rshift_func_uint16_t_u_u(((*l_14)--), 0))),
                   l_18, l_19, l_20[0][2]);
  return l_18;
}

static int32_t **func_6(uint16_t p_7, int32_t *p_8, union U3 p_9,
                        int32_t p_10) {
  uint32_t l_24 = 0xDD7582BAL;
  int32_t l_32[3][1];
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++)
      l_32[i][j] = 0xFE35FE57L;
  }
  for (p_10 = 0; (p_10 <= 12); p_10 = safe_add_func_uint32_t_u_u(p_10, 5)) {
    uint64_t l_33[1];
    int32_t l_37 = 0L;
    int32_t l_39[2][2];
    uint8_t *l_45 = &g_46;
    uint32_t *l_52 = &l_24;
    uint8_t *l_61 = &g_62;
    int i, j;
    for (i = 0; i < 1; i++)
      l_33[i] = 0xEA3821C760FC5C2FLL;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++)
        l_39[i][j] = 0x1947684AL;
    }
    if ((*p_8)) {
      int32_t *l_23[1];
      int i;
      for (i = 0; i < 1; i++)
        l_23[i] = &g_11.f1;
      ++l_24;
    } else {
      int32_t *l_27 = &g_5[0][0];
      int32_t *l_28 = &g_5[0][0];
      int32_t *l_29 = &g_5[0][0];
      int32_t *l_30 = &g_11.f1;
      int32_t *l_31[1];
      int8_t l_36 = 0x6CL;
      int32_t l_38[1];
      int64_t l_40 = (-1L);
      int8_t l_41[2][2];
      int i, j;
      for (i = 0; i < 1; i++)
        l_31[i] = &g_5[0][1];
      for (i = 0; i < 1; i++)
        l_38[i] = 0L;
      for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++)
          l_41[i][j] = 0x15L;
      }
      --l_33[0];
      --g_42[0][0];
    }
    (*p_8) |=
        (((*l_61) =
              (((*l_45)++) !=
               (!(safe_mod_func_int32_t_s_s(
                   (((*l_52)++) < 3UL),
                   (safe_sub_func_uint64_t_u_u(
                       (safe_add_func_uint8_t_u_u(
                           (safe_div_func_uint32_t_u_u(p_9.f0, g_42[0][0])),
                           p_10)),
                       g_5[0][0]))))))),
         1L);
  }
  for (p_10 = 0; (p_10 >= 0); p_10 -= 1) {
    uint64_t l_64 = 0x3E61D3DFD4C6E647LL;
    (*p_8) =
        ((+(l_32[1][0] = (l_64 | (safe_mod_func_int16_t_s_s(p_7, p_9.f0))))) ==
         g_42[0][0]);
    for (p_7 = 0; (p_7 <= 0); p_7 += 1) {
      return &g_4[1];
    }
  }
  return &g_4[1];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_5[i][j];
    }
  }
  csmith_sink_ = g_11.f0;
  csmith_sink_ = g_11.f1;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_15[i][j];
    }
  }
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_42[i][j];
    }
  }
  csmith_sink_ = g_46;
  csmith_sink_ = g_62;
  platform_main_end(0, 0);
  return 0;
}
