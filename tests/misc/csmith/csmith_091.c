// Options:   --seed 100091 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_091.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint64_t g_13 = 0UL;
static int32_t g_29 = (-8L);
static int64_t g_39[4][3] = {{0xC369029EFEC1A2C9LL, 3L, 0L},
                             {(-5L), 3L, (-5L)},
                             {(-1L), 0xC369029EFEC1A2C9LL, 0L},
                             {(-1L), (-1L), 0xC369029EFEC1A2C9LL}};

static int64_t func_1(void);
static const int16_t func_5(int8_t p_6, int32_t p_7, int32_t p_8, int16_t p_9,
                            uint32_t p_10);

static int64_t func_1(void) {
  int32_t l_4 = 0x1BD97A88L;
  uint32_t **l_30 = (void *)0;
  int32_t *l_40 = &l_4;
  if ((safe_sub_func_int16_t_s_s(
          ((l_4 <=
            (func_5(l_4, (safe_sub_func_int64_t_s_s((l_4 != g_13), g_13)), l_4,
                    g_13, g_13) < l_4)) &
           0x2845L),
          0x245CL))) {
    uint32_t ***l_31 = (void *)0;
    uint32_t **l_32 = (void *)0;
    l_32 = l_30;
  } else {
    uint32_t l_33[1][1];
    int64_t *l_38 = &g_39[3][2];
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 1; j++)
        l_33[i][j] = 0x4E7CCCE1L;
    }
    l_40 =
        ((((l_33[0][0] &&
            (((((((*l_38) = (safe_sub_func_uint8_t_u_u(
                      ((safe_sub_func_int64_t_s_s(0x0B739032F82966B9LL, g_29)) &
                       g_13),
                      g_29))) |
                 l_33[0][0]) == g_29),
               (void *)0) == &l_4) < l_33[0][0])) ^
           0xC90ACEFCE06DFE53LL) > 2L),
         &g_29);
  }
  return g_39[3][2];
}

static const int16_t func_5(int8_t p_6, int32_t p_7, int32_t p_8, int16_t p_9,
                            uint32_t p_10) {
  uint32_t l_20[1];
  uint32_t l_25 = 18446744073709551615UL;
  uint32_t *l_26 = &l_20[0];
  const int16_t l_27[3][1] = {{0x3659L}, {0x3659L}, {0x3659L}};
  int32_t *l_28 = &g_29;
  int i, j;
  for (i = 0; i < 1; i++)
    l_20[i] = 0x2E65251CL;
  (*l_28) =
      ((safe_div_func_int8_t_s_s(
           (safe_sub_func_uint32_t_u_u(
               ((*l_26) = (safe_mul_func_uint8_t_u_u(
                    (l_20[0] && p_8), (safe_add_func_uint64_t_u_u(
                                          (safe_mul_func_uint16_t_u_u(
                                              ((l_20[0] < g_13), g_13), g_13)),
                                          l_25))))),
               1L)),
           l_27[1][0])) &
       2L);
  return g_13;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_13;
  csmith_sink_ = g_29;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_39[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
