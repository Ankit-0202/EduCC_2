// Options:   --seed 200171 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_171.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile float g_4 = 0x5.1F2000p+7;
static uint8_t g_5 = 0x7BL;
static int32_t g_23 = (-1L);
static int32_t g_33[4][2] = {{0xD8D46C64L, 0xD8D46C64L},
                             {0xD8D46C64L, 0xD8D46C64L},
                             {0xD8D46C64L, 0xD8D46C64L},
                             {0xD8D46C64L, 0xD8D46C64L}};
static int8_t g_34 = 0x4CL;

static float func_1(void);
static float func_6(int32_t p_7, uint16_t p_8, float p_9, int32_t p_10);

static float func_1(void) {
  uint16_t l_13 = 0x46DDL;
  uint32_t l_14 = 18446744073709551608UL;
  int32_t *l_32 = &g_33[1][1];
  g_34 =
      ((*l_32) ^= (safe_sub_func_int64_t_s_s(
           g_5,
           ((func_6((0UL || (safe_sub_func_int16_t_s_s((g_5, l_13), 65535UL))),
                    g_5, l_13, l_14) > g_5),
            l_13))));
  for (g_23 = 0; (g_23 <= 14); g_23 = safe_add_func_int8_t_s_s(g_23, 7)) {
    for (g_34 = 0; (g_34 > 7); ++g_34) {
      if (g_33[1][1])
        break;
      return g_23;
    }
  }
  return g_33[0][1];
}

static float func_6(int32_t p_7, uint16_t p_8, float p_9, int32_t p_10) {
  uint16_t l_17[4];
  int32_t l_18 = 0x96753F3AL;
  int32_t *l_19 = (void *)0;
  int32_t l_20 = 0xF51AE9A0L;
  int32_t *l_21 = (void *)0;
  int32_t *l_22[3];
  int i;
  for (i = 0; i < 4; i++)
    l_17[i] = 0x8EA5L;
  for (i = 0; i < 3; i++)
    l_22[i] = &g_23;
  if ((g_23 = (l_20 = (((p_7 ^ (-4L)) &&
                        (safe_div_func_int16_t_s_s(0x8FE7L, l_17[3]))),
                       l_18)))) {
    int32_t l_24[3];
    int i;
    for (i = 0; i < 3; i++)
      l_24[i] = 1L;
    for (l_20 = 0; (l_20 <= 2); l_20 += 1) {
      int i;
      if (l_24[2])
        break;
    }
  } else {
    int32_t **l_25[2];
    int64_t l_30 = (-6L);
    int i;
    for (i = 0; i < 2; i++)
      l_25[i] = &l_21;
    l_22[2] = (void *)0;
    for (g_23 = 12; (g_23 > 15); ++g_23) {
      uint32_t l_31 = 0x74600EBEL;
      if (p_10)
        break;
      l_31 =
          ((p_8, (0xBFD0L != ((safe_mod_func_int8_t_s_s((g_5 < p_8), 0xC8L)) >
                              g_23))) != l_30);
    }
  }
  return p_9;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  csmith_sink_ = g_23;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_33[i][j];
    }
  }
  csmith_sink_ = g_34;
  platform_main_end(0, 0);
  return 0;
}
