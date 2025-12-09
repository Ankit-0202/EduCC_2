// Options:   --seed 200200 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_200.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_3 = 0x256A9EF7L;
static int16_t g_19 = 0xD833L;
static float g_25 = (-0x1.Cp+1);
static float *volatile g_24 = &g_25;
static int32_t g_30 = (-1L);
static volatile uint16_t g_36 = 65534UL;
static volatile uint16_t g_42 = 1UL;

static int16_t func_1(void);
static int32_t *func_4(int16_t p_5, uint8_t p_6, int32_t *p_7, float p_8);

static int16_t func_1(void) {
  float l_2[3][2] = {
      {0x8.8p+1, 0x1.Dp-1}, {0x1.Dp-1, 0x8.8p+1}, {0x1.Dp-1, 0x1.Dp-1}};
  int32_t l_16[4];
  uint32_t l_17[1][3];
  float *l_45 = (void *)0;
  float *l_46 = &l_2[1][1];
  int i, j;
  for (i = 0; i < 4; i++)
    l_16[i] = 9L;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++)
      l_17[i][j] = 0x1311E2DBL;
  }
  for (g_3 = 1; (g_3 >= 0); g_3 -= 1) {
    uint64_t l_9 = 0x1D26EC17E5C285CELL;
    int16_t *l_18[1];
    int32_t *l_20 = &g_3;
    int32_t **l_31 = (void *)0;
    int64_t l_34 = 0x21BA52B3395CC9E5LL;
    int32_t l_35 = 0L;
    int i;
    for (i = 0; i < 1; i++)
      l_18[i] = &g_19;
    l_20 = func_4(
        ((g_3 != l_9), (l_16[1] = ((+(safe_sub_func_uint16_t_u_u(
                                       ((!(safe_add_func_uint8_t_u_u(
                                            ((l_16[2] == g_3) <= g_3), g_3))) &
                                        0xFD81438367457993LL),
                                       65528UL))) >= l_17[0][2]))),
        g_3, l_20, g_19);
    for (g_19 = 3; (g_19 >= 0); g_19 -= 1) {
      int32_t *l_32 = &l_16[1];
      int32_t *l_33[4] = {&g_30, &g_30, &g_30, &g_30};
      int i;
      ++g_36;
    }
    for (g_30 = 1; (g_30 >= 0); g_30 -= 1) {
      int32_t *l_39 = (void *)0;
      int32_t *l_40 = &l_35;
      int32_t *l_41[3][1];
      int i, j;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++)
          l_41[i][j] = &l_16[1];
      }
      g_42--;
    }
  }
  l_16[0] = ((*l_46) = l_17[0][2]);
  return l_17[0][2];
}

static int32_t *func_4(int16_t p_5, uint8_t p_6, int32_t *p_7, float p_8) {
  int32_t *l_23 = (void *)0;
  uint32_t l_28 = 1UL;
  int32_t *l_29 = &g_30;
  (*g_24) = (safe_mul_func_float_f_f((&g_3 == l_23), g_19));
  (*l_29) |= ((safe_rshift_func_uint8_t_u_s(
                  (((p_5 & (((l_23 == l_23), 1UL) == (-10L))), l_28) & 0xA77DL),
                  g_19)) >= p_6);
  return l_29;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_19;
  csmith_sink_ = g_25;
  csmith_sink_ = g_30;
  csmith_sink_ = g_36;
  csmith_sink_ = g_42;
  platform_main_end(0, 0);
  return 0;
}
