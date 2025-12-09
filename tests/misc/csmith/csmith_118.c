// Options:   --seed 200118 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_118.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2 = 0xF6AF1124L;
static int32_t *volatile g_26 = (void *)0;
static uint8_t g_27[3] = {3UL, 3UL, 3UL};
static int8_t g_30 = 0x47L;
static int64_t g_32 = 0xCAEABA4A2C6EB81FLL;
static uint32_t g_33[3] = {6UL, 6UL, 6UL};
static int32_t *volatile g_39 = (void *)0;
static int32_t g_41[3] = {(-4L), (-4L), (-4L)};

static float func_1(void);
static int8_t func_13(uint32_t p_14);

static float func_1(void) {
  const int32_t l_29 = 0xC328129EL;
  int32_t *l_38 = &g_2;
  int32_t **l_37 = &l_38;
  int32_t *l_40[1][1];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++)
      l_40[i][j] = &g_41[2];
  }
  for (g_2 = 0; (g_2 <= (-30)); --g_2) {
    int64_t l_28 = 0x1FB9A31C0A9C5A74LL;
    uint64_t *l_31 = (void *)0;
    uint64_t l_34 = 18446744073709551615UL;
    if (((g_33[2] =
              (g_32 = ((safe_div_func_uint64_t_u_u(
                           ((safe_mul_func_uint16_t_u_u(
                                ((((safe_div_func_uint16_t_u_u(
                                       g_2,
                                       (safe_sub_func_int8_t_s_s(
                                           func_13(((0x6BC3EC3D4E703026LL ^
                                                     ((18446744073709551615UL |
                                                       (-1L)) == g_2)) ==
                                                    0xE665969AL)),
                                           l_28)))) != l_29),
                                  g_27[2]) |
                                 g_30),
                                l_29)) > l_29),
                           (-4L))) < l_29))) < 0x0BA5FC0266D9918CLL)) {
      return l_34;
    } else {
      int32_t *l_36 = &g_2;
      int32_t **l_35 = &l_36;
      (*l_35) = (void *)0;
    }
  }
  g_41[2] |=
      ((((((g_2 ^ g_27[1]), &g_26) == l_37) ^ (*l_38)), 0x2CDFL), (**l_37));
  return (*l_38);
}

static int8_t func_13(uint32_t p_14) {
  uint16_t l_25 = 0xFA55L;
  g_27[2] |= (safe_div_func_uint8_t_u_u(
      ((safe_mod_func_uint32_t_u_u(
           (safe_mod_func_int64_t_s_s(
               (((safe_mod_func_int8_t_s_s(0x54L, g_2)) &
                 (safe_rshift_func_int8_t_s_u(
                     (((g_2, p_14) <= 0xA47CDEDFC3E8CE6FLL), l_25), p_14))) >
                p_14),
               0x33EE67684593F6A0LL)),
           l_25)),
       p_14),
      l_25));
  return p_14;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_27[i];
  }
  csmith_sink_ = g_30;
  csmith_sink_ = g_32;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_33[i];
  }
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_41[i];
  }
  platform_main_end(0, 0);
  return 0;
}
