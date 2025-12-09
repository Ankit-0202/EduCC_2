// Options:   --seed 200143 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_143.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2 = 0x5464B5F5L;
static volatile int32_t g_6 = (-4L);
static int32_t g_7[1][4] = {
    {0x2B29949DL, 0x2B29949DL, 0x2B29949DL, 0x2B29949DL}};
static float g_9 = (-0x10.Ep+1);
static float *volatile g_8[4][4] = {{&g_9, &g_9, &g_9, &g_9},
                                    {&g_9, &g_9, &g_9, &g_9},
                                    {&g_9, &g_9, &g_9, &g_9},
                                    {&g_9, &g_9, &g_9, &g_9}};
static float *volatile g_10[4][2] = {{(void *)0, (void *)0},
                                     {(void *)0, (void *)0},
                                     {(void *)0, (void *)0},
                                     {(void *)0, (void *)0}};
static uint32_t g_14 = 0x817D1DC6L;
static const uint32_t g_23 = 0x60D64C9DL;
static int32_t *g_25 = (void *)0;
static int32_t *const volatile g_27 = (void *)0;
static int8_t g_35 = 0x8CL;
static int16_t g_39 = 1L;
static int8_t g_65 = 0x26L;

static uint32_t func_1(void);
static uint32_t func_15(int64_t p_16, const float *p_17, int32_t p_18,
                        uint32_t p_19, const uint32_t *p_20);

static uint32_t func_1(void) {
  const uint32_t *l_22[2][2];
  int32_t l_26 = 8L;
  int16_t *l_38 = &g_39;
  int32_t l_41 = (-1L);
  int32_t l_42 = 0x9BDCCB4FL;
  int32_t l_43[4];
  float l_44 = (-0x1.Ep-1);
  int32_t *l_72 = (void *)0;
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++)
      l_22[i][j] = &g_23;
  }
  for (i = 0; i < 4; i++)
    l_43[i] = 0x89665FECL;
  for (g_2 = (-29); (g_2 < (-30)); g_2 = safe_sub_func_int16_t_s_s(g_2, 9)) {
    int64_t l_5[4][1];
    int32_t l_12 = 4L;
    int32_t l_21 = 3L;
    int i, j;
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 1; j++)
        l_5[i][j] = 1L;
    }
    for (g_7[0][0] = 0; (g_7[0][0] <= 0); g_7[0][0] += 1) {
      float *l_11[4][4];
      uint32_t *l_13 = &g_14;
      int32_t *l_28 = &l_12;
      int i, j;
      for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++)
          l_11[i][j] = &g_9;
      }
      l_12 = (l_5[g_7[0][0]][g_7[0][0]] > 0x4.D1878Ap+96);
      (*l_28) ^= (((((*l_13) = 0xED7C6AE4L) &
                    func_15(l_5[(g_7[0][0] + 1)][g_7[0][0]], l_11[3][2],
                            g_7[0][3], l_21, l_22[0][0])) > l_26) &&
                  0xBAL);
    }
  }
  if ((safe_mod_func_int16_t_s_s(
          l_26,
          (safe_add_func_uint64_t_u_u(
              (safe_mul_func_uint64_t_u_u(
                  (g_35 = l_26),
                  (safe_mul_func_int16_t_s_s(
                      ((*l_38) &= (((g_7[0][0], 0UL), 0UL) <= l_26)), 0L)))),
              g_14))))) {
    int32_t *l_40[3][4] = {{&g_2, &g_2, &g_2, &g_2},
                           {&g_2, &g_2, &g_2, &g_2},
                           {&g_2, &g_2, &g_2, &g_2}};
    int16_t l_45[1][2];
    int8_t l_46[1];
    uint16_t l_47 = 6UL;
    float *l_54 = &l_44;
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 2; j++)
        l_45[i][j] = 1L;
    }
    for (i = 0; i < 1; i++)
      l_46[i] = 0x0CL;
    l_47--;
    if ((((safe_mul_func_int8_t_s_s(
              (g_35 = (safe_mul_func_int8_t_s_s(
                   ((void *)0 != l_54),
                   (safe_mod_func_int8_t_s_s(
                       (safe_div_func_uint64_t_u_u(g_14, 3UL)), l_41))))),
              g_39)) ^
          l_42) &&
         0L)) {
      return g_14;
    } else {
      int64_t *l_63 = (void *)0;
      int64_t *l_64 = (void *)0;
      int32_t **l_66 = &l_40[0][0];
      (*l_66) = ((g_65 &= (safe_div_func_int32_t_s_s(
                      (g_14 > ((safe_lshift_func_int8_t_s_s(((void *)0 != l_54),
                                                            5)) <= g_23)),
                      0xD9FC31E8L))),
                 (void *)0);
      g_6 &= (safe_div_func_uint8_t_u_u(
          g_14, (((+(safe_lshift_func_uint16_t_u_s(
                      (&g_7[0][0] == (l_72 = (l_26, (void *)0))), 15))) ||
                  g_14) |
                 l_43[3])));
    }
  } else {
    const int32_t *l_75[2];
    const int32_t **l_76 = &l_75[1];
    int16_t l_77 = 0xCC1BL;
    float *l_78 = &g_9;
    int i;
    for (i = 0; i < 2; i++)
      l_75[i] = (void *)0;
    (*l_78) =
        ((safe_add_func_float_f_f(l_42, (((((*l_76) = l_75[1]) != &g_7[0][0]),
                                          l_77) == l_77))) != 0x1.6p-1);
  }
  return l_42;
}

static uint32_t func_15(int64_t p_16, const float *p_17, int32_t p_18,
                        uint32_t p_19, const uint32_t *p_20) {
  int32_t **l_24[4];
  int i;
  for (i = 0; i < 4; i++)
    l_24[i] = (void *)0;
  g_25 = &g_7[0][2];
  return g_23;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_6;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_7[i][j];
    }
  }
  csmith_sink_ = g_9;
  csmith_sink_ = g_14;
  csmith_sink_ = g_23;
  csmith_sink_ = g_35;
  csmith_sink_ = g_39;
  csmith_sink_ = g_65;
  platform_main_end(0, 0);
  return 0;
}
