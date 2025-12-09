// Options:   --seed 200131 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_131.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_8 = 1L;
static float g_39 = 0x5.0p-1;
static uint8_t g_42 = 255UL;
static int32_t g_51 = 0L;
static int32_t g_52 = 1L;
static uint32_t g_55 = 1UL;
static float *volatile g_57 = (void *)0;
static float *volatile g_58 = &g_39;
static int32_t *g_60[2] = {&g_8, &g_8};
static int32_t **volatile g_59 = &g_60[0];
static int32_t g_63 = 1L;

static uint32_t func_1(void);
static int64_t func_2(int8_t p_3, uint64_t p_4, int8_t p_5, uint8_t p_6,
                      int64_t p_7);

static uint32_t func_1(void) {
  int32_t l_11 = 0xF6EFBA1AL;
  int32_t *l_61 = (void *)0;
  int32_t *l_62[1];
  int i;
  for (i = 0; i < 1; i++)
    l_62[i] = &g_63;
  g_63 |= (func_2(g_8, ((g_8, (safe_sub_func_int64_t_s_s(g_8, g_8))) < 0L), g_8,
                  g_8, l_11) ^
           4L);
  return g_63;
}

static int64_t func_2(int8_t p_3, uint64_t p_4, int8_t p_5, uint8_t p_6,
                      int64_t p_7) {
  int32_t l_16 = 0xB2C57E71L;
  int32_t l_44 = 0xA22F0F5BL;
  int32_t *l_48 = &l_44;
  if (((safe_mul_func_int8_t_s_s(
           (safe_div_func_int16_t_s_s((0x7979L & 0L), p_5)), l_16)),
       1L)) {
    uint32_t l_17[1];
    float *l_38 = &g_39;
    uint8_t *l_40 = (void *)0;
    uint8_t *l_41 = &g_42;
    int32_t *l_43[2];
    int i;
    for (i = 0; i < 1; i++)
      l_17[i] = 4294967295UL;
    for (i = 0; i < 2; i++)
      l_43[i] = &g_8;
    for (p_5 = 0; (p_5 >= 0); p_5 -= 1) {
      uint8_t l_18 = 0x52L;
      int32_t l_19 = 2L;
      int i;
      if (l_17[p_5])
        break;
      l_19 = l_18;
    }
    if ((safe_div_func_int32_t_s_s(
            (l_44 =
                 ((p_6 |
                   (safe_lshift_func_uint8_t_u_u(
                       ((*l_41) =
                            (((((((safe_lshift_func_uint8_t_u_s(
                                      ((safe_mul_func_int16_t_s_s(
                                           (safe_lshift_func_int16_t_s_u(
                                               (safe_lshift_func_int8_t_s_s(
                                                   ((safe_rshift_func_int16_t_s_u(
                                                        (((safe_sub_func_float_f_f(
                                                              (safe_add_func_float_f_f(
                                                                  (((*l_38) = l_17
                                                                        [0]) >=
                                                                   g_8),
                                                                  g_8)),
                                                              g_8)),
                                                          l_17[0]) ^
                                                         l_17[0]),
                                                        l_16)) ||
                                                    g_8),
                                                   6)),
                                               p_5)),
                                           l_16)) == g_8),
                                      5)) != 0xCB51404FC4B664FBLL) >= l_16) |
                                l_16),
                               l_17[0]) < 2L) &&
                             l_16)),
                       6))),
                  p_3)),
            0xD4E02302L))) {
      uint64_t l_45 = 0x8B697689278A4911LL;
      l_45++;
    } else {
      l_48 = &g_8;
      g_52 =
          ((*l_48) = (g_51 &= (safe_mul_func_int16_t_s_s(
                          (-1L), ((((g_42, l_38) != &g_8) >= g_8) && g_42)))));
    }
  } else {
    const uint8_t l_53[1] = {1UL};
    int32_t l_56 = (-2L);
    int i;
    if (l_53[0]) {
      uint32_t *l_54[1][4];
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 4; j++)
          l_54[i][j] = &g_55;
      }
      (*g_58) = (0x7.2DBE42p-77 <
                 (0x1.Dp-1 ==
                  (((g_55 ^= (l_56 = (g_52 >= (-1L)))), g_52) > 0x2.Ap-1)));
    } else {
      (*g_59) = &g_8;
    }
  }
  return p_7;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_8;
  csmith_sink_ = g_39;
  csmith_sink_ = g_42;
  csmith_sink_ = g_51;
  csmith_sink_ = g_52;
  csmith_sink_ = g_55;
  csmith_sink_ = g_63;
  platform_main_end(0, 0);
  return 0;
}
