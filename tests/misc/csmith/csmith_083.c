// Options:   --seed 100083 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_083.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile uint16_t g_9[2] = {1UL, 1UL};
static uint16_t g_15[1][3] = {{8UL, 8UL, 8UL}};
static uint16_t g_17 = 1UL;
static const int16_t g_18 = (-9L);
static uint32_t g_30[1] = {0x48DC164FL};
static int32_t g_32[4][4] = {{0xA80278EEL, (-5L), 0x215A6091L, (-5L)},
                             {(-5L), 0xBB002891L, 0x215A6091L, 0x215A6091L},
                             {0xA80278EEL, 0xA80278EEL, (-5L), 0x215A6091L},
                             {(-1L), 0xBB002891L, (-1L), (-5L)}};
static int32_t g_35[3][4] = {{(-1L), (-1L), 0x7800FF68L, (-1L)},
                             {(-1L), (-10L), (-10L), (-1L)},
                             {(-10L), (-1L), (-10L), (-10L)}};

static uint64_t func_1(void);
static int8_t func_21(int8_t p_22, uint32_t p_23);

static uint64_t func_1(void) {
  int16_t l_10 = (-1L);
  uint8_t l_13 = 0UL;
  uint16_t *l_14 = &g_15[0][0];
  uint16_t *l_16 = &g_17;
  int32_t *l_38 = &g_35[1][2];
  int32_t **l_37 = &l_38;
  if ((safe_rshift_func_uint16_t_u_s(
          (!(safe_mod_func_int32_t_s_s(
              ((safe_add_func_int32_t_s_s(g_9[0], l_10)) ^
               ((safe_sub_func_int8_t_s_s((((*l_16) &= ((*l_14) = l_13)), 6L),
                                          g_18)) |
                0x0BFB3A4DF6F97812LL)),
              g_18))),
          9))) {
    const int16_t l_33 = 0xCFD8L;
    int32_t *l_34[2];
    int i;
    for (i = 0; i < 2; i++)
      l_34[i] = &g_35[0][3];
    g_35[0][3] |= (safe_div_func_int8_t_s_s(
        func_21(g_9[0], (safe_lshift_func_int8_t_s_u(
                            (safe_rshift_func_int16_t_s_s(g_15[0][0], 3)), 6))),
        l_33));
  } else {
    int32_t l_36 = 0L;
    return l_36;
  }
  (*l_37) = (g_17, &g_32[0][2]);
  return g_35[0][3];
}

static int8_t func_21(int8_t p_22, uint32_t p_23) {
  uint32_t *l_29 = &g_30[0];
  int32_t *l_31[4] = {&g_32[3][3], &g_32[3][3], &g_32[3][3], &g_32[3][3]};
  int i;
  g_32[3][3] ^= (safe_unary_minus_func_uint32_t_u(((*l_29) = 0UL)));
  return p_22;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_9[i];
  }
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_15[i][j];
    }
  }
  csmith_sink_ = g_17;
  csmith_sink_ = g_18;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_30[i];
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_32[i][j];
    }
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_35[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
