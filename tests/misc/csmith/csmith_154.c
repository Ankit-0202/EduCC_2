// Options:   --seed 200154 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_154.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_3 = 0x457102D1L;
static const volatile int32_t *g_2[2][4] = {{&g_3, &g_3, &g_3, &g_3},
                                            {&g_3, &g_3, &g_3, &g_3}};
static int32_t g_13 = (-5L);
static int32_t *g_12 = &g_13;
static uint16_t g_29 = 0x930FL;
static volatile uint8_t g_32[1] = {0x4BL};
static int32_t g_35 = 1L;

static uint32_t func_1(void);
static uint16_t func_6(int64_t p_7, int32_t *p_8, const float p_9,
                       int32_t *p_10, int32_t *p_11);

static uint32_t func_1(void) {
  const volatile int32_t **l_4 = (void *)0;
  const volatile int32_t **l_5 = &g_2[1][0];
  int32_t l_16 = 0x7689A5A4L;
  int32_t *l_34 = &g_35;
  (*l_5) = g_2[0][3];
  (*l_34) |=
      (func_6(g_3, g_12,
              ((safe_mul_func_float_f_f(((g_13 >= l_16) == 0xF.DAD5A5p+94),
                                        l_16)) >= 0x5.6p+1),
              &l_16, &l_16),
       (*g_12));
  return g_29;
}

static uint16_t func_6(int64_t p_7, int32_t *p_8, const float p_9,
                       int32_t *p_10, int32_t *p_11) {
  uint16_t *l_28 = &g_29;
  int32_t l_30[1][2];
  int32_t l_31 = (-4L);
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++)
      l_30[i][j] = (-9L);
  }
  for (g_13 = (-15); (g_13 <= (-22));
       g_13 = safe_sub_func_int16_t_s_s(g_13, 2)) {
    if ((*g_12))
      break;
  }
  if ((safe_rshift_func_uint16_t_u_s(
          (((((safe_mod_func_int8_t_s_s(
                  (-1L),
                  (safe_add_func_int8_t_s_s(
                      (safe_lshift_func_uint16_t_u_u(
                          ((*l_28) =
                               (((((1L | ((!g_13) < p_7)) & (-7L)) | p_7) &
                                 8UL) == (-1L))),
                          8)),
                      p_7)))) &&
              l_30[0][0]) <= l_31) == 0xB430688CL),
           p_7),
          g_32[0]))) {
    (*g_12) &= ((~((void *)0 == &g_3)) == p_7);
  } else {
    for (p_7 = 0; p_7 < 2; p_7 += 1) {
      for (g_29 = 0; g_29 < 4; g_29 += 1) {
        g_2[p_7][g_29] = &g_3;
      }
    }
  }
  return g_3;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_13;
  csmith_sink_ = g_29;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_32[i];
  }
  csmith_sink_ = g_35;
  platform_main_end(0, 0);
  return 0;
}
