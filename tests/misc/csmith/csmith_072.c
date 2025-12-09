// Options:   --seed 100072 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_072.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint64_t g_11 = 0xC17E5C285CE96B77LL;
static const volatile int64_t g_12 = 7L;
static int32_t g_22[1][1] = {{(-8L)}};
static int32_t g_25 = (-3L);

static int64_t func_1(void);
static const int32_t func_2(uint16_t p_3, int16_t p_4);

static int64_t func_1(void) {
  uint8_t l_5[4];
  uint64_t *l_10 = &g_11;
  uint32_t l_13 = 1UL;
  int32_t *l_24 = &g_25;
  int i;
  for (i = 0; i < 4; i++)
    l_5[i] = 0xDFL;
  (*l_24) &= func_2(
      l_5[2],
      (safe_mod_func_int8_t_s_s(
          (((safe_mod_func_uint8_t_u_u(
                ((((*l_10) = (((l_5[2] == l_5[1]) & 1L) && 0x2A83L)), 0UL) |
                 g_12),
                l_13)) <= l_5[0]),
           0L),
          l_5[2])));
  return (*l_24);
}

static const int32_t func_2(uint16_t p_3, int16_t p_4) {
  uint32_t l_20[4] = {1UL, 1UL, 1UL, 1UL};
  uint64_t *l_21 = &g_11;
  int32_t l_23 = 3L;
  int i;
  l_23 = (safe_mod_func_int32_t_s_s(
      ((((safe_mod_func_uint8_t_u_u(
             (safe_div_func_int16_t_s_s(
                 (((((*l_21) = ((p_4 & g_11) == l_20[1])) >= g_12) || p_4),
                  p_3),
                 g_22[0][0])),
             1L)),
         (void *)0) != (void *)0),
       p_3),
      g_22[0][0]));
  return l_20[1];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_11;
  csmith_sink_ = g_12;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_22[i][j];
    }
  }
  csmith_sink_ = g_25;
  platform_main_end(0, 0);
  return 0;
}
