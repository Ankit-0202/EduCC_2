// Options:   --seed 100002 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_002.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_3 = 0x7C8748AFL;
static volatile int32_t g_4 = (-1L);
static int32_t g_5[1][1] = {{0x35A23E86L}};
static uint64_t g_15 = 1UL;
static uint32_t g_18[4] = {0x40EE1D45L, 0x40EE1D45L, 0x40EE1D45L, 0x40EE1D45L};
static int32_t g_20 = 0x68FAB8D2L;
static volatile int32_t g_27[2][4] = {{0xA7E1289EL, (-5L), (-5L), 0xA7E1289EL},
                                      {(-5L), 0xA7E1289EL, (-5L), (-5L)}};

static uint8_t func_1(void);
static uint64_t func_8(int64_t p_9, uint32_t p_10, const int64_t p_11);

static uint8_t func_1(void) {
  uint64_t l_2[2][4] = {{0x76F5020F89B54615LL, 0x76F5020F89B54615LL,
                         18446744073709551615UL, 0x76F5020F89B54615LL},
                        {0x76F5020F89B54615LL, 0x8C3AD3B3152C58FBLL,
                         0x8C3AD3B3152C58FBLL, 0x76F5020F89B54615LL}};
  int32_t l_24 = (-2L);
  int32_t l_25[4] = {0x2DDFDAF0L, 0x2DDFDAF0L, 0x2DDFDAF0L, 0x2DDFDAF0L};
  int i, j;
  for (g_3 = 1; (g_3 >= 0); g_3 -= 1) {
    const uint16_t l_16 = 0x40E1L;
    int32_t l_31[1][2];
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 2; j++)
        l_31[i][j] = 0xFAADAD2DL;
    }
    for (g_5[0][0] = 1; (g_5[0][0] >= 0); g_5[0][0] -= 1) {
      uint64_t *l_13 = (void *)0;
      uint64_t *l_14 = &g_15;
      uint32_t *l_17 = &g_18[1];
      int32_t l_26 = 1L;
      int32_t l_28 = 1L;
      int32_t l_29 = (-1L);
      int32_t l_30[3];
      uint32_t l_32 = 0x32CBEB03L;
      uint32_t l_35 = 9UL;
      int i, j;
      for (i = 0; i < 3; i++)
        l_30[i] = (-1L);
      if (((l_2[g_3][g_5[0][0]] |
            (((*l_17) = (((l_2[1][3],
                           (safe_mod_func_uint8_t_u_u(
                               (((((*l_14) = func_8(g_4, l_2[g_3][g_5[0][0]],
                                                    l_2[0][2])) == l_16) ^
                                 l_2[g_3][g_5[0][0]]) &
                                0UL),
                               l_2[1][1]))),
                          1UL) == l_16)) != l_2[g_5[0][0]][(g_3 + 1)])) &&
           l_2[g_5[0][0]][(g_3 + 1)])) {
        int32_t *l_19 = &g_20;
        int32_t *l_21 = &g_20;
        int32_t *l_22 = &g_20;
        int32_t *l_23[3];
        int i;
        for (i = 0; i < 3; i++)
          l_23[i] = (void *)0;
        l_32--;
        l_35++;
      } else {
        int64_t l_41 = (-5L);
        int32_t *l_42 = (void *)0;
        int32_t *l_43 = (void *)0;
        int32_t *l_44 = &l_31[0][1];
        (*l_44) |=
            (((safe_lshift_func_int8_t_s_s(
                  (safe_unary_minus_func_int16_t_s(l_41)), g_4)) != g_18[1]) ||
             0xFFL);
      }
    }
  }
  return g_20;
}

static uint64_t func_8(int64_t p_9, uint32_t p_10, const int64_t p_11) {
  uint32_t l_12 = 2UL;
  return l_12;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_5[i][j];
    }
  }
  csmith_sink_ = g_15;
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_18[i];
  }
  csmith_sink_ = g_20;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_27[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
