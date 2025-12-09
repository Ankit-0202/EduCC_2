// Options:   --seed 300279 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_279.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  volatile int8_t *f0;
};

union U1 {
  uint32_t f0;
  volatile int16_t f1;
};

static union U1 g_2 = {1UL};
static int8_t g_13 = 0x7BL;
static int8_t *g_12 = &g_13;
static union U0 g_22 = {0};
static int32_t g_27 = 0xEC51938DL;
static int32_t *volatile g_26 = &g_27;
static union U0 *g_47 = &g_22;
static uint32_t g_48 = 4UL;
static int64_t g_50 = (-1L);
static int8_t g_56 = (-1L);

static uint32_t func_1(void);
static uint8_t func_7(int16_t p_8, int16_t p_9, int8_t *p_10);
static union U0 *func_14(int32_t p_15, int8_t p_16);

static uint32_t func_1(void) {
  uint8_t l_11 = 0UL;
  int64_t *l_49 = &g_50;
  int32_t *l_51[1][2];
  int32_t l_57 = 0L;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++)
      l_51[i][j] = &g_27;
  }
  (*g_26) =
      (((((g_2,
           (safe_rshift_func_uint8_t_u_s(
               ((g_2.f1 && ((*l_49) = (safe_sub_func_uint8_t_u_u(
                                func_7(l_11, l_11, g_12), g_48)))) != l_11),
               g_48))) == l_11) >= l_11) ||
        l_11),
       (*g_26));
  l_57 = ((*g_26) = (safe_mul_func_uint16_t_u_u(
              0UL,
              ((safe_div_func_int32_t_s_s(((-6L) ^ (*g_12)), g_13)) && g_56))));
  return g_56;
}

static uint8_t func_7(int16_t p_8, int16_t p_9, int8_t *p_10) {
  int8_t l_18 = 9L;
  union U0 *l_21 = &g_22;
  union U0 **l_46[3];
  int i;
  for (i = 0; i < 3; i++)
    l_46[i] = &l_21;
  g_47 = func_14(
      (((((((g_2.f1 >= (safe_unary_minus_func_int32_t_s(
                           (l_18, ((((safe_add_func_int64_t_s_s(g_2.f0, 1UL)),
                                     1L) <= (*g_12)) > (*g_12)))))) &
            p_9),
           0UL) >= g_2.f0) ^
         0x55L),
        (void *)0) == l_21),
      l_18);
  return l_18;
}

static union U0 *func_14(int32_t p_15, int8_t p_16) {
  uint16_t l_37 = 65535UL;
  union U0 *l_44 = &g_22;
  for (g_2.f0 = 0; (g_2.f0 < 49);
       g_2.f0 = safe_add_func_uint8_t_u_u(g_2.f0, 8)) {
    int8_t **l_25 = &g_12;
    int32_t l_32 = (-1L);
    int32_t l_33 = 0x6DE0D615L;
    int32_t l_34 = 2L;
    int32_t l_35 = (-1L);
    int32_t l_36 = 1L;
    (*g_26) |= ((((*l_25) = &g_13) != (g_2.f0, (void *)0)) || 0L);
    for (g_13 = 0; (g_13 <= (-23)); g_13--) {
      int32_t *l_30[1][2];
      int64_t l_31 = 0L;
      int32_t l_40 = 0L;
      union U0 **l_45 = &l_44;
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++)
          l_30[i][j] = &g_27;
      }
      l_37--;
      g_27 &=
          ((g_13 >
            (((l_40 != (!(safe_rshift_func_int16_t_s_u(
                           (((((*l_45) = l_44) == (void *)0), p_15) && p_16),
                           g_2.f1)))) ^
              (-1L)) |
             0x430F0C86L)) == l_33);
    }
  }
  return &g_22;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2.f0;
  csmith_sink_ = g_2.f1;
  csmith_sink_ = g_13;
  csmith_sink_ = g_27;
  csmith_sink_ = g_48;
  csmith_sink_ = g_50;
  csmith_sink_ = g_56;
  platform_main_end(0, 0);
  return 0;
}
