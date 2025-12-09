// Options:   --seed 100031 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_031.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int8_t g_19[1] = {0x8CL};
static int32_t g_20 = 0xB09F5954L;
static int64_t g_22 = 0x12E7550730467731LL;
static int32_t g_24 = 0x939E63A5L;
static int32_t *volatile g_23 = &g_24;
static uint8_t g_37 = 9UL;
static int32_t *g_44 = (void *)0;
static int32_t **volatile g_43 = &g_44;
static int32_t **volatile g_45 = (void *)0;

static int64_t func_1(void);
static uint64_t func_3(int16_t p_4, uint16_t p_5, int16_t p_6);

static int64_t func_1(void) {
  int32_t l_2 = (-5L);
  int32_t l_38 = 0x324E8160L;
  int32_t *l_46 = (void *)0;
  if ((l_2 && func_3(l_2, (safe_rshift_func_uint16_t_u_s(65535UL, 7)), l_2))) {
    const int32_t l_36 = 0xAD1532D4L;
    l_38 &= ((safe_rshift_func_int16_t_s_u(
                 (g_37 = ((safe_sub_func_int64_t_s_s(
                              (safe_sub_func_int32_t_s_s(
                                  ((((!(safe_mul_func_int16_t_s_s(
                                         g_22, ((safe_lshift_func_int8_t_s_u(
                                                    0L, (&g_24 != &g_24))) ==
                                                l_36)))) > 0x85BB31CFL) > 1UL) &
                                   (-10L)),
                                  l_2)),
                              g_22)),
                          0x3337L)),
                 g_24)) != g_24);
  } else {
    for (l_38 = (-18); (l_38 >= 1); ++l_38) {
      for (g_20 = (-2); (g_20 > (-13)); g_20--) {
        (*g_43) = &g_24;
        if (l_38)
          break;
      }
      for (g_22 = 0; (g_22 <= 0); g_22 += 1) {
        l_46 = &l_38;
      }
    }
  }
  return g_19[0];
}

static uint64_t func_3(int16_t p_4, uint16_t p_5, int16_t p_6) {
  int64_t l_9 = 0x23498E64E6DC660FLL;
  int8_t *l_18[4][4] = {{(void *)0, &g_19[0], (void *)0, &g_19[0]},
                        {(void *)0, &g_19[0], &g_19[0], &g_19[0]},
                        {&g_19[0], &g_19[0], &g_19[0], &g_19[0]},
                        {&g_19[0], (void *)0, &g_19[0], (void *)0}};
  int64_t *l_21 = &g_22;
  int i, j;
  (*g_23) =
      ((((l_9 > (((*l_21) = ((safe_div_func_int64_t_s_s(
                                 (safe_mul_func_int8_t_s_s(
                                     (safe_rshift_func_uint16_t_u_s(
                                         (safe_mul_func_int8_t_s_s(
                                             (g_19[0] = p_6), (g_20, l_9))),
                                         1)),
                                     p_6)),
                                 1L)),
                             0xEB2FC257A10DD664LL)) > l_9)) <= (-10L)) ^
        1UL) ^
       g_20);
  g_23 = (void *)0;
  return l_9;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_19[i];
  }
  csmith_sink_ = g_20;
  csmith_sink_ = g_22;
  csmith_sink_ = g_24;
  csmith_sink_ = g_37;
  platform_main_end(0, 0);
  return 0;
}
