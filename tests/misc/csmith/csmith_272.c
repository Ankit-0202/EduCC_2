// Options:   --seed 300272 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_272.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int16_t g_2 = 4L;
static int32_t g_25[1] = {0x587C7AB8L};
static int32_t ***volatile g_30 = (void *)0;
static int32_t g_35 = 0x62C4DF8EL;
static int32_t *g_41[1][1] = {{&g_25[0]}};
static int32_t **g_40[1][2] = {{&g_41[0][0], &g_41[0][0]}};
static int32_t g_46 = 0x05618D7CL;

static uint64_t func_1(void);
static uint64_t func_8(uint32_t p_9, int32_t p_10, int16_t p_11, uint16_t p_12,
                       uint16_t p_13);
static const uint64_t func_14(uint8_t p_15);

static uint64_t func_1(void) {
  int32_t *l_32 = (void *)0;
  int32_t *l_33 = (void *)0;
  int32_t *l_34 = &g_35;
  int32_t l_36 = 0x84B7B831L;
  int16_t l_43 = 0x30B1L;
  uint8_t l_44 = 0x83L;
  int32_t *l_45 = &g_46;
  (*l_45) &=
      ((((g_2 >= (safe_unary_minus_func_uint64_t_u(
                     ((safe_sub_func_uint32_t_u_u(
                          ((safe_sub_func_uint64_t_u_u(
                               func_8(g_2, ((*l_34) = (func_14(g_2) & g_2)),
                                      l_36, l_36, l_36),
                               18446744073709551612UL)),
                           0x5F93BE41L),
                          l_43)) <= 0xD3L)))),
         0UL) != l_44) > g_2);
  return (*l_45);
}

static uint64_t func_8(uint32_t p_9, int32_t p_10, int16_t p_11, uint16_t p_12,
                       uint16_t p_13) {
  int32_t *l_38 = &g_25[0];
  int32_t **l_37 = &l_38;
  int32_t ***l_39[3];
  uint64_t l_42 = 0x295A527720104353LL;
  int i;
  for (i = 0; i < 3; i++)
    l_39[i] = &l_37;
  g_40[0][0] = l_37;
  for (p_10 = 0; (p_10 >= 0); p_10 -= 1) {
    return g_25[0];
  }
  return l_42;
}

static const uint64_t func_14(uint8_t p_15) {
  uint32_t l_23 = 4294967291UL;
  if ((safe_rshift_func_int16_t_s_u(
          0x7084L,
          (((safe_add_func_int8_t_s_s((+(safe_add_func_int16_t_s_s(g_2, p_15))),
                                      g_2)) < p_15) ^
           g_2)))) {
    int32_t *l_24 = &g_25[0];
    (*l_24) = (g_2, l_23);
  } else {
    int32_t *l_29 = &g_25[0];
    int32_t **l_28[2][2];
    int32_t ***l_31 = &l_28[1][0];
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++)
        l_28[i][j] = &l_29;
    }
    for (l_23 = 22; (l_23 <= 16); l_23--) {
      if (l_23)
        break;
    }
    (*l_31) = l_28[1][0];
  }
  return p_15;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_25[i];
  }
  csmith_sink_ = g_35;
  csmith_sink_ = g_46;
  platform_main_end(0, 0);
  return 0;
}
