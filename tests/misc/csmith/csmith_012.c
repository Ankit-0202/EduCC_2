// Options:   --seed 100012 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_012.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2 = (-1L);
static volatile int32_t g_5 = 0x822B1658L;
static volatile int32_t g_6[1] = {(-7L)};
static int32_t g_7 = 9L;
static uint32_t g_21 = 5UL;
static uint8_t g_23 = 250UL;
static int32_t g_27 = 0xD840DFE9L;
static int32_t g_30[1][4] = {{0L, 0L, 0L, 0L}};
static int32_t g_43 = 9L;

static int32_t func_1(void);
static int32_t func_16(const uint8_t p_17, uint64_t p_18);

static int32_t func_1(void) {
  uint64_t l_31 = 0xF0D4A7C769867F5DLL;
  for (g_2 = 0; (g_2 != 0); g_2++) {
    int32_t l_13 = 0x006310FEL;
    for (g_7 = 17; (g_7 > 9); --g_7) {
      uint16_t *l_20 = (void *)0;
      uint8_t *l_22[3][3] = {{&g_23, (void *)0, &g_23},
                             {&g_23, &g_23, &g_23},
                             {&g_23, (void *)0, &g_23}};
      uint8_t *l_24 = &g_23;
      int32_t *l_44 = &l_13;
      int i, j;
      if ((~(safe_sub_func_uint8_t_u_u(
              l_13,
              ((*l_24) =
                   ((((safe_lshift_func_int8_t_s_s(
                          (((func_16(
                                 (l_13,
                                  ((*l_24) = (((g_21 = (((~0x1FC6L), 65535UL) &
                                                        g_6[0])) == g_7) ^
                                              0xD06721F7D96711DBLL))),
                                 g_7) == g_7) < g_2) &&
                           g_27),
                          g_2)) ||
                      g_7) <= l_13) > g_7)))))) {
        if (l_31)
          break;
        if (l_31)
          break;
      } else {
        int16_t l_32 = 0x35CFL;
        g_30[0][0] = (g_6[0] != ((((g_2, g_23) || l_32), l_32) ^ g_30[0][3]));
      }
      (*l_44) = (safe_div_func_int16_t_s_s(
          (((l_20 == (void *)0) ||
            (safe_rshift_func_uint8_t_u_s(
                (safe_sub_func_uint16_t_u_u(
                    (g_43 = (safe_div_func_int64_t_s_s(
                         (safe_mul_func_uint16_t_u_u((g_21, g_7), l_13)),
                         0x585C2C102D1F73E7LL))),
                    0x3353L)),
                l_13))),
           g_30[0][2]),
          l_13));
    }
  }
  for (g_21 = 13; (g_21 == 44); g_21 = safe_add_func_int32_t_s_s(g_21, 6)) {
    uint16_t l_47 = 0xBF62L;
    return l_47;
  }
  return g_6[0];
}

static int32_t func_16(const uint8_t p_17, uint64_t p_18) {
  for (p_18 = 0; (p_18 == 41); p_18 = safe_add_func_uint16_t_u_u(p_18, 1)) {
    for (g_23 = 0; (g_23 <= 0); g_23 += 1) {
      int i;
      g_27 ^= g_6[g_23];
      for (g_27 = 0; (g_27 <= 0); g_27 += 1) {
        int32_t *l_28 = (void *)0;
        int32_t *l_29 = &g_30[0][3];
        int i;
        (*l_29) ^= g_6[g_23];
      }
    }
  }
  return p_18;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_5;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_6[i];
  }
  csmith_sink_ = g_7;
  csmith_sink_ = g_21;
  csmith_sink_ = g_23;
  csmith_sink_ = g_27;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_30[i][j];
    }
  }
  csmith_sink_ = g_43;
  platform_main_end(0, 0);
  return 0;
}
