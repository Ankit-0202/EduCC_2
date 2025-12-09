// Options:   --seed 200196 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_196.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint64_t g_9 = 0x22E6E7F737A9A971LL;
static int32_t g_25 = 0x551B32E2L;
static int32_t *volatile g_24 = &g_25;
static uint32_t g_37 = 4294967295UL;
static int16_t g_39 = 0x2542L;
static float g_40 = 0xD.F7DC23p+83;
static int16_t g_42 = 0xEA37L;
static int32_t g_45 = 5L;
static int32_t *g_49 = &g_45;
static int32_t **volatile g_48 = &g_49;

static uint8_t func_1(void);
static int8_t func_4(int16_t p_5, int32_t p_6);

static uint8_t func_1(void) {
  int64_t l_10[1][1];
  int32_t *l_33 = &g_25;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++)
      l_10[i][j] = 5L;
  }
  if (((safe_lshift_func_int8_t_s_s(
           func_4(((((safe_mod_func_uint16_t_u_u(
                         (g_9 >
                          (l_10[0][0] && (safe_mul_func_uint8_t_u_u(
                                             ((safe_add_func_float_f_f(
                                                  ((safe_sub_func_float_f_f(
                                                       (l_10[0][0] > g_9),
                                                       0xE.5A9864p+14)) < g_9),
                                                  (-0x5.Bp+1))),
                                              g_9),
                                             0x27L)))),
                         l_10[0][0])) < 0x5725L) |
                    0L) &
                   l_10[0][0]),
                  g_9),
           5)) > l_10[0][0])) {
    uint64_t l_34 = 0xBDAE89405DBD55ADLL;
    uint32_t *l_35 = (void *)0;
    uint32_t *l_36 = &g_37;
    int16_t *l_38 = &g_39;
    int16_t *l_41[3];
    int32_t l_43 = (-1L);
    int32_t *l_44[1];
    int i;
    for (i = 0; i < 3; i++)
      l_41[i] = &g_42;
    for (i = 0; i < 1; i++)
      l_44[i] = &g_45;
    g_45 ^=
        (((safe_mul_func_float_f_f(
              g_9,
              (((safe_unary_minus_func_int16_t_s((
                    l_43 &=
                    (g_42 = ((((*l_38) |= (safe_mod_func_int16_t_s_s(
                                   (-1L),
                                   (((*l_36) ^= (safe_sub_func_int64_t_s_s(
                                         (((void *)0 != l_33) == l_34), 3L))) &&
                                    (*g_24))))) <= g_9) == g_25))))),
                g_40) > 0x6.A8ACDDp+98))) == l_34),
         l_34);
    for (g_39 = 0; (g_39 != (-27)); --g_39) {
      if ((*g_24))
        break;
      (*g_48) = &g_25;
    }
  } else {
    for (g_42 = 0; (g_42 <= 0); g_42 += 1) {
      int16_t l_50 = (-2L);
      return l_50;
    }
  }
  return g_9;
}

static int8_t func_4(int16_t p_5, int32_t p_6) {
  const uint8_t l_23 = 0xF4L;
  (*g_24) ^=
      (safe_sub_func_uint8_t_u_u((((safe_div_func_uint8_t_u_u(p_6, g_9)) <=
                                   (safe_div_func_int64_t_s_s(l_23, g_9))),
                                  255UL),
                                 p_6));
  return p_6;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  csmith_sink_ = g_25;
  csmith_sink_ = g_37;
  csmith_sink_ = g_39;
  csmith_sink_ = g_40;
  csmith_sink_ = g_42;
  csmith_sink_ = g_45;
  platform_main_end(0, 0);
  return 0;
}
