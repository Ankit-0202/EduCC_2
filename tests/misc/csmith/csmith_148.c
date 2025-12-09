// Options:   --seed 200148 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_148.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2 = (-1L);
static float g_26 = 0x7.Dp+1;
static int8_t g_27 = (-6L);
static int16_t g_30 = 0x8661L;
static uint16_t g_44 = 0xCB06L;
static int32_t *g_47 = &g_2;
static int32_t **volatile g_46 = &g_47;
static int32_t g_49[2] = {0L, 0L};
static int32_t *volatile g_50 = &g_2;

static uint32_t func_1(void);
static uint32_t func_7(uint8_t p_8, uint32_t p_9, int16_t p_10);

static uint32_t func_1(void) {
  int32_t l_11 = 6L;
  for (g_2 = 29; (g_2 != (-30)); g_2--) {
    int32_t l_12 = 0xEF307D7CL;
    uint64_t l_13 = 0x2CF415D7249AAED6LL;
    int32_t *l_48 = &g_49[0];
    (*l_48) |= (safe_mod_func_uint32_t_u_u(
        func_7(g_2, l_11, (((l_12 ^ l_11) == l_13) >= g_2)), 0xA2F725DCL));
  }
  (*g_50) = l_11;
  return g_27;
}

static uint32_t func_7(uint8_t p_8, uint32_t p_9, int16_t p_10) {
  uint64_t *l_24[3];
  int32_t l_25 = 0L;
  int32_t l_28 = (-4L);
  int32_t l_29 = 1L;
  uint8_t l_31 = 251UL;
  int16_t l_42 = 0x3418L;
  uint16_t *l_43 = &g_44;
  int i;
  for (i = 0; i < 3; i++)
    l_24[i] = (void *)0;
  if ((((safe_mul_func_int16_t_s_s(
            (0L ||
             (safe_lshift_func_uint16_t_u_u(
                 (((*l_43) &= (safe_unary_minus_func_int8_t_s((~(
                       (safe_lshift_func_uint16_t_u_u(
                           ((safe_sub_func_int64_t_s_s(
                                (((++l_31) !=
                                  ((safe_lshift_func_uint16_t_u_s(
                                       ((safe_lshift_func_int8_t_s_s(
                                            (((((safe_add_func_float_f_f(
                                                    l_25,
                                                    (((((safe_sub_func_float_f_f(
                                                            (l_28 < g_26),
                                                            0x5.EF1355p-64)) <
                                                        0x1.6p-1) >
                                                       (-0x5.3p-1)) >= l_42) <=
                                                     g_27))),
                                                0x9150040BL),
                                               p_8) <= p_9) |
                                             l_25),
                                            3)) |
                                        l_29),
                                       11)),
                                   p_8)) != p_9),
                                0L)),
                            1UL),
                           3)) == l_28))))) |
                  p_9),
                 11))),
            p_8)) == l_25) <= p_9)) {
    int32_t *l_45 = &l_29;
    (*g_46) = l_45;
    (*l_45) = p_9;
  } else {
    return p_9;
  }
  return g_2;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_26;
  csmith_sink_ = g_27;
  csmith_sink_ = g_30;
  csmith_sink_ = g_44;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_49[i];
  }
  platform_main_end(0, 0);
  return 0;
}
